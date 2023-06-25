cmake_minimum_required(VERSION 3.0.0)
project(offline-2 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(offline-2
    "src/main.cpp"
    "src/Bowl.cpp"
    "src/BigBowl.cpp"
    "src/MancalaState.cpp"
    "src/HeuristicData.cpp"
    "src/Window.cpp"
    "src/HumanVsAiWindow.cpp"
    "src/AiVsAiWindow.cpp"
    "src/HumanVsAiGameWindow.cpp"
    "src/AiVsAiGameWindow.cpp"
    "src/State.cpp"
    "src/HumanVsAiStartState.cpp"
    "src/AiVsAiStartState.cpp"
    "src/HumanState.cpp"
    "src/AiState.cpp"
)