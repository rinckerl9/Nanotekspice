/*
** EPITECH PROJECT, 2020
** NanoTekSpice
** File description:
** A slightly crappier version of something I've done already
*/

#include "Error.hpp"
#include <memory>
#include <iostream>
#include <array>
#include "IComponent.hpp"
#include "Component.hpp"
#include "Factory.hpp"
#include "Gates.hpp"

template<typename T> void Factory::assemble(nts::Component &chipset, std::vector<unsigned int> inputIndexes, std::vector<unsigned int> outputIndexes, std::vector<unsigned int> uselessIndexes, unsigned int nbGates)
{
    for (unsigned int i = 0, j = 0; i < nbGates; i++, j += 2) {
        chipset.addGate((nts::Gate *)new T);
        if (!inputIndexes.empty()) {
            chipset.getGate(i)->setFirstLink(inputIndexes[j]);
            chipset.getGate(i)->setSecondLink(inputIndexes[j + 1]);
        }
        chipset.getGate(i)->setOutputLink(outputIndexes[i]);
    }
    for (unsigned int j = 0; j < inputIndexes.size(); j++)
        chipset.addPin(inputIndexes[j], new nts::Pin(nts::INPUT));
    for (unsigned int j = 0; j < outputIndexes.size(); j++)
        chipset.addPin(outputIndexes[j], new nts::Pin(nts::OUTPUT));
    for (unsigned int j = 0; j < uselessIndexes.size(); j++)
        chipset.addPin(uselessIndexes[j], new nts::Pin(nts::USELESS));
}

nts::Component *Factory::create4081(const std::string &name) noexcept
{
    nts::Component *chipset = new nts::Component;
    std::vector<unsigned int> inputIndexes = {1, 2, 5, 6, 8, 9, 12, 13};
    std::vector<unsigned int> outputIndexes = {3, 4, 10, 11};
    std::vector<unsigned int> uselessIndexes = {7, 14};

    chipset->setType("4081");
    chipset->setName(name);
    this->assemble<nts::AndGate>(*chipset, inputIndexes, outputIndexes, uselessIndexes, 4);
    return (chipset);
}

nts::Component *Factory::create4011(const std::string &name) noexcept
{
    nts::Component *chipset = new nts::Component;
    std::vector<unsigned int> inputIndexes = {1, 2, 5, 6, 8, 9, 12, 13};
    std::vector<unsigned int> outputIndexes = {3, 4, 10, 11};
    std::vector<unsigned int> uselessIndexes = {7, 14};

    chipset->setType("4011");
    chipset->setName(name);
    this->assemble<nts::NandGate>(*chipset, inputIndexes, outputIndexes, uselessIndexes, 4);
    return (chipset);
}

nts::Component *Factory::create4071(const std::string &name) noexcept
{
    nts::Component *chipset = new nts::Component;
    std::vector<unsigned int> inputIndexes = {1, 2, 5, 6, 8, 9, 12, 13};
    std::vector<unsigned int> outputIndexes = {3, 4, 10, 11};
    std::vector<unsigned int> uselessIndexes = {7, 14};

    chipset->setType("4071");
    chipset->setName(name);
    this->assemble<nts::OrGate>(*chipset, inputIndexes, outputIndexes, uselessIndexes, 4);
    return (chipset);
}

nts::Component *Factory::create4030(const std::string &name) noexcept
{
    nts::Component *chipset = new nts::Component;
    std::vector<unsigned int> inputIndexes = {1, 2, 5, 6, 8, 9, 12, 13};
    std::vector<unsigned int> outputIndexes = {3, 4, 10, 11};
    std::vector<unsigned int> uselessIndexes = {7, 14};

    chipset->setType("4030");
    chipset->setName(name);
    this->assemble<nts::XorGate>(*chipset, inputIndexes, outputIndexes, uselessIndexes, 4);
    return (chipset);
}

nts::Component *Factory::create4001(const std::string &name) noexcept
{
    nts::Component *chipset = new nts::Component;
    std::vector<unsigned int> inputIndexes = {1, 2, 5, 6, 8, 9, 12, 13};
    std::vector<unsigned int> outputIndexes = {3, 4, 10, 11};
    std::vector<unsigned int> uselessIndexes = {7, 14};

    chipset->setType("4001");
    chipset->setName(name);
    this->assemble<nts::NorGate>(*chipset, inputIndexes, outputIndexes, uselessIndexes, 4);
    return (chipset);
}

nts::Component *Factory::createInput(const std::string &name, nts::Tristate state = nts::UNDEFINED) noexcept
{
    nts::Component *input (new nts::Component);
    std::vector<unsigned int> inputIndexes = {2, 3};
    std::vector<unsigned int> outputIndexes = {1};
    std::vector<unsigned int> uselessIndexes = {};

    input->setType("input");
    input->setName(name);
    this->assemble<nts::AndGate>(*input, inputIndexes, outputIndexes, uselessIndexes, 1);
    input->pins[1]->value = state;
    return (input);
}

nts::Component *Factory::createTrue(const std::string &name) noexcept
{
    nts::Component *input (new nts::Component);
    std::vector<unsigned int> inputIndexes = {2, 3};
    std::vector<unsigned int> outputIndexes = {1};
    std::vector<unsigned int> uselessIndexes = {};

    input->setType("true");
    input->setName(name);
    this->assemble<nts::AndGate>(*input, inputIndexes, outputIndexes, uselessIndexes, 1);
    input->pins[1]->value = nts::TRUE;
    return (input);
}

nts::Component *Factory::createFalse(const std::string &name) noexcept
{
    nts::Component *input (new nts::Component);
    std::vector<unsigned int> inputIndexes = {2, 3};
    std::vector<unsigned int> outputIndexes = {1};
    std::vector<unsigned int> uselessIndexes = {};

    input->setType("false");
    input->setName(name);
    this->assemble<nts::AndGate>(*input, inputIndexes, outputIndexes, uselessIndexes, 1);
    input->pins[1]->value = nts::FALSE;
    return (input);
}

nts::Component *Factory::createClock(const std::string &name) noexcept
{
    nts::Component *input (new nts::Component);
    std::vector<unsigned int> inputIndexes = {2, 3};
    std::vector<unsigned int> outputIndexes = {1};
    std::vector<unsigned int> uselessIndexes = {};

    input->setType("clock");
    input->setName(name);
    this->assemble<nts::AndGate>(*input, inputIndexes, outputIndexes, uselessIndexes, 1);
    return (input);
}

nts::Component *Factory::createOutput(const std::string &name) noexcept
{
    nts::Component *output (new nts::Component);
    std::vector<unsigned int> inputIndexes = {1, 2};
    std::vector<unsigned int> outputIndexes = {3};
    std::vector<unsigned int> uselessIndexes = {};

    output->setType("output");
    output->setName(name);
    this->assemble<nts::AndGate>(*output, inputIndexes, outputIndexes, uselessIndexes, 1);
    return (output);
}

nts::Component *Factory::createComponent(const std::string &type, const std::string &name, nts::Tristate inputState)
{
    if (type == "4030")
        return (this->create4030(name));
    if (type == "4011")
        return (this->create4011(name));
    if (type == "4001")
        return (this->create4001(name));
    if (type == "4081")
        return (this->create4081(name));
    if (type == "4071")
        return (this->create4071(name));
    if (type == "input")
        return (this->createInput(name, inputState));
    if (type == "output")
        return (this->createOutput(name));
    if (type == "true")
        return (this->createTrue(name));
    if (type == "false")
        return (this->createFalse(name));
    if (type == "clock")
        return (this->createClock(name));
    throw Error("Unknown chipset type, aborting");
}