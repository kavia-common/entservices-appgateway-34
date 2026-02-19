# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2026
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

# Minimal ConfigGenerator package config.
#
# Purpose:
# - Step 23c configures Tests/L1Tests with CMAKE_PREFIX_PATH=<repo>/install/usr
# - WPEFrameworkPluginsConfig.cmake calls: find_package(ConfigGenerator REQUIRED)
# - The repo already ships a Find-module at:
#     <prefix>/include/WPEFramework/Modules/FindConfigGenerator.cmake
#   but it is not on CMAKE_MODULE_PATH during the standalone L1Tests configure.
#
# This package config bridges that gap by delegating to the existing find-module.

include(CMakeFindDependencyMacro)

# Make the shipped FindConfigGenerator.cmake discoverable.
set(_cg_module_dir "${CMAKE_CURRENT_LIST_DIR}/../../include/WPEFramework/Modules")
get_filename_component(_cg_module_dir "${_cg_module_dir}" ABSOLUTE)

if(EXISTS "${_cg_module_dir}/FindConfigGenerator.cmake")
    list(PREPEND CMAKE_MODULE_PATH "${_cg_module_dir}")
endif()

# Delegate to the find-module (provides write_config()).
find_package(ConfigGenerator REQUIRED MODULE)
