#pragma once

#include "assets.h"
#include "world.h"

#include <memory>

class Game;

extern std::unique_ptr<Game> game;

class Game
{
  public:
    Game() : running( false ),
             assets( std::make_unique<Assets>() ),
             world( std::make_unique<World>() ) {}
    ~Game();

    bool start_up();
    void update();
    void shut_down();
    bool is_running();

    std::unique_ptr<Assets> assets;
    std::unique_ptr<World> world;

  private:
    bool running;
};
