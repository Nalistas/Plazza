/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** NamedPipeInput
*/

#ifndef NAMEDPIPEINPUT_HPP_
    #define NAMEDPIPEINPUT_HPP_

    #include "ANamedPipeEntry.hpp"

namespace ipc {
    class NamedPipeInput : public ipc::ANamedPipeEntry {
        public:

            NamedPipeInput(std::string const &name);
            NamedPipeInput();
            ANamedPipeEntry &open(std::string const &name) override;
            NamedPipeInput &operator>>(std::string &str);

            bool hasBeenUpdated();
            void setCheckerTimeout(int timeout);

        private:
            StreamChecker _streamChecker;

    };
}

#endif /* !NAMEDPIPEINPUT_HPP_ */
