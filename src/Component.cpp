/*
** EPITECH PROJECT, 2020
** NanoTekSpice
** File description:
** A slightly crappier version of something I've done already
*/

#include <cstddef>
#include <iostream>
#include <array>
#include <vector>
#include "IComponent.hpp"
#include "Component.hpp"

nts::Component::Component()
{

}

nts::Component::~Component()
{
    /// ???
}

void nts::Component::simulate (std::size_t tick)
{
    // ???
}

void nts::Component::compute()
{
    for (int i = 0; i < this->gates.size(); i++) {
        this->gates[i]->first = this->pins[this->gates[i]->firstLink]->value;
        this->gates[i]->second = this->pins[this->gates[i]->secondLink]->value;
        // std::cerr << this->name << " " << this->gates[i]->outputLink << " set to " << this->gates[i]->compute() << std::endl;
        this->pins[this->gates[i]->outputLink]->value = this->gates[i]->compute();
    }
}

void nts::Component::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    // ???
}

void nts::Component::dump()
{
    if (this->pins[1]->value != nts::UNDEFINED)
        std::cout << this->name << ": " << this->pins[1]->value << std::endl;
    else
        std::cout << this->name << ": U" << std::endl;
}

void nts::Component::setType(std::string newtype)
{
    this->type = newtype;
}

std::string nts::Component::getType(void)
{
    return this->type;
}

void nts::Component::addGate(nts::Gate *newGate)
{
    this->gates.push_back(newGate);
}

nts::Gate *nts::Component::getGate(unsigned short i)
{
    return this->gates[i];
}

void nts::Component::addPin(unsigned int index, nts::Pin *newPin)
{
    this->pins.insert(std::pair<unsigned int, nts::Pin *>(index, newPin));
}

nts::Pin *nts::Component::getPin(unsigned short i)
{
    return this->pins[i];
}

void nts::Component::setName(std::string name)
{
    this->name = name;
}
