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

# NOTE:
# The repo vendors a WPEFramework CMake package under install/usr/.
# That package's WPEFrameworkPluginsConfig.cmake lists ConfigGenerator as a REQUIRED
# dependency. In minimal host/CI environments we only need the plugin and L1 test
# libraries to configure and build; the actual ConfigGenerator tool is not invoked.
#
# This stub package unblocks `find_package(ConfigGenerator REQUIRED)` so that
# consumers can configure successfully.

set(ConfigGenerator_FOUND TRUE)

# Provide a conventional variable that downstream projects may check.
set(CONFIGGENERATOR_FOUND TRUE)

# No imported targets are defined intentionally.
