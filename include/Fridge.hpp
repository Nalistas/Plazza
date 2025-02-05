/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Fridge
*/

#ifndef FRIDGE_HPP_
    #define FRIDGE_HPP_

    #include "Thread/Mutex.hpp"
    #include "Thread/ScopeLock.hpp"
    #include "Thread/ConditionVariable.hpp"

    #include <map>
    #include <iostream>

namespace plazza {
    class Fridge {
        public:
            Fridge();
            ~Fridge();
            void takeIngredients(std::map<std::string, int> ingredients);
            void refillIngredients(void);
            bool checkIngredients(std::map<std::string, int> ingredients);
            void waitForRefill(void);

            std::map<std::string, int> const &getIngredients() const;
            thread::Mutex &getMutex();

        protected:
        private:
            thread::Mutex _mutex;
            std::map<std::string, int> _ingredients;
            thread::ConditionVariable _condition;

    };
}

#endif /* !FRIDGE_HPP_ */
