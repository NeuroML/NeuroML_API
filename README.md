# NeuroML API for C++

C++ API for NeuroML 2

**Work in progress!** See https://github.com/NeuroML/NeuroML2/issues/102.

To generate the C++ classes from the schema, use

```
xsd cxx-tree --options-file XsdOptions.txt NeuroML_v2beta4.xsd
```

or just run `make` to generate classes and the simple test program,
having checked the path definitions match your system.

For more info on the generated C++ structure, see the
[XSD user manual](http://www.codesynthesis.com/projects/xsd/documentation/cxx/tree/manual/)
