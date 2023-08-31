#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <random>
#include <algorithm>
#include "token_mapper.hpp"
#include "sample.hpp"
#include "learner.hpp"
#include "classifier.hpp"

std::vector<std::string> string_spilt(const std::string &string, const std::string &delimiter)
{
    std::string temp_string = string;
    size_t pos = 0;
    std::vector<std::string> to_return;

    while((pos = temp_string.find(delimiter)) != std::string::npos)
    {
        std::string token = temp_string.substr(0, pos);

        to_return.push_back(token);
        temp_string.erase(0, pos + delimiter.length());
    }

    to_return.push_back(temp_string);

    return to_return;
}

int main(int argc, char **argv)
{
    std::random_device random_device_engine;
    std::ifstream learn_data_file(argv[1]);
    offline4::token_mapper class_mapper({"unacc", "acc", "good", "vgood"});
    std::vector<offline4::token_mapper> attribute_value_mappers
    {
        offline4::token_mapper({"vhigh", "high", "med", "low"}),
        offline4::token_mapper({"vhigh", "high", "med", "low"}),
        offline4::token_mapper({"2", "3", "4", "5more"}),
        offline4::token_mapper({"2", "4", "more"}),
        offline4::token_mapper({"small", "med", "big"}),
        offline4::token_mapper({"low", "med", "high"}),
    };
    std::vector<offline4::sample> dataset_samples;

    while(learn_data_file.peek() != EOF)
    {
        std::string line;

        std::getline(learn_data_file, line);

        std::vector<std::string> tokens = string_spilt(line, ",");
        std::vector<uint64_t> attribute_indices(6);
        uint64_t class_index = class_mapper.get_index(tokens[6]);

        for(size_t i = 0; i < attribute_indices.size(); ++i)
        {
            attribute_indices[i] = attribute_value_mappers[i].get_index(tokens[i]);
        }

        dataset_samples.push_back(offline4::sample(attribute_indices, class_index));
    }

    for(size_t i = 0; i < 10000; ++i)
    {
        std::vector<offline4::sample> shuffled_dataset_samples(dataset_samples);
        std::vector<offline4::sample> learn_dataset;
        std::vector<offline4::sample> test_dataset;
        
        std::shuffle(shuffled_dataset_samples.begin(), shuffled_dataset_samples.end(), random_device_engine);

        uint64_t learn_sample_count = 0.8 * shuffled_dataset_samples.size();

        for(size_t i = 0; i < learn_sample_count; ++i)
        {
            learn_dataset.push_back(shuffled_dataset_samples[i]);
        }

        for(size_t i = learn_sample_count; i < shuffled_dataset_samples.size(); ++i)
        {
            test_dataset.push_back(shuffled_dataset_samples[i]);
        }

        offline4::learner learner(&learn_dataset, &attribute_value_mappers, &class_mapper);
        offline4::decision_tree_node_ptr tree_root = learner.learn();
        uint64_t matched_count = 0;
        
        for(size_t i = 0; i < test_dataset.size(); ++i)
        {
            offline4::classifier classifier(&test_dataset[i], &attribute_value_mappers, &class_mapper, tree_root.get());
            uint64_t classification = classifier.classify();

            if(classification == test_dataset[i].get_classification())
            {
                ++matched_count;
            }
        }

        std::cout << (matched_count * 100.0) / test_dataset.size() << std::endl;
    }

    return 0;
}