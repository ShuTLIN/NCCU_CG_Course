#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libglew_static" for configuration "RelWithDebInfo"
set_property(TARGET libglew_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(libglew_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C;RC"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/glew.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS libglew_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_libglew_static "${_IMPORT_PREFIX}/lib/glew.lib" )

# Import target "libglew_shared" for configuration "RelWithDebInfo"
set_property(TARGET libglew_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(libglew_shared PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/glew-shared.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS libglew_shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_libglew_shared "${_IMPORT_PREFIX}/lib/glew-shared.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
