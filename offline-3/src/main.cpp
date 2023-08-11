#include <iostream>
#include "vertex.hpp"
#include "graph.hpp"
#include "edge.hpp"
#include "maxcut_solver.hpp"

int main()
{
    size_t n, m;

    offline_3::graph graph(4);

    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 3, 2);
    graph.add_edge(4, 3, 3);
    graph.add_edge(1, 4, 4);

    offline_3::edge heaviest = graph.get_heaviest_edge();
    offline_3::edge lightest = graph.get_lightest_edge();

    std::cout << heaviest.get_from().get_id() << " " << heaviest.get_to().get_id() << " " << heaviest.get_weight() << std::endl;
    std::cout << lightest.get_from().get_id() << " " << lightest.get_to().get_id() << " " << lightest.get_weight() << std::endl;

    graph.clear();

    return 0;
}
