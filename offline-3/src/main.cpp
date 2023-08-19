#include <iostream>
#include <fstream>
#include "graph.hpp"
#include "edge.hpp"
#include "maxcut_solver.hpp"
#include "argument_parser.hpp"

int main(int arguments_count, char **arguments_value)
{
    offline_3::argument_parser::parse(arguments_count, arguments_value);

    if(offline_3::argument_parser::show_help_set())
    {
        offline_3::argument_parser::print_help();

        return 0;
    }

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
    }

    std::tuple<int64_t, int64_t, uint64_t> maxcut_solve = offline_3::maxcut_solver::get_maxcut(graph);

    std::cout << std::get<0>(maxcut_solve) << " " << std::get<1>(maxcut_solve) << " " << std::get<2>(maxcut_solve) << std::endl;

    return 0;
}
