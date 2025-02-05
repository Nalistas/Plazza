/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** main
*/

#include "Reception.hpp"

int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: ./plazza [time_modifier] [nb_cooks] [time_refill]" << std::endl;
        return 84;
    }
    try {
        double value = std::stod(av[1]);
        int value2 = std::stoi(av[2]);
        int value3 = std::stoi(av[3]);
        if (std::string(av[2]).find('.') != std::string::npos || std::string(av[3]).find('.') != std::string::npos) {
            std::cerr << "Error: invalid argument, nb_cooks and time_refill must be integers" << std::endl;
            return 84;
        }
        if (value <= 0 || value2 <= 0 || value3 <= 0) {
            std::cerr << "Error: invalid argument, values must be non-negative" << std::endl;
            return 84;
        }
    } catch (const std::invalid_argument&) {
        std::cerr << "Error: invalid argument, not a number" << std::endl;
        return 84;
    } catch (const std::out_of_range&) {
        std::cerr << "Error: invalid argument, out of range" << std::endl;
        return 84;
    }
    plazza::Reception reception(std::stoi(av[1]), std::stod(av[2]), std::stoi(av[3]));
    reception.run();
}
