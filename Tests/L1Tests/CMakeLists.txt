# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2020 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.8)
set(PLUGIN_NAME L1TestsIN)
set(MODULE_NAME ${NAMESPACE}${PLUGIN_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(${NAMESPACE}Plugins REQUIRED)
find_package(Threads REQUIRED)

set(TEST_SRC
    tests/test_UtilsFile.cpp
    tests/test_AppGateway.cpp
)

set(TEST_LIB
    ${NAMESPACE}Plugins::${NAMESPACE}Plugins
)

# Include the code-under-test headers (Resolver, Module, helpers)
set(TEST_INC
    ../../helpers
    ../../AppGateway
)

#########################################################################################
# add_plugin_test_ex: Macro to add plugin tests, it will append to TEST_SRC, TEST_INC,
#                     and TEST_LIB. Args are positional.
#                     arg1: test file list as **string**
#                     arg2: include dir list as **string**
#                     arg3: plugin libs to link list as **string**
#########################################################################################
macro(add_plugin_test_ex plugin_opt plugin_test_sources_str plugin_includes_str plugin_libs_str)
    # Check if the plugin option is enabled
    if(${plugin_opt})
        message(STATUS "${plugin_opt}=ON")

        string(REPLACE ";" ";" srclist "${plugin_test_sources_str}")
        string(REPLACE ";" ";" inclist "${plugin_includes_str}")
        string(REPLACE ";" ";" liblist "${plugin_libs_str}")

        foreach(item IN LISTS srclist)
            # Add each test source file
            list(APPEND TEST_SRC ${item})
        endforeach()

        foreach(item IN LISTS inclist)
            # Add each include directory
            list(APPEND TEST_INC ${item})
        endforeach()

        foreach(item IN LISTS liblist)
            # Add each libraries to link
            list(APPEND TEST_LIB ${item})
        endforeach()
    else()
        message(STATUS "${plugin_opt}=OFF")
    endif()
endmacro()

# helper to add plugin test
macro(add_plugin_test plugin_name test_files)
    # Convert plugin name to uppercase for the option variable
    string(TOUPPER "${plugin_name}" plugin_option)
    set(plugin_opt "PLUGIN_${plugin_option}")

    add_plugin_test_ex(${plugin_opt} "${test_files}" "../../${plugin_name}" "${NAMESPACE}${plugin_name}")
endmacro()

# Shared library form (CI/testframework parity). This can still be used by an external runner.
add_library(${MODULE_NAME} SHARED ${TEST_SRC})

if(RDK_SERVICES_L1_TEST)
    target_link_options(${MODULE_NAME} PRIVATE "-Wl,-wrap,opendir")
endif()

target_link_directories(${MODULE_NAME}
    PUBLIC
        ${CMAKE_INSTALL_PREFIX}/lib
        ${CMAKE_INSTALL_PREFIX}/lib/wpeframework/plugins
)

target_link_libraries(${MODULE_NAME} ${TEST_LIB})

# IMPORTANT:
# Do NOT depend on external `entservices-testframework` include paths.
# Instead, use locally vendored mocks under Tests/mocks/.
target_include_directories(${MODULE_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        ${TEST_INC}
        ${CMAKE_CURRENT_SOURCE_DIR}/../mocks
        ${CMAKE_CURRENT_SOURCE_DIR}/../mocks/thunder
)

target_compile_definitions(${MODULE_NAME} PRIVATE UNIT_TEST)

install(TARGETS ${MODULE_NAME} DESTINATION lib)
write_config(PLUGINS ${PLUGIN_NAME})

# -----------------------------------------------------------------------------
# Standalone L1 test runner (no entservices-testframework / no RdkServicesL1Test)
# -----------------------------------------------------------------------------
#
# This executable enables `ctest` to run L1 tests in minimal environments.
# It links directly against gtest and the AppGateway plugin (code under test).
#
# NOTE:
# We intentionally compile the same test sources into this executable so the
# linker cannot drop them under --as-needed.
#
# This does not replace the shared-library-based flow used by the upstream
# testframework runner, it complements it.
find_library(GTEST_LIB NAMES gtest libgtest.a PATHS ${CMAKE_INSTALL_PREFIX}/lib)
if(NOT GTEST_LIB)
    message(FATAL_ERROR "gtest library not found under ${CMAKE_INSTALL_PREFIX}/lib (expected libgtest.a).")
endif()

add_executable(AppGatewayL1Tests
    tests/l1_main.cpp
    ${TEST_SRC}
)

target_include_directories(AppGatewayL1Tests
    PRIVATE
        ${TEST_INC}
        ${CMAKE_CURRENT_SOURCE_DIR}/../mocks
        ${CMAKE_CURRENT_SOURCE_DIR}/../mocks/thunder
)

# AppGateway plugin contains Resolver.cpp (symbols required by test_AppGateway.cpp).
target_link_libraries(AppGatewayL1Tests
    PRIVATE
        ${TEST_LIB}
        ${NAMESPACE}AppGateway
        Threads::Threads
        ${GTEST_LIB}
)

add_test(NAME AppGatewayL1Tests COMMAND AppGatewayL1Tests)
