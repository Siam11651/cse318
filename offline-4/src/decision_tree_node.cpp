#include "decision_tree_node.hpp"

offline4::decision_tree_node::decision_tree_node(const uint64_t &attribute_index)
{
    this->attribute_index = attribute_index;
}

void offline4::decision_tree_node::add_child(const uint64_t &value, offline4::decision_tree_node_ptr &child_node)
{
    children[value] = std::move(child_node);
}

uint64_t offline4::decision_tree_node::get_attribute_index() const
{
    return attribute_index;
}

const offline4::decision_tree_node_ptr &offline4::decision_tree_node::get_child(const uint64_t &value) const
{
    return children.at(value);
}

uint64_t offline4::decision_tree_node::get_child_count() const
{
    return children.size();
}