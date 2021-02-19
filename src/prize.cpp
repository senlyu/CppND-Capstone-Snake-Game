#include "prize.h"
#include <array>

// if type is not set, set as food
Prize::Prize() {
  type = 4;
}

// init
Prize::Prize(int n) {
  type = n;
}

// change type of the food
void Prize::setType(int n) {
  type = n;
}

// return type of the food
string Prize::GetType() {
  string name;
  switch (type)
  {
  case 1:
    name = "speed-down";
    break;
  case 2:
    name = "size-shrink";
    break;
  case 3:
    name = "score-more";
    break;
  case 4:
    name = "food";
    break;
  case 5:
    name = "wall";
    break;
  case 6:
    name = "invincible";
    break;
  }
  return name;
}

// return color of the prize
string Prize::GetColor() {
  string color;
  switch (type)
  {
  case 1:
    color = "red";
    break;
  case 2:
    color = "green";
    break;
  case 3:
    color = "yellow";
    break;
  case 4:
    color = "pink";
    break;
  case 5:
    color = "light-blue";
    break;
  case 6:
    color = "gold";
    break;
  }
  return color;
}

// return socre of the prize
int Prize::Score() {
  if (type==3) {
    return 2;
  }
  return 1;
}

// return the speed of the prize
int Prize::Speed() {
  if (type==1) {
    return -1;
  }
  return 1;
}

// return the size of the prize
int Prize::Size() {
  if (type==2) {
    return -1;
  }
  if (type==4) {
    return 1;
  }
  return 0;
}
