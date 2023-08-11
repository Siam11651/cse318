#include "graph.hpp"
#include "vertex.hpp"

offline_3::graph::graph(const uint64_t &initial_size)
{
    for(size_t i = 1; i <= initial_size; ++i)
    {
        add_vertex(i);
    }
}

bool offline_3::graph::add_vertex(const uint64_t &id)
{
    offline_3::vertex new_vertex(id);

    if(vertices.find(new_vertex) != vertices.end())
    {
        return false;
    }

    vertices.insert(new_vertex);

    return true;
}

bool offline_3::graph::add_edge(const uint64_t &from, const uint64_t &to, const int64_t &weight)
{
    std::set<offline_3::vertex>::iterator from_iterator = vertices.find(offline_3::vertex(from));
    std::set<offline_3::vertex>::iterator to_iterator = vertices.find(offline_3::vertex(to));

    if(from_iterator == vertices.end() || to_iterator == vertices.end())
    {
        return false;
    }

    if(from_iterator->has_adjacent(to))
    {
        return false;
    }

    from_iterator->insert_adjacent(*to_iterator, weight);

    return true;
}

offline_3::vertex offline_3::graph::get_vertex(const uint64_t &id) const
{
    std::set<offline_3::vertex>::iterator vertex_iterator = vertices.find(offline_3::vertex(id));

    if(vertex_iterator == vertices.end())
    {
        return offline_3::vertex(0);
    }

    return *vertex_iterator;
}

offline_3::edge offline_3::graph::get_heaviest_edge() const
{
    int64_t max_weight = INT64_MIN;
    std::pair<offline_3::vertex, offline_3::vertex> heaviest_edge = {offline_3::vertex(0), offline_3::vertex(0)};

    for(std::set<offline_3::vertex>::iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        std::pair<offline_3::vertex, int64_t> heaviest_adjacent = iterator->get_heaviest_adjacent();

        if(heaviest_adjacent.second > max_weight)
        {
            max_weight = heaviest_adjacent.second;
            heaviest_edge = {*iterator, heaviest_adjacent.first};
        }
    }

    return offline_3::edge(heaviest_edge.first, heaviest_edge.second, max_weight);
}

offline_3::edge offline_3::graph::get_lightest_edge() const
{
    int64_t min_weight = INT64_MAX;
    std::pair<offline_3::vertex, offline_3::vertex> lightest_edge = {offline_3::vertex(0), offline_3::vertex(0)};

    for(std::set<offline_3::vertex>::iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        std::pair<offline_3::vertex, int64_t> lightest_adjacent = iterator->get_lightest_adjacent();

        if(lightest_adjacent.second < min_weight)
        {
            min_weight = lightest_adjacent.second;
            lightest_edge = {*iterator, lightest_adjacent.first};
        }
    }

    return offline_3::edge(lightest_edge.first, lightest_edge.second, min_weight);
}

std::shared_ptr<std::vector<offline_3::edge>> offline_3::graph::get_restricted_candidate_list(const int64_t &mu) const
{
    std::shared_ptr<std::vector<offline_3::edge>> rcl = std::make_shared<std::vector<offline_3::edge>>();

    for(std::set<offline_3::vertex>::iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        std::shared_ptr<std::vector<std::pair<offline_3::vertex, int64_t>>> ral = iterator->get_restricted_adjacent_list(mu);

        for(size_t i = 0; i < ral->size(); ++i)
        {
            if((*ral)[i].second <= mu)
            {
                offline_3::edge new_edge(*iterator, (*ral)[i].first, (*ral)[i].second);

                rcl->push_back(new_edge);
            }
        }
    }

    return rcl;
}

void offline_3::graph::clear()
{
    vertices.clear();
}