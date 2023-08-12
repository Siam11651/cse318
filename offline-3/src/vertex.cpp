#include "vertex.hpp"
#include "edge.hpp"

offline_3::vertex::vertex(const uint64_t &id)
{
    this->id = id;

    adjacents = new std::map<uint64_t, int64_t>();
}

uint64_t offline_3::vertex::get_id() const
{
    return id;
}

void offline_3::vertex::insert_adjacent(const uint64_t &id, const int64_t &weight) const
{
    adjacents->insert({id, weight});
}

int64_t offline_3::vertex::get_weight(const uint64_t &id) const
{
    std::map<uint64_t, int64_t>::const_iterator adjacent_iterator = adjacents->find(id);

    if(adjacent_iterator == adjacents->end())
    {
        return 0;
    }

    return adjacent_iterator->second;
}

offline_3::edge offline_3::vertex::get_heaviest_adjacent() const
{
    int64_t max_weight = INT64_MIN;
    uint64_t heaviest_adjacent = 0;

    for(std::map<uint64_t, int64_t>::const_iterator iterator = adjacents->begin(); iterator != adjacents->end(); ++iterator)
    {
        if(iterator->second > max_weight)
        {
            max_weight = iterator->second;
            heaviest_adjacent = iterator->first;
        }
    }

    return offline_3::edge(id, heaviest_adjacent, max_weight);
}

offline_3::edge offline_3::vertex::get_lightest_adjacent() const
{
    int64_t min_weight = INT64_MAX;
    uint64_t lightest_adjacent = 0;

    for(std::map<uint64_t, int64_t>::const_iterator iterator = adjacents->begin(); iterator != adjacents->end(); ++iterator)
    {
        if(iterator->second < min_weight)
        {
            min_weight = iterator->second;
            lightest_adjacent = iterator->first;
        }
    }

    return offline_3::edge(id, lightest_adjacent, min_weight);
}

bool offline_3::vertex::has_adjacent(const uint64_t &id) const
{
    if(adjacents->find(id) == adjacents->end())
    {
        return false;
    }

    return true;
}

std::vector<offline_3::edge> offline_3::vertex::get_restricted_adjacent_list(const int64_t &mu) const
{
    std::vector<offline_3::edge> ral;

    for(std::map<uint64_t, int64_t>::const_iterator iterator = adjacents->begin(); iterator != adjacents->end(); ++iterator)
    {
        if(iterator->second >= mu)
        {
            ral.push_back(offline_3::edge(id, iterator->first, iterator->second));
        }
    }

    return ral;
}

bool offline_3::vertex::operator < (const offline_3::vertex &other) const
{
    return id < other.id;
}