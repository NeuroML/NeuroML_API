# NeuroML API for C++

C++ API for NeuroML 2.

[![Build Status](https://travis-ci.org/NeuroML/NeuroML_API.svg?branch=master)](https://travis-ci.org/NeuroML/NeuroML_API)
[![GitHub](https://img.shields.io/github/license/NeuroML/NeuroML_API)](https://github.com/NeuroML/NeuroML_API/blob/master/License.txt)
![GitHub release (latest SemVer including pre-releases)](https://img.shields.io/github/v/release/NeuroML/NeuroML_API?include_prereleases)
![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/NeuroML/NeuroML_API)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/NeuroML/NeuroML_API)](https://github.com/NeuroML/NeuroML_API/pulls)
[![GitHub issues](https://img.shields.io/github/issues/NeuroML/NeuroML_API)](https://github.com/NeuroML/NeuroML_API/issues)
[![GitHub Org's stars](https://img.shields.io/github/stars/NeuroML?style=social)](https://github.com/NeuroML)
[![Twitter Follow](https://img.shields.io/twitter/follow/NeuroML?style=social)](https://twitter.com/NeuroML)


## Using the API

For more info on the generated C++ structure, see the [XSD user manual](https://www.codesynthesis.com/products/xsd/).
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

## Building the API

The NeuroML API is built using CMake (versions >= 3.14), and the process works
best with 'out of source' builds, where you build the API in a folder separate
from the source tree. Having cloned the repository, we therefore suggest you
create a separate 'NeuroML_API_build' folder adjacent to the source, change
into it, and then run the build configuration commands:

```
mkdir NeuroML_API_build
cd NeuroML_API_build
cmake ../NeuroML_API
```

You may then run

* `make` to build,
* `make doc` to build the HTML documentation using Doxygen (in a `docs`
  subfolder of your build folder; only available if Doxygen installed),
* `ctest` (or `make test`) to run tests,
* `sudo make install` to install on your system, or
* `cpack` to generate an installable package (see [cpack documentation](https://cmake.org/cmake/help/latest/manual/cpack.1.html)).

The default CMake options should be appropriate for most cases. The only
essential external dependencies are [Xerces
C++](http://xerces.apache.org/xerces-c/) and [CodeSynthesis
XSD](https://www.codesynthesis.com/products/xsd/).

On Ubuntu based systems, you can install Xerces and xsd from the standard
repositories using `apt`:

```
sudo apt-get install xsdcxx libxerces-c-dev
```

On Fedora and other RPM based distributions, you can install Xerces and xsd
from the standard repositories using `dnf` or `yum`:

```
sudo dnf install xsd xerces-c-devel
```

If you install xsd in a non-standard location, please set the `XSD_ROOT`
_environment_ variable to the root folder for the software (i.e. the folder
containing `bin` and `libxsd` folders).

You may wish to change the `CMAKE_INSTALL_PREFIX` to specify where the API
will be installed. The generated library will be placed in a `lib` subfolder,
and all necessary headers in an `include/neuroml` subfolder.

If you wish to regenerate the C++ bindings (because you have changed the
XML Schema or xsdcxx options) you will need to pass `REGENERATE_BINDINGS=ON` to
the CMake command:

```
cmake -DREGENERATE_BINDINGS=ON ...
```

You can also change the path to the schema file to use by setting the variable
`NeuroML_SCHEMA_PATH` in CMake.

Once the bindings have been regenerated, you can run `make copy_wrappers`
to copy the new versions back into the source tree, for committing to the
repository.
