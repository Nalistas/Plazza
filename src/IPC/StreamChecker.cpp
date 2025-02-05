/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** StreamChecker
*/

#include "IPC/StreamChecker.hpp"

ipc::StreamChecker::StreamChecker(int fd) :
    _fd(fd)
{
    _tv = {.tv_sec = 1, .tv_usec = 0};
}

ipc::StreamChecker::StreamChecker() :
    ipc::StreamChecker(-1)
{}

ipc::StreamChecker::~StreamChecker()
{}

void ipc::StreamChecker::lookFor(int fd)
{
    _fd = fd;
}

void ipc::StreamChecker::setTimeout(int sec, int usec)
{
    _tv = {.tv_sec = sec, .tv_usec = usec};
}

bool ipc::StreamChecker::hasBeenUpdated()
{
    if (_fd < 0) {
        return false;
    }
    struct timeval tv = _tv;
    FD_ZERO(&_fds);
    FD_SET(_fd, &_fds);
    if (select(_fd + 1, &_fds, NULL, NULL, &tv) == 1) {
        return true;
    }
    return false;
}
