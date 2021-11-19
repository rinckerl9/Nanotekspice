/*
** EPITECH PROJECT, 2020
** NanoTekSpice
** File description:
** A slightly crappier version of something I've done already
*/

#include "IComponent.hpp"

void nts::Gate::setFirstLink(unsigned int index)
{
    this->firstLink = index;
}

void nts::Gate::setSecondLink(unsigned int index)
{
    this->secondLink = index;
}

void nts::Gate::setOutputLink(unsigned int index)
{
    this->outputLink = index;
}

nts::Tristate nts::AndGate::compute(void)
{
    if (this->first == FALSE || this->second == FALSE)
        return FALSE;
    if (this->first == TRUE && this->second == TRUE)
        return TRUE;
    return UNDEFINED;
}

nts::Tristate nts::NandGate::compute(void)
{
    if (this->first == FALSE || this->second == FALSE)
        return TRUE;
    if (this->first == TRUE && this->second == TRUE)
        return FALSE;
    return UNDEFINED;
}

nts::Tristate nts::OrGate::compute(void)
{
    if (this->first == TRUE || this->second == TRUE)
        return TRUE;
    if (this->first == UNDEFINED || this->second == UNDEFINED)
        return UNDEFINED;
    return FALSE;
}

nts::Tristate nts::XorGate::compute(void)
{
    if (this->first == UNDEFINED || this->second == UNDEFINED)
        return UNDEFINED;
    if (this->first == TRUE && this->second == TRUE)
        return FALSE;
    if (this->first == TRUE || this->second == TRUE)
        return TRUE;
    return FALSE;
}

nts::Tristate nts::NorGate::compute(void)
{
    if (this->first == TRUE || this->second == TRUE)
        return FALSE;
    if (this->first == UNDEFINED || this->second == UNDEFINED)
        return UNDEFINED;
    return TRUE;
}