#pragma once

#include <vector>
#include <cstdint>
#include "Player.hpp"
#include "Bowl.hpp"
#include "BigBowl.hpp"

class MancalaState
{
private:
    std::vector<Bowl *> bowls;
    std::vector<MancalaState *> moves;

public:
    MancalaState();
    Bowl *GetBowl(const size_t &bowl) const;
    void MakeMove(const Player &player, const size_t &index);
    size_t GetBestMove(const Player &player, const size_t &heuristic, const size_t &depth);
    int64_t GetHeuristic(const Player &player, const size_t &heuristic, const size_t &depth, int64_t &alpha, int64_t &beta); // alpha for black, beta for white
    int64_t heuristic1(const Player &player) const;
    void Print() const;
    ~MancalaState();
};