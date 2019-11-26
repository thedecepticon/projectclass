

#include "species.hpp"
#include "attributes.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#define DEBUG
//building components for class project
//link to base github announcement https://github.com/uiowa-cs-3210-0001/cs3210-assignments-fall2019/tree/master/course-project
//concepts
// https://repl.it/@Sorceror89/lab13-exercise2
// https://repl.it/@Sorceror89/lab14-exercise1
//reference to matrix homework https://repl.it/@Sorceror89/hw9-problem1
//read istream https://repl.it/@Sorceror89/hw10-problem1
//https://repl.it/@Sorceror89/hw11-problem1
//https://repl.it/@Sorceror89/stringtolist
//https://repl.it/@Sorceror89/Readline     //error reproduction

class environment{
  public:
    environment(char id):id(id){}
    char id;
    bool moveable = false;
};

class organism: public environment{
    public:
      organism(char id):environment(id){}
      organism(char id, attr info):environment(id),specs(info){}
      organism* pos_overlap; //point to an object that we're taking the place of
      attr specs; //dynamic attributes of an organism
      
    };


class point {
      public:
      point(int x, int y): x(x),y(y){}
      point(){}
      bool operator==( point const& p ) const { return x==p.x && y==p.y; }
      bool operator!=( point const& p ) const{ return !( x==p.x && y==p.y ); }
      int x = 0;
      int y = 0;
  };

struct area_map{
  // area_map(std::istream& incoming){
  //   read(incoming);
  // }
  area_map(std::istream& incoming,std::istream& spec){
    species = readSpecies(spec);
    myMap = read(incoming); //constructor initiates the read
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
    if(species.count(alpha)>0){
      return new organism(alpha,species.find(alpha)->second);
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

  std::vector<std::vector<environment*> > myMap;
  std::map<char,attr> species;
};


class simulation{
  public:
  simulation(std::istream& inMap,std::istream& inSpecies):envMap(inMap,inSpecies){}

  void printMap(){
    std::ostringstream out;
    envMap.save(out);  //save reused
    std::cout<<out.str()<<std::endl;
  }

  void saveMap(std::string fn="testSave.txt"){
    std::ofstream output(fn);
    envMap.save(output); //save reused
    output.close();
  }
  
  //map
  area_map envMap; //error when trying to initialize as envMap(12,48) 

  // engine/menu once started 
  
};//end class simulation

  
//menu (engine) input loop q to quit or type a map name to open test/verify, then 2nd input interation count

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
  std::cout<<"saving to file"<<std::endl;
  testtwo.saveMap("testSavingAReadSave.txt");
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
  std::map<char, attr> species = readSpecies(rdspecies);
  rdspecies.close();
  // for (auto e : species)
  //   std::cout << e.second.type<<std::endl;

  print(species);
  
  std::ofstream output("testSaveSpecies.txt");
  saveSpecies(output, species);
  output.close();
}