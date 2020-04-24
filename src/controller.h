#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void ReadInput();
  bool GetQuitInput() const;
  Snake::Direction GetArrowInput() const;
 private:
  bool _quite_key{false};
  Snake::Direction _arrow_keys{Snake::Direction::kUp};
};

#endif