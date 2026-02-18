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

set (TEST_SRC
    tests/test_AppGateway.cpp
)

set (TEST_LIB
    ${NAMESPACE}Plugins::${NAMESPACE}Plugins
)

set (TEST_INC ../../helpers)

#########################################################################################
# add_plugin_test_ex: Macro to add plugin tests, it will append to TEST_SRC, TEST_INC,
#                     and TEST_LIB. Args are positional.
#                     arg1: test file list as **string**
#                     arg2: include dir list as **string**
#                     arg3: plugin libs to link list as **string**
#
# sample invocation : 
#    add_plugin_test_ex(PLUGIN_NAME
#                       "test/file1.cpp;test/file2.cpp"
#                       "../../inc_dir1;../../inc_dir2"
#                       "${NAMESPACE}PluginName;${NAMESPACE}PluginNameImplementation")
# ----------------------------------------- OR ------------------------------------------
# list(APPEND PLUGIN_NAME_SRC test/file1.cpp)
# list(APPEND PLUGIN_NAME_SRC test/file2.cpp)
#
# list(APPEND PLUGIN_NAME_INC ../../inc_dir1)
# list(APPEND PLUGIN_NAME_INC ../../inc_dir2)
#
# list(APPEND PLUGIN_NAME_LIB ${NAMESPACE}PluginName)
# list(APPEND PLUGIN_NAME_LIB ${NAMESPACE}PluginNameImplementation)
#
#    add_plugin_test_ex(PLUGIN_NAME
#                       "${PLUGIN_NAME_SRC}"
#                       "${PLUGIN_NAME_INC}"
#                       "${PLUGIN_NAME_LIB}")
#
# NOTE: Alternatively test can choose to update `TEST_SRC`, `TEST_INC` & `TEST_LIB`
#       directly (like in the case of Miracast)
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

# -----------------------------------------------------------------------------
# Existing behavior: build L1 tests as a shared library.
# -----------------------------------------------------------------------------
add_library(${MODULE_NAME} SHARED ${TEST_SRC})

if (RDK_SERVICES_L1_TEST)
    target_link_options(${MODULE_NAME} PRIVATE "-Wl,-wrap,opendir")
endif (RDK_SERVICES_L1_TEST)

include_directories(${TEST_INC})

# Ensure gtest/gmock headers are discoverable when googletest is installed into the
# workflow prefix (see build log: install/usr/include/{gtest,gmock} exists but is
# not in the compile command).
#
# Note: We intentionally keep this minimal (header discovery only) because this
# repo's tests primarily use header-only gmock macros and the environment may
# already provide the appropriate gtest/gmock libs via toolchain or other linkage.
target_include_directories(${MODULE_NAME}
        PRIVATE
        ${CMAKE_INSTALL_PREFIX}/include
)

target_link_directories(${MODULE_NAME} PUBLIC ${CMAKE_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib/wpeframework/plugins)

target_link_libraries(${MODULE_NAME} ${TEST_LIB})

target_include_directories(${MODULE_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        ${CMAKE_SOURCE_DIR}/Tests/mocks
        ${CMAKE_SOURCE_DIR}/../Thunder/Source/plugins
        # Allow tests to include AppGateway headers like "AppGatewayImplementation.h" and "Resolver.h"
        ${CMAKE_SOURCE_DIR}/AppGateway
        )

# Compile tests (and local mocks) against Thunder R4 interfaces.
target_compile_definitions(${MODULE_NAME} PRIVATE UNIT_TEST USE_THUNDER_R4)

install(TARGETS ${MODULE_NAME} DESTINATION lib)

# ConfigGenerator requires a matching template file (<plugin>.conf.in). In this repo,
# Tests/L1Tests/L1TestsIN.conf.in is missing, which breaks configure when
# RDK_SERVICES_L1_TEST=ON (coverage workflow). Since coverage only needs the
# AppGatewayL1Test runner binary, make config generation best-effort.
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN_NAME}.conf.in")
    write_config(${PLUGIN_NAME})
else()
    message(WARNING
        "Skipping write_config(${PLUGIN_NAME}): missing template "
        "'${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN_NAME}.conf.in'. "
        "This does not affect building/running AppGatewayL1Test for coverage.")
endif()

# -----------------------------------------------------------------------------
# New behavior (guarded): also build a runnable AppGateway-only L1 test executable.
#
# IMPORTANT:
#   Only build/install this binary when RDK_SERVICES_L1_TEST=ON, because the
#   coverage workflow enables that option and expects the binary to exist in
#   ${CMAKE_INSTALL_PREFIX}/bin (install/usr/bin).
# -----------------------------------------------------------------------------
if (RDK_SERVICES_L1_TEST)
    set(APPGATEWAY_L1_TEST_EXE AppGatewayL1Test)

    add_executable(${APPGATEWAY_L1_TEST_EXE} ${TEST_SRC})

    # Mirror compile definitions/includes/linking from the shared library target.
    # Compile tests (and local mocks) against Thunder R4 interfaces.
    target_compile_definitions(${APPGATEWAY_L1_TEST_EXE} PRIVATE UNIT_TEST USE_THUNDER_R4)

    target_link_options(${APPGATEWAY_L1_TEST_EXE} PRIVATE "-Wl,-wrap,opendir")

    target_include_directories(${APPGATEWAY_L1_TEST_EXE}
            PRIVATE
            ${TEST_INC}
            ${CMAKE_SOURCE_DIR}/Tests/mocks
            ${CMAKE_SOURCE_DIR}/../Thunder/Source/plugins
            # Allow tests to include AppGateway headers like "AppGatewayImplementation.h" and "Resolver.h"
            ${CMAKE_SOURCE_DIR}/AppGateway
            # googletest install prefix include dir (gtest/gmock headers)
            ${CMAKE_INSTALL_PREFIX}/include
            )

    target_link_directories(${APPGATEWAY_L1_TEST_EXE} PRIVATE
            ${CMAKE_INSTALL_PREFIX}/lib
            ${CMAKE_INSTALL_PREFIX}/lib/wpeframework/plugins
            )

    # Explicitly link gtest/gmock and the AppGateway plugin implementation.
    # The build log shows gtest/gmock headers are found under ${CMAKE_INSTALL_PREFIX}/include,
    # but the link step is missing the corresponding libs.
    find_package(GTest REQUIRED)

    target_link_libraries(${APPGATEWAY_L1_TEST_EXE} PRIVATE
            ${TEST_LIB}
            # Provides WPEFramework::Plugin::AppGatewayImplementation symbols
            ${NAMESPACE}AppGateway
            # Provides testing::Test, gmock expectation machinery, and main()
            GTest::gtest
            GTest::gmock
            GTest::gtest_main
            )

    # Install to ${CMAKE_INSTALL_PREFIX}/bin => install/usr/bin in the workflow.
    install(TARGETS ${APPGATEWAY_L1_TEST_EXE} RUNTIME DESTINATION bin)
endif()


