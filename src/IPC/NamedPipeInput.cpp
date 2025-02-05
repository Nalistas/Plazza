/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** NamedPipeInput
*/

#include "IPC/NamedPipeInput.hpp"

ipc::NamedPipeInput::NamedPipeInput(std::string const &name) :
    ipc::ANamedPipeEntry(name)
{
    this->open(_name);
}

ipc::NamedPipeInput::NamedPipeInput() :
    ipc::ANamedPipeEntry()
{}

ipc::ANamedPipeEntry &ipc::NamedPipeInput::open(std::string const &name)
{
    if (_isOpened) {
        close(_fd);
    }
    mkfifo(name.c_str(), 0666);
    _name = name;
    _fd = ::open(_name.c_str(), O_RDONLY);
    if (_fd == -1) {
        throw std::runtime_error("NamedPipeInput " + _name + ": open failed");
    }
    _isOpened = true;
    return *this;
}

ipc::NamedPipeInput &ipc::NamedPipeInput::operator>>(std::string &str)
{
    if (!_isOpened) {
        throw std::runtime_error("NamedPipeInput " + _name + ": not opened");
    }
    str.clear();
    char c;
    int nb = read(_fd, &c, 1);
    while (nb > 0 && c != '\n' && c != '\0') {
        str += c;
        nb = read(_fd, &c, 1);
    }
    return *this;
}


bool ipc::NamedPipeInput::hasBeenUpdated()
{
    _streamChecker.lookFor(_fd);
    return _streamChecker.hasBeenUpdated();
}

void ipc::NamedPipeInput::setCheckerTimeout(int timeout)
{
    _streamChecker.setTimeout(timeout, 0);
}

