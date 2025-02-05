/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "APizza.hpp"
#include <chrono>

plazza::Kitchen::Kitchen(std::string const &name, int cooks_number, double time_modifier, std::time_t time_refill_fridge) :
    _name(name), _time_modifier(time_modifier), _cooks(cooks_number), _pipe(name + "read", name + "write"),
    _last_used(std::time(nullptr)),
    _time_refill_fridge(time_refill_fridge),
    _last_time_refill_fridge(std::chrono::steady_clock::now())
{
        run();
}

plazza::Kitchen::~Kitchen()
{
}

void plazza::Kitchen::analyseCommand(std::string const &command)
{
    if (command.empty()) {
        return;
    }
    if (command == "status") {
        status();
        return;
    }
    if (command == "soon") {
        _last_used = std::time(nullptr) - 4;
        return;
    }
    _cooks.addTask<std::string>(command);
}

void plazza::Kitchen::status()
{
    std::string content;
    thread::ScopeLock lock(_fridge.getMutex());

    content = std::to_string(_cooks.getBusyThreads() + _cooks.getWaitingTasks());
    content += " pizzas in going, ";
    for (auto it = _fridge.getIngredients().begin(); it != _fridge.getIngredients().end(); it++) {
        if (it != _fridge.getIngredients().begin()) {
            content += ", ";
        }
        content += (*it).first + ": " + std::to_string((*it).second);
    }
    _pipe << content;
}

void plazza::Kitchen::checkRefillFridge()
{    
    auto now = std::chrono::steady_clock::now();
    auto time_passed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _last_time_refill_fridge);

    if (time_passed >= _time_refill_fridge) {
        _last_time_refill_fridge = now;
        _fridge.refillIngredients();
    }
}

void plazza::Kitchen::run()
{
    std::string content;
    std::array<std::string, 3> command;
    _pipe.initInput();
    _pipe.initOutput();
    _cooks.run<plazza::Fridge &, ipc::NamedPipe &, thread::Mutex &, int>(_fridge, _pipe, _mutex_pipe, _time_modifier);

    std::time_t time;
    std::chrono::milliseconds miliseconds(_time_refill_fridge);

    while (1) {
        if (_pipe.inputUpdate()) {
            _pipe >> content;
            analyseCommand(content);
            continue;
        }
        time = std::time(nullptr);
        checkRefillFridge();
        if (time - _last_used > 5) {
            _pipe << "exit";
            break;
        }
        if (_cooks.getBusyThreads() + _cooks.getWaitingTasks() != 0) {
            _last_used = std::time(nullptr);
        }
    }
    while(1) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

