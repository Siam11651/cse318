#include <iostream>
#include "vertex.hpp"
#include "graph.hpp"
#include "edge.hpp"
#include "maxcut_solver.hpp"

int main()
{
    size_t vertices_count, edges_count;

    std::cin >> vertices_count >> edges_count;

    offline_3::graph graph(vertices_count);

    for(size_t i = 0; i < edges_count; ++i)
    {
        uint64_t from;
        uint64_t to;
        int64_t weight;

        std::cin >> from >> to >> weight;

        graph.add_edge(from, to, weight);
        graph.add_edge(to, from, weight);
    }

    offline_3::maxcut maxcut = offline_3::maxcut_solver::get_maxcut(graph);

    std::cout << offline_3::maxcut_solver::get_cut_weight(graph, maxcut.first, maxcut.second) << std::endl;

    return 0;
}
