#include <iostream>
#include "vertex.hpp"
#include "graph.hpp"
#include "edge.hpp"
#include "maxcut_solver.hpp"

int main()
{
    size_t n, m;

    offline_3::graph graph(3);

    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 3, 1);
    graph.add_edge(3, 1, 1);

    graph.clear();

    return 0;
}
