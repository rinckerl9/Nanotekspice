/*
** EPITECH PROJECT, 2020
** NanoTekSpice
** File description:
** A slightly crappier version of something I've done already
*/

#pragma once

namespace nts {
    enum Tristate {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
    };
    enum PinType {
        INPUT = true,
        OUTPUT = false,
        USELESS = (-true)
    };
}