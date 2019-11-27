
// #include "attributes.hpp"
// #include <map>
// #include <set>
// #include <iostream>
// #include <sstream>

// std::set<char> filter{',', '[', ']', ' '};

// std::map<char,attr> readSpecies(std::istream& input){
//     std::map<char, attr> attributes;
    
//     for(std::string line; std::getline(input,line);){
//       //std::cout << line << std::endl;
//       std::istringstream in(line);
//       std::string type;
//       char id;
//       std::string foodchain;
//       int max_energy;
//       int regrowth;
//       in >> type >> id;
//       if (type=="plant"){
//           in >> regrowth >> max_energy;
//           attr curEle(type,regrowth,max_energy);
//           attributes[id]=curEle;
          
//       }
//       else{
//           getline(in, foodchain,']');
//           in >> max_energy;
//           std::vector<char> edible;
//           for (int i = 0; i < foodchain.size(); ++i){
//               if(filter.count(foodchain[i])==0){
//                 char foodtoken = foodchain[i];
//                 edible.push_back(foodtoken);
//               }
//           }
//           attr curEle(type,max_energy,edible,true);
//           attributes[id]=curEle;
//       }

//     }
//     return attributes;
// }

// void saveSpecies(std::ostream& out, std::map<char, attr>const& species) {

//       for(auto e: species){
//         if (e.second.type=="plant"){
//           out << e.second.type <<" " << e.first << " " << e.second.regrowth << " " << e.second.max_energy;
//         }else{
//           out << e.second.type <<" "<< e.first <<" [";
//           for (int i = 0; i < e.second.food.size();++i){
//                 out << e.second.food[i];
//                 if (i != e.second.food.size()-1)
//                     out << ", ";
//           }
//           out << "] " << e.second.max_energy;
//         }
//         out << std::endl;
//       }
  
// }

// void printSpecies(std::map<char, attr>const& attr){
//     std::ostringstream out;
//     saveSpecies(out,attr);
//     std::cout<<out.str()<<std::endl;
//   }

