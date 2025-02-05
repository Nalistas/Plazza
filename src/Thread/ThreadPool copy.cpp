/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ThreadPool
*/

#include "Thread/ThreadPool.hpp"

thread::ThreadPool::ThreadPool(size_t maxThreads) :
    _run(false), _maxThreads(maxThreads), _busyThreads(0)
{
    run();
}

thread::ThreadPool::~ThreadPool()
{
    stop();
}

size_t thread::ThreadPool::getWaitingTasks()
{
    return _queue.size();
}

size_t thread::ThreadPool::getBusyThreads()
{
    return _busyThreads;
}

void thread::ThreadPool::addTask(std::function<void()> func)
{
    _queue.push(func);
    _cv.notify();
}

void thread::ThreadPool::run()
{
    _run = true;

    for (size_t i = 0; i < _maxThreads; i++) {
        _threads.push_back(std::thread(ThreadWorker(*this)));
    }
}

void thread::ThreadPool::stop()
{
    _run = false;
    _cv.notifyAll();
    for (auto &thread : _threads) {
        if (thread.joinable())
            thread.join();
    }
    
}

bool thread::ThreadPool::isRunning()
{
    return _run;
}

thread::ThreadPool::ThreadWorker::ThreadWorker(ThreadPool &pool) :
    _pool(pool)
{}

thread::ThreadPool::ThreadWorker::~ThreadWorker()
{}

void thread::ThreadPool::ThreadWorker::operator()()
{
    std::function<void()> func;

    while (_pool._run || !_pool._queue.empty()) {
    
        if (_pool._queue.tryPop(func)) {
            _pool._busyThreads++;
            func();
            _pool._busyThreads--;
        } else {
            _pool._cv.wait();
        }
    }
}
