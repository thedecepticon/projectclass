

#include "simulation.hpp"
#include "area_map.hpp"
#include "point.hpp"
#include "organism.hpp"
#include "environment.hpp"
#include "species.hpp"
#include "attributes.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

int main() {
  //base testing
  // organism a1('o');
  // std::cout<<a1.id<<std::endl;

  // area_map::planta p1('a');
  // std::cout<<p1.id<<std::endl;

  // std::fstream readMap("map.txt");
  // area_map areaMap(readMap); //map initialized with organism x
  // std::cout << areaMap.at(3,3) <<std::endl;
  // readMap.close();
  
  //given map read
  std::fstream readS("species.txt");
  std::fstream readM("map.txt"); 
  simulation sim(readM,readS);
  readM.close();
  std::cout<<"Printing map"<<std::endl;
  sim.printMap();
  std::cout<<"saving to file"<<std::endl;
  sim.saveMap();//testSave.txt
  // std::cout<<sim.envMap.at(48,12)<<std::endl; //space
  // //std::cout<<sim.envMap.at(49,12)<<std::endl; //seg fault
  // std::cout<<sim.envMap.at(49,11)<<std::endl; // x 
  // std::cout<<sim.envMap.at(49,0)<<std::endl; //shows the x id

  //saved map read
  std::fstream readS2("species.txt");
  std::fstream read2nd("testSave.txt");
  simulation testtwo(read2nd,readS2);
  read2nd.close();
  std::cout<<"Printing map"<<std::endl;
  testtwo.printMap();
  //std::cout<<"saving to file"<<std::endl;
  //testtwo.saveMap("testSavingAReadSave.txt");
  // std::cout<<testtwo.envMap.at(43,0)<<std::endl;
  // std::cout<<testtwo.envMap.at(44,0)<<std::endl;
  // std::cout<<testtwo.envMap.at(45,0)<<std::endl;
  // std::cout<<testtwo.envMap.at(46,0)<<std::endl;
  // std::cout<<testtwo.envMap.at(47,0)<<std::endl;
  // std::cout<<testtwo.envMap.at(48,0)<<std::endl;
  // std::cout<<testtwo.envMap.at(49,0)<<std::endl; //seg fault

  //species file testing
  std::cout<<std::endl;
  std::fstream rdspecies("species.txt");
  // std::map<char, attr> species = readSpecies(rdspecies);
  species species(rdspecies);
  rdspecies.close();
  // for (auto e : species)
  //   std::cout << e.second.type<<std::endl;

  species.printSpecies();
  
  std::ofstream output("testSaveSpecies.txt");
  species.saveSpecies(output);
  output.close();
}