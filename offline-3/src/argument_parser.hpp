#pragma once

#include <cstdint>
#include <utility>
#include <string>

namespace offline_3
{
    class argument_parser
    {
    private:
        static bool show_help;
        static std::string program_name;
        static std::string help_command;

        static void set_value(const std::string &name, const std::string &value);
        static void set_flag(const std::string &name);

    public:
        static bool show_help_set();
        static void print_help();
        static void parse(uint64_t argument_count, char **argument_values);
    };
}