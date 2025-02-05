/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ThreadPool
*/

#include "Thread/ThreadPool.hpp"

template <typename Worker, typename Task>
thread::ThreadPool<Worker, Task>::ThreadPool(size_t maxThreads) :
    _run(false), _maxThreads(maxThreads), _busyThreads(0)
{}

template <typename Worker, typename Task>
thread::ThreadPool<Worker, Task>::~ThreadPool()
{
    stop();
}

template <typename Worker, typename Task>
size_t thread::ThreadPool<Worker, Task>::getWaitingTasks()
{
    return _queue.size();
}

template <typename Worker, typename Task>
size_t thread::ThreadPool<Worker, Task>::getBusyThreads()
{
    return _busyThreads;
}

template <typename Worker, typename Task>
template <typename... Args>
void thread::ThreadPool<Worker, Task>::addTask(Args... args)
{
    _queue.push(Task(std::forward<Args>(args)...));
    _cv.notify();
}


template <typename Worker, typename Task>
template <typename... Args>
void thread::ThreadPool<Worker, Task>::run(Args... args)
{
    _run = true;

    for (size_t i = 0; i < _maxThreads; i++) {
        _threads.emplace_back(Worker(*this, std::forward<Args>(args)...));
    }
}

template <typename Worker, typename Task>
void thread::ThreadPool<Worker, Task>::stop()
{
    _run = false;
    _cv.notifyAll();
    for (auto &thread : _threads) {
        if (thread.joinable())
            thread.join();
    }
    
}

template <typename Worker, typename Task>
bool thread::ThreadPool<Worker, Task>::isRunning()
{
    return _run;
}


template <typename Worker, typename Task>
bool thread::ThreadPool<Worker, Task>::empty()
{
    return _queue.empty();
}


template <typename Worker, typename Task>
size_t thread::ThreadPool<Worker, Task>::nbWaitingTasks()
{
    return _queue.size();
}

template <typename Worker, typename Task>
bool thread::ThreadPool<Worker, Task>::tryPop(Task &func)
{
    return _queue.tryPop(func);
}

template <typename Worker, typename Task>
void thread::ThreadPool<Worker, Task>::waitForTask()
{
    _cv.wait();
}

template <typename Worker, typename Task>
void thread::ThreadPool<Worker, Task>::addThreadIsBusy()
{
    _busyThreads++;
}

template <typename Worker, typename Task>
void thread::ThreadPool<Worker, Task>::addThreadIsFree()
{
    _busyThreads--;
}

    #include "Cooks.hpp"
    #include "APizza.hpp"
template class thread::ThreadPool<plazza::Cooks, plazza::APizza>;
template void thread::ThreadPool<plazza::Cooks, plazza::APizza>::run<plazza::Fridge &, ipc::NamedPipe &, thread::Mutex &, int>
    (plazza::Fridge &, ipc::NamedPipe &, thread::Mutex &, int);
template void thread::ThreadPool<plazza::Cooks, plazza::APizza>::addTask<std::string>(std::string);
