/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** NamedPipe
*/

#include "IPC/NamedPipe.hpp"

ipc::NamedPipe::NamedPipe(std::string const &nameInput, std::string const &nameOutput) :
    _nameInput(nameInput), _nameOutput(nameOutput)
{}

ipc::NamedPipe::~NamedPipe()
{}

bool ipc::NamedPipe::inputUpdate()
{
    return _input.hasBeenUpdated();
}

void ipc::NamedPipe::setInputUpdateTimeout(int timeout)
{
    _input.setCheckerTimeout(timeout);
}

void ipc::NamedPipe::initOutput()
{
    _output.open(_nameOutput);
}

void ipc::NamedPipe::initInput()
{
    _input.open(_nameInput);
}

ipc::NamedPipe &ipc::NamedPipe::operator<<(std::string const &str)
{
    _output << str;
    return *this;
}

ipc::NamedPipe &ipc::NamedPipe::operator>>(std::string &str)
{
    _input >> str;
    return *this;
}
