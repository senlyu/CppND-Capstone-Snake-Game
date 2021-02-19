#ifndef PRIZE_H
#define PRIZE_H

#include <array>
#include <string>
using std::string;

class Prize {
 public:
  Prize();
  Prize(int n);
  // ~Prize();
  string GetType();
  string GetColor();
  int Score();
  int Speed();
  int Size();
  int x;
  int y; 
  void setType(int n);

 private:
  int type;
  
};

#endif