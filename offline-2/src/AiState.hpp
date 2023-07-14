#pragma once

#include "State.hpp"

class AiState : public State
{
private:
    bool versusHuman;
    Player player;
    
public:
    AiState(const bool &versusHuman, const Player &player, MancalaState *mancalaState);
    State *Execute();
};