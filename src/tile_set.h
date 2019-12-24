#pragma once

#include <memory>
#include <string>
#include <vector>

constexpr int MAX_TILES = 100;

struct Tile {
    std::string gfx;
    std::string ceilingGfx;
    bool collidable = false;
};

class TileSet
{
  public:
    TileSet() {}
    ~TileSet();

    void load_tile_set( const std::string& file_name );
    Tile* get_tile( int id );

  private:
    std::vector<std::unique_ptr<Tile>> tiles;
};
