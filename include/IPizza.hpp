/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** IPizza
*/

#ifndef IPIZZA_HPP_
    #define IPIZZA_HPP_


    #include "Fridge.hpp"
    #include "IPC/NamedPipe.hpp"

    #include <iostream>
    #include <map>

namespace plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    class IPizza {
        public:
            virtual ~IPizza() = default;
            virtual std::string unpack() = 0;
            virtual void setIngredients(std::map<std::string, int> ingredients) = 0;
            virtual void setTime(double time) = 0;
            virtual void setSize(enum PizzaSize size) = 0;
            virtual void setType(enum PizzaType type) = 0;
            virtual std::map<std::string, int> getIngredients() = 0;
            virtual double getTime() = 0;

        protected:
        private:
    };
}

#endif /* !IPIZZA_HPP_ */
