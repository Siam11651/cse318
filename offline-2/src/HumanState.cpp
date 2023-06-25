#include <iostream>
#include "HumanState.hpp"
#include "AiState.hpp"

HumanState::HumanState(MancalaState *mancalaState) : State(mancalaState)
{

}

State *HumanState::Execute()
{
    mancalaState->Print();

    std::cout << "Human to move" << std::endl;
    std::cout << "Next move:" << std::endl;

    uint16_t move;

    std::cin >> move;

    if(mancalaState->MakeMove(Player::BLACK, move))
    {
        return new HumanState(mancalaState);
    }
    else
    {
        return new AiState(true, Player::WHITE, mancalaState);
    }
}