#pragma once

#include "State.hpp"

class HumanVsHumanStartState : public State
{
public:
    HumanVsHumanStartState(MancalaState *mancalaState);
    State *Execute();
};