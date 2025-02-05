/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** APizza
*/

#ifndef APIZZA_HPP_
    #define APIZZA_HPP_

    #include "IPizza.hpp"
    #include "Factory.hpp"

    #include <chrono>
    #include <iomanip>
    #include <ctime>
    #include <thread>
    #include <iostream>

namespace plazza {
    class APizza: public IPizza {
        public:
            APizza();
            APizza(std::string pizza);
            ~APizza() override;
            std::string unpack(void) override;
            void setIngredients(std::map<std::string, int> ingredients) override;
            void setTime(double time) override;
            void setSize(enum PizzaSize size) override;
            void setType(enum PizzaType type) override;
            std::map<std::string, int> getIngredients(void) override;
            double getTime(void) override;


        protected:
        private:
            std::map<std::string, int> _ingredients;
            double _time;
            enum PizzaSize _size;
            enum PizzaType _type;
    };
}

#endif /* !APIZZA_HPP_ */
