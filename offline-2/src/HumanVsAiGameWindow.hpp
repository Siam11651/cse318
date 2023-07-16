#pragma once

#include <cstdint>
#include "Window.hpp"
#include "State.hpp"

class HumanVsAiGameWindow : public Window
{
private:
    State *state;

public:
    HumanVsAiGameWindow();
    Window *ProcessInput();
};