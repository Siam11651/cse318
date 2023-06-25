#pragma once

#include "MancalaState.hpp"

class State
{
protected:
    MancalaState *mancalaState;
public:
    State(MancalaState *mancalaState);
    virtual State *Execute() = 0;
};