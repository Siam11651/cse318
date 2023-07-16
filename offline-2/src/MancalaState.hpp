#pragma once

#include <vector>
#include <cstdint>
#include "Player.hpp"
#include "WinnerPlayer.hpp"
#include "Bowl.hpp"
#include "BigBowl.hpp"

class MancalaState
{
private:
    std::vector<Bowl *> bowls;
    size_t additionalMoveCount;
    size_t caputured;

public:
    MancalaState();
    MancalaState(const MancalaState &other);
    Bowl *GetBowl(const size_t &bowl) const;
    bool WinnerDecided(WinnerPlayer &player) const;
    bool MakeMove(const Player &player, const size_t &index);
    size_t GetBestMove(const Player &player, const size_t &heuristic, const size_t &depth);
    int64_t GetHeuristic(const Player &prevPlayer, const Player &player, const size_t &heuristic, const size_t &depth, int64_t alpha, int64_t beta); // alpha for black, beta for white
    int64_t Heuristic1(const Player &player) const;
    int64_t Heuristic2(const Player &player) const;
    int64_t Heuristic3(const Player &player) const;
    int64_t Heuristic4(const Player &player) const;
    void Print() const;
    ~MancalaState();
};