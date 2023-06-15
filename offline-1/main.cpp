#include <iostream>
#include "HammingBoard.hpp"
#include "ManhattanBoard.hpp"
#include "AStarSearch.hpp"
#include "HeuristicEnum.hpp"

int main(int argc, char **argv)
{
    if(argc < 1)
    {
        std::cerr << "Need an argument for heuristic" << std::endl;

        return -1;
    }

    std::string heuristicArgument(argv[1]);

    for(size_t i = 0; i < heuristicArgument.size(); ++i)
    {
        heuristicArgument[i] = std::tolower(heuristicArgument[i]);
    }

    HeuristicEnum heuristicEnum;

    if(heuristicArgument == "hamming")
    {
        heuristicEnum = HeuristicEnum::HAMMING;
    }
    else if(heuristicArgument == "manhattan")
    {
        heuristicEnum = HeuristicEnum::MANHATTAN;
    }
    else
    {
        std::cerr << "No such heuristic" << std::endl;

        return -1;
    }

    size_t k;

    std::cin >> k;

    std::vector<uint64_t> boardArray(k * k);

    for(size_t i = 0; i < k; ++i)
    {
        for(size_t j = 0; j < k; ++j)
        {
            std::cin >> boardArray[i * k + j];
        }
    }

    Board *board = nullptr;

    if(heuristicEnum == HeuristicEnum::HAMMING)
    {
        board = new HammingBoard(0, k, boardArray, nullptr);
    }
    else
    {
        board = new ManhattanBoard(0, k, boardArray, nullptr);
    }

    if(board->IsSolvable())
    {
        AStarSearch *aStarSearch = new AStarSearch(board);

        aStarSearch->ExecuteSearch();

        size_t moveCount = aStarSearch->GetMoveCount();

        std::cout << "Minimum number of moves = " << moveCount << std::endl << std::endl;

        std::vector<Board> solvePath = aStarSearch->GetSolve();

        for(size_t i = 0; i < solvePath.size(); ++i)
        {
            solvePath[i].Print(std::cout);
        }

        delete aStarSearch;
    }
    else
    {
        std::cout << "Unsolvable puzzle" << std::endl;
    }

    delete board;

    return 0;
}