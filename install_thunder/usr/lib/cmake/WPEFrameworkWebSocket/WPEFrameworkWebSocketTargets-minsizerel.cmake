#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "WPEFrameworkWebSocket::WPEFrameworkWebSocket" for configuration "MinSizeRel"
set_property(TARGET WPEFrameworkWebSocket::WPEFrameworkWebSocket APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(WPEFrameworkWebSocket::WPEFrameworkWebSocket PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_MINSIZEREL "WPEFrameworkCore::WPEFrameworkCore;WPEFrameworkCryptalgo::WPEFrameworkCryptalgo"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/libWPEFrameworkWebSocket.so.1.0.0"
  IMPORTED_SONAME_MINSIZEREL "libWPEFrameworkWebSocket.so.1"
  )

list(APPEND _cmake_import_check_targets WPEFrameworkWebSocket::WPEFrameworkWebSocket )
list(APPEND _cmake_import_check_files_for_WPEFrameworkWebSocket::WPEFrameworkWebSocket "${_IMPORT_PREFIX}/lib/libWPEFrameworkWebSocket.so.1.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
