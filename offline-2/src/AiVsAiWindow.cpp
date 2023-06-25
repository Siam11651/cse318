#include <cstdint>
#include <iostream>
#include "AiVsAiWindow.hpp"
#include "AiVsAiGameWindow.hpp"
#include "HeuristicData.hpp"

extern Window *currentWindow;
extern AiVsAiGameWindow *aiVsAiGameWindow;

AiVsAiWindow::AiVsAiWindow() : Window()
{

}

void AiVsAiWindow::ProcessInput()
{
    std::cout << "Select heuristic of AI-1 and AI-2 seperated by whitespace:" << std::endl;
    std::cout << "[1] Heuristic 1" << std::endl;
    std::cout << "[2] Heuristic 2" << std::endl;
    std::cout << "[3] Heuristic 3" << std::endl;
    std::cout << "[4] Heuristic 4" << std::endl;

    uint8_t heuristic1, heuristic2;

    std::cin >> heuristic1 >> heuristic1;

    std::cout << "Insert values of w1, w2, w2 and w4 for AI-1 seperated by whitespaces:" << std::endl;

    uint64_t w11, w12, w13, w14;

    std::cin >> w11 >> w12 >> w13 >> w14;

    std::cout << "Insert values of w1, w2, w2 and w4 for AI-2 seperated by whitespaces:" << std::endl;

    uint64_t w21, w22, w23, w24;

    std::cin >> w21 >> w22 >> w23 >> w24;

    HeuristicData::heuristic1 = heuristic1;
    HeuristicData::heuristic2 = heuristic2;
    HeuristicData::w11 = w11;
    HeuristicData::w12 = w12;
    HeuristicData::w13 = w13;
    HeuristicData::w14 = w14;
    HeuristicData::w21 = w21;
    HeuristicData::w22 = w22;
    HeuristicData::w23 = w23;
    HeuristicData::w24 = w24;

    currentWindow = aiVsAiGameWindow;
}