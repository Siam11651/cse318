#ifndef DECISION_TREE_NODE_H
#define DECISION_TREE_NODE_H

#include <cstdint>
#include <utility>
#include <map>

namespace offline4
{
    class decision_tree_node
    {
    private:
        uint64_t attribute_index;
        std::map<uint64_t, offline4::decision_tree_node *> children;

    public:
        decision_tree_node(const uint64_t &attribute_index);
        void add_child(const uint64_t &value, offline4::decision_tree_node *child_node);
        uint64_t get_attribute_index() const;
        offline4::decision_tree_node *get_child(const uint64_t &value) const;
        uint64_t get_child_count() const;
    };
}

#endif