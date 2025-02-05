/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Factory
*/

#include "Factory.hpp"

plazza::Factory::Factory()
{
    _pizzaMap[plazza::Margarita] = [this](IPizza &apizza) { this->createMargherita(apizza); };
    _pizzaMap[plazza::Regina] = [this](IPizza &apizza) { this->createRegina(apizza); };
    _pizzaMap[plazza::Americana] = [this](IPizza &apizza) { this->createAmericana(apizza); };
    _pizzaMap[plazza::Fantasia] = [this](IPizza &apizza) { this->createFantasia(apizza); };
}

plazza::Factory::~Factory()
{
}

void plazza::Factory::createPizza(std::string pizza, plazza::IPizza &apizza)
{
    std::istringstream iss(pizza);
    std::string type_str;
    std::string size_str;
    iss >> type_str >> size_str;

    enum plazza::PizzaType type = static_cast<plazza::PizzaType>(std::stoi(type_str));
    enum plazza::PizzaSize size = static_cast<plazza::PizzaSize>(std::stoi(size_str));

    apizza.setSize(size);
    _pizzaMap[type](apizza);
}

void plazza::Factory::createMargherita(plazza::IPizza &apizza)
{
    std::map<std::string, int> ingredients;
    ingredients["dough"] = 1;
    ingredients["tomato"] = 1;
    ingredients["gruyere"] = 1;
    apizza.setIngredients(ingredients);
    apizza.setTime(1);
    apizza.setType(plazza::Margarita);
}

void plazza::Factory::createRegina(plazza::IPizza &apizza)
{
    std::map<std::string, int> ingredients;
    ingredients["dough"] = 1;
    ingredients["tomato"] = 1;
    ingredients["gruyere"] = 1;
    ingredients["ham"] = 1;
    ingredients["mushrooms"] = 1;
    apizza.setIngredients(ingredients);
    apizza.setTime(2);
    apizza.setType(plazza::Regina);
}

void plazza::Factory::createAmericana(plazza::IPizza &apizza)
{
    std::map<std::string, int> ingredients;
    ingredients["dough"] = 1;
    ingredients["tomato"] = 1;
    ingredients["gruyere"] = 1;
    ingredients["steak"] = 1;
    apizza.setIngredients(ingredients);
    apizza.setTime(2);
    apizza.setType(plazza::Americana);
}

void plazza::Factory::createFantasia(plazza::IPizza &apizza)
{
    std::map<std::string, int> ingredients;
    ingredients["dough"] = 1;
    ingredients["tomato"] = 1;
    ingredients["eggplant"] = 1;
    ingredients["goatCheese"] = 1;
    ingredients["chiefLove"] = 1;
    apizza.setIngredients(ingredients);
    apizza.setTime(4);
    apizza.setType(plazza::Fantasia);
}
