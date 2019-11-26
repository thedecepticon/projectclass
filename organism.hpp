#ifndef ORGANISM_HPP
#define ORGANISM_HPP

#include "attributes.hpp"
#include "environment.hpp"

class organism: public environment{
    public:
      organism(char id):environment(id){}
      organism(char id, attr info):environment(id),specs(info){}
      organism* pos_overlap; //point to an object that we're taking the place of
      attr specs; //dynamic attributes of an organism
      
    };


#endif