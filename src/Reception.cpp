/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Reception
*/

#include "Reception.hpp"

plazza::Reception::Reception(size_t nb_max_cooks, double time_modifier, int time_refill_fridge) :
    _parser(), _process(), _pipes(), _run(true), _kitchens_count(0),
    _nb_max_cooks(nb_max_cooks), _time_modifier(time_modifier), _time_refill_fridge(time_refill_fridge)
{}

plazza::Reception::~Reception()
{}

void plazza::Reception::createNewKitchen()
{
    _kitchens_count++;
    std::string name = "kitchen" + std::to_string(_kitchens_count);

    _process.fork<Kitchen, std::string, int, double, std::time_t>(name, _nb_max_cooks, _time_modifier, _time_refill_fridge);
    _pipes.push_back(std::make_unique<ipc::NamedPipe>(name + "write", name + "read"));

    _pipes[_pipes.size() - 1]->initOutput();
    _pipes[_pipes.size() - 1]->initInput();
    _pipes[_pipes.size() - 1]->setInputUpdateTimeout(0);
}

void plazza::Reception::sendPizza(std::string const &command)
{
    for (size_t i = 0; i < _pipes.size(); i++) {
        (*_pipes[i]) << "soon";
    }
    std::vector<int> status = getNbWorkingCooks();

    if (status.size() == 0) {
        createNewKitchen();
        sendPizza(command);
        return;
    }

    auto it = std::min_element(status.begin(), status.end());
    int index = std::distance(status.begin(), it);
    std::string answer;

    if (status[index] >= (_nb_max_cooks * 2)) {
        createNewKitchen();
        sendPizza(command);
        return;
    }
    (*_pipes[index]) << command + '\n';
}

void plazza::Reception::analyseCommand(std::string const &command)
{
    std::vector<std::array<int, 3>> commands;
    std::vector<std::array<int, 2>> final_commands;

    commands = _parser.parse(command);
    for (auto const &cmd : commands) {
        for (int i = 0; i < cmd[2]; i++) {
            final_commands.push_back({cmd[0], cmd[1]});
        }
    }
    for (auto c : final_commands) {
        std::string tmp = std::to_string(c[0]) + " " + std::to_string(c[1]) + " ";
        sendPizza(tmp);
    }
}

void plazza::Reception::getUserCommand()
{
    std::string input;
    std::getline(std::cin, input);
    if (input == "exit" || std::cin.eof()) {
        _run = false;
        return;
    }
    if (input == "status") {
        std::vector <std::string> status = getStatusOfAllKitchens();
        for (size_t i = 0; i < status.size(); i++) {
            std::cout << "Kitchen " << i << " status: " << status[i] << std::endl << std::flush;
        }
        return;
    }
    analyseCommand(input);
}

std::vector<std::string> plazza::Reception::getStatusOfAllKitchens()
{
    std::vector<std::string> status;
    std::string answer;

    for (size_t i = 0; i < _pipes.size(); i++) {
        (*_pipes[i]) << "status";
        (*_pipes[i]) >> answer;
        if (answer == "exit") {
            _pipes.erase(_pipes.begin() + i);
            _process.killChild(i);
            i--;
            continue;
        }
        status.push_back(answer);
    }
    return status;
}

std::vector<int> plazza::Reception::getNbWorkingCooks()
{
    std::vector<int> nb_working_cooks;
    std::vector<std::string> status = getStatusOfAllKitchens();

    for (auto s : status) {
        nb_working_cooks.push_back(std::stoi(s));
    }
    return nb_working_cooks;
}

void plazza::Reception::executeKitchenCommand(size_t &i, std::string const &command)
{
    if (command == "exit") {
        _pipes.erase(_pipes.begin() + i);
        _process.killChild(i);
        i--;
        return;
    }
    if (command.substr(0, 5) == "Pizza") {
        _logger << command;
        return;
    }
}

void plazza::Reception::checkKitchenCommand()
{
    std::string input;

    for (size_t i = 0; i < _pipes.size(); i++) {
        if (_pipes[i]->inputUpdate()) {
            (*_pipes[i]) >> input;
            executeKitchenCommand(i, input);
        }
    }
}

void plazza::Reception::run()
{
    ipc::StreamChecker checker(STDIN_FILENO);
    _run = true;

    std::cout << "Enter a command: " << std::flush;
    while (_run) {
        if (checker.hasBeenUpdated()) {
            checkKitchenCommand();
            getUserCommand();
            std::cout << "Enter a command: " << std::flush;
        }
        checkKitchenCommand();
    }
}
