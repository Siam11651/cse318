#pragma once

#include <cstdint>
#include <cstddef>

class HeuristicData
{
public:
    static uint16_t heuristic1, heuristic2;
    static int64_t w11, w12, w13, w14, w21, w22, w23, w24;
    static size_t depth1, depth2;
};