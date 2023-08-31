#ifndef TOKEN_MAPPER_H
#define TOKEN_MAPPER_H

#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace offline4
{
    class token_mapper
    {
    private:
        uint64_t next_index;
        std::map<std::string, uint64_t> token_to_index_map;
        std::vector<std::string> index_to_token_map;

    public:
        token_mapper(const std::vector<std::string> &initial_tokens = {});
        uint64_t get_index(const std::string &token);
        std::string get_token(const uint64_t &index);
        uint64_t peek_next_index() const;
    };
}

#endif