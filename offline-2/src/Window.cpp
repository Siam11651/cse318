#include <iostream>
#include "Window.hpp"
#include "HumanVsAiWindow.hpp"
#include "AiVsAiWindow.hpp"
#include "HumanVsHumanWindow.hpp"

extern Window *currentWindow;

Window::Window()
{

}

Window *Window::ProcessInput()
{
    std::cout << "Choose mode:" << std::endl;
    std::cout << "[1] Human vs AI" << std::endl;
    std::cout << "[2] AI vs AI" << std::endl;
    std::cout << "[3] Human vs Human" << std::endl;

    char c;

    std::cin >> c;

    if(c == '1')
    {
        return new HumanVsAiWindow();
    }
    else if(c == '2')
    {
        return new AiVsAiWindow();
    }
    else if(c == '3')
    {
        return new HumanVsHumanWindow();
    }
    else
    {
        std::cout << "Invalid input" << std::endl;

        return new Window();
    }
}