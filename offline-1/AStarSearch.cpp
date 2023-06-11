#include <iostream>
#include "AStarSearch.hpp"

void AStarSearch::BuildSolution()
{
    while(currentBoard)
    {
        solvePath.push_back(currentBoard);

        currentBoard = currentBoard->GetParent();
    }

    std::reverse(solvePath.begin(), solvePath.end());
}

bool AStarSearch::InClosedList(Board *board)
{
    bool inClosedList = false;

    for(size_t i = 0; i < closedList.size(); ++i)
    {
        if(*board == *closedList[i])
        {
            inClosedList = true;

            break;
        }
    }

    return inClosedList;
}

AStarSearch::AStarSearch(Board *currentBoard)
{
    this->currentBoard = currentBoard;
    solved = false;
}

Board *AStarSearch::GetCurrentBoard() const
{
    return currentBoard;
}

void AStarSearch::ExecuteSearch()
{
    std::priority_queue<Board *, std::vector<Board *>, BoardComparator> openList;

    openList.push(currentBoard);

    size_t count = 0;

    while(!openList.empty())
    {
        Board *parentBoard = openList.top();

        openList.pop();
        closedList.push_back(parentBoard);

        if(parentBoard->IsSolved())
        {
            currentBoard = parentBoard;

            break;
        }

        ++count;

        std::cout << count << std::endl;

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

std::vector<Board *> AStarSearch::GetSolve()
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
        return std::vector<Board *>();
    }
}

AStarSearch::~AStarSearch()
{

}