#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Init(std::unique_ptr<Controller> controller,
            std::unique_ptr<Renderer> renderer);
  void Run(std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  
 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  std::unique_ptr<Controller> _controller;
  std::unique_ptr<Renderer> _renderer;

  bool _running{true};
  int score{0};

  void PlaceFood();
  void Update();
  void HandleInput();
  void VerifyDirection(const Snake::Direction& direction);
};

#endif