#pragma once

#include "State.hpp"

class HumanState : public State
{
private:
    bool versusHuman;
    Player player;

public:
    HumanState(const bool &versusHuman, const Player &player, MancalaState *MancalaState);
    State *Execute();
};