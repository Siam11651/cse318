#include <iostream>
#include <cstdint>
#include "HumanVsAiWindow.hpp"
#include "HumanVsAiGameWindow.hpp"
#include "HeuristicData.hpp"

extern Window *currentWindow;
extern HumanVsAiGameWindow *humanVsAiGameWindow;

HumanVsAiWindow::HumanVsAiWindow() : Window()
{

}

void HumanVsAiWindow::ProcessInput()
{
    std::cout << "Select AI heuristic:" << std::endl;
    std::cout << "[1] Heuristic 1" << std::endl;
    std::cout << "[2] Heuristic 2" << std::endl;
    std::cout << "[3] Heuristic 3" << std::endl;
    std::cout << "[4] Heuristic 4" << std::endl;

    uint8_t heuristic;

    std::cin >> heuristic;
    
    std::cout << "Insert values of w1, w2, w2 and w4 seperated by whitespaces:" << std::endl;

    uint64_t w1, w2, w3, w4;

    std::cin >> w1 >> w2 >> w3 >> w4;

    HeuristicData::heuristic2 = heuristic;
    HeuristicData::w21 = w1;
    HeuristicData::w22 = w2;
    HeuristicData::w23 = w3;
    HeuristicData::w24 = w4;

    currentWindow = humanVsAiGameWindow;
}