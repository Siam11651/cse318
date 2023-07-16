#pragma once

#include "Window.hpp"

class HumanVsHumanWindow : public Window
{
public:
    HumanVsHumanWindow();
    Window *ProcessInput();
};