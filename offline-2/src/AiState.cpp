#include <iostream>
#include "AiState.hpp"
#include "HumanState.hpp"
#include "HeuristicData.hpp"

AiState::AiState(const bool &versusHuman, const Player &player, MancalaState *mancalaState) : State(mancalaState)
{
    this->versusHuman = versusHuman;
    this->player = player;
}

State *AiState::Execute()
{
    mancalaState->Print();

    std::cout << std::endl;

    WinnerPlayer winner;

    if(mancalaState->WinnerDecided(winner))
    {
        if(winner == WinnerPlayer::BLACK)
        {
            std::cout << "Black won" << std::endl;
        }
        else if(winner == WinnerPlayer::WHITE)
        {
            std::cout << "White won" << std::endl;
        }
        else
        {
            std::cout << "Draw" << std::endl;
        }

        delete mancalaState;

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

    std::cout << "Press any key for AI to make a move" << std::endl;

    while(std::cin.get() == 10);

    size_t heuristic;

    if(player == Player::BLACK)
    {
        heuristic = HeuristicData::heuristic1;
    }
    else
    {
        heuristic = HeuristicData::heuristic2;
    }

    size_t depth;

    if(player == Player::BLACK)
    {
        depth = HeuristicData::depth1;
    }
    else
    {
        depth = HeuristicData::depth2;
    }

    size_t bestMove = mancalaState->GetBestMove(player, heuristic, depth);

    if(mancalaState->MakeMove(player, bestMove))
    {
        return new AiState(false, player, mancalaState);
    }
    else
    {
        if(versusHuman)
        {
            return new HumanState(false, nextPlayer, mancalaState);
        }
        else
        {
            return new AiState(false, nextPlayer, mancalaState);
        }
    }   
}