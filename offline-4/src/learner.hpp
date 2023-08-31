#ifndef LEARNER_H
#define LEARNER_H

#include <cmath>
#include <vector>
#include <set>
#include <memory>
#include "token_mapper.hpp"
#include "sample.hpp"
#include "decision_tree_node.hpp"

namespace offline4
{
    class learner
    {
    private:
        const std::vector<offline4::sample> *samples;
        const std::vector<offline4::token_mapper> *attribute_value_mappers;
        const offline4::token_mapper *class_mapper;
        uint64_t attribute_count;

        offline4::decision_tree_node_ptr get_plurality_value(const std::vector<offline4::sample> &samples);
        double_t get_reminder(uint64_t attribute_index, const std::vector<offline4::sample> &samples) const;
        offline4::decision_tree_node_ptr learn_helper(const std::vector<offline4::sample> &samples, const std::set<uint64_t> attribute_indices, const std::vector<offline4::sample> &parent_samples);

    public:
        learner(const std::vector<offline4::sample> *samples, const std::vector<offline4::token_mapper> *attribute_mapper, const offline4::token_mapper *class_mapper);
        learner(const offline4::learner &other) = delete;   // would not let it to copy, lol
        offline4::decision_tree_node_ptr learn();
    };
}

#endif