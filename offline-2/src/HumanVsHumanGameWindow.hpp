#pragma once

#include "Window.hpp"
#include "State.hpp"

class HumanVsHumanGameWindow : public Window
{
private:
    State *state;

public:
    HumanVsHumanGameWindow();
    void ProcessInput();
};