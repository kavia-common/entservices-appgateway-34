#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "WPEFrameworkDefinitions::WPEFrameworkDefinitions" for configuration "MinSizeRel"
set_property(TARGET WPEFrameworkDefinitions::WPEFrameworkDefinitions APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(WPEFrameworkDefinitions::WPEFrameworkDefinitions PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_MINSIZEREL "WPEFrameworkCore::WPEFrameworkCore"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/libWPEFrameworkDefinitions.so.4.4.1"
  IMPORTED_SONAME_MINSIZEREL "libWPEFrameworkDefinitions.so.4"
  )

list(APPEND _cmake_import_check_targets WPEFrameworkDefinitions::WPEFrameworkDefinitions )
list(APPEND _cmake_import_check_files_for_WPEFrameworkDefinitions::WPEFrameworkDefinitions "${_IMPORT_PREFIX}/lib/libWPEFrameworkDefinitions.so.4.4.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
