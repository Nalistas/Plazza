/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ANamedPipeEntry
*/

#include "IPC/ANamedPipeEntry.hpp"

ipc::ANamedPipeEntry::ANamedPipeEntry(std::string const &name) :
    ipc::ANamedPipeEntry()
{
    _name = name;
    mkfifo(_name.c_str(), 0666);
}

ipc::ANamedPipeEntry::ANamedPipeEntry() :
    _name(""), _fd(-1), _isOpened(false)
{}

ipc::ANamedPipeEntry::~ANamedPipeEntry()
{
    if (_isOpened) {
        ::close(_fd);
        unlink(_name.c_str());
    }
}

bool ipc::ANamedPipeEntry::isOpened() const
{
    return _isOpened;
}
