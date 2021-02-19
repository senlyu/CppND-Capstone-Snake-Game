#ifndef GAME_H
#define GAME_H

#include <random>

#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <vector>
#include "board.h"
#include <memory>
using std::vector;


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  bool* invincibleSnake;
  Snake snake;
  Prize food;
  Prize prize;
  Board board;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_p;
  std::uniform_int_distribution<int> random_d;

  int score{0};

  void Place(Prize &p, int t, Snake s);
  void PrizeUpdate(Prize &p, int new_x, int new_y, int t);
  void Update();

  void placeWall();
};

#endif