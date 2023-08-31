#include <fstream>
#include <array>
#include <vector>
#include "token_mapper.hpp"
#include "sample.hpp"
#include "learner.hpp"

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
    offline4::token_mapper class_mapper;
    offline4::token_mapper attribute_mapper;
    std::vector<offline4::token_mapper> attribute_value_mapper(6, offline4::token_mapper());
    std::vector<offline4::sample> samples;

    attribute_mapper.get_index("buying");
    attribute_mapper.get_index("maint");
    attribute_mapper.get_index("doors");
    attribute_mapper.get_index("persons");
    attribute_mapper.get_index("lug_boot");
    attribute_mapper.get_index("safety");

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

    offline4::learner learner(samples, attribute_value_mapper, class_mapper);

    learner.learn();

    return 0;
}