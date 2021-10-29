#/bin/zsh

emcc \
    hello.cpp memzero.cpp sha256.cpp hex.cpp \
    -O3 \
    -o ../src/lib/hello.js \
    -s EXPORTED_FUNCTIONS='["_free","_malloc"]' \
    -s EXPORT_ES6=1 \
    -s MODULARIZE=1 \
    -s ENVIRONMENT='web' \
    -s NO_DISABLE_EXCEPTION_CATCHING \
    --post-js hello.post.js

cp hello.d.ts ../src/lib/
