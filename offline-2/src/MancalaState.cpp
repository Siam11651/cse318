#include <iostream>
#include "MancalaState.hpp"
#include "HeuristicData.hpp"

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
    additionalMoveCount = other.additionalMoveCount;
    caputured = other.caputured;
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

bool MancalaState::WinnerDecided(WinnerPlayer &player) const
{
    bool allZeroBlack = true, allZeroWhite = true;

    for(size_t i = 0; allZeroBlack && i < 6; ++i)
    {
        if(bowls[i]->GetCount() > 0)
        {
            allZeroBlack = false;
        }
    }

    for(size_t i = 7; allZeroWhite && i < 13; ++i)
    {
        if(bowls[i]->GetCount() > 0)
        {
            allZeroWhite = false;
        }
    }

    if(allZeroBlack)
    {
        for(size_t i = 7; i < 13; ++i)
        {
            bowls[13]->SetCount(bowls[i]->GetCount() + bowls[13]->GetCount());
        }
    }
    
    if(allZeroWhite)
    {
        for(size_t i = 0; i < 6; ++i)
        {
            bowls[6]->SetCount(bowls[i]->GetCount() + bowls[6]->GetCount());
        }
    }

    if(allZeroBlack || allZeroWhite)
    {
        if(bowls[6]->GetCount() > bowls[13]->GetCount())
        {
            player = WinnerPlayer::BLACK;
        }
        else if(bowls[6]->GetCount() < bowls[13]->GetCount())
        {
            player = WinnerPlayer::WHITE;
        }
        else
        {
            player = WinnerPlayer::NONE;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool MancalaState::MakeMove(const Player &player, const size_t &index)
{
    size_t actualIndex;

    if(player == Player::BLACK)
    {
        actualIndex = index - 1;
    }
    else
    {
        actualIndex = 6 + index;
    }

    size_t hand = bowls[actualIndex]->GetCount();

    bowls[actualIndex]->SetCount(0);

    ++actualIndex;
    bool moveAgain = false, couldMove = false;
    size_t lastBowlPreviousCount = hand;

    while(hand > 0)
    {
        couldMove = true;
        lastBowlPreviousCount = bowls[actualIndex % 14]->GetCount();
        moveAgain = bowls[actualIndex % 14]->TakePebble(player, hand);
        ++actualIndex;
    }

    --actualIndex;
    bool inMyTerritory = false;

    if((actualIndex % 14) < 7 && player == Player::BLACK)
    {
        inMyTerritory = true;
    }
    else if((actualIndex % 14) > 6 && player == Player::WHITE)
    {
        inMyTerritory = true;
    }

    if(inMyTerritory && couldMove && !moveAgain && lastBowlPreviousCount == 0 && bowls[12 - (actualIndex % 14)]->GetCount() > 0)
    {
        if(player == Player::BLACK)
        {
            bowls[6]->SetCount(bowls[6]->GetCount() + bowls[actualIndex % 14]->GetCount() + bowls[12 - (actualIndex % 14)]->GetCount());
        }
        else
        {
            bowls[13]->SetCount(bowls[13]->GetCount() + bowls[actualIndex % 14]->GetCount() + bowls[12 - (actualIndex % 14)]->GetCount());
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
    additionalMoveCount = 0;
    caputured = 0;

    if(player == Player::BLACK)
    {
        int64_t maxHeuristic = INT64_MIN;

        for(size_t i = 0; i < 6; ++i)
        {
            MancalaState *newMancalaState = new MancalaState(*this);

            if(newMancalaState->GetBowl(i)->GetCount() == 0)
            {
                delete newMancalaState;

                continue;
            }

            Player nextPlayer;

            if(newMancalaState->MakeMove(Player::BLACK, i + 1))
            {
                nextPlayer = Player::BLACK;
                ++additionalMoveCount;
            }
            else
            {
                nextPlayer = Player::WHITE;
            }

            int64_t heuristic = newMancalaState->GetHeuristic(player, nextPlayer, heuristicType, depth - 1, alpha, beta);

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
                delete newMancalaState;

                continue;
            }

            Player nextPlayer;

            if(newMancalaState->MakeMove(Player::WHITE, i + 1))
            {
                nextPlayer = Player::WHITE;
                ++additionalMoveCount;
            }
            else
            {
                nextPlayer = Player::BLACK;
            }

            int64_t heuristic = newMancalaState->GetHeuristic(player, nextPlayer, heuristicType, depth - 1, alpha, beta);

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

int64_t MancalaState::GetHeuristic(const Player &previousPlayer, const Player &player, const size_t &heuristicType, const size_t &depth, int64_t alpha, int64_t beta)
{
    WinnerPlayer winner;

    if(depth == 0 || WinnerDecided(winner))
    {
        if(heuristicType == 1)
        {
            return Heuristic1(previousPlayer);
        }
        else if(heuristicType == 2)
        {
            return Heuristic2(previousPlayer);
        }
        else if(heuristicType == 3)
        {
            return Heuristic3(previousPlayer);
        }
        else if(heuristicType == 4)
        {
            return Heuristic4(previousPlayer);
        }
    }
    else
    {
        if(player == Player::BLACK)
        {
            int64_t maxHeuristic = INT64_MIN;

            for(int64_t i = 5; i >= 0; --i)
            {
                MancalaState *newMancalaState = new MancalaState(*this);

                if(newMancalaState->GetBowl(i)->GetCount() == 0)
                {
                    delete newMancalaState;

                    continue;
                }

                Player nextPlayer;

                if(newMancalaState->MakeMove(Player::BLACK, i + 1))
                {
                    nextPlayer = Player::BLACK;
                    ++additionalMoveCount;
                }
                else
                {
                    nextPlayer = Player::WHITE;
                }

                int64_t heuristic = newMancalaState->GetHeuristic(player, nextPlayer, heuristicType, depth - 1, alpha, beta);
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

            for(int64_t i = 5; i >= 0; --i)
            {
                MancalaState *newMancalaState = new MancalaState(*this);

                if(newMancalaState->GetBowl(i + 7)->GetCount() == 0)
                {
                    delete newMancalaState;

                    continue;
                }

                Player nextPlayer;

                if(newMancalaState->MakeMove(Player::WHITE, i + 1))
                {
                    nextPlayer = Player::WHITE;
                    ++additionalMoveCount;
                }
                else
                {
                    nextPlayer = Player::BLACK;
                }

                int64_t heuristic = newMancalaState->GetHeuristic(player, nextPlayer, heuristicType, depth - 1, alpha, beta);
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

int64_t MancalaState::Heuristic1(const Player &player) const
{
    return (int64_t)bowls[6]->GetCount() - (int64_t)bowls[13]->GetCount();
}

int64_t MancalaState::Heuristic2(const Player &player) const
{
    size_t blackCount = 0;
    size_t whiteCount = 0;

    for(size_t i = 0; i < 6; ++i)
    {
        blackCount += bowls[i]->GetCount();
        whiteCount += bowls[12 - i]->GetCount();
    }

    int64_t w1 = HeuristicData::w21;
    int64_t w2 = HeuristicData::w22;
    int64_t part1 = ((int64_t)bowls[6]->GetCount() - (int64_t)bowls[13]->GetCount()) * w1;
    int64_t part2 = ((int64_t)blackCount - (int64_t)whiteCount) * w2;

    return part1 + part2;
}

int64_t MancalaState::Heuristic3(const Player &player) const
{
    size_t blackCount = 0;
    size_t whiteCount = 0;

    for(size_t i = 0; i < 6; ++i)
    {
        blackCount += bowls[i]->GetCount();
        whiteCount += bowls[12 - i]->GetCount();
    }

    int64_t w1 = HeuristicData::w21;
    int64_t w2 = HeuristicData::w22;
    int64_t w3 = HeuristicData::w23;
    int64_t part1 = ((int64_t)bowls[6]->GetCount() - (int64_t)bowls[13]->GetCount()) * w1;
    int64_t part2 = ((int64_t)blackCount - (int64_t)whiteCount) * w2;
    int64_t part3 = additionalMoveCount * w3;

    return part1 + part2 + part3;
}

int64_t MancalaState::Heuristic4(const Player &player) const
{
    size_t blackCount = 0;
    size_t whiteCount = 0;

    for(size_t i = 0; i < 6; ++i)
    {
        blackCount += bowls[i]->GetCount();
        whiteCount += bowls[12 - i]->GetCount();
    }

    int64_t w1 = HeuristicData::w21;
    int64_t w2 = HeuristicData::w22;
    int64_t w3 = HeuristicData::w23;
    int64_t w4 = HeuristicData::w24;
    int64_t part1 = ((int64_t)bowls[6]->GetCount() - (int64_t)bowls[13]->GetCount()) * w1;
    int64_t part2 = ((int64_t)blackCount - (int64_t)whiteCount) * w2;
    int64_t part3 = additionalMoveCount * w3;
    int64_t part4 = caputured * w4;

    return part1 + part2 + part3 + part4;
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