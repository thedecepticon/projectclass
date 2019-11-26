#ifndef SPECIES_HPP
#define SPECIES_HPP

#include "attributes.hpp"
#include <iostream>
#include <map>

std::map<char, attr> readSpecies(std::istream&);
void saveSpecies(std::ostream& out, std::map<char, attr>const&);
void printSpecies(std::map<char, attr>const&);

#endif