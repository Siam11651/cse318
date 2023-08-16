#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "argument_parser.hpp"
#include "maxcut_solver.hpp"

bool offline_3::argument_parser::show_help = false;
std::string offline_3::argument_parser::program_name;
std::string offline_3::argument_parser::help_command;

void offline_3::argument_parser::set_value(const std::string &name, const std::string &value)
{
    if(name == "iteration-count")
    {
        try
        {
            uint64_t iteration_count = std::stoi(value);

            offline_3::maxcut_solver::set_iteration_count(iteration_count);
        }
        catch(const std::exception &exception)
        {
            std::cerr << "Cannot parse argument value" << std::endl;
            std::cerr << help_command << std::endl;
        }
    }
    else
    {
        std::cerr << "No such argument" << std::endl;
        std::cerr << help_command << std::endl;
    }
}


void offline_3::argument_parser::set_flag(const std::string &name)
{
    if(name == "semi-greedy")
    {
        offline_3::maxcut_solver::set_semi_greedy(true);
    }
    else
    {
        std::cerr << "No such flag" << std::endl;
        std::cerr << help_command << std::endl;
    }
}

void offline_3::argument_parser::parse(uint64_t argument_count, char **argument_values)
{
    program_name = std::string(argument_values[0]);
    help_command = "To learn more \"" + program_name + " --help\"";
    std::vector<std::string> arguments(argument_values + 1, argument_values + argument_count);

    for(std::vector<std::string>::const_iterator iterator = arguments.begin(); iterator != arguments.end(); ++iterator)
    {   
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
}

bool offline_3::argument_parser::show_help_set()
{
    return show_help;
}