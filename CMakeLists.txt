# TODO: Licence information
#
# CMake settings for building & installing the NeuroML2 C++ API

cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0028 NEW) # Strict use of :: in target names
cmake_policy(SET CMP0042 NEW) # Mac OS @rpath
cmake_policy(SET CMP0048 NEW) # VERSION option to project()

project(NeuroML_API VERSION 0.1.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Developer settable options
############################

# Which schema to provide the API for
set(NeuroML_SCHEMA_PATH "${PROJECT_SOURCE_DIR}/src/schema/NeuroML_v2beta4.xsd"
    CACHE PATH
    "Path to the schema file to base the API on.")

get_filename_component(NeuroML_SCHEMA_ABSPATH "${NeuroML_SCHEMA_PATH}" REALPATH)
get_filename_component(NeuroML_SCHEMA_NAME "${NeuroML_SCHEMA_PATH}" NAME_WE)

# Default to shared libs
option(BUILD_SHARED_LIBS "Build NeuroML API as a shared library" ON)

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
    "Set the build type, e.g. Debug, Release, RelWithDebInfo")

# Build rules
#############

# We use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configure a header file to pass some of the CMake settings to the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/src/NeuroML_config.hxx.in"
    "${PROJECT_BINARY_DIR}/src/NeuroML_config.hxx"
    )

# Generate the main header for users of the API
configure_file(
    "${PROJECT_SOURCE_DIR}/src/neuroml.hxx.in"
    "${PROJECT_BINARY_DIR}/src/neuroml.hxx"
    )
 
# Add the binary tree to the search path for include files
# so that we will find generated sources
include_directories("${PROJECT_BINARY_DIR}/src")

# Xerces
find_package(XercesC REQUIRED)
list(APPEND NeuroML_INCLUDES "${XercesC_INCLUDE_DIRS}")

# Can we regenerate the schema wrapper?
find_package(XSD QUIET)
if (XSD_FOUND)
    list(APPEND NeuroML_INCLUDES "${XSD_INCLUDE_DIRS}")
    xsd_schema(NeuroML_SCHEMA_SRCS "${NeuroML_SCHEMA_PATH}"
               --options-file "${PROJECT_SOURCE_DIR}/src/schema/XsdOptions.txt")
else (XSD_FOUND)
    # Use pre-generated sources & CodeSynthesis headers shipped with the project
    set(XSD_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libxsd")
    list(APPEND NeuroML_INCLUDES "${XSD_INCLUDE_DIR}")
    set(NeuroML_SCHEMA_SRCS "${PROJECT_SOURCE_DIR}/src/schema/${NeuroML_SCHEMA_NAME}.cxx")
endif (XSD_FOUND)

# The main API library
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(${NeuroML_INCLUDES})
add_library(neuroml ${NeuroML_SCHEMA_SRCS} src/NeuroML_custom.cxx)
target_link_libraries(neuroml XercesC::XercesC)
# TODO: Set library version properties

# Install rules
###############

install(TARGETS neuroml
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)
install(DIRECTORY "${XSD_INCLUDE_DIR}/xsd" DESTINATION include/neuroml)
install(DIRECTORY "${PROJECT_BINARY_DIR}/src/"
        DESTINATION include/neuroml
        FILES_MATCHING PATTERN "*.hxx")
install(FILES src/NeuroML_custom.hxx DESTINATION include/neuroml)

# Testing
#########

# TODO: Split into a separate CMakeLists.txt in the test folder, and add more tests!
include(CTest)

add_executable(example test/example.cxx)
target_link_libraries(example neuroml)

add_test(ExampleRuns example "${PROJECT_SOURCE_DIR}/test/samples/Purk2M9s.nml" test_output.nml test_output.txt)

# Building documentation
########################

find_package(Doxygen)
if (DOXYGEN_FOUND)
    configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

# Building packages for distribution
####################################

include (InstallRequiredSystemLibraries)
#set (CPACK_RESOURCE_FILE_LICENSE  
#     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${NeuroML_API_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${NeuroML_API_VERSION_MINOR}")
include (CPack)
