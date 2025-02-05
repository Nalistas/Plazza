/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Reception
*/

#ifndef Reception_HPP_
    #define Reception_HPP_

    #include "Parser.hpp"
    #include "Kitchen.hpp"
    #include "Process/Process.hpp"
    #include "IPC/NamedPipeInput.hpp"
    #include "IPC/NamedPipeOutput.hpp"
    #include "Logger.hpp"

    #include <signal.h>
    #include <iostream>
    #include <vector>
    #include <limits>
    #include <memory>

namespace plazza {
    class Reception {
        public:
            Reception(size_t nb_max_cooks, double time_modifier, int time_refill_fridge);
            ~Reception();
            void run();

        private:
            void createNewKitchen();
            void analyseCommand(std::string const &command);
            void getUserCommand();
            void sendPizza(std::string const &command);

            std::vector<std::string> getStatusOfAllKitchens();
            std::vector<int> getNbWorkingCooks();

            void checkKitchenCommand();
            void executeKitchenCommand(size_t &i, std::string const &command);

            Parser _parser;
            process::Process _process;
            std::vector<std::unique_ptr<ipc::NamedPipe>> _pipes;
            bool _run;
            size_t _kitchens_count;

            int _nb_max_cooks;
            double _time_modifier;
            Logger _logger;
            int _time_refill_fridge;
    };
}

#endif /* !Reception_HPP_ */
