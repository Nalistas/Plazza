/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** NamedPipeOutput
*/

#ifndef NAMEDPIPEOUTPUT_HPP_
    #define NAMEDPIPEOUTPUT_HPP_

    #include "ANamedPipeEntry.hpp"

namespace ipc {
    class NamedPipeOutput : public ipc::ANamedPipeEntry {
        public:

            NamedPipeOutput();
            NamedPipeOutput(std::string const &name);
            NamedPipeOutput &open(std::string const &name) override;
            NamedPipeOutput &operator<<(std::string const &str);
    };
}

#endif /* !NAMEDPIPEOUTPUT_HPP_ */
