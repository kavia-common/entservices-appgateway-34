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

# -----------------------------------------------------------------------------
# L1Tests build products
#
# Historically this directory only built a shared object (L1TestsIN) that is
# loadable by Thunder. For coverage we additionally need a *runnable* test
# executable for AppGateway: AppGatewayL1Test.
# -----------------------------------------------------------------------------
set(PLUGIN_NAME L1TestsIN)
set(MODULE_NAME ${NAMESPACE}${PLUGIN_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# L1Tests-only build support
#
# When configuring only Tests/L1Tests (Step 23c), the repo provides the needed
# CMake package configs under:
#   <repo>/install/usr/lib/cmake/WPEFrameworkPlugins/WPEFrameworkPluginsConfig.cmake
#
# However this CMakeLists historically asks for "${NAMESPACE}Plugins", which
# resolves to "Plugins" if NAMESPACE is empty. In standalone test builds this
# can fail because the package name is actually WPEFrameworkPlugins.
#
# We bridge this by mapping "Plugins" to WPEFrameworkPlugins *when needed*.
# This keeps existing flows working while allowing the L1Tests-only configure to
# succeed with -DCMAKE_PREFIX_PATH=<repo>/install/usr.
# ---------------------------------------------------------------------------
if(NOT DEFINED NAMESPACE)
    set(NAMESPACE "")
endif()

if("${NAMESPACE}" STREQUAL "")
    # Prefer the canonical Thunder package name.
    find_package(WPEFrameworkPlugins REQUIRED)

    # Provide compatibility variables so existing references like
    #   ${NAMESPACE}Plugins::${NAMESPACE}Plugins
    # still work (they become Plugins::Plugins when NAMESPACE is empty).
    if(NOT TARGET Plugins::Plugins AND TARGET WPEFrameworkPlugins::WPEFrameworkPlugins)
        add_library(Plugins::Plugins ALIAS WPEFrameworkPlugins::WPEFrameworkPlugins)
    endif()
else()
    # For non-empty namespaces keep the original behavior.
    find_package(${NAMESPACE}Plugins REQUIRED)
endif()

# -----------------------------------------------------------------------------
# Shared-object (legacy) test module sources
#   NOTE: Per request, keep this limited to test_UtilsFile.cpp for now.
# -----------------------------------------------------------------------------
set(TEST_SRC
    tests/test_UtilsFile.cpp
)

set(TEST_LIB
    ${NAMESPACE}Plugins::${NAMESPACE}Plugins
)

set(TEST_INC ../../helpers)

# -----------------------------------------------------------------------------
# AppGateway-specific L1 tests (executable)
# -----------------------------------------------------------------------------
set(APPGATEWAY_L1TEST_SRC "")
set(APPGATEWAY_L1TEST_INC "")
set(APPGATEWAY_L1TEST_LIB "")

if(PLUGIN_APPGATEWAY)
    message(STATUS "AppGateway L1 tests: ENABLED (PLUGIN_APPGATEWAY=ON)")

    # Source(s)
    list(APPEND APPGATEWAY_L1TEST_SRC tests/test_AppGateway.cpp)

    # Includes needed by test_AppGateway.cpp (plus common test headers)
    list(APPEND APPGATEWAY_L1TEST_INC
        ../../helpers
        ../../AppGateway
        ../../AppGatewayCommon
    )

    # Libraries: link against the plugin collection to satisfy Thunder symbols used in tests.
    list(APPEND APPGATEWAY_L1TEST_LIB
        ${NAMESPACE}Plugins::${NAMESPACE}Plugins
    )
else()
    message(STATUS "AppGateway L1 tests: DISABLED (set -DPLUGIN_APPGATEWAY=ON to enable)")
endif()

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
# Legacy shared object
# -----------------------------------------------------------------------------
add_library(${MODULE_NAME} SHARED ${TEST_SRC})

if(RDK_SERVICES_L1_TEST)
    target_link_options(${MODULE_NAME} PRIVATE "-Wl,-wrap,opendir")
endif(RDK_SERVICES_L1_TEST)

target_link_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_INSTALL_PREFIX}/lib
    ${CMAKE_INSTALL_PREFIX}/lib/wpeframework/plugins
)

target_link_libraries(${MODULE_NAME} ${TEST_LIB})

target_include_directories(${MODULE_NAME}
    PUBLIC
    ${TEST_INC}
    ${CMAKE_INSTALL_PREFIX}/include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Tests/mocks
    ${CMAKE_SOURCE_DIR}/../Thunder/Source/plugins
)

target_compile_definitions(${MODULE_NAME} PRIVATE UNIT_TEST)

install(TARGETS ${MODULE_NAME} DESTINATION lib)
# Use the non-deprecated invocation form expected by FindConfigGenerator.cmake.
write_config(PLUGINS ${PLUGIN_NAME})

# -----------------------------------------------------------------------------
# AppGatewayL1Test executable (required by the workflow/script)
# -----------------------------------------------------------------------------
if(PLUGIN_APPGATEWAY)
    add_executable(AppGatewayL1Test ${APPGATEWAY_L1TEST_SRC})

    target_include_directories(AppGatewayL1Test
        PRIVATE
        ${APPGATEWAY_L1TEST_INC}
        ${CMAKE_INSTALL_PREFIX}/include
        ${CMAKE_SOURCE_DIR}/Tests/mocks
        ${CMAKE_SOURCE_DIR}/../Thunder/Source/plugins
    )

    target_link_directories(AppGatewayL1Test PRIVATE
        ${CMAKE_INSTALL_PREFIX}/lib
        ${CMAKE_INSTALL_PREFIX}/lib/wpeframework/plugins
    )

    target_link_libraries(AppGatewayL1Test PRIVATE
        ${APPGATEWAY_L1TEST_LIB}
        gmock
        gtest
        gtest_main
        pthread
    )

    target_compile_definitions(AppGatewayL1Test PRIVATE UNIT_TEST)

    # Install to the location the script checks first: install/usr/bin/AppGatewayL1Test
    install(TARGETS AppGatewayL1Test RUNTIME DESTINATION bin)
endif()
