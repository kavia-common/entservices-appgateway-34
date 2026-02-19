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

# -----------------------------------------------------------------------------
# Helper: link a test target against AppGateway plugin.
#
# Preferred behavior:
#   - Link against the in-build AppGateway plugin target if it is part of the
#     current build (avoids configure-time dependency on an already-installed .so).
#
# Fallback behavior:
#   - Link against an already-installed plugin .so (system or install prefix).
# -----------------------------------------------------------------------------
function(link_against_appgateway_plugin TARGET_NAME)
    # If the plugin is part of this build, link directly to the target.
    # This guarantees correct build order and avoids undefined references.
    if (TARGET ${NAMESPACE}AppGateway)
        message(STATUS "Linking ${TARGET_NAME} against AppGateway plugin target: ${NAMESPACE}AppGateway")
        target_link_libraries(${TARGET_NAME} PRIVATE ${NAMESPACE}AppGateway)
        return()
    endif()

    # Otherwise, attempt to link against an installed .so.
    set(APPGATEWAY_PLUGIN_DIR_SYSTEM "/usr/lib/wpeframework/plugins")

    # Prefer the plugin directory configured by the top-level build.
    # WPEFRAMEWORK_PLUGIN_INSTALL_DIR is relative to CMAKE_INSTALL_PREFIX unless absolute.
    if (DEFINED WPEFRAMEWORK_PLUGIN_INSTALL_DIR)
        if (IS_ABSOLUTE "${WPEFRAMEWORK_PLUGIN_INSTALL_DIR}")
            set(APPGATEWAY_PLUGIN_DIR_PREFIX "${WPEFRAMEWORK_PLUGIN_INSTALL_DIR}")
        else()
            set(APPGATEWAY_PLUGIN_DIR_PREFIX "${CMAKE_INSTALL_PREFIX}/${WPEFRAMEWORK_PLUGIN_INSTALL_DIR}")
        endif()
    else()
        # Fallback for older configurations.
        set(APPGATEWAY_PLUGIN_DIR_PREFIX "${CMAKE_INSTALL_PREFIX}/lib/wpeframework/plugins")
    endif()

    file(GLOB APPGATEWAY_PLUGIN_SO_SYSTEM
        "${APPGATEWAY_PLUGIN_DIR_SYSTEM}/*AppGateway*.so"
        "${APPGATEWAY_PLUGIN_DIR_SYSTEM}/*AppGateway*.so.*"
    )
    file(GLOB APPGATEWAY_PLUGIN_SO_PREFIX
        "${APPGATEWAY_PLUGIN_DIR_PREFIX}/*AppGateway*.so"
        "${APPGATEWAY_PLUGIN_DIR_PREFIX}/*AppGateway*.so.*"
    )

    # Make selection deterministic.
    if (APPGATEWAY_PLUGIN_SO_SYSTEM)
        list(SORT APPGATEWAY_PLUGIN_SO_SYSTEM)
        list(GET APPGATEWAY_PLUGIN_SO_SYSTEM 0 APPGATEWAY_PLUGIN_SO)
        message(STATUS "Linking ${TARGET_NAME} against installed AppGateway plugin (system): ${APPGATEWAY_PLUGIN_SO}")
        target_link_libraries(${TARGET_NAME} PRIVATE "${APPGATEWAY_PLUGIN_SO}")
    elseif (APPGATEWAY_PLUGIN_SO_PREFIX)
        list(SORT APPGATEWAY_PLUGIN_SO_PREFIX)
        list(GET APPGATEWAY_PLUGIN_SO_PREFIX 0 APPGATEWAY_PLUGIN_SO)
        message(STATUS "Linking ${TARGET_NAME} against installed AppGateway plugin (prefix): ${APPGATEWAY_PLUGIN_SO}")
        target_link_libraries(${TARGET_NAME} PRIVATE "${APPGATEWAY_PLUGIN_SO}")
    else()
        message(FATAL_ERROR
            "AppGateway plugin shared library not found.\n"
            "Searched for '*AppGateway*.so' in:\n"
            "  - ${APPGATEWAY_PLUGIN_DIR_SYSTEM}\n"
            "  - ${APPGATEWAY_PLUGIN_DIR_PREFIX}\n"
            "Ensure configure uses -DPLUGIN_APPGATEWAY=ON and the plugin has been built+installed.")
    endif()
endfunction()

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

# When RDK_SERVICES_L1_TEST is enabled, test objects reference AppGateway symbols.
# Link against the AppGateway plugin to resolve them.
if (RDK_SERVICES_L1_TEST)
    link_against_appgateway_plugin(${MODULE_NAME})
endif()

target_include_directories(${MODULE_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        ${CMAKE_SOURCE_DIR}/Tests/mocks

        # Thunder/WPEFramework headers:
        # - In this repo Thunder is vendored under ${CMAKE_SOURCE_DIR}/Thunder (NOT ../Thunder).
        # - The build uses includes like <plugins/plugins.h>, so include root must be ".../Source".
        # - Additionally, the installed headers are available as:
        #     ${CMAKE_INSTALL_PREFIX}/include/WPEFramework/plugins/plugins.h
        #   so we add that include root as well.
        ${CMAKE_SOURCE_DIR}/Thunder/Source
        ${CMAKE_SOURCE_DIR}/Thunder/Source/plugins
        ${CMAKE_INSTALL_PREFIX}/include/WPEFramework

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
# Build a runnable AppGateway-only L1 test executable.
#
# IMPORTANT:
#   Only build/install this binary when RDK_SERVICES_L1_TEST=ON, because the
#   script-driven workflow enables that option and expects the binary to exist in
#   ${CMAKE_INSTALL_PREFIX}/bin (install/usr/bin).
#
# Key change:
#   Do NOT compile any AppGateway implementation sources (incl. Module.cpp) into
#   this test binary. Instead, link against the AppGateway plugin shared library
#   produced/installed by the build/install script to avoid duplicate Thunder
#   module metadata/symbols.
# -----------------------------------------------------------------------------
if (RDK_SERVICES_L1_TEST)
    set(APPGATEWAY_L1_TEST_EXE AppGatewayL1Test)

    add_executable(${APPGATEWAY_L1_TEST_EXE}
            ${TEST_SRC}
            )

    # Tests/mocks expect Thunder R4 interfaces.
    target_compile_definitions(${APPGATEWAY_L1_TEST_EXE} PRIVATE UNIT_TEST USE_THUNDER_R4)

    target_link_options(${APPGATEWAY_L1_TEST_EXE} PRIVATE "-Wl,-wrap,opendir")

    target_include_directories(${APPGATEWAY_L1_TEST_EXE}
            PRIVATE
            ${TEST_INC}
            ${CMAKE_SOURCE_DIR}/Tests/mocks

            # Thunder/WPEFramework headers (repo-local + installed):
            ${CMAKE_SOURCE_DIR}/Thunder/Source
            ${CMAKE_SOURCE_DIR}/Thunder/Source/plugins
            ${CMAKE_INSTALL_PREFIX}/include/WPEFramework

            # Allow tests to include AppGateway headers like "AppGatewayImplementation.h" and "Resolver.h"
            ${CMAKE_SOURCE_DIR}/AppGateway

            # googletest install prefix include dir (gtest/gmock headers)
            ${CMAKE_INSTALL_PREFIX}/include
            )

    target_link_directories(${APPGATEWAY_L1_TEST_EXE} PRIVATE
            ${CMAKE_INSTALL_PREFIX}/lib
            ${CMAKE_INSTALL_PREFIX}/lib/wpeframework/plugins
            )

    find_package(GTest REQUIRED)

    # Link against AppGateway plugin (prefer in-build target; fallback to installed .so).
    link_against_appgateway_plugin(${APPGATEWAY_L1_TEST_EXE})

    # Keep existing Thunder plugin host linkage.
    target_link_libraries(${APPGATEWAY_L1_TEST_EXE} PRIVATE
            ${TEST_LIB}

            # Keep gtest/gmock linkage intact.
            GTest::gtest
            GTest::gmock
            GTest::gtest_main
            )

    # Install to ${CMAKE_INSTALL_PREFIX}/bin => install/usr/bin in the workflow.
    install(TARGETS ${APPGATEWAY_L1_TEST_EXE} RUNTIME DESTINATION bin)
endif()


