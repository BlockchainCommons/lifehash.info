#!/bin/zsh

set +e

pushd bc-lifehash/wasm
./build.sh
cp lib/lifehash* ../../src/lib/
popd
