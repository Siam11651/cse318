cmake_minimum_required(VERSION 3.20)
project(offline-4)

set(CXX_STANDARD 11)

add_executable(offline-4
    "src/argument_parser.cpp"
    "src/classifier.cpp"
    "src/decision_tree_node.cpp"
    "src/learner.cpp"
    "src/main.cpp"
    "src/sample.cpp"
    "src/token_mapper.cpp"
)
