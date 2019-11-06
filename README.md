# NeuroML API for C++

C++ API for NeuroML 2

**Work in progress, but usable.** See https://github.com/NeuroML/NeuroML2/issues/102.

## Using the API

For more info on the generated C++ structure, see the [XSD user manual].
The sample programs in the test folder will also give you a reasonable
idea of how things work.

If you have a project built with CMake that depends on the API, you can
include it (and its own dependencies) very easily in your project. Once
the API has been installed (see below) simply add the following line to
your `CMakeLists.txt`:

```
find_package(NeuroML_API REQUIRED)
```

and then link against the `NeuroML::neuroml` library, e.g. by

```
add_executable(example example.cxx)
target_link_libraries(example NeuroML::neuroml)
```

If you installed the NeuroML_API in a non-standard location, you may need
to set the `CMAKE_PREFIX_PATH` CMake variable to that location in order to
find the package.

## Building the API yourself

The NeuroML API is built using CMake, and the process works best with
'out of source' builds, where you build the API in a folder separate
from the source tree. Having cloned the repository, we therefore suggest
you create a separate 'NeuroML_API_build' folder adjacent to the source,
change into it, and run

```
cmake ../NeuroML_API
```

to configure the build. You may then run

* `make` to build,
* `make doc` to build the HTML documentation using Doxygen (in a `docs`
  subfolder of your build folder; only available if Doxygen installed),
* `ctest` (or `make test`) to run tests,
* `sudo make install` to install on your system, or
* `cpack` to generate an installable package (see [cpack documentation]).

The default CMake options should be appropriate for most cases. The only
essential external dependency is [Xerces C++] which should be found
automatically if installed.

You may wish to change the `CMAKE_INSTALL_PREFIX` to specify where the API
will be installed. The generated library will be placed in a `lib` subfolder,
and all necessary headers in an `include/neuroml` subfolder.

If you wish to regenerate the C++ bindings (because you have changed the
XML Schema or xsdcxx options) you will need CodeSynthesis XSD installed on
your system and findable by CMake. The build will search standard install
locations, but you can also set the `XSD_ROOT` _environment_ variable to the
root folder for the software (i.e. the folder containing `bin` and `libxsd`
folders). You can also change the schema file to use by setting the variable
`NeuroML_SCHEMA_PATH` in ccmake.

Once the bindings have been regenerated, you can run `make copy_wrappers`
to copy the new versions back into the source tree, for committing to the
repository.

[XSD user manual]: http://www.codesynthesis.com/projects/xsd/documentation/cxx/tree/manual/
[cpack documentation]: https://cmake.org/cmake/help/v3.5/manual/cpack.1.html
[Xerces C++]: http://xerces.apache.org/xerces-c/

[![Build Status](https://travis-ci.org/NeuroML/NeuroML_API.svg?branch=master)](https://travis-ci.org/NeuroML/NeuroML_API)
