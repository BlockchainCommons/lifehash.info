# LifeHash: Beautiful Visual Hashes

This page is a demonstration of running the [LifeHash](https://github.com/BlockchainCommons/bc-lifehash) visual hash algorithm in the web browser. It uses the reference C++ implementation compiled to [WebAssembly](https://webassembly.org/). The page itself can be accessed [here](https://blockchaincommons.github.io/lifehash-web/).

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
