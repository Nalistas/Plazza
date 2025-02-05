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

    class IThreadWorker {
        public:
            virtual ~IThreadWorker() = default;
            virtual void operator()() = 0;
    };

    template <typename Worker, typename Task>
    class ThreadPool {
        static_assert(std::is_base_of<IThreadWorker, Worker>::value, "Worker must inherit from IThreadWorker");
        private:
            std::vector<std::thread> _threads;
            SafeQueue<Task> _queue;

            ConditionVariable _cv;
            bool _run;

            size_t _maxThreads;
            size_t _busyThreads;

            Mutex _mutex;


        public:
            ThreadPool(size_t maxThreads = 4);
            ~ThreadPool();

            template <typename... Args>
            void run(Args...);
            void stop();
            bool isRunning();

            template <typename... Args>
            void addTask(Args...);
            bool tryPop(Task &func);
            bool empty();
            size_t nbWaitingTasks();
            void waitForTask();

            void addThreadIsBusy();
            void addThreadIsFree();

            size_t getBusyThreads();
            size_t getWaitingTasks();
    };
}

#endif /* !THREADPOOL_HPP_ */
