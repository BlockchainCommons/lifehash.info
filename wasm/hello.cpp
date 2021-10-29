#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <emscripten.h>
#include <algorithm>
#include "sha256.hpp"
#include "hex.hpp"

extern "C" {

EMSCRIPTEN_KEEPALIVE
int int_sqrt(int x) {
    return sqrt(x);
}

EMSCRIPTEN_KEEPALIVE
int add(int a, int b) {
    return a + b;
}

EMSCRIPTEN_KEEPALIVE
void print_u8(uint8_t n) {
    printf("0x%02hhx\n", n);
}

EMSCRIPTEN_KEEPALIVE
uint8_t increment_u8(uint8_t n) {
    return n + 1;
}

EMSCRIPTEN_KEEPALIVE
void print_u16(uint16_t n) {
    printf("0x%04hx\n", n);
}

EMSCRIPTEN_KEEPALIVE
void print_u8_array(uint8_t* bytes, size_t len) {
    for(auto i = 0; i < len; i++) {
        printf("0x%02hhx\n", bytes[i]);
    }
}

EMSCRIPTEN_KEEPALIVE
char* return_string() {
    auto s = "Hello, WebAssembly!";
    char* c = (char*)malloc(strlen(s)+1);
    strcpy(c, s);
    return c;
}

EMSCRIPTEN_KEEPALIVE
void reverse(int32_t* p, size_t len) {
    for(int i = 0; i < len / 2; i++) {
        std::swap(p[i], p[len - i - 1]);
    }
}

EMSCRIPTEN_KEEPALIVE
void sha256(const uint8_t* data, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH]) {
    Hello::sha256_Raw(data, len, digest);
}

EMSCRIPTEN_KEEPALIVE
char* data_to_hex(const uint8_t* data, size_t len) {
    auto d = Hello::Data(data, data + len);
    auto hex = Hello::data_to_hex(d);
    auto str = (char*)malloc(hex.length() + 1);
    strcpy(str, hex.c_str());
    return str;
}

EMSCRIPTEN_KEEPALIVE
bool hex_to_data(const uint8_t* utf8, size_t utf8_len, uint8_t** out, size_t* out_len) {
    try {
        auto hex = std::string(utf8, utf8 + utf8_len);
        auto data = Hello::hex_to_data(hex);
        auto buf = (uint8_t*)malloc(data.size());
        memcpy(buf, &data[0], data.size());
        *out = buf;
        *out_len = data.size();
        return true;
    } catch(...) {
        return false;
    }
}

} // extern "C"
