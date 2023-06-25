#include <iostream>
#include "AiState.hpp"
#include "HumanState.hpp"

AiState::AiState(const bool &versusHuman, const Player &player, MancalaState *mancalaState) : State(mancalaState)
{
    this->versusHuman = versusHuman;
    this->player = player;
}

State *AiState::Execute()
{
    mancalaState->Print();

    Player nextPlayer;

    if(player == Player::BLACK)
    {
        std::cout << "Black to move" << std::endl;

        nextPlayer = Player::WHITE;
    }
    else
    {
        std::cout << "White to move" << std::endl;

        nextPlayer = Player::BLACK;
    }

    std::cout << "Press any key for AI to make a move" << std::endl;

    getchar();

    if(versusHuman)
    {
        return new HumanState(mancalaState);
    }
    else
    {
        return new AiState(false, nextPlayer, mancalaState);
    }
}