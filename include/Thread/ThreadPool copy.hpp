/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ThreadPool
*/


#ifndef THREADPOOL_HPP_
    #define THREADPOOL_HPP_

    #include "Mutex.hpp"
    #include "SafeQueue.hpp"
    #include "ConditionVariable.hpp"
    #include "Thread/ScopeLock.hpp"

    #include <thread>
    #include <functional>
    #include <vector>

namespace thread {
    class ThreadPool {
        private:
            std::vector<std::thread> _threads;
            SafeQueue<std::function<void()>> _queue;
            ConditionVariable _cv;
            bool _run;

            size_t _maxThreads;
            size_t _busyThreads;

            Mutex _mutex;


        public:
            ThreadPool(size_t maxThreads = 4);
            ~ThreadPool();

            void addTask(std::function<void()> func);
            void run();
            void stop();
            bool isRunning();
            size_t getBusyThreads();
            size_t getWaitingTasks();

        class ThreadWorker {
            private:
                ThreadPool &_pool;

            public:
                ThreadWorker(ThreadPool &pool);
                ~ThreadWorker();

                void operator()();

        };



    };
}

#endif /* !THREADPOOL_HPP_ */
