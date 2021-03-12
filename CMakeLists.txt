# Copyright 2017 University College London.
# See Licence.txt for details.
#
# CMake settings for building & installing the NeuroML2 C++ API

cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0022 NEW) # Link interfaces for export
cmake_policy(SET CMP0028 NEW) # Strict use of :: in target names
cmake_policy(SET CMP0042 NEW) # Mac OS @rpath
cmake_policy(SET CMP0048 NEW) # VERSION option to project()

# Note: the version number uses Semantic Versioning http://semver.org/
project(NeuroML_API
    VERSION 2.1.0
    DESCRIPTION "C++ API for NeuroML 2"
    HOMEPAGE_URL "https://github.com/NeuroML/NeuroML_API"
    )
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

# Developer settable options
############################

# Which schema to provide the API for
set(NeuroML_SCHEMA_PATH "${PROJECT_SOURCE_DIR}/src/schema/NeuroML_v2.1.xsd"
    CACHE PATH
    "Path to the schema file to base the API on.")

get_filename_component(NeuroML_SCHEMA_ABSPATH "${NeuroML_SCHEMA_PATH}" REALPATH)
get_filename_component(NeuroML_SCHEMA_NAME "${NeuroML_SCHEMA_ABSPATH}" NAME_WLE)

# Default to shared libs
option(BUILD_SHARED_LIBS "Build NeuroML API as a shared library" ON)

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
    "Set the build type, e.g. Debug, Release, RelWithDebInfo")

# Build rules
#############

# Some standard locations used below
set(IncludeLocation include/neuroml)
set(ConfigPackageLocation lib/cmake/${CMAKE_PROJECT_NAME})

# Configure header files to pass some of the CMake settings to the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/src/NeuroML_config.hxx.in"
    "${PROJECT_BINARY_DIR}/src/NeuroML_config.hxx"
    )
configure_file(
    "${PROJECT_SOURCE_DIR}/src/internal.hxx.in"
    "${PROJECT_BINARY_DIR}/src/internal.hxx"
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

# XSD
find_package(XSD REQUIRED)
list(APPEND NeuroML_INCLUDES "${XSD_INCLUDE_DIRS}")

# Regenerate bindings?
set (REGENERATE_BINDINGS OFF CACHE BOOL "Regenerate the C++ bindings. [default: OFF]")

# Yes: and use newly generated copy
if (REGENERATE_BINDINGS)
    file(GLOB _XSD_DEPS "src/schema/*.txt")
    xsd_schema(NeuroML_SCHEMA_SRCS "${NeuroML_SCHEMA_PATH}" "${_XSD_DEPS}"
               --options-file "${PROJECT_SOURCE_DIR}/src/schema/XsdOptions.txt")
    # A special target to copy newly generated wrappers back into the source tree for distribution.
    add_custom_target(copy_wrappers
                      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${NeuroML_SCHEMA_SRCS}
                              ${PROJECT_SOURCE_DIR}/src/schema
                      COMMENT "Copying new XSD wrappers to source tree"
                      VERBATIM)
else (REGENERATE_BINDINGS)
    # No: use pre-generated bindings
    # Will fail if bindings cannot be found in the src/schema directory
    list(APPEND NeuroML_INCLUDES "${PROJECT_SOURCE_DIR}/src/schema")
    set(NeuroML_SCHEMA_SRCS "${PROJECT_SOURCE_DIR}/src/schema/${NeuroML_SCHEMA_NAME}.cxx")
endif (REGENERATE_BINDINGS)

# The main API library
add_library(neuroml ${NeuroML_SCHEMA_SRCS} src/NeuroML_custom.cxx)
target_link_libraries(neuroml PUBLIC XercesC::XercesC)
target_include_directories(neuroml PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>" $<BUILD_INTERFACE:${NeuroML_INCLUDES}>
    $<INSTALL_INTERFACE:include/neuroml>)
set_target_properties(neuroml PROPERTIES VERSION ${NeuroML_API_VERSION})
# We use C++11 features. Ensure these propagate to users of the library.
target_compile_features(neuroml PUBLIC cxx_auto_type cxx_constexpr cxx_right_angle_brackets)

# Install rules
###############

install(TARGETS neuroml EXPORT NeuroML_API
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION ${IncludeLocation})
install(DIRECTORY "${XSD_INCLUDE_DIR}/xsd" DESTINATION ${IncludeLocation})
install(DIRECTORY "${PROJECT_BINARY_DIR}/src/"
        DESTINATION ${IncludeLocation}
        FILES_MATCHING PATTERN "*.hxx")
install(FILES src/NeuroML_custom.hxx "${NeuroML_SCHEMA_PATH}"
        DESTINATION ${IncludeLocation})

# Export package config so other CMake-using software can use NeuroML with just
# find_package(NeuroML_API REQUIRED).
install(FILES cmake/NeuroML_APIConfig.cmake DESTINATION ${ConfigPackageLocation})
install(EXPORT NeuroML_API DESTINATION ${ConfigPackageLocation}
        NAMESPACE NeuroML::
        EXPORT_LINK_INTERFACE_LIBRARIES)

# Testing
#########

# TODO: Split into a separate CMakeLists.txt in the test folder, and add more tests!
include(CTest)

add_executable(example test/example.cxx)
target_link_libraries(example neuroml)

add_test(ExampleRuns example "${PROJECT_SOURCE_DIR}/test/samples/Purk2M9s.nml" test_output.nml test_output.txt)

add_executable(create_net test/create_net.cxx)
target_link_libraries(create_net neuroml)

add_test(CreateNet create_net test_net.nml)

# Building documentation
########################

find_package(Doxygen)
if (DOXYGEN_FOUND)
    configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

# Building packages for distribution
####################################

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/Licence.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${NeuroML_API_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${NeuroML_API_VERSION_MINOR}")
include (CPack)
