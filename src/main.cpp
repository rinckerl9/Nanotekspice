/*
** EPITECH PROJECT, 2020
** NanoTekSpice
** File description:
** A slightly crappier version of something I've done already
*/

#include "Error.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <regex>
#include "Factory.hpp"
#include "Component.hpp"

void doSimulation(std::map<std::string, nts::Component *> &components, std::vector<std::pair<std::pair<std::string, unsigned int>, std::pair<std::string, unsigned int>>> &links)
{
    for (unsigned int i = 0; i < links.size(); i++) {
        // std::cerr << links[i].first.first << " / " << links[i].first.second << " / " << links[i].second.first << " / " << links[i].second.second << "\n";
        components[links[i].second.first]->pins[links[i].second.second]->value = components[links[i].first.first]->pins[links[i].first.second]->value;
        if (components[links[i].second.first]->getType() != "output" && components[links[i].second.first]->getType() != "input" && components[links[i].second.first]->getType() != "clock" && components[links[i].second.first]->getType() != "true" && components[links[i].second.first]->getType() != "false")
            components[links[i].second.first]->compute();
    }
}

void parseFirst(std::string &buffer, std::string *splitBuffer)
{
    int j = 0;

    for (int i = 0; i < 4; i++)
        splitBuffer[i] = "";
    for (int i = 0; i < buffer.size(); i++) {
        if (j == 4)
            break;
        if (buffer[i] == ' ' || buffer[i] == '\t') {
            if (buffer[i + 1] && buffer[i + 1] != ' ' && buffer[i + 1] != '\t')
                j++;
            continue;
        }
        splitBuffer[j] += buffer[i];
    }
    if (j == 0)
        throw Error("parsing error, aborting");
}

void parseSecond(std::string &buffer, std::string *splitBuffer)
{
    int j = 0;

    for (int i = 0; i < 4; i++)
        splitBuffer[i] = "";
    for (int i = 0; i < buffer.size(); i++) {
        if (j == 4)
            break;
        if (buffer[i] == ' ' || buffer[i] == ':' || buffer[i] == '\t') {
            if (buffer[i + 1] && buffer[i + 1] != ' ' && buffer[i + 1] != '\t' && buffer[i + 1] != ':')
                j++;
            continue;
        }
        splitBuffer[j] += buffer[i];
    }
    if (j == 0)
        throw Error("parsing error, aborting");
}

int main(int argc, char **argv)
{
    Factory fact;
    std::map<std::string, nts::Component *> components;
    std::vector<std::pair<std::pair<std::string, unsigned int>, std::pair<std::string, unsigned int>>> links;
    std::regex rgxEq("[A-Za-z0-9]+=[0-9]+");
    std::string buffer;
    std::string sBuf[] = {"", "", "", ""};
    std::ifstream stream;
    unsigned int tick = 0;
    bool secondaryParsingMode = false;

    if (argc != 2)
        return 84;
    else {
        try {
            stream.open(argv[1]);
            if (!stream.is_open())
                throw Error("Can't find file");
            if (stream.peek() == std::ifstream::traits_type::eof())
                throw Error("File is empty, aborting");
            while (std::getline(stream, buffer)) {
                if (!buffer.empty() && buffer == ".links:") {
                    secondaryParsingMode = true;
                    continue;
                }
                if (buffer.empty() || buffer[0] == '#' || buffer[0] == '.')
                    continue;
                if (!secondaryParsingMode) {
                    parseFirst(buffer, sBuf);
                    components[sBuf[1]] = fact.createComponent(sBuf[0], sBuf[1]);
                } else {
                    parseSecond(buffer, sBuf);
                    for (int h = 0; h < 4; h++) {
                        if (sBuf[h].empty())
                            throw Error("Fatal parsing error, aborting");
                    }
                    if (components[sBuf[0]]->getType() == "output" || components[sBuf[2]]->getType() == "input" || components[sBuf[2]]->getType() == "true" || components[sBuf[2]]->getType() == "false" || components[sBuf[2]]->getType() == "clock" || components[sBuf[2]]->pins[std::stoi(sBuf[3])]->state == nts::OUTPUT)
                        links.push_back({{sBuf[2], std::stoi(sBuf[3])}, {sBuf[0], std::stoi(sBuf[1])}});
                    else
                        links.push_back({{sBuf[0], std::stoi(sBuf[1])}, {sBuf[2], std::stoi(sBuf[3])}});
                }
            }
            stream.close();
            std::cout << "> ";
            while (std::getline(std::cin, buffer)) {
                if (std::regex_match(buffer, rgxEq)
                    && components.find(buffer.substr(0, buffer.find('='))) != components.end()
                    && (components[buffer.substr(0, buffer.find('='))]->getType() == "input" || components[buffer.substr(0, buffer.find('='))]->getType() == "clock"))
                    components[buffer.substr(0, buffer.find('='))]->pins[1]->value = (nts::Tristate)(std::stoi(buffer.substr(buffer.find('=') + 1)) % 2);
                if (buffer == "simulate") {
                    doSimulation(components, links);
                    tick++;
                    for (const auto &it: components) {
                        if (it.second->getType() == "clock" && it.second->pins[1]->value == nts::TRUE)
                            it.second->pins[1]->value = nts::FALSE;
                        else if (it.second->getType() == "clock" && it.second->pins[1]->value != nts::UNDEFINED)
                            it.second->pins[1]->value = nts::TRUE;
                    }
                }
                if (buffer == "display") {
                    std::cout << "tick: " << tick << "\ninput(s):\n";
                    for (const auto &it: components) {
                        if (it.second->getType() == "input" || it.second->getType() == "clock" || it.second->getType() == "true" || it.second->getType() == "false")
                            it.second->dump();
                    }
                    std::cout << "output(s):\n";
                    for (const auto &it: components) {
                        if (it.second->getType() == "output")
                            it.second->dump();
                    }
                }
                if (buffer == "exit")
                    break;
                std::cout << "> ";
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
            return (84);
        }
    }
    return 0;
}