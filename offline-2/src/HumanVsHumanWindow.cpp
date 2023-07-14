#include <iostream>
#include "HumanVsHumanWindow.hpp"
#include "HumanVsHumanGameWindow.hpp"

extern Window *currentWindow;
extern HumanVsHumanGameWindow *humanVsHumanGameWindow;

HumanVsHumanWindow::HumanVsHumanWindow() : Window()
{

}

void HumanVsHumanWindow::ProcessInput()
{
    currentWindow = humanVsHumanGameWindow;
}