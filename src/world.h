#pragma once

#include <string>
#include <vector>

static const int WORLD_MAX_WIDTH = 50;
static const int WORLD_MAX_HEIGHT = 50;

class World {
public:
    World()
        : tiles(WORLD_MAX_WIDTH, std::vector<int>(WORLD_MAX_HEIGHT))
    {
    }
    ~World(){};

    /**
     * Loads a map from a CSV file.
     */
    void load_map(const std::string& file_name);
    void render();

private:
    std::vector<std::vector<int>> tiles;
};

//static std::string determine_texture(int id);
//
///**
// * Parses a CSV line into integers.
// * Results are pushed back into the provided vector 
// */
//static void parse_csv_line(const std::string& line, std::vector<int>& vec);
