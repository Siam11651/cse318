#include <iostream>
#include "MancalaState.hpp"

MancalaState::MancalaState()
{
    bowls = 
    {
        new Bowl(Player::BLACK),
        new Bowl(Player::BLACK),
        new Bowl(Player::BLACK),
        new Bowl(Player::BLACK),
        new Bowl(Player::BLACK),
        new Bowl(Player::BLACK),
        new BigBowl(Player::BLACK),
        new Bowl(Player::WHITE),
        new Bowl(Player::WHITE),
        new Bowl(Player::WHITE),
        new Bowl(Player::WHITE),
        new Bowl(Player::WHITE),
        new Bowl(Player::WHITE),
        new BigBowl(Player::WHITE)
    };
}

Bowl *MancalaState::GetBowl(const size_t &bowlIndex) const
{
    return bowls[bowlIndex];
}

void MancalaState::MakeMove(const Player &player, const size_t &index)
{
    size_t actualIndex;

    if(player == Player::BLACK)
    {
        actualIndex = index;
    }
    else
    {
        actualIndex = index + 6;
    }

    size_t hand = bowls[actualIndex]->GetCount();
    ++actualIndex;

    while(hand > 0)
    {
        hand = bowls[actualIndex]->TakePebble(player, hand);
    }
}

size_t MancalaState::GetBestMove(const Player &player, const size_t &heuristic, const size_t &depth)
{
    int64_t alpha = INT64_MAX, beta = INT64_MIN;
    size_t index;

    if(player == Player::BLACK)
    {
        int64_t maxHeuristic = INT64_MIN;

        for(size_t i = 0; i < moves.size(); ++i)
        {
            MancalaState *newMancalaState = new MancalaState();

            newMancalaState->MakeMove(Player::WHITE, i + 6);

            int64_t heuristic = moves[i]->GetHeuristic(Player::WHITE, heuristic, depth - 1, alpha, beta);

            if(heuristic > maxHeuristic)
            {
                maxHeuristic = heuristic;
                index = i;
            }

            maxHeuristic = std::max(maxHeuristic, heuristic);
            alpha = std::max(alpha, heuristic);

            if(alpha >= beta)
            {
                delete newMancalaState;

                break;
            }

            delete newMancalaState;
        }
    }
    else
    {
        int64_t minHeuristic = INT64_MAX;

        for(size_t i = 0; i < moves.size(); ++i)
        {
            MancalaState *newMancalaState = new MancalaState();

            newMancalaState->MakeMove(Player::BLACK, i);

            int64_t heuristic = newMancalaState->GetHeuristic(Player::BLACK, heuristic, depth - 1, alpha, beta);

            if(heuristic < minHeuristic)
            {
                minHeuristic = heuristic;
                index = i;
            }

            beta = std::min(beta, heuristic);

            if(alpha >= beta)
            {
                delete newMancalaState;

                break;
            }

            delete newMancalaState;
        }
    }

    return index;
}

int64_t MancalaState::GetHeuristic(const Player &player, const size_t &heuristic, const size_t &depth, int64_t &alpha, int64_t &beta)
{
    if(depth == 0)
    {
        if(heuristic == 1)
        {
            return heuristic1(player);
        }
    }
    else
    {
        if(player == Player::BLACK)
        {
            int64_t maxHeuristic = INT64_MIN;

            for(size_t i = 0; i < moves.size(); ++i)
            {
                MancalaState *newMancalaState = new MancalaState();

                newMancalaState->MakeMove(Player::WHITE, i + 6);

                int64_t heuristic = newMancalaState->GetHeuristic(Player::WHITE, heuristic, depth - 1, alpha, beta);
                maxHeuristic = std::max(maxHeuristic, heuristic);
                alpha = std::max(alpha, heuristic);

                if(alpha >= beta)
                {
                    delete newMancalaState;

                    break;
                }

                delete newMancalaState;
            }

            return maxHeuristic;
        }
        else
        {
            int64_t minHeuristic = INT64_MAX;

            for(size_t i = 0; i < moves.size(); ++i)
            {
                MancalaState *newMancalaState = new MancalaState();

                newMancalaState->MakeMove(Player::BLACK, i);

                int64_t heuristic = newMancalaState->GetHeuristic(Player::BLACK, heuristic, depth - 1, alpha, beta);
                minHeuristic = std::min(minHeuristic, heuristic);
                beta = std::min(beta, heuristic);

                if(alpha >= beta)
                {
                    delete newMancalaState;

                    break;
                }

                delete newMancalaState;
            }

            return minHeuristic;
        }
    }
}

int64_t MancalaState::heuristic1(const Player &player) const
{
    if(player == Player::BLACK)
    {
        return bowls[6] - bowls[13];
    }
    else
    {
        return bowls[13] - bowls[6];
    }
}

void MancalaState::Print() const
{
    std::cout << "White" << std::endl;
    
    for(size_t i = 13; i > 6; --i)
    {
        std::cout << bowls[i] << "\t";
    }

    std::cout << std::endl;
    std::cout << "\t";

    for(size_t i = 0; i < 7; ++i)
    {
        std::cout << bowls[i] << "\t";
    }

    std::cout << std::endl;
}

MancalaState::~MancalaState()
{
    
}