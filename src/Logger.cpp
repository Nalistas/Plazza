/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Logger
*/

#include "Logger.hpp"

plazza::Logger::Logger()
{
    _file.open("orders.txt");
    _pizzaSize[plazza::S] = "S";
    _pizzaSize[plazza::M] = "M";
    _pizzaSize[plazza::L] = "L";
    _pizzaSize[plazza::XL] = "XL";
    _pizzaSize[plazza::XXL] = "XXL";
    _pizzaType[plazza::Regina] = "Regina";
    _pizzaType[plazza::Margarita] = "Margarita";
    _pizzaType[plazza::Americana] = "Americana";
    _pizzaType[plazza::Fantasia] = "Fantasia";
}

plazza::Logger::~Logger()
{
    if (_file.is_open())
        _file.close();
}

std::string plazza::Logger::enumToPizza(std::string str)
{
    std::istringstream iss(str);
    std::string pizza;
    std::string type_str;
    std::string size_str;
    iss >> pizza >> type_str >> size_str;

    PizzaType type = static_cast<PizzaType>(std::stoi(type_str));
    PizzaSize size = static_cast<PizzaSize>(std::stoi(size_str));

    return "Pizza " + _pizzaType[type] + " " + _pizzaSize[size];
}

plazza::Logger &plazza::Logger::operator<<(std::string str)
{
    if (_file.is_open())
        _file << enumToPizza(str) << std::endl;
    return *this;
}
