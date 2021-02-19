#ifndef WALL_H
#define WALL_H

#include <vector>
#include "SDL.h"
using std::vector;



class Wall {
 public:
  Wall();
  Wall(const Wall &wall);
  ~Wall();
  Wall &operator=(const Wall &wall);
  Wall(Wall &&wall);
  Wall &operator=(Wall &&wall);

  Wall(int x, int y, int d, int l);
  vector<SDL_Point> getPosition();

 private:
  vector<SDL_Point> _position;
  
};

#endif