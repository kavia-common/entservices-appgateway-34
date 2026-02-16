###
# If not stated otherwise in this file or this component's LICENSE
# file the following copyright and licenses apply:
#
# Copyright 2023 RDK Management
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
###

cmake_minimum_required(VERSION 3.3)

project(entservices-appgateway LANGUAGES C CXX)

# All packages that did not deliver a CMake Find script (and some deprecated scripts that need to be removed)
# are located in the cmake directory. Include it in the search.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# Make repo-bundled WPEFramework/Thunder "tooling" find-modules available (e.g. FindConfigGenerator.cmake,
# FindProxyStubGenerator.cmake). Some environments install ThunderTools into install_thundertools/ to avoid
# permission issues; include both locations so `find_package(ProxyStubGenerator)` works.
# L1/L2 test CMakeLists call `write_config()` which is defined by FindConfigGenerator.cmake.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/install/tools/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/install_thundertools/tools/cmake")

# Host-shell / CI convenience:
# Prefer the repo-bundled WPEFramework CMake package when available (install/usr/lib/cmake/WPEFramework/...)
# This makes `find_package(WPEFramework)` work without requiring a system-wide Thunder/WPEFramework SDK.
#
# NOTE (host-shell/CI):
# Do NOT include(CTest) at top-level. In some restricted environments this triggers
# /usr/share/cmake-*/Modules/CTestTargets.cmake which uses configure_file() and can fail
# with "Operation not permitted" during configure.
#
# We enable testing only when L1/L2 tests are requested (see below).
if(EXISTS "${CMAKE_SOURCE_DIR}/install/usr/lib/cmake/WPEFramework/WPEFrameworkConfig.cmake")
    list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/install/usr")
endif()

find_package(WPEFramework)

# Product configuration dir
set(PRODUCT_CONFIG_DIR "/etc/entservices")

# Library installation section
# NAMESPACE is normally provided by WPEFrameworkConfig.cmake; keep a safe fallback for host builds.
if(DEFINED NAMESPACE)
    string(TOLOWER "${NAMESPACE}" STORAGE_DIRECTORY)
else()
    set(STORAGE_DIRECTORY "wpeframework")
endif()

# for writing pc and config files (provided by WPEFramework under .../common)
include(CmakeHelperFunctions)

# Provides the `write_config()` CMake function used by Tests/L1Tests and the testframework.
find_package(ConfigGenerator REQUIRED)

# ProxyStubGenerator is used by Thunder/WPEFramework build tooling to generate proxy/stub code.
# It is provided by ThunderTools and typically found via FindProxyStubGenerator.cmake.
find_package(ProxyStubGenerator REQUIRED)

if(RDK_SERVICE_L2_TEST)
    add_subdirectory(Tests/L2Tests)
endif()

option(DISABLE_SECURITY_TOKEN "Disable security token" OFF)

if(RDK_SERVICES_L1_TEST)
    enable_testing()
    add_subdirectory(Tests/L1Tests)
endif()

if(DISABLE_SECURITY_TOKEN)
    add_definitions(-DDISABLE_SECURITY_TOKEN)
endif()

if(PLUGIN_APPGATEWAY)
    add_subdirectory(AppGateway)
endif()

if(PLUGIN_APPNOTIFICATIONS)
    add_subdirectory(AppNotifications)
endif()

if(PLUGIN_APPGATEWAYCOMMON)
    add_subdirectory(AppGatewayCommon)
endif()


if(WPEFRAMEWORK_CREATE_IPKG_TARGETS)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEB_COMPONENT_INSTALL ON)
    set(CPACK_COMPONENTS_GROUPING IGNORE)

    set(CPACK_DEBIAN_PACKAGE_NAME "${WPEFRAMEWORK_PLUGINS_OPKG_NAME}")
    set(CPACK_DEBIAN_PACKAGE_VERSION "${WPEFRAMEWORK_PLUGINS_OPKG_VERSION}")
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${WPEFRAMEWORK_PLUGINS_OPKG_ARCHITECTURE}")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${WPEFRAMEWORK_PLUGINS_OPKG_MAINTAINER}")
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "${WPEFRAMEWORK_PLUGINS_OPKG_DESCRIPTION}")
    set(CPACK_PACKAGE_FILE_NAME "${WPEFRAMEWORK_PLUGINS_OPKG_FILE_NAME}")

    include(CPack)
endif()
