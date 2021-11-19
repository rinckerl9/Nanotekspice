/*
** EPITECH PROJECT, 2020
** NanoTekSpice
** File description:
** A slightly less good version of something I've done already
*/

#pragma once
#include <cstddef>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include "Enums.hpp"

namespace nts {
    class Gate {
        public:
            Gate() {};
            virtual ~Gate() = default;

            virtual nts::Tristate compute(void) = 0;
            void setFirstLink(unsigned int index);
            void setSecondLink(unsigned int index);
            void setOutputLink(unsigned int index);

            nts::Tristate first = UNDEFINED;
            nts::Tristate second = UNDEFINED;
            nts::Tristate output = UNDEFINED;

            int firstLink = -1;
            int secondLink = -1;
            int outputLink = -1;
    };
    class AndGate: public Gate {
        public:
            AndGate() {};
            ~AndGate() {};

            nts::Tristate compute(void);
    };

    class NandGate: public Gate {
        public:
            NandGate() {};
            ~NandGate() {};

            nts::Tristate compute(void);
    };

    class OrGate: public Gate {
        public:
            OrGate() {};
            ~OrGate() {};

            nts::Tristate compute(void);
    };

     class XorGate: public Gate {
        public:
            XorGate() {};
            ~XorGate() {};

            nts::Tristate compute(void);
    };

    class NorGate: public Gate {
        public:
            NorGate() {};
            ~NorGate() {};

            nts::Tristate compute(void);
    };
}