#pragma once

#include "State.hpp"

class HumanState : public State
{
public:
    HumanState(MancalaState *MancalaState);
    State *Execute();
};