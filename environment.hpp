#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

class environment{
  public:
    environment(char id):id(id){}
    char id;
    bool moveable = false;
};

#endif