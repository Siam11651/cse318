#include <iostream>
#include "HumanVsHumanWindow.hpp"
#include "HumanVsHumanGameWindow.hpp"

HumanVsHumanWindow::HumanVsHumanWindow() : Window()
{

}

Window *HumanVsHumanWindow::ProcessInput()
{
    return new HumanVsHumanGameWindow();
}