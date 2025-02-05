/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** APizza
*/

#include "APizza.hpp"

plazza::APizza::APizza()
{}

plazza::APizza::APizza(std::string pizza)
{
    Factory factory;

    factory.createPizza(pizza, *this);
}

plazza::APizza::~APizza()
{
}

std::string plazza::APizza::unpack()
{
    std::string str = std::to_string(_type) + " " + std::to_string(_size) + " ";

    return str;
}

void plazza::APizza::setIngredients(std::map<std::string, int> ingredients)
{
    _ingredients = ingredients;
}

void plazza::APizza::setTime(double time)
{
    _time = time;
}

void plazza::APizza::setSize(enum PizzaSize size)
{
    _size = size;
}

void plazza::APizza::setType(enum PizzaType type)
{
    _type = type;
}

std::map<std::string, int> plazza::APizza::getIngredients()
{
    return _ingredients;
}

double plazza::APizza::getTime()
{
    return _time;
}
