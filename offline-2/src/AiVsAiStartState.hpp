#pragma once

#include "State.hpp"

class AiVsAiStartState : public State
{
public:
    AiVsAiStartState(MancalaState *mancalaState);
    State *Execute();
};