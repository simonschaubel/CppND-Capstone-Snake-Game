#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood();
}

void Game::Init(std::unique_ptr<Controller> controller,
                std::unique_ptr<Renderer> renderer){
  _controller = std::move(controller);
  _renderer = std::move(renderer);
}

void Game::Run(std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (_running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    HandleInput();
    Update();
    _renderer->Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer->UpdateWindowTitle(score, frame_count);
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

void Game::HandleInput(){
  _controller->ReadInput();
  _running = !_controller->GetQuitInput();
  auto direction = _controller->GetArrowInput();
  VerifyDirection(direction);
}

void Game::VerifyDirection(const Snake::Direction& direction){
  if (snake.size == 1){
    snake.direction = direction;
    return;
  }

  switch (direction){
    case (Snake::Direction::kUp):
      if (snake.direction != Snake::Direction::kDown) snake.direction = Snake::Direction::kUp;
      break;
    case (Snake::Direction::kDown):
      if (snake.direction != Snake::Direction::kUp) snake.direction = Snake::Direction::kDown;
      break;
    case (Snake::Direction::kRight):
      if (snake.direction != Snake::Direction::kLeft) snake.direction = Snake::Direction::kRight;
      break;
    case (Snake::Direction::kLeft):
      if (snake.direction != Snake::Direction::kRight) snake.direction = Snake::Direction::kLeft;
      break;
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }