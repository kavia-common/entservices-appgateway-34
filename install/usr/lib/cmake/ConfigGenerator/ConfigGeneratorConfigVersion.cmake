# Minimal version file for ConfigGenerator.
#
# The underlying "package" is a set of CMake macros + python tooling.
# We accept any requested version.

set(PACKAGE_VERSION "0.0.0")

if(PACKAGE_FIND_VERSION)
    set(PACKAGE_VERSION_COMPATIBLE TRUE)
    set(PACKAGE_VERSION_EXACT FALSE)
else()
    set(PACKAGE_VERSION_COMPATIBLE TRUE)
    set(PACKAGE_VERSION_EXACT TRUE)
endif()
