/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** StreamChecker
*/

#ifndef STREAMCHECKER_HPP_
    #define STREAMCHECKER_HPP_

    #include <sys/time.h>
    #include <sys/select.h>
    #include <fstream>
    #include <iostream>
    #include <ext/stdio_filebuf.h>

namespace ipc {
    class StreamChecker {
        public:
            StreamChecker(int fd);
            StreamChecker();
            ~StreamChecker();

            bool hasBeenUpdated();
            void lookFor(int fd);
            void setTimeout(int sec, int usec);

        private:
            int _fd;
            fd_set _fds;
            struct timeval _tv;
    };
}

#endif /* !STREAMCHECKER_HPP_ */
