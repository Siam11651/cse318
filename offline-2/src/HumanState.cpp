#include <iostream>
#include "HumanState.hpp"
#include "AiState.hpp"

HumanState::HumanState(MancalaState *mancalaState) : State(mancalaState)
{

}

State *HumanState::Execute()
{
    mancalaState->Print();

    std::cout << "Next move:" << std::endl;

    uint8_t move;

    std::cin >> move;

    mancalaState->MakeMove(Player::BLACK, move);

    return new AiState(true, Player::WHITE, mancalaState);
}