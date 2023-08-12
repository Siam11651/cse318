#include <iostream>
#include "vertex.hpp"
#include "graph.hpp"
#include "edge.hpp"
#include "maxcut_solver.hpp"

int main()
{
    offline_3::graph graph(3);

    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 1, 1);
    graph.add_edge(2, 3, 2);
    graph.add_edge(3, 2, 2);
    graph.add_edge(3, 1, 3);
    graph.add_edge(1, 3, 3);

    offline_3::maxcut maxcut = offline_3::maxcut_solver::get_maxcut(graph);

    std::cout << offline_3::maxcut_solver::get_cut_weight(graph, maxcut.first, maxcut.second) << std::endl;

    return 0;
}
