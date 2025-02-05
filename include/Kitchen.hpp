/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

    #include "Fridge.hpp"
    #include "IPC/NamedPipe.hpp"
    #include "Thread/ThreadPool.hpp"
    #include "Parser.hpp"
    #include "Cooks.hpp"

    #include <memory>
    #include <chrono>
    #include <thread>

namespace plazza {
    class Kitchen {
        public:
            Kitchen(std::string const &name, int cooks_number, double time_modifier, std::time_t time_refill_fridge);
            ~Kitchen();
            void run();

        private:
            void analyseCommand(std::string const &command);
            void status();

            void checkRefillFridge();

            std::string _name;
            double _time_modifier;
            thread::ThreadPool<Cooks, APizza> _cooks;
            Parser _parser;
            plazza::Fridge _fridge;


            ipc::NamedPipe _pipe;
            thread::Mutex _mutex_pipe;
            std::time_t _last_used;
            std::chrono::milliseconds _time_refill_fridge;
             std::chrono::steady_clock::time_point _last_time_refill_fridge;
    };
}

#endif /* !KITCHEN_HPP_ */
