

#include "species.hpp"
#include "attributes.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

//building components for class project
//link to base github announcement https://github.com/uiowa-cs-3210-0001/cs3210-assignments-fall2019/tree/master/course-project
//concepts
// https://repl.it/@Sorceror89/lab13-exercise2
// https://repl.it/@Sorceror89/lab14-exercise1
//reference to matrix homework https://repl.it/@Sorceror89/hw9-problem1
//read istream https://repl.it/@Sorceror89/hw10-problem1
//https://repl.it/@Sorceror89/hw11-problem1
//https://repl.it/@Sorceror89/stringtolist

class environment{
  public:
    environment(unsigned char id):id(id){}
    unsigned char id;
    bool moveable = false;
};

class organism: public environment{
    public:
      organism(unsigned char id):environment(id){}
      organism(unsigned char id, attr info):environment(id),specs(info){}
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
  area_map(std::istream& incoming){
    read(incoming);
  }
  area_map(std::istream& incoming,std::istream& spec){
    species = readSpecies(spec);
    myMap = read(incoming); //constructor initiates the read
  }
  std::vector<std::vector<environment*> > read(std::istream& incoming){
    std::vector<std::vector<environment*> > localMap;
    int row = 0;
    int col = 0;
    std::string line;
    while(std::getline(incoming, line)){
        //std::cout<<"Line is: " << line <<":end"<< std::endl;
        //dimension inspection
        //row 0 is not compared with anything
        //line dimension check integration fails on the last row. due to missing new line characters? rather all lines contain crlf vs lf with the exception of the last row and the last row is the one triggering a bad dimension check.
        if(localMap.size() && line.size() != localMap.front().size())
            std::cout<<"dimension error "<<localMap.size()<<" "<< line.size() << " "<< localMap.front().size()<< " manual row count " << row << std::endl;
        //     // return std::vector<std::vector<environment*> >();

           
        // if(localMap.size()>0)
        //   std::cout<<localMap.size()<<" "<< line.size() << " "<< localMap.front().size()<< " manual row count " << row << std::endl;
        // else{
        //   std::cout<<"row 0 not inspected"<<std::endl;
        // }
        ++row; 
        // std::cout<<row<<std::endl;
        col = 0; //reset for next row (consider int old_col as a means of finding a maximum column width as a just in case)
        std::vector<environment*> currentrow;
        std::istringstream ss(line);
        unsigned char charIn;
        while(ss>>std::noskipws>>charIn){//don't skip whitespace
            
            //std::cout<<"pushing: " << charIn<<std::endl;
            //currentrow.push_back(charIn); //push characters into current row
            
            currentrow.push_back(categorize(charIn));
            col++;
            
        }          
        localMap.push_back(currentrow);//push finished row into matrix
    }
    //std::cout<<"Row: "<< row << " Col: "<<col<<std::endl;
    //update the point of the class (recall backward than used to col x row)
    // p.x = col;
    // p.y = row;
    // std::cout<<localMap.size()<<" "<<localMap.front().size()<< col<< std::endl;
    return localMap;
  }
  void save(std::ostream& out) const{
      for ( auto j = 0; j < extent().y; ++j ){
            for ( auto i = 0; i < extent().x; ++i )
                out<< at( i, j );
            if (j !=extent().y-1) out <<"\r\n";//tag new lines when another row will be processed (none for last line)
            //out<<"\n";  // new line every time
      }
      //std::cout << out.str(); //when input arg changed to ostringstream
            
  }
  environment* categorize(unsigned char alpha){
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
    //integration of extent without point requires adjustment
    auto nrows = myMap.size();
    return nrows > 0
        ? point( myMap.front().size()-1, nrows )
        : point();} 
  //methods
  //char& at(int i, int j){return myMap[j][i]; }
  const unsigned char& at(int i, int j) const {return myMap[j][i]->id; }     
  //members
  //dimension of the matrix (col x row)
  //point p;
  std::vector<std::vector<environment*> > myMap;
  std::map<unsigned char,attr> species;
};


class simulation{
  public:
  simulation(std::istream& inMap,std::istream& inSpecies):envMap(inMap,inSpecies){}

  
  void printMap(){
    std::ostringstream out;
    envMap.save(out);
    std::cout<<out.str()<<std::endl;
  }
  void saveMap(std::string fn="testSave.txt"){
    std::ofstream output(fn);
    envMap.save(output);
    output.close();
  }
  //read should add objects to map and to organism vector when appropriate
  //map
  //use a basic rectangle as an empty map clone with contains to check coordinates or error trap 2d array lookups??
  
  //map for read to load for the sim
  area_map envMap; //error when trying to initialize as envMap(12,48) 
  // std::map<unsigned char,attr> species;
  //vector of organisms for iteration

  //counter
  //concatenate a string with a stringified integer to dynamically name living organism and subsequently count the total number of living organism for the lifetime of the simulation

  //decide()
  //check the area of the map around a living organism from the vector and try to decide if it is going to move, eat, grow, regrow, or flee.


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
  sim.printMap();
  sim.saveMap();//testSave.txt

  //saved map read
  std::fstream readS2("species.txt");
  std::fstream read2nd("testSave.txt");
  simulation testtwo(read2nd,readS2);
  read2nd.close();
  testtwo.printMap();
  testtwo.saveMap("testSavingAReadSave.txt");

  //species file testing
  std::fstream rdspecies("species.txt");
  std::map<unsigned char, attr> species = readSpecies(rdspecies);
  rdspecies.close();
  // for (auto e : species)
  //   std::cout << e.second.type<<std::endl;

  print(species);
  
  std::ofstream output("testSaveSpecies.txt");
  saveSpecies(output, species);
  output.close();
}