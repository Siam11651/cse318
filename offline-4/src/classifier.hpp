#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "sample.hpp"
#include "token_mapper.hpp"
#include "decision_tree_node.hpp"

namespace offline4
{
    class classifier
    {
    private:
        const offline4::sample *sample;
        const std::vector<offline4::token_mapper> *attribute_mappers;
        const offline4::token_mapper *class_mapper;
        const offline4::decision_tree_node *tree_root;

    public:
        classifier(const offline4::sample *sample, const std::vector<offline4::token_mapper> *attribute_value_mappers, const offline4::token_mapper *class_mapper, const offline4::decision_tree_node *tree_root);
        classifier(const offline4::classifier &other) = delete;
        uint64_t classify() const;
    };
}

#endif