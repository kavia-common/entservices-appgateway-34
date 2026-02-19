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

project(entservices_appgateway_plugins LANGUAGES C CXX)

# Ensure a system-style default so plugin install ends up in:
#   /usr/lib/wpeframework/plugins
# unless the user/toolchain explicitly overrides CMAKE_INSTALL_PREFIX.
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "Default install prefix" FORCE)
endif()

include(GNUInstallDirs)

# If dependencies (Thunder/WPEFramework) are installed into the same prefix used for this build,
# make them discoverable without requiring callers to manually set CMAKE_PREFIX_PATH.
# This is particularly important for scripted CI flows that install Thunder into a prefix
# and then configure this repo with the same prefix.
list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")

find_package(WPEFramework REQUIRED)

# All packages that did not deliver a CMake Find script (and some deprecated scripts that need to be removed)
# are located in the cmake directory. Include it in the search.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# Ensure CmakeHelperFunctions (typically shipped with WPEFramework) is discoverable via include().
if(DEFINED WPEFramework_DIR)
    list(APPEND CMAKE_MODULE_PATH "${WPEFramework_DIR}")
endif()

# Product configuration dir
set(PRODUCT_CONFIG_DIR "/etc/entservices")

# WPEFramework uses NAMESPACE to form target names (e.g. WPEFrameworkAppGateway).
# If the package didn't define it for some reason, default to WPEFramework.
if(NOT DEFINED NAMESPACE)
    set(NAMESPACE "WPEFramework")
endif()

# Library installation section
string(TOLOWER ${NAMESPACE} STORAGE_DIRECTORY)

# Centralize plugin install directory. This is relative to CMAKE_INSTALL_PREFIX unless set to an absolute path.
# Default resolves to:
#   ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/wpeframework/plugins
set(WPEFRAMEWORK_PLUGIN_INSTALL_DIR
    "${CMAKE_INSTALL_LIBDIR}/${STORAGE_DIRECTORY}/plugins"
    CACHE PATH "Install directory for WPEFramework plugin shared libraries (relative to CMAKE_INSTALL_PREFIX unless absolute)."
)

# Build options (must be ON for AppGateway plugin .so to be built)
option(PLUGIN_APPGATEWAY "Build the AppGateway plugin shared library" OFF)
option(PLUGIN_APPNOTIFICATIONS "Build the AppNotifications plugin shared library" OFF)
option(PLUGIN_APPGATEWAYCOMMON "Build the AppGatewayCommon plugin shared library" OFF)

# for writing pc and config files
include(CmakeHelperFunctions)

if(RDK_SERVICE_L2_TEST)
    add_subdirectory(Tests/L2Tests)
endif()

option(DISABLE_SECURITY_TOKEN "Disable security token" OFF)

if(RDK_SERVICES_L1_TEST)
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
