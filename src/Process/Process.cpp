/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Process
*/

#include "Process/Process.hpp"

process::Process::Process()
{
    _pid = getpid();
}

process::Process::~Process()
{
    for (auto childpid : _childpids) {
        kill(childpid, SIGKILL);
    }
}

template <typename T, typename... Args>
void process::Process::fork(Args... args)
{
    pid_t pid = ::fork();

    if (pid == 0) {
        _childpids.clear();
        _pid = getpid();
        T obj(std::forward<Args>(args)...);
        exit(0);
    } else {
        _childpids.push_back(pid);
    }
}

pid_t process::Process::getPid()
{
    return _pid;
}

void process::Process::killChild(size_t ndx)
{
    kill(_childpids[ndx], SIGKILL);
    _childpids.erase(_childpids.begin() + ndx);
}

    #include "Kitchen.hpp"

template void process::Process::fork<plazza::Kitchen, std::string, int, double, std::time_t>(std::string, int, double, std::time_t);
