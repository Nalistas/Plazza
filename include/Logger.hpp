/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
    #define LOGGER_HPP_

    #include "IPizza.hpp"

    #include <iostream>
    #include <fstream>
    #include <map>
    #include <sstream>

namespace plazza {
    class Logger {
        public:
            Logger();
            ~Logger();
            Logger &operator<<(std::string str);
            std::string enumToPizza(std::string str);

        protected:
        private:
            std::ofstream _file;
            std::map<enum PizzaSize, std::string> _pizzaSize;
            std::map<enum PizzaType, std::string> _pizzaType;

    };
}

#endif /* !LOGGER_HPP_ */
