#include "core/HitComponent.hpp"
#include <algorithm>
#include <array>
#include <functional>
#include <random>

HitComponent::HitComponent() : m_UUID{} {
    // Source: https://github.com/mariusbancila/stduuid?tab=readme-ov-file#using-the-library
    std::random_device rd;
    auto seed_data = std::array<int, 6>{};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::ranlux48_base generator(seq);

    uuids::basic_uuid_random_generator<std::ranlux48_base> gen(&generator);
    m_UUID = gen();
}