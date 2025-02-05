/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Parser
*/

#ifndef PARSER_HPP_
    #define PARSER_HPP_

    #include "IPizza.hpp"

    #include <iostream>
    #include <vector>
    #include <array>
    #include <sstream>
    #include <string>
    #include <algorithm>
    #include <cctype>

namespace plazza {
    class Parser {
        public:
            Parser();
            ~Parser();
            std::array<std::string, 3> parse_command(std::string command);
            std::vector<std::array<int, 3>> parse(std::string input);
            bool check_command(std::array<std::string, 3> command);
            std::array<int, 3> getCommandParse(std::array<std::string, 3> command);

        protected:
        private:
            std::vector<std::array<std::string, 3>> _commands;
            std::array<std::string, 5> _pizza_sizes;
            std::array<std::string, 4> _pizza_types;
    };
}

#endif /* !PARSER_HPP_ */
