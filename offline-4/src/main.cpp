#include <iostream>
#include <fstream>
#include <array>
#include <vector>
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
    std::ifstream learn_data_file(argv[1]);
    offline4::token_mapper class_mapper({"unacc", "acc", "good", "vgood"});
    std::vector<offline4::token_mapper> attribute_value_mapper
    {
        offline4::token_mapper({"vhigh", "high", "med", "low"}),
        offline4::token_mapper({"vhigh", "high", "med", "low"}),
        offline4::token_mapper({"2", "3", "4", "5more"}),
        offline4::token_mapper({"2", "4", "more"}),
        offline4::token_mapper({"small", "med", "big"}),
        offline4::token_mapper({"low", "med", "high"}),
    };
    std::vector<offline4::sample> samples;

    while(learn_data_file.peek() != EOF)
    {
        std::string line;

        std::getline(learn_data_file, line);

        std::vector<std::string> tokens = string_spilt(line, ",");
        std::vector<uint64_t> attribute_indices(6);
        uint64_t class_index = class_mapper.get_index(tokens[6]);

        for(size_t i = 0; i < attribute_indices.size(); ++i)
        {
            attribute_indices[i] = attribute_value_mapper[i].get_index(tokens[i]);
        }

        samples.push_back(offline4::sample(attribute_indices, class_index));
    }

    learn_data_file.close();

    offline4::learner learner(&samples, &attribute_value_mapper, &class_mapper);
    offline4::decision_tree_node *root = learner.learn();
    std::ifstream test_data_file(argv[2]);

    while(test_data_file.peek() != EOF)
    {
        std::string line;

        std::getline(test_data_file, line);

        std::vector<std::string> tokens = string_spilt(line, ",");
        std::vector<uint64_t> attribute_indices(6);
        uint64_t class_index = class_mapper.get_index(tokens[6]);

        for(size_t i = 0; i < attribute_indices.size(); ++i)
        {
            attribute_indices[i] = attribute_value_mapper[i].get_index(tokens[i]);
        }

        offline4::sample sample(attribute_indices, class_index);
        offline4::classifier classifier(&sample, &attribute_value_mapper, &class_mapper, root);

        std::cout << classifier.classify() << std::endl;
    }

    return 0;
}