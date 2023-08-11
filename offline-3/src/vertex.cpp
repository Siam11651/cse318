#include "vertex.hpp"

offline_3::vertex::vertex(const uint64_t &id)
{
    set_id(id);

    adjacents = std::make_shared<std::map<offline_3::vertex, int64_t>>();
}

void offline_3::vertex::set_id(const uint64_t &id)
{
    this->id = id;
}

uint64_t offline_3::vertex::get_id() const
{
    return id;
}

void offline_3::vertex::insert_adjacent(const offline_3::vertex &vertex, const int64_t &weight) const
{
    adjacents->insert({vertex, weight});
}

int64_t offline_3::vertex::get_weight(const uint64_t &id) const
{
    std::map<offline_3::vertex, int64_t>::iterator adjacent_iterator = adjacents->find(offline_3::vertex(id));

    if(adjacent_iterator == adjacents->end())
    {
        return 0;
    }

    return adjacent_iterator->second;
}

std::pair<offline_3::vertex, int64_t> offline_3::vertex::get_heaviest_adjacent() const
{
    int64_t max_weight = INT64_MIN;
    offline_3::vertex heaviest_adjacent = offline_3::vertex(0);

    for(std::map<offline_3::vertex, int64_t>::iterator iterator = adjacents->begin(); iterator != adjacents->end(); ++iterator)
    {
        if(iterator->second > max_weight)
        {
            max_weight = iterator->second;
            heaviest_adjacent = iterator->first;
        }
    }

    return {heaviest_adjacent, max_weight};
}

std::pair<offline_3::vertex, int64_t> offline_3::vertex::get_lightest_adjacent() const
{
    int64_t min_weight = INT64_MAX;
    offline_3::vertex lightest_adjacent = offline_3::vertex(0);

    for(std::map<offline_3::vertex, int64_t>::iterator iterator = adjacents->begin(); iterator != adjacents->end(); ++iterator)
    {
        if(iterator->second < min_weight)
        {
            min_weight = iterator->second;
            lightest_adjacent = iterator->first;
        }
    }

    return {lightest_adjacent, min_weight};
}

bool offline_3::vertex::has_adjacent(const uint64_t &id) const
{
    if(adjacents->find(offline_3::vertex(id)) == adjacents->end())
    {
        return false;
    }

    return true;
}

std::shared_ptr<std::vector<std::pair<offline_3::vertex, int64_t>>> offline_3::vertex::get_restricted_adjacent_list(const int64_t &mu) const
{
    std::shared_ptr<std::vector<std::pair<offline_3::vertex, int64_t>>> ral = std::make_shared<std::vector<std::pair<offline_3::vertex, int64_t>>>();

    for(std::map<offline_3::vertex, int64_t>::iterator iterator = adjacents->begin(); iterator != adjacents->end(); ++iterator)
    {
        if(iterator->second >= mu)
        {
            ral->push_back(*iterator);
        }
    }

    return ral;
}

bool offline_3::vertex::operator < (const offline_3::vertex &other) const
{
    return id < other.id;
}