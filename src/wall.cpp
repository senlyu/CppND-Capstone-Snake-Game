#include "wall.h" 
#include "board.h"

// init a wall with position_x, position_y, direction, and length
Wall::Wall(int x, int y, int d, int l) {
  SDL_Point newOne{x,y};
  _position.push_back(newOne);
  for (int i=1;i<l;i++) {
    switch (d)
    {
    case 0:
      x++;
      break;
    case 1:
      x--;
      break;
    case 2:
      y++;
      break;
    case 3:
      y--;
      break;
    }
    SDL_Point newOne{x,y};
    _position.push_back(newOne);
  }
}

// return all points of that wall
vector<SDL_Point> Wall::getPosition() {
  return _position;
}

Wall::Wall() {
  return;
}

Wall::~Wall() {
  return;
}

Wall::Wall(const Wall &wall) {
  _position = wall._position;
}

Wall &Wall::operator=(const Wall &wall) {
  _position = wall._position;
}

Wall::Wall(Wall &&wall) {
  _position = wall._position;
}

Wall &Wall::operator=(Wall &&wall) {
  _position = wall._position;
}