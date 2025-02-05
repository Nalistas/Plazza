/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Cooks
*/

#ifndef COOKS_HPP_
    #define COOKS_HPP_

    #include "APizza.hpp"
    #include "Thread/ThreadPool.hpp"
    #include "Fridge.hpp"

namespace plazza {
    class Cooks : public thread::IThreadWorker {
        public:
            Cooks(thread::ThreadPool<Cooks, APizza> &pool, Fridge &fridge, ipc::NamedPipe &pipe, thread::Mutex &mutexPipe, int time_modifier);
            ~Cooks();

            void operator()() override;
            void bakePizza(APizza &pizza);

        private:
            thread::ThreadPool<Cooks, APizza> &_pool;
            Fridge &_fridge;
            ipc::NamedPipe &_pipe;
            thread::Mutex &_mutex_pipe;
            int _time_modifier;
    };
}

#endif /* !COOKS_HPP_ */
