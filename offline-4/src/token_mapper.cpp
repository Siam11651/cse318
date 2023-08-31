#include "token_mapper.hpp"

offline4::token_mapper::token_mapper()
{
    next_index = 0;
}

uint64_t offline4::token_mapper::get_index(const std::string &token)
{
    uint64_t to_return = 0;

    if(token_to_index_map.find(token) == token_to_index_map.end())
    {
        token_to_index_map[token] = next_index;
        to_return = next_index;
        ++next_index;

        index_to_token_map.push_back(token);
    }
    else
    {
        to_return = token_to_index_map[token];
    }

    return to_return;
}

std::string offline4::token_mapper::get_token(const uint64_t &index)
{
    return index_to_token_map[index];
}

uint64_t offline4::token_mapper::peek_next_index() const
{
    return next_index;
}