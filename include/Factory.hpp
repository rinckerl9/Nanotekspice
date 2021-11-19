/*
** EPITECH PROJECT, 2020
** NanoTekSpice
** File description:
** A slightly crappier version of something I've done already
*/

#pragma once
#include <memory>
#include "IComponent.hpp"
#include "Component.hpp"

class Factory {
    public:
        Factory() {};
        ~Factory() {};

        nts::Component *createComponent(const std::string &type, const std::string &name, nts::Tristate inputState = nts::UNDEFINED);
    private:
        template<typename T> void assemble(nts::Component &chipset, std::vector<unsigned int> inputIndexes, std::vector<unsigned int> outputIndexes, std::vector<unsigned int> uselessIndexes, unsigned int nbGates);
        nts::Component *createInput(const std::string &name, nts::Tristate state) noexcept;
        nts::Component *createOutput(const std::string &name) noexcept;
        nts::Component *createTrue(const std::string &name) noexcept;
        nts::Component *createFalse(const std::string &name) noexcept;
        nts::Component *createClock(const std::string &name) noexcept;
        nts::Component *create4081(const std::string &name) noexcept;
        nts::Component *create4071(const std::string &name) noexcept;
        nts::Component *create4030(const std::string &name) noexcept;
        nts::Component *create4011(const std::string &name) noexcept;
        nts::Component *create4001(const std::string &name) noexcept;
};