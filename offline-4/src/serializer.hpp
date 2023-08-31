#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>
#include <stack>
#include "decision_tree_node.hpp"
#include "token_mapper.hpp"

namespace offline4
{
    class serializer
    {
    private:
        const offline4::decision_tree_node *root;
        std::ostream *ostream;
        std::vector<offline4::token_mapper> attribute_value_mappers;
        offline4::token_mapper attribute_mapper;
        offline4::token_mapper class_mapper;

        void serialize_helper(const uint64_t &attribute_index, const uint64_t &attribute_value_index, const offline4::decision_tree_node *root);

    public:
        serializer(const decision_tree_node &root, const offline4::token_mapper &attribute_mapper, const std::vector<offline4::token_mapper> &attribute_value_mappers, const offline4::token_mapper &class_mapper, std::ostream &ostream = std::cout);
        void serialize();
    };
}

#endif