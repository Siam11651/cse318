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
    size_t explored, expanded;
    bool solved;

    void BuildSolution();
    bool InClosedList(Board *board);

public:
    AStarSearch(Board *currentBoard);
    Board *GetCurrentBoard() const;
    size_t GetExploredCount() const;
    size_t GetExpandedCount() const;
    void ExecuteSearch();
    size_t GetMoveCount();
    std::vector<Board> GetSolve();
    void Clean();
    ~AStarSearch();
};