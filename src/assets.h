#pragma once

#include "tile_set.h"

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <unordered_map>

struct Texture {
    SDL_Texture* tex;
    SDL_Rect rect = { 0, 0, 0, 0 };
};

struct TextureDestroyer {
    void operator()(Texture* t) const
    {
        SDL_DestroyTexture(t->tex);
        delete t;
    }
};

using TexturePtr = std::unique_ptr<Texture, TextureDestroyer>;

class Assets {
public:
    Assets() {}
    ~Assets(){};

    void load_texture(SDL_Renderer* renderer, const std::string& file_name);
    Texture* get_texture(const std::string& file_name);

    void load_tile_set(const std::string& file_name);
    TileSet* get_tile_set();

private:
    std::unordered_map<std::string, TexturePtr> texture_map;

    std::unique_ptr<TileSet> tile_set;
};
