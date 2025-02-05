/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Cooks
*/

#include "Cooks.hpp"

plazza::Cooks::Cooks(thread::ThreadPool<Cooks, APizza> &pool, Fridge &fridge, ipc::NamedPipe &pipe, thread::Mutex &mutexPipe, int timeModifier) :
    _pool(pool), _fridge(fridge), _pipe(pipe), _mutex_pipe(mutexPipe), _time_modifier(timeModifier)
{}

plazza::Cooks::~Cooks()
{}

void plazza::Cooks::bakePizza(APizza &pizza)
{
    while (!_fridge.checkIngredients(pizza.getIngredients())) {
        _fridge.waitForRefill();
    }

    _fridge.takeIngredients(pizza.getIngredients());
    auto duration = std::chrono::duration<double>(pizza.getTime() * _time_modifier);
    std::this_thread::sleep_for(duration);
    thread::ScopeLock lock(_mutex_pipe);
    _pipe << "Pizza " + pizza.unpack();
}

void plazza::Cooks::operator()()
{
    APizza pizza;

    while (_pool.isRunning() || !_pool.empty()) {
        if (_pool.tryPop(pizza)) {
            _pool.addThreadIsBusy();
            bakePizza(pizza);
            _pool.addThreadIsFree();
        } else {
            _pool.waitForTask();
        }
    }

}
