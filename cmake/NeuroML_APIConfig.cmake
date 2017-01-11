# TODO: Licence

# Package configuration file for the NeuroML2 C++ API (NeuroML_API package)
#
# Allows users of the API to use just find_package(NeuroML_API) and get
# everything to work nicely by linking the NeuroML::neuroml library.

include(CMakeFindDependencyMacro)
find_dependency(XercesC)

include("${CMAKE_CURRENT_LIST_DIR}/NeuroML_API.cmake")
