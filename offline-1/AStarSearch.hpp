#pragma once

#include <queue>
#include <set>
#include "Board.hpp"
#include "BoardComparator.hpp"

class AStarSearch
{
private:
    Board *currentBoard;
    std::vector<Board> solvePath;
    std::priority_queue<Board *, std::vector<Board *>, BoardComparator> openList;
    std::set<Board> closedList;
    std::vector<Board *> closedPointers;
    Board *finalBoard;
    bool solved;

    void BuildSolution();
    bool InClosedList(Board *board);

public:
    AStarSearch(Board *currentBoard);
    Board *GetCurrentBoard() const;
    void ExecuteSearch();
    size_t GetMoveCount();
    std::vector<Board> GetSolve();
    void Clean();
    ~AStarSearch();
};