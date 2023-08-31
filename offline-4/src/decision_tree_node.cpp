#include "decision_tree_node.hpp"

offline4::decision_tree_node::decision_tree_node(const uint64_t &attribute_index)
{
    this->attribute_index = attribute_index;
}

void offline4::decision_tree_node::add_child(const uint64_t &value, const offline4::decision_tree_node &child_node)
{
    children.push_back({value, child_node});
}

uint64_t offline4::decision_tree_node::get_attribute_index() const
{
    return attribute_index;
}

const std::vector<std::pair<uint64_t, offline4::decision_tree_node>> &offline4::decision_tree_node::get_children() const
{
    return children;
}