#include <iostream>
#include "HumanState.hpp"
#include "AiState.hpp"

HumanState::HumanState(const bool &versusHuman, const Player &player, MancalaState *mancalaState) : State(mancalaState)
{
    this->versusHuman = versusHuman;
    this->player = player;
}

State *HumanState::Execute()
{
    mancalaState->Print();

    std::cout << std::endl;

    Player winner;

    if(mancalaState->WinnerDecided(winner))
    {
        if(winner == Player::BLACK)
        {
            std::cout << "Black won" << std::endl;
        }
        else
        {
            std::cout << "White won" << std::endl;
        }

        return nullptr;
    }

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

    std::cout << "Input next move:" << std::endl;

    uint16_t move;

    std::cin >> move;

    if(mancalaState->MakeMove(player, move))
    {
        return new HumanState(true, player, mancalaState);
    }
    else
    {
        if(versusHuman)
        {
            return new HumanState(true, nextPlayer, mancalaState);
        }
        else
        {
            return new AiState(true, nextPlayer, mancalaState);
        }
    }
}