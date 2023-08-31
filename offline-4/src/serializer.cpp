#include "serializer.hpp"

void offline4::serializer::serialize_helper(const uint64_t &attribute_index, const uint64_t &attribute_value_index, const offline4::decision_tree_node *root)
{
    *ostream << attribute_value_mappers[attribute_index].get_token(attribute_value_index) << " " << attribute_mapper.get_token(root->get_attribute_index()) << std::endl;

    std::vector<std::pair<uint64_t, offline4::decision_tree_node>> &children = root->get_children();

    for(std::vector<std::pair<uint64_t, offline4::decision_tree_node>>::const_iterator iterator = children.begin(); iterator != children.end(); ++iterator)
    {
        *ostream << ">" << std::endl;

        serialize_helper(root->get_attribute_index(), iterator->first, &iterator->second);
    }

    *ostream << "<" << std::endl;
}

offline4::serializer::serializer(const decision_tree_node &root, const offline4::token_mapper &attribute_mapper, const std::vector<offline4::token_mapper> &attribute_value_mappers, const offline4::token_mapper &class_mapper, std::ostream &ostream)
{
    this->root = &root;
    this->ostream = &ostream;
    this->attribute_mapper = attribute_mapper;
    this->attribute_value_mappers = attribute_value_mappers;
    this->class_mapper = class_mapper;
}

void offline4::serializer::serialize()
{
    *ostream << attribute_mapper.get_token(root->get_attribute_index()) << std::endl;

    std::vector<std::pair<uint64_t, offline4::decision_tree_node>> &children = root->get_children();

    for(std::vector<std::pair<uint64_t, offline4::decision_tree_node>>::const_iterator iterator = children.begin(); iterator != children.end(); ++iterator)
    {
        *ostream << ">" << std::endl;


    }
}