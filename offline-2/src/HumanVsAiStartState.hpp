#pragma once

#include "State.hpp"

class HumanVsAiStartState : public State
{
public:
    HumanVsAiStartState(MancalaState *mancalaState);
    State *Execute();
};