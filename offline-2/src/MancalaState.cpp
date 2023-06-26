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

MancalaState::MancalaState(const MancalaState &other)
{
    bowls = 
    {
        new Bowl(*other.bowls[0]),
        new Bowl(*other.bowls[1]),
        new Bowl(*other.bowls[2]),
        new Bowl(*other.bowls[3]),
        new Bowl(*other.bowls[4]),
        new Bowl(*other.bowls[5]),
        new BigBowl(*other.bowls[6]),
        new Bowl(*other.bowls[7]),
        new Bowl(*other.bowls[8]),
        new Bowl(*other.bowls[9]),
        new Bowl(*other.bowls[10]),
        new Bowl(*other.bowls[11]),
        new Bowl(*other.bowls[12]),
        new BigBowl(*other.bowls[13])
    };
}

Bowl *MancalaState::GetBowl(const size_t &bowlIndex) const
{
    return bowls[bowlIndex];
}

bool MancalaState::MakeMove(const Player &player, const size_t &index)
{
    size_t actualIndex;

    if(player == Player::BLACK)
    {
        actualIndex = 6 - index;
    }
    else
    {
        actualIndex = 6 + index;
    }

    size_t hand = bowls[actualIndex]->GetCount();

    bowls[actualIndex]->SetCount(0);

    ++actualIndex;
    bool moveAgain, couldMove = false;
    size_t lastBowlPreviousCount = hand;

    while(hand > 0)
    {
        couldMove = true;
        lastBowlPreviousCount = bowls[actualIndex % 14]->GetCount();
        moveAgain = bowls[actualIndex % 14]->TakePebble(player, hand);
        ++actualIndex;
    }

    if(couldMove && !moveAgain && lastBowlPreviousCount == 0)
    {
        --actualIndex;

        if(player == Player::BLACK)
        {
            bowls[6]->SetCount(bowls[6]->GetCount() + bowls[actualIndex % 14]->GetCount() + bowls[12 - (actualIndex % 14)]->GetCount());
        }
        else
        {
            bowls[13]->SetCount(bowls[6]->GetCount() + bowls[actualIndex % 14]->GetCount() + bowls[12 - (actualIndex % 14)]->GetCount());
        }

        bowls[actualIndex % 14]->SetCount(0);
        bowls[12 - (actualIndex % 14)]->SetCount(0);
    }

    return moveAgain;
}

size_t MancalaState::GetBestMove(const Player &player, const size_t &heuristicType, const size_t &depth)
{
    int64_t alpha = INT64_MIN, beta = INT64_MAX;
    size_t index;

    if(player == Player::BLACK)
    {
        int64_t maxHeuristic = INT64_MIN;

        for(size_t i = 0; i < 6; ++i)
        {
            MancalaState *newMancalaState = new MancalaState(*this);

            if(newMancalaState->GetBowl(i)->GetCount() == 0)
            {
                continue;
            }

            newMancalaState->MakeMove(Player::WHITE, i + 1);

            int64_t heuristic = newMancalaState->GetHeuristic(Player::WHITE, heuristicType, depth - 1, alpha, beta);

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

        for(size_t i = 0; i < 6; ++i)
        {
            MancalaState *newMancalaState = new MancalaState(*this);

            if(newMancalaState->GetBowl(i + 7)->GetCount() == 0)
            {
                continue;
            }

            newMancalaState->MakeMove(Player::BLACK, i + 1);

            int64_t heuristic = newMancalaState->GetHeuristic(Player::BLACK, heuristicType, depth - 1, alpha, beta);

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

    ++index;

    return index;
}

int64_t MancalaState::GetHeuristic(const Player &player, const size_t &heuristicType, const size_t &depth, int64_t &alpha, int64_t &beta)
{
    if(depth == 0)
    {
        if(heuristicType == 1)
        {
            return heuristic1(player);
        }
    }
    else
    {
        if(player == Player::BLACK)
        {
            int64_t maxHeuristic = INT64_MIN;

            for(size_t i = 0; i < 6; ++i)
            {
                MancalaState *newMancalaState = new MancalaState(*this);

                if(newMancalaState->GetBowl(i)->GetCount() == 0)
                {
                    continue;
                }

                newMancalaState->MakeMove(Player::WHITE, i + 1);

                int64_t heuristic = newMancalaState->GetHeuristic(Player::WHITE, heuristicType, depth - 1, alpha, beta);
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

            for(size_t i = 0; i < 6; ++i)
            {
                MancalaState *newMancalaState = new MancalaState(*this);

                if(newMancalaState->GetBowl(i + 7)->GetCount() == 0)
                {
                    continue;
                }

                newMancalaState->MakeMove(Player::BLACK, i + 1);

                int64_t heuristic = newMancalaState->GetHeuristic(Player::BLACK, heuristicType, depth - 1, alpha, beta);
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
        return bowls[6]->GetCount() - bowls[13]->GetCount();
    }
    else
    {
        return bowls[13]->GetCount() - bowls[6]->GetCount();
    }
}

void MancalaState::Print() const
{
    std::cout << "White" << std::endl;
    
    for(size_t i = 13; i > 6; --i)
    {
        std::cout << bowls[i]->GetCount() << "\t";
    }

    std::cout << std::endl;
    std::cout << "\t";

    for(size_t i = 0; i < 7; ++i)
    {
        std::cout << bowls[i]->GetCount() << "\t";
    }

    std::cout << std::endl;
    std::cout << "Black" << std::endl;
}

MancalaState::~MancalaState()
{
    
}