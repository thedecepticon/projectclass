#ifndef AREA_MAP_HPP
#define AREA_MAP_HPP

#include "species.hpp"
#include "attributes.hpp"
#include "organism.hpp"
#include "environment.hpp"
#include "point.hpp"
#include <map>
#include <vector>
#include <sstream>
#include <iostream>

//#define DEBUG

struct area_map{
  area_map(std::istream& inMap,std::istream& inSpec):mySpecies(inSpec){
    //species = readSpecies(inSpec);
    myMap = read(inMap); //constructor initiates the read
  }
  std::vector<std::vector<environment*> > read(std::istream& incoming){
      std::vector<std::vector<environment*> > localMap;
      std::string line;
#ifdef DEBUG
      int row = 0;
      int col = 0;
      while(std::getline(incoming, line)){
        std::cout<<"Line is: " << line <<":end"<< std::endl;
        if(localMap.size() && line.size() != localMap.front().size()){
            std::cout<<"dimension error "<<localMap.size()<<" "<< line.size() << " "<< localMap.front().size()<< " manual row count " << row << std::endl;
        }
        ++row;
        col = 0;//reset for next row
        std::vector<environment*> currentrow;
        std::istringstream ss(line);
        char charIn;
        while(ss>>std::noskipws>>charIn){//don't skip whitespace
            std::cout<<"pushing: " << charIn<<std::endl;
            currentrow.push_back(categorize(charIn));
            col++;
        }          
        localMap.push_back(currentrow);//push finished row into matrix
      }
      // p.x = col;
      // p.y = row;
      //std::cout<<"Row: "<< row << " Col: "<<col<<std::endl;
      std::cout<<localMap.size()<<" "<<localMap.front().size()<< col<< std::endl;
    return localMap;
#else
    while(std::getline(incoming, line)){
        if(localMap.size() && line.size() != localMap.front().size()){
            std::cout<<"map dimension mismatch"<<std::endl;
            return std::vector<std::vector<environment*> >();
        }
        std::vector<environment*> currentrow;
        std::istringstream ss(line);
        char charIn;
        while(ss>>std::noskipws>>charIn){//don't skip whitespace
            currentrow.push_back(categorize(charIn));
        }          
        localMap.push_back(currentrow);//push finished row into matrix
    }
    return localMap;
#endif    
  }//end read()

  void save(std::ostream& out) const{
#ifdef DEBUG
    std::cout<<"(front.size , size) " << myMap.front().size()<<","<<myMap.size()<< " (back.size) "<<myMap.back().size()<<std::endl;
#endif
      for ( auto j = 0; j < extent().y; ++j ){
            for ( auto i = 0; i < extent().x; ++i )
                out<< at( i, j );
            if (j !=extent().y-1) out <<"\n";//tag new lines minus last row
      }            
  }
  environment* categorize(char alpha){
    if(mySpecies.mySpecies.count(alpha)>0){
      return new organism(alpha,mySpecies.mySpecies.find(alpha)->second);
    }
    switch(alpha){
      case '~': return new environment('~');
      case ' ': return new environment(' ');
      case '#': return new environment('#');
    }
    return new environment('x');//indicate error
  }
 
  
  point extent() const {
    if (myMap.size()){ //captures seg fault if map not init
      return point (myMap.front().size(),myMap.size());
    }
    else{
      return point();
    }
  }
  //char& at(int i, int j){return myMap[j][i]; }
  const char& at(int i, int j) const {return myMap[j][i]->id; }  
  //decide()
  //check the area of the map around a living organism from the vector and try to decide if it is going to move, eat, grow, regrow, or flee.

  //members
  //std::map<char,attr> species;
  species mySpecies;
  std::vector<std::vector<environment*> > myMap;
  
}; //end area_map

#endif