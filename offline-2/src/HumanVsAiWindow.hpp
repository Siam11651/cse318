#pragma once

#include "Window.hpp"

class HumanVsAiWindow : public Window
{
public:
    HumanVsAiWindow();
    Window *ProcessInput();
};