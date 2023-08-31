#include <limits>
#include "learner.hpp"

offline4::decision_tree_node_ptr offline4::learner::get_plurality_value(const std::vector<offline4::sample> &samples)
{
    uint64_t class_count = class_mapper->peek_next_index();
    std::vector<uint64_t> class_instance_count(class_count, 0);
    uint64_t max_class = std::numeric_limits<uint64_t>::max();
    uint64_t max_instance_count = 0;

    for(std::vector<offline4::sample>::const_iterator iterator = samples.begin(); iterator != samples.end(); ++iterator)
    {
        uint64_t count = ++class_instance_count[iterator->get_classification()];

        if(count > max_instance_count)
        {
            max_instance_count = count;
            max_class = iterator->get_classification();
        }
    }

    return std::make_unique<offline4::decision_tree_node, const uint64_t &>(max_class);
}

double_t offline4::learner::get_reminder(uint64_t attribute_index, const std::vector<offline4::sample> &samples) const
{
    uint64_t value_count = (*attribute_value_mappers)[attribute_index].peek_next_index();
    uint64_t class_count = class_mapper->peek_next_index();
    std::vector<uint64_t> value_instance_count(value_count, 0);
    std::vector<std::vector<uint64_t>> value_class_instance_count(value_count, std::vector<uint64_t>(class_count, 0));

    for(std::vector<offline4::sample>::const_iterator iterator = samples.begin(); iterator != samples.end(); ++iterator)
    {
        ++value_instance_count[iterator->get_attribute_value(attribute_index)];
        ++value_class_instance_count[iterator->get_attribute_value(attribute_index)][iterator->get_classification()];
    }

    double_t reminder = 0.0;

    for(size_t i = 0; i < value_count; ++i)
    {
        double_t value_probability = (double_t)value_instance_count[i] / samples.size();
        double_t entropy = 0.0;

        for(size_t j = 0; j < class_count; ++j)
        {
            double_t class_probabilty = (double_t)value_class_instance_count[i][j] / value_instance_count[i];

            if(class_probabilty > 0.0)
            {
                entropy -= class_probabilty * std::log2(class_probabilty);
            }
        }

        reminder += value_probability * entropy;
    }

    return reminder;
}

offline4::decision_tree_node_ptr offline4::learner::learn_helper(const std::vector<offline4::sample> &samples, const std::set<uint64_t> attribute_indices, const std::vector<offline4::sample> &parent_samples)
{
    if(samples.empty())
    {
        return get_plurality_value(parent_samples);
    }
    
    uint64_t classification = samples.front().get_classification();
    bool all_same = true;

    for(std::vector<offline4::sample>::const_iterator iterator = samples.begin() + 1; iterator != samples.end(); ++iterator)
    {
        if(iterator->get_classification() != classification)
        {
            all_same = false;

            break;
        }
    }

    if(all_same)
    {
        return std::make_unique<offline4::decision_tree_node, const uint64_t &>(classification);
    }

    if(attribute_indices.empty())
    {
        return get_plurality_value(samples);
    }

    uint64_t best_attribute = std::numeric_limits<uint64_t>::max(); // assume it never reaches max, so max is null
    double_t min_reminder = std::numeric_limits<double_t>::max();

    for(std::set<uint64_t>::const_iterator iterator = attribute_indices.begin(); iterator != attribute_indices.end(); ++iterator)
    {
        double_t reminder = get_reminder(*iterator, samples);

        if(reminder < min_reminder)
        {
            min_reminder = reminder;
            best_attribute = *iterator;
        }
    }

    offline4::decision_tree_node_ptr tree = std::make_unique<offline4::decision_tree_node, const uint64_t &>(best_attribute);

    for(size_t i = 0; i < (*attribute_value_mappers)[best_attribute].peek_next_index(); ++i) // next index is the current number of indices
    {
        std::vector<offline4::sample> new_samples;

        for(std::vector<offline4::sample>::const_iterator iterator = samples.begin(); iterator != samples.end(); ++iterator)
        {
            if(iterator->get_attribute_value(best_attribute) == i)
            {
                new_samples.push_back(*iterator);
            }
        }

        std::set<uint64_t> new_attribute_set = attribute_indices;

        new_attribute_set.erase(best_attribute);

        offline4::decision_tree_node_ptr subtree = learn_helper(new_samples, new_attribute_set, samples);

        tree->add_child(i, subtree);
    }

    return tree;
}

offline4::learner::learner(const std::vector<offline4::sample> *samples, const std::vector<offline4::token_mapper> *attribute_value_mapper, const offline4::token_mapper *class_mapper)
{
    this->samples = samples;
    this->attribute_value_mappers = attribute_value_mapper;
    this->class_mapper = class_mapper;
    attribute_count = samples->front().get_attribute_count();
}

offline4::decision_tree_node_ptr offline4::learner::learn()
{
    std::set<uint64_t> attribute_indices;

    for(size_t i = 0; i < attribute_count; ++i)
    {
        attribute_indices.insert(i);
    }

    return learn_helper(*samples, attribute_indices, {});
}