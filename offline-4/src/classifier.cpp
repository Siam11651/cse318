#include "classifier.hpp"

offline4::classifier::classifier(const offline4::sample *sample, const std::vector<offline4::token_mapper> *attribute_value_mappers, const offline4::token_mapper *class_mapper, const offline4::decision_tree_node *tree_root)
{
    this->sample = sample;
    this->attribute_mappers = attribute_value_mappers;
    this->class_mapper = class_mapper;
    this->tree_root = tree_root;
}

uint64_t offline4::classifier::classify() const
{
    const offline4::decision_tree_node *current_node = tree_root;

    while(true)
    {
        if(current_node->get_child_count())
        {
            current_node = current_node->get_child(sample->get_attribute_value(current_node->get_attribute_index())).get();
        }
        else
        {
            return current_node->get_attribute_index();
        }
    }
}