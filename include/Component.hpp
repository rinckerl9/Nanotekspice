/*
** EPITECH PROJECT, 2020
** NanoTekSpice
** File description:
** A slightly crappier version of something I've done already
*/

#pragma once
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "IComponent.hpp"

namespace nts {
    class Component : public IComponent {
        public:
            Component();
            ~Component();

            void simulate (std::size_t tick);
            void compute();
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
            void dump();

            // setters / getters
            void setType(std::string);
            std::string getType(void);
            void addGate(nts::Gate *);
            nts::Gate *getGate(unsigned short);
            void addPin(unsigned int, nts::Pin *);
            nts::Pin *getPin(unsigned short);
            void setName(std::string);

            std::map<unsigned int, nts::Pin *> pins;
        private:
            std::vector<nts::Gate *> gates;
            std::string type;
            std::string name;
    };
}