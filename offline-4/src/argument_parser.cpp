#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "argument_parser.hpp"

std::map<std::string, std::function<void(const std::string &)>> offline4::argument_parser::value_setters =
{
    {
        "iteration-count",
        [](const std::string &value)
        {
            try
            {
                iteration_count = std::stoi(value);
            }
            catch(const std::exception &exception)
            {
                std::cerr << "Cannot parse argument value" << std::endl;
                std::cerr << help_command << std::endl;
            }
        }
    },
    {
        "dataset-path",
        [](const std::string &value)
        {
            dataset_path = value;
        }
    }
};
std::map<std::string, std::function<void()>> offline4::argument_parser::flag_setters =
{
    {
        "help",
        []()
        {
            show_help = true;
        }
    }
};
bool offline4::argument_parser::show_help = false;
uint64_t offline4::argument_parser::iteration_count = offline4::argument_parser::DEFAULT_ITERATION_COUNT;
std::string offline4::argument_parser::dataset_path = "";
std::string offline4::argument_parser::program_name;
std::string offline4::argument_parser::help_command;

void offline4::argument_parser::set_value(const std::string &name, const std::string &value)
{
    try
    {
        value_setters.at(name)(value);
    }
    catch(const std::out_of_range &exception)
    {
        std::cerr << "Error: No such argument" << std::endl;
        std::cerr << help_command << std::endl;
    }
}

void offline4::argument_parser::set_flag(const std::string &name)
{
    try
    {
        flag_setters.at(name)();
    }
    catch(const std::out_of_range &exception)
    {
        std::cerr << "Error: No such flag" << std::endl;
        std::cerr << help_command << std::endl;
    }
}

bool offline4::argument_parser::parse(uint64_t argument_count, char **argument_values)
{
    program_name = std::string(argument_values[0]);
    help_command = "To learn more \"" + program_name + " --help\"";
    std::vector<std::string> arguments(argument_values + 1, argument_values + argument_count);

    for(std::vector<std::string>::const_iterator iterator = arguments.begin(); iterator != arguments.end(); ++iterator)
    {
        if(iterator->substr(0, 2) != "--")
        {
            std::cerr << "Error: Invalid argument \"" << *iterator << "\"" << std::endl;
            std::cerr << help_command << std::endl;

            return false;
        }

        size_t split_position;

        if((split_position = iterator->find_first_of('=')) == std::string::npos)
        {
            std::string flag_name = iterator->substr(2);

            set_flag(flag_name);
        }
        else
        {
            std::string argument_name = iterator->substr(2, split_position - 2);
            std::string argument_value = iterator->substr(split_position + 1);

            set_value(argument_name, argument_value);
        }
    }

    return true;
}

void offline4::argument_parser::print_help()
{
    std::cout << "Usage: " << program_name << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "--iterator-count\tSet number of learn iterations (default=" << offline4::argument_parser::DEFAULT_ITERATION_COUNT << ")" << std::endl;
    std::cout << "--dataset-path\t\tSet path to dataset" << std::endl;
    std::cout << "--help\t\t\tShow this message" << std::endl;
}

bool offline4::argument_parser::show_help_set()
{
    return show_help;
}

uint64_t offline4::argument_parser::get_iteraion_count()
{
    return iteration_count;
}

std::string offline4::argument_parser::get_dataset_path()
{
    return dataset_path;
}