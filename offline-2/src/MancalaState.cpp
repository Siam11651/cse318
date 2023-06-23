#include "MancalaState.hpp"

MancalaState::MancalaState(const Player &player, const size_t &heuristic)
{
    this->heuristic = heuristic;
    this->player = player;
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

void MancalaState::MakeMove(const size_t &index)
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

size_t MancalaState::GetBestMove(const size_t &depth)
{
    int64_t alpha = INT64_MAX, beta = INT64_MIN;
    size_t index;

    if(player == Player::BLACK)
    {
        int64_t maxHeuristic = INT64_MIN;

        for(size_t i = 0; i < moves.size(); ++i)
        {
            if(!moves[i])
            {
                moves[i] = new MancalaState(Player::WHITE, 1);

                moves[i]->MakeMove(i + 6);
            }

            int64_t heurisitic = moves[i]->GetHeuristic(depth - 1, alpha, beta);

            if(heurisitic > maxHeuristic)
            {
                maxHeuristic = heurisitic;
                index = i;
            }

            maxHeuristic = std::max(maxHeuristic, heurisitic);
            alpha = std::max(alpha, heurisitic);

            if(alpha >= beta)
            {
                break;
            }
        }
    }
    else
    {
        int64_t minHeuristic = INT64_MAX;

        for(size_t i = 0; i < moves.size(); ++i)
        {
            if(!moves[i])
            {
                moves[i] = new MancalaState(Player::BLACK, 1);

                moves[i]->MakeMove(i);
            }

            int64_t heurisitic = moves[i]->GetHeuristic(depth - 1, alpha, beta);

            if(heurisitic < minHeuristic)
            {
                minHeuristic = heurisitic;
                index = i;
            }

            beta = std::min(beta, heurisitic);

            if(alpha >= beta)
            {
                break;
            }
        }
    }

    return index;
}

int64_t MancalaState::GetHeuristic(const size_t &depth, int64_t &alpha, int64_t &beta)
{
    if(depth == 0)
    {
        if(heuristic == 1)
        {
            return Heurisitic1();
        }
    }
    else
    {
        if(player == Player::BLACK)
        {
            int64_t maxHeuristic = INT64_MIN;

            for(size_t i = 0; i < moves.size(); ++i)
            {
                if(!moves[i])
                {
                    moves[i] = new MancalaState(Player::WHITE, 1);

                    moves[i]->MakeMove(i + 6);
                }

                int64_t heurisitic = moves[i]->GetHeuristic(depth - 1, alpha, beta);
                maxHeuristic = std::max(maxHeuristic, heurisitic);
                alpha = std::max(alpha, heurisitic);

                if(alpha >= beta)
                {
                    break;
                }
            }

            return maxHeuristic;
        }
        else
        {
            int64_t minHeuristic = INT64_MAX;

            for(size_t i = 0; i < moves.size(); ++i)
            {
                if(!moves[i])
                {
                    moves[i] = new MancalaState(Player::BLACK, 1);

                    moves[i]->MakeMove(i);
                }

                int64_t heurisitic = moves[i]->GetHeuristic(depth - 1, alpha, beta);
                minHeuristic = std::min(minHeuristic, heurisitic);
                beta = std::min(beta, heurisitic);

                if(alpha >= beta)
                {
                    break;
                }
            }

            return minHeuristic;
        }
    }
}

int64_t MancalaState::Heurisitic1() const
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

MancalaState::~MancalaState()
{
    
}