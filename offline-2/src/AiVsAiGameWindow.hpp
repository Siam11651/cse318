#pragma once

#include <cstdint>
#include "Window.hpp"
#include "State.hpp"

class AiVsAiGameWindow : public Window
{
private:
    State *state;
    
public:
    AiVsAiGameWindow();
    void ProcessInput();
};