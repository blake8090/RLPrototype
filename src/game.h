#pragma once

#include "assets.h"

#include <memory>

class Game;

extern std::unique_ptr<Game> game;

class Game
{
  public:
    Game() : running( false ),
             assets( std::make_unique<Assets>() ) {}
    ~Game();

    bool start_up();
    void update();
    void shut_down();
    bool is_running();

    std::unique_ptr<Assets> assets;

  private:
    bool running;
};
