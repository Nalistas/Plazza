/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ANamedPipeEntry
*/

#ifndef ANAMEDPIPEENTRY_HPP_
    #define ANAMEDPIPEENTRY_HPP_

    #include "IPC/StreamChecker.hpp"

    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>

namespace ipc {
    class ANamedPipeEntry {
        public:
            ANamedPipeEntry(std::string const &name);
            ANamedPipeEntry();
            ~ANamedPipeEntry();

            virtual ANamedPipeEntry &open(std::string const &name) = 0;
            bool isOpened() const;

        protected:
            std::string _name;
            int _fd;
            bool _isOpened;
    };
}

#endif /* !ANAMEDPIPEENTRY_HPP_ */
