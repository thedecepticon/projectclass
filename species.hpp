#ifndef SPECIES_HPP
#define SPECIES_HPP

#include "attributes.hpp"
#include <iostream>
#include <map>

std::map<unsigned char, attr> readSpecies(std::istream&);
void saveSpecies(std::ostream& out, std::map<unsigned char, attr>const&);
void print(std::map<unsigned char, attr>const&);

#endif