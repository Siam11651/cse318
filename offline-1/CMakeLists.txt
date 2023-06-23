cmake_minimum_required(VERSION 3.0.0)
project(offline-1 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(offline-1 
    "src/main.cpp"
    "src/AStarSearch.cpp"
    "src/Board.cpp"
    "src/BoardComparator.cpp"
    "src/HammingBoard.cpp"
    "src/ManhattanBoard.cpp"
    "src/OutOfCellException.cpp"
)
