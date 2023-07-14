#include <iostream>
#include "HumanVsAiStartState.hpp"
#include "HumanState.hpp"
#include "AiState.hpp"

HumanVsAiStartState::HumanVsAiStartState(MancalaState *mancalaState) : State(mancalaState)
{

}

State *HumanVsAiStartState::Execute()
{
    std::cout << "Shall you start first? [y/n]" << std::endl;

    char c;

    std::cin >> c;

    if(c == 'y' || c == 'Y')
    {
        return new HumanState(false, Player::BLACK, mancalaState);
    }
    else if(c == 'n' || c == 'N')
    {
        return new AiState(true, Player::WHITE, mancalaState);
    }
    else
    {
        return new HumanVsAiStartState(mancalaState);
    }
}