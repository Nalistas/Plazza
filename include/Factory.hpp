/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
    #define FACTORY_HPP_

    #include "IPizza.hpp"

    #include <memory>
    #include <map>
    #include <iostream>
    #include <functional>
    #include <istream>
    #include <sstream>
    #include <string>

namespace plazza {
    class Factory {
        public:
            Factory();
            ~Factory();
            void createPizza(std::string pizza, plazza::IPizza &apizza);
        protected:
        private:
            void createMargherita(plazza::IPizza &apizza);
            void createRegina(plazza::IPizza &apizza);
            void createAmericana(plazza::IPizza &apizza);
            void createFantasia(plazza::IPizza &apizza);
            std::map<enum plazza::PizzaType, std::function<void(plazza::IPizza &apizza)>> _pizzaMap;
    };
}

#endif /* !FACTORY_HPP_ */
