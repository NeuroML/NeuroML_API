# NeuroML API for C++

C++ API for NeuroML 2

**Work in progress!** See https://github.com/NeuroML/NeuroML2/issues/102.

## Using the API

For more info on the generated C++ structure, see the
[XSD user manual](http://www.codesynthesis.com/projects/xsd/documentation/cxx/tree/manual/)

## Building the API yourself

The NeuroML API is built using CMake, and the process works best with
'out of source' builds, where you build the API in a folder separate
from the source tree. Having cloned the repository, we therefore suggest
you create a separate 'NeuroML_API_build' folder adjacent to the source,
change into it, and run

```
ccmake ../NeuroML_API
```

to configure the build. You may then run

* `make` to build,
* `make doc` to build the HTML documentation using Doxygen (in a `docs`
  subfolder of your build folder),
* `ctest` to run tests,
* `sudo make install` to install on your system, or
* `cpack` to generate an installable package.

The default CMake options should be appropriate for most cases, although
you may wish to change the `CMAKE_INSTALL_PREFIX` to specify where the API
will be installed. The generated library will be placed in a `lib` subfolder,
and all necessary headers in an `include/neuroml` subfolder.

If you wish to regenerate the C++ bindings (because you have changed the
XML Schema or xsdcxx options) you will need CodeSynthesis XSD installed on
your system and findable by CMake. The build will search standard install
locations, but you can also set the `XSD_ROOT` _environment_ variable to the
root folder for the software (i.e. the folder containing `bin` and `libxsd`
folders). You can also change the schema file to use by setting the variable
`NeuroML_SCHEMA_PATH` in ccmake.
