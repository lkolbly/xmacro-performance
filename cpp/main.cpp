#include <benchmark/benchmark.h>
#include <stdint.h>
#include <string>
#include <iostream>

#define productList \
  product("Product Flawnberry-5629", 0x5d2b) \
  product("Product Flawnberry-3187", 0x4794) \
  product("Product Flawnberry-3678", 0xc091) \
  product("Product Flawnberry-4953", 0x640e) \
  product("Product Flawnberry-4153", 0xde21) \
  product("Product Flawnberry-7573", 0x548b) \
  product("Product Flawnberry-5436", 0x7795) \
  product("Product Flawnberry-5758", 0x25e6) \
  product("Product Flawnberry-9495", 0x6b6e) \
  product("Product Flawnberry-5002", 0xb742) \
  product("Product Flawnberry-2731", 0xad46) \
  product("Product Flawnberry-6701", 0x79b0) \
  product("Product Flawnberry-8346", 0x88bb) \
  product("Product Flawnberry-1315", 0x5c32) \
  product("Product Flawnberry-9331", 0xc939) \
  product("Product Flawnberry-8280", 0x73d2) \
  product("Product Flawnberry-1179", 0xbd7c) \
  product("Product Flawnberry-8942", 0x23bf) \
  product("Product Flawnberry-8981", 0xdd36) \
  product("Product Flawnberry-2810", 0xfa7a) \
  product("Product Flawnberry-8880", 0xbea4) \
  product("Product Flawnberry-4074", 0x8fb7) \
  product("Product Flawnberry-1733", 0xdadd) \
  product("Product Flawnberry-5748", 0xd290) \
  product("Product Flawnberry-1233", 0xf569) \
  product("Product Flawnberry-3638", 0xa3f0) \
  product("Product Flawnberry-4639", 0x53e4) \
  product("Product Flawnberry-7291", 0xcfd1) \
  product("Product Flawnberry-4267", 0x24e1) \
  product("Product Flawnberry-8307", 0xff10) \
  product("Product Flawnberry-2361", 0x1d46) \
  product("Product Flawnberry-6727", 0x34d6) \
  product("Product Flawnberry-4286", 0x8626) \
  product("Product Flawnberry-5212", 0xdfa2) \
  product("Product Flawnberry-2850", 0x0854) \
  product("Product Flawnberry-6239", 0x5a8d) \
  product("Product Flawnberry-4872", 0xda79)

const std::vector<std::tuple<std::string, uint16_t>> PRODUCTS = {
    #define product(name, id) \
        {name, id},
    productList
    #undef product
};

std::vector<uint16_t> enumerate_codes() {
    std::vector<uint16_t> codes;
    #define product(name, id) \
        codes.push_back(id);
    productList
    #undef product
    return codes;
}

bool beautifyModelName(std::string &model, uint16_t productCode) {
    #define product(productName, productID)    \
        case productID:                        \
            model = productName;               \
            return true;

    switch (productCode) {
        productList
    }

    #undef product

    return false;
}

static void BM_beautify(benchmark::State& state) {
    auto legal_codes = enumerate_codes();
    std::vector<uint16_t> codes;
    for (size_t i=0; i<10000; i++) {
        codes.push_back(legal_codes[rand() % legal_codes.size()]);
    }
    for (auto _ : state) {
        for (auto code : codes) {
            std::string result;
            beautifyModelName(result, code);
        }
    }
}
BENCHMARK(BM_beautify);

bool beautifyModelFromVec(std::string &model, uint16_t productCode) {
    for (auto& product : PRODUCTS) {
        if (std::get<1>(product) == productCode) {
            model = std::get<0>(product);
            return true;
        }
    }
    return false;
}

static void BM_beautify_from_vec(benchmark::State& state) {
    auto legal_codes = enumerate_codes();
    std::vector<uint16_t> codes;
    for (size_t i=0; i<10000; i++) {
        codes.push_back(legal_codes[rand() % legal_codes.size()]);
    }
    for (auto _ : state) {
        for (auto code : codes) {
            std::string result;
            beautifyModelFromVec(result, code);
        }
    }
}
BENCHMARK(BM_beautify_from_vec);

bool beautifyModelFromVecByRef(const char **model, uint16_t productCode) {
    for (auto& product : PRODUCTS) {
        if (std::get<1>(product) == productCode) {
            *model = std::get<0>(product).c_str();
            return true;
        }
    }
    return false;
}

static void BM_beautify_from_vec_by_ref(benchmark::State& state) {
    auto legal_codes = enumerate_codes();
    std::vector<uint16_t> codes;
    for (size_t i=0; i<10000; i++) {
        codes.push_back(legal_codes[rand() % legal_codes.size()]);
    }
    for (auto _ : state) {
        for (auto code : codes) {
            const char *result;
            beautifyModelFromVecByRef(&result, code);
        }
    }
}
BENCHMARK(BM_beautify_from_vec_by_ref);

BENCHMARK_MAIN();
