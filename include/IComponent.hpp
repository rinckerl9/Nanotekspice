/*
** EPITECH PROJECT, 2020
** NanoTekSpice
** File description:
** A slightly crappier version of something I've done already
*/

#pragma once
#include <cstddef>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include "Gates.hpp"
#include "Enums.hpp"

namespace nts {
    class Pin {
        public:
            Pin() {};
            Pin(PinType tp) {
                this->state = tp;
            };
            ~Pin() {};
            nts::PinType state = USELESS;
            nts::Tristate value = UNDEFINED;
    };
    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual void simulate (std::size_t tick) = 0;
            virtual void compute() = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
            virtual void dump() = 0;

            virtual void setType(std::string) = 0;
            virtual void setName(std::string) = 0;
            virtual std::string getType(void) = 0;
            virtual void addGate(nts::Gate *) = 0;
            virtual nts::Gate *getGate(unsigned short) = 0;
    };
}