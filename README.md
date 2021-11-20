# LifeHash: Beautiful Visual Hashes

This page is a demonstration of running the [LifeHash](https://github.com/BlockchainCommons/bc-lifehash) visual hash algorithm in the web browser. It uses the reference C++ implementation compiled to [WebAssembly](https://webassembly.org/). The page itself can be accessed [here](http://lifehash.info).

## Displaying a Specific LifeHash

You can access this page's URL with a query parameter to populate the string input field with a specific value. Example:

[http://lifehash.info?s=RBH-AOZ](http://lifehash.info?s=RBH-AOZ)

If you want to generate a LifeHash directly from a SHA-256 digest, you can use this form:

[http://lifehash.info?f=70b0db749f1cb026282693b236048cefa3395fc580e91b7c62666b0bdc97c0e3](http://lifehash.info?f=70b0db749f1cb026282693b236048cefa3395fc580e91b7c62666b0bdc97c0e3)

## Installation

Prerequsites: Node, Emscripten

```
git clone https://github.com/BlockchainCommons/lifehash-web/
cd lifehash-web
git submodule update --init
npm install
./build_wasm.sh
npm run dev
```
