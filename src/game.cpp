#include "game.h"
#include <iostream>
#include "SDL.h"
#include "prize.h"
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)),
      random_p(0, static_cast<int>(5)),
      random_d(0, static_cast<int>(3))
      {
  
  // init variable for invincible snake
  // if true the snake should not dead
  // heap variable
  bool* invincibleS = new bool;
  *invincibleS = false;
  invincibleSnake = invincibleS;

  // init first prize, always be food
  Game::Place(food, 4, snake);

  // update prize and snake to board
  board.updatePrize(food);
  board.updateSnake(snake);
}

Game::~Game() {
  // delete heap variable
  delete invincibleSnake;
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    
    //render all things in the game 
    renderer.Render(snake, food, board, invincibleSnake);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

// place a prize into the game
// t is used manually setting the type of the prize
void Game::Place(Prize &p, int t, Snake s) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      int type;
      // if t is 0, will random set the type of the prize
      if (t==0) {
        // if the snake is too short, should not provide shrink prize
        if (s.size<=2) {
          type = 4;
        // if the speed of the snake is too slow, should not provide slow-down prize
        } else if (s.speed<=0.1) {
          type = 4;
        } else {
          type = random_p(engine) + 1;  
        }
      } else {
        // if the type of the prize is setted up, use it
        type = t;
      }
      std::cout << "next food type: " << type << std::endl;
      p.setType(type);
      p.x = x;
      p.y = y;
      std::cout << "next food position: " << p.x << ", " << p.y << std::endl;
      std::cout << "next food type: " << p.GetType() << std::endl;
      return;
    }
  }
}

// new thread to calculate time
// snake have 5 second invicible time
void TimerThread(bool *invincibleSnake) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // get back to normal after 5 seconds
    *invincibleSnake = false;
}

// update the prize information
// different type of prize will have different effect for snake's status
void Game::PrizeUpdate(Prize &p, int new_x, int new_y, int t) {
  if (p.x == new_x && p.y == new_y) {
    std::cout << "eat " << p.GetType() << std::endl;
    if (p.GetType().compare("wall")==0) {
      std::cout << "start wall" << std::endl;
      Game::placeWall();
    } else if (p.GetType().compare("invincible")==0) {
      std::cout << "invincible" << std::endl;
      *invincibleSnake = true;
      std::thread invincibleTime(TimerThread, invincibleSnake);
      invincibleTime.detach();
    }
    score = score + p.Score();
    snake.GrowBody(p.Size());
    snake.speed = snake.speed + 0.01 * p.Speed();
    Place(p, t, snake);
    std::cout << "status " << "growing: " << snake.growing << std::endl;
    std::cout << "status " << "size: " << snake.size << std::endl;
    std::cout << "status " << "speed: " << snake.speed << std::endl;
  }
}

// build a wall
void Game::placeWall() {
  int x, y, d, l;
  if (board.wallMax()) {
    return;
  }
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    d = random_d(engine);
    l = 3;
    std::unique_ptr<Wall> wall = std::make_unique<Wall>(x, y, d, l);
    vector<SDL_Point> wallPoints = wall->getPosition();
    if (board.enterPoint(wallPoints)) {
      board.addWall(std::move(wall));
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update(invincibleSnake);

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  PrizeUpdate(food, new_x, new_y, 0);

  board.updatePrize(prize);
  board.updateSnake(snake);

// if snake get into wall also dead
  vector<SDL_Point> total = snake.body;
  SDL_Point current_cell{
      static_cast<int>(snake.head_x),
      static_cast<int>(snake.head_y)};
  total.push_back(current_cell);
  if ( !(*invincibleSnake) && board.deadEnter(total) ) {
    snake.alive = false;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }