#include <iostream>
#include "HammingBoard.hpp"

int main()
{
    size_t k;

    std::cin >> k;

    uint64_t **boardArray = new uint64_t *[k];

    for(size_t i = 0; i < k; ++i)
    {
        boardArray[i] = new uint64_t[k];

        for(size_t j = 0; j < k; ++j)
        {
            std::cin >> boardArray[i][j];
        }
    }

    HammingBoard *hammingBoard = new HammingBoard(0, k, boardArray, nullptr);

    std::cout << hammingBoard->IsSolvable() << std::endl << std::endl;

    return 0;
}