#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <cstdint>
#include <utility>
#include <string>
#include <map>
#include <functional>

namespace offline4
{
    class argument_parser
    {
    private:
        static constexpr uint64_t DEFAULT_ITERATION_COUNT = 20;
        static std::map<std::string, std::function<void(const std::string &)>> value_setters;
        static std::map<std::string, std::function<void()>> flag_setters;
        static bool show_help;
        static uint64_t iteration_count;
        static std::string dataset_path;
        static std::string program_name;
        static std::string help_command;

        static void set_value(const std::string &name, const std::string &value);
        static void set_flag(const std::string &name);

    public:
        static bool show_help_set();
        static void print_help();
        static bool parse(uint64_t argument_count, char **argument_values);
        static uint64_t get_iteraion_count();
        static std::string get_dataset_path();
    };
}

#endif