#ifndef BOARD_H
#define BOARD_H

#include "snake.h"
#include "prize.h"
#include <vector>
#include "wall.h"
#include <memory>
using std::vector;

class Board {
 public:
  Board();
  // ~Board();
  void addWall(std::unique_ptr<Wall> wall);
  void updateSnake(Snake snake);
  void updatePrize(Prize prize);
  bool enterPoint(vector<SDL_Point> points);
  bool deadEnter(vector<SDL_Point> points);
  bool wallMax();
  vector<SDL_Point> allWallsPoints();

 private:
  vector<SDL_Point> allPoints();
  vector<std::unique_ptr<Wall>> _walls;
  Snake _snake;
  Prize _prize;
};

#endif