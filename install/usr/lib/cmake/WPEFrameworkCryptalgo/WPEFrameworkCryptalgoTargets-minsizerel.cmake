#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "WPEFrameworkCryptalgo::WPEFrameworkCryptalgo" for configuration "MinSizeRel"
set_property(TARGET WPEFrameworkCryptalgo::WPEFrameworkCryptalgo APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(WPEFrameworkCryptalgo::WPEFrameworkCryptalgo PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_MINSIZEREL "WPEFrameworkCore::WPEFrameworkCore"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/libWPEFrameworkCryptalgo.so.1.0.0"
  IMPORTED_SONAME_MINSIZEREL "libWPEFrameworkCryptalgo.so.1"
  )

list(APPEND _cmake_import_check_targets WPEFrameworkCryptalgo::WPEFrameworkCryptalgo )
list(APPEND _cmake_import_check_files_for_WPEFrameworkCryptalgo::WPEFrameworkCryptalgo "${_IMPORT_PREFIX}/lib/libWPEFrameworkCryptalgo.so.1.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
