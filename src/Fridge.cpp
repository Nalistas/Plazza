/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Fridge
*/

#include "Fridge.hpp"

plazza::Fridge::Fridge()
{
    _ingredients["dough"] = 5;
    _ingredients["tomato"] = 5;
    _ingredients["gruyere"] = 5;
    _ingredients["ham"] = 5;
    _ingredients["mushrooms"] = 5;
    _ingredients["steak"] = 5;
    _ingredients["eggplant"] = 5;
    _ingredients["goatCheese"] = 5;
    _ingredients["chiefLove"] = 5;
}

plazza::Fridge::~Fridge()
{
}

std::map<std::string, int> const &plazza::Fridge::getIngredients() const
{
    return _ingredients;
}

thread::Mutex &plazza::Fridge::getMutex()
{
    return _mutex;
}

bool plazza::Fridge::checkIngredients(std::map<std::string, int> ingredients)
{
    thread::ScopeLock lock(_mutex);
    for (auto &ingredient : ingredients) {
        if (_ingredients[ingredient.first] < ingredient.second)
            return false;
    }
    return true;
}

void plazza::Fridge::takeIngredients(std::map<std::string, int> ingredients)
{
    thread::ScopeLock lock(_mutex);
    for (auto &ingredient : ingredients) {
        _ingredients[ingredient.first] -= ingredient.second;
    }
}

void plazza::Fridge::refillIngredients(void)
{
    thread::ScopeLock lock(_mutex);
    for (auto &ingredient : _ingredients) {
        ingredient.second += 1;
    }
    _condition.notifyAll();
}

void plazza::Fridge::waitForRefill(void)
{
    _condition.wait();
}
