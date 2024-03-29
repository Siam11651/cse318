#include <iostream>
#include "AStarSearch.hpp"

void AStarSearch::BuildSolution()
{
    Board *now = finalBoard;

    while(now)
    {
        solvePath.push_back(*now);

        now = now->GetParent();
    }

    std::reverse(solvePath.begin(), solvePath.end());
}

bool AStarSearch::InClosedList(Board *board)
{
    if(closedList.find(*board) == closedList.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

AStarSearch::AStarSearch(Board *currentBoard)
{
    this->currentBoard = currentBoard;
    solved = false;
    finalBoard = nullptr;
    explored = expanded = 0;
}

Board *AStarSearch::GetCurrentBoard() const
{
    return currentBoard;
}

size_t AStarSearch::GetExploredCount() const
{
    return explored;
}

size_t AStarSearch::GetExpandedCount() const
{
    return expanded;
}

void AStarSearch::ExecuteSearch()
{
    openList.push(currentBoard);
    closedList.insert(*currentBoard);

    ++expanded;

    while(!openList.empty())
    {
        Board *parentBoard = openList.top();
        ++explored;

        openList.pop();

        if(parentBoard->IsSolved())
        {
            finalBoard = parentBoard;

            break;
        }

        Board *children[] =
        {
            parentBoard->CreateNewChildBoard(Direction::LEFT),
            parentBoard->CreateNewChildBoard(Direction::RIGHT),
            parentBoard->CreateNewChildBoard(Direction::UP),
            parentBoard->CreateNewChildBoard(Direction::DOWN)
        };

        for(size_t i = 0; i < 4; ++i)
        {
            if(children[i] && !InClosedList(children[i]))
            {
                openList.push(children[i]);
                closedList.insert(*children[i]);
                closedPointers.push_back(children[i]);

                ++expanded;
            }
            else
            {
                delete children[i];
            }
        }
    }

    solved = true;
}

size_t AStarSearch::GetMoveCount()
{
    if(solved)
    {
        if(solvePath.size() == 0)
        {
            BuildSolution();
        }
        
        return solvePath.size() - 1;
    }
    else
    {
        return 0;
    }
}

std::vector<Board> AStarSearch::GetSolve()
{
    if(solved)
    {
        if(solvePath.size() == 0)
        {
            BuildSolution();
        }
        
        return solvePath;
    }
    else
    {
        return std::vector<Board>();
    }
}

AStarSearch::~AStarSearch()
{
    std::set<Board *> deleted;

    while(!openList.empty())
    {
        delete openList.top();

        deleted.insert(openList.top());        
        openList.pop();
    }

    for(size_t i = 0; i < closedPointers.size(); ++i)
    {
        if(deleted.find(closedPointers[i]) == deleted.end())
        {
            delete closedPointers[i];   
        }
    }
}