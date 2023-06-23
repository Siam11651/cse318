#pragma once

#include <vector>
#include <cstdint>
#include "Player.hpp"
#include "Bowl.hpp"
#include "BigBowl.hpp"

class MancalaState
{
private:
    size_t heuristic;
    Player player;
    std::vector<Bowl *> bowls;
    std::vector<MancalaState *> moves;

public:
    MancalaState(const Player &player, const size_t &heurisitic1);
    Bowl *GetBowl(const size_t &bowl) const;
    void MakeMove(const size_t &index);
    size_t GetBestMove(const size_t &depth);
    int64_t GetHeuristic(const size_t &depth, int64_t &alpha, int64_t &beta); // alpha for black, beta for white
    int64_t Heurisitic1() const;
    ~MancalaState();
};