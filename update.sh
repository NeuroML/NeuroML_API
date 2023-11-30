#!/bin/bash

# Copyright 2023 NeuroML contributors
# Author: NeuroML contributors
# File : update.sh
#
# Script to regenerate and update the API for a new version of the NeuroML schema
#
NEUROML_VERSION="2.3"

echo "Please ensure that you have ctest and xsd installed. See readme for details."
echo "For building documentation doxygen is required also."

rm -rf build && \
    mkdir build && \
    pushd build && \
    cmake -DREGENERATE_BINDINGS=ON ../ && \
    make && \
    pushd src && sed -i -e 's/:param \(.*\):/@param \1/' -e '/:type/ d' -e '/\\n/ d' NeuroML_v${NEUROML_VERSION}.hxx && popd && \
    make doc && make copy_wrappers &&
    make test && popd && \
    echo "All done"
