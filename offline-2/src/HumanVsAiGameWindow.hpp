#pragma once

#include <cstdint>
#include "Window.hpp"
#include "State.hpp"

class HumanVsAiGameWindow : public Window
{
    State *state;

public:
    HumanVsAiGameWindow();
    void ProcessInput();
};