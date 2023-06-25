#include <iostream>
#include "Window.hpp"
#include "HumanVsAiWindow.hpp"
#include "AiVsAiWindow.hpp"

extern Window *currentWindow;
extern HumanVsAiWindow *humanVsAiWindow;
extern AiVsAiWindow *aiVsAiWindow;

Window::Window()
{

}

void Window::ProcessInput()
{
    std::cout << "Choose mode:" << std::endl;
    std::cout << "[1] Human vs AI" << std::endl;
    std::cout << "[2] AI vs AI" << std::endl;

    char c;

    std::cin >> c;

    if(c == '1')
    {
        currentWindow = humanVsAiWindow;
    }
    else if(c == '2')
    {
        currentWindow = aiVsAiWindow;
    }
    else
    {
        std::cout << "Invalid input" << std::endl;
    }
}