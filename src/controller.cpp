#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ReadInput(){
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      _quite_key = true;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          _arrow_keys = Snake::Direction::kUp;
          break;
        case SDLK_DOWN:
          _arrow_keys = Snake::Direction::kDown;
          break;
        case SDLK_LEFT:
          _arrow_keys = Snake::Direction::kLeft;
          break;
        case SDLK_RIGHT:
          _arrow_keys = Snake::Direction::kRight;
          break;
      }
    }
  }
}

Snake::Direction Controller::GetArrowInput() const { return _arrow_keys; }
bool Controller::GetQuitInput() const { return _quite_key; }