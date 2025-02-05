/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Parser
*/

#include "Parser.hpp"

plazza::Parser::Parser()
{
    _pizza_sizes = {"S", "M", "L", "XL", "XXL"};
    _pizza_types = {"regina", "margarita", "americana", "fantasia"};
}

plazza::Parser::~Parser()
{
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::array<std::string, 3> plazza::Parser::parse_command(std::string command) {
    std::array<std::string, 3> parsed_command;
    std::istringstream stream(trim(command));
    std::string token;
    int i = 0;

    while (i < 3 && std::getline(stream, token, ' ')) {
        parsed_command[i] = trim(token);
        i++;
    }
    if (std::getline(stream, token, ' ') || i < 3) {
        return {"", "", ""};
    }
    return parsed_command;
}

bool plazza::Parser::check_command(std::array<std::string, 3> command) {
    if (command[0].empty() || command[1].empty() || command[2].empty())
        return false;
    if (std::find(_pizza_sizes.begin(), _pizza_sizes.end(), command[1]) == _pizza_sizes.end())
        return false;
    if (std::all_of(command[2].begin() + 1, command[2].end(), ::isdigit) == false ||
        command[2].size() < 2 || std::stoi(command[2].substr(1)) <= 0 || command[2][0] != 'x' || command[2][1] == '0')
        return false;
    if (std::find(_pizza_types.begin(), _pizza_types.end(), command[0]) == _pizza_types.end())
        return false;
    return true;
}

std::array<int, 3> plazza::Parser::getCommandParse(std::array<std::string, 3> command) {
    std::array<int, 3> parsed_command;
    std::map<std::string, enum plazza::PizzaType> pizza_types = {
        {"regina", plazza::PizzaType::Regina},
        {"margarita", plazza::PizzaType::Margarita},
        {"americana", plazza::PizzaType::Americana},
        {"fantasia", plazza::PizzaType::Fantasia}
    };

    std::map<std::string, enum plazza::PizzaSize> pizza_sizes = {
        {"S", plazza::PizzaSize::S},
        {"M", plazza::PizzaSize::M},
        {"L", plazza::PizzaSize::L},
        {"XL", plazza::PizzaSize::XL},
        {"XXL", plazza::PizzaSize::XXL}
    };

    parsed_command[0] = pizza_types[command[0]];
    parsed_command[1] = pizza_sizes[command[1]];
    parsed_command[2] = std::stoi(command[2].substr(1));
    return parsed_command;
}

std::vector<std::array<int, 3>> plazza::Parser::parse(std::string input) {
    std::vector<std::array<int, 3>> commands;
    std::array<std::string, 3> command;
    std::string token;
    std::istringstream stream(input);

    while (std::getline(stream, token, ';')) {
        command = parse_command(token);
        if (check_command(command))
            commands.push_back(getCommandParse(command));
        else
            std::cerr << "Invalid command" << std::endl;
    }
    return commands;
}