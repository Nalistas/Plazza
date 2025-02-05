/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Process
*/


#ifndef PROCESS_HPP_
    #define PROCESS_HPP_

    #include <sys/types.h>
    #include <vector>
    #include <functional>
    #include <signal.h>
    #include <unistd.h>

namespace process
{
    class Process {
        public:
            Process();
            ~Process();

            template <typename T, typename... Args>
            void fork(Args...);

            void killChild(size_t ndx);
            pid_t getPid();

        private:
            pid_t _pid;
            std::vector<pid_t> _childpids;
    };
}

#endif /* !PROCESS_HPP_ */
