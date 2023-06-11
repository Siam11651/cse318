#include <iostream>
#include "HammingBoard.hpp"
#include "ManhattanBoard.hpp"
#include "AStarSearch.hpp"

int main()
{
    size_t k;

    std::cin >> k;

    std::vector<std::vector<uint64_t>> boardArray(k, std::vector<uint64_t>(k));

    for(size_t i = 0; i < k; ++i)
    {
        for(size_t j = 0; j < k; ++j)
        {
            std::cin >> boardArray[i][j];
        }
    }

    std::cout << "--- Using Hamming Distance ---" << std::endl;

    Board *board = new HammingBoard(0, k, boardArray, nullptr);

    if(board->IsSolvable())
    {
        AStarSearch *aStarSearch = new AStarSearch(board);

        aStarSearch->ExecuteSearch();

        size_t moveCount = aStarSearch->GetMoveCount();

        std::cout << std::endl << "Minimum number of moves = " << moveCount << std::endl;

        std::vector<Board *> solvePath = aStarSearch->GetSolve();

        for(size_t i = 0; i < solvePath.size(); ++i)
        {
            for(size_t p = 0; p < board->GetDimension(); ++p)
            {
                for(size_t q = 0; q < board->GetDimension(); ++q)
                {
                    std::cout << solvePath[i]->GetCellValue(p, q) << " ";
                }

                std::cout << std::endl;
            }

            std::cout << std::endl;
        }

        delete aStarSearch;
        delete board;

        std::cout << "--- Using Manhattan Distance ---" << std::endl;

        board = new ManhattanBoard(0, k, boardArray, nullptr);
        aStarSearch = new AStarSearch(board);

        aStarSearch->ExecuteSearch();

        size_t moveCount = aStarSearch->GetMoveCount();

        std::cout << std::endl << "Minimum number of moves = " << moveCount << std::endl;

        std::vector<Board *> solvePath = aStarSearch->GetSolve();

        for(size_t i = 0; i < solvePath.size(); ++i)
        {
            for(size_t p = 0; p < board->GetDimension(); ++p)
            {
                for(size_t q = 0; q < board->GetDimension(); ++q)
                {
                    std::cout << solvePath[i]->GetCellValue(p, q) << " ";
                }

                std::cout << std::endl;
            }

            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "This puzzle is not solvable" << std::endl;
    }

    return 0;
}