/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** NamedPipe
*/

#ifndef NAMEDPIPE_HPP_
    #define NAMEDPIPE_HPP_

    #include "IPC/NamedPipeInput.hpp"
    #include "IPC/NamedPipeOutput.hpp"

    #include <iostream>

namespace ipc {
    class NamedPipe {
        public:
            NamedPipe(std::string const &nameInput, std::string const &nameOutput);
            ~NamedPipe();

            void initOutput();
            void initInput();

            bool inputUpdate();
            void setInputUpdateTimeout(int timeout);

            NamedPipe &operator<<(std::string const &str);
            NamedPipe &operator>>(std::string &str);

        private:
            std::string _nameInput;
            std::string _nameOutput;
            NamedPipeInput _input;
            NamedPipeOutput _output;
    };
}

#endif /* !NAMEDPIPE_HPP_ */
