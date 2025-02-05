/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** NamedPipeOutput
*/

#include "IPC/NamedPipeOutput.hpp"

ipc::NamedPipeOutput::NamedPipeOutput(std::string const &name) :
    ipc::ANamedPipeEntry(name)
{
    this->open(_name);
}

ipc::NamedPipeOutput::NamedPipeOutput() :
    ipc::ANamedPipeEntry()
{}

ipc::NamedPipeOutput &ipc::NamedPipeOutput::open(std::string const &name)
{
    if (_isOpened) {
        close(_fd);
    }
    mkfifo(name.c_str(), 0666);
    _name = name;
    _fd = ::open(_name.c_str(), O_WRONLY);
    if (_fd == -1) {
        throw std::runtime_error("NamedPipeOutput: " + _name + " open failed");
    }
    _isOpened = true;
    return *this;
}

ipc::NamedPipeOutput &ipc::NamedPipeOutput::operator<<(std::string const &str)
{
    if (!_isOpened) {
        throw std::runtime_error("NamedPipeOutput: " + _name + " not opened");
    }
    write(_fd, str.c_str(), str.length());
    write(_fd, "\n", 1);
    return *this;
}
