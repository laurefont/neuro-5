find_package (Doxygen)
if (DOXYGEN_FOUND)
    set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM)
else()
    MESSAGE(FATAL_ERROR "Doxygen not found. Re-run cmake with -Ddoc=OFF to disable generation of documentation.")
endif()
