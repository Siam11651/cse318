#include <iostream>
#include "AiVsAiStartState.hpp"
#include "AiState.hpp"

AiVsAiStartState::AiVsAiStartState(MancalaState *mancalaState) : State(mancalaState)
{

}

State *AiVsAiStartState::Execute()
{
    std::cout << "Which AI to start first?" << std::endl;
    std::cout << "[1] Black" << std::endl;
    std::cout << "[2] White" << std::endl;

    uint8_t option;

    std::cin >> option;

    if(option == 1)
    {
        return new AiState(false, Player::BLACK, mancalaState);
    }
    else if(option == 2)
    {
        return new AiState(false, Player::WHITE, mancalaState);
    }
    else
    {
        return new AiVsAiStartState(mancalaState);
    }
}