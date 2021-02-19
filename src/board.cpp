#include "board.h"
#include <vector>
#include <memory>
#include <iostream>
using std::vector;

Board::Board() {}

// add a wall into the board
void Board::addWall(std::unique_ptr<Wall> wall) {
  std::cout << "wall: " << _walls.size() << std::endl;
  _walls.push_back(std::move(wall));
}

// update newest snake into board
void Board::updateSnake(Snake snake) {
  _snake = snake;
}

// update newest prize into board
void Board::updatePrize(Prize prize) {
  _prize = prize;
}

// if a group of points want to added into board, check if the points are occupied 
bool Board::enterPoint(vector<SDL_Point> points) {
  vector<SDL_Point> all = Board::allPoints();
  for (auto & item : all) {
    for (auto & point : points) {
      if (point.x==item.x&&point.y==item.y) {
        std::cout << "found same: " << point.x << "," << point.y << std::endl;
        return false;
      }
    }
  }
  std::cout << "safe" << std::endl;
  return true;
}

// see if a group points is in wall area
bool Board::deadEnter(vector<SDL_Point> points) {
  vector<SDL_Point> all = Board::allWallsPoints();
  for (auto & item : all) {
    for (auto & point : points) {
      if (point.x==item.x&&point.y==item.y) {
        return true;
      }
    }
  }
  return false;
}

// retrieve all points in board which are occupied now
// including wall, snake, prize
vector<SDL_Point> Board::allPoints() {
  vector<SDL_Point> all = Board::allWallsPoints();

  vector<SDL_Point> t;
  vector<SDL_Point> snake_p = _snake.body;
  t.reserve(all.size()+snake_p.size());
  t.insert(t.end(), all.begin(), all.end());
  t.insert(t.end(), snake_p.begin(), snake_p.end());
  all = t;
  
  SDL_Point prize_p{_prize.x, _prize.y};
  all.push_back(prize_p);
  return all;
}

// if meets the maxmium amount of the walls, no longer add wall to the board
bool Board::wallMax() {
  if (_walls.size()>3) {
    return true;
  } else {
    return false;
  }
}

// return all points occupied by walls
vector<SDL_Point> Board::allWallsPoints() {
  vector<SDL_Point> all;
  for (auto & wall : _walls) {
    vector<SDL_Point> wallPoints = wall->getPosition();
    vector<SDL_Point> t;
    t.reserve(all.size()+wallPoints.size());
    t.insert(t.end(), wallPoints.begin(), wallPoints.end());
    t.insert(t.end(), all.begin(), all.end());
    all = t;
  }
  return all;
}