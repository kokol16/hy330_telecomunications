#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "gnuradio::gnuradio-constelation_mapping_module" for configuration "Release"
set_property(TARGET gnuradio::gnuradio-constelation_mapping_module APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(gnuradio::gnuradio-constelation_mapping_module PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libgnuradio-constelation_mapping_module.so.v1.0-compat-xxx-xunknown"
  IMPORTED_SONAME_RELEASE "libgnuradio-constelation_mapping_module.so.1.0.0git"
  )

list(APPEND _IMPORT_CHECK_TARGETS gnuradio::gnuradio-constelation_mapping_module )
list(APPEND _IMPORT_CHECK_FILES_FOR_gnuradio::gnuradio-constelation_mapping_module "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libgnuradio-constelation_mapping_module.so.v1.0-compat-xxx-xunknown" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
