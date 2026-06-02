#include <SDL3/SDL.h>
#include <fstream>
#include <iostream>

#include "../include/state.h"
#include "../include/gameState.h"
#include "../include/resources.h"
#include "../ext/json.hpp"

using json = nlohmann::json;

void GameState::init(const SDLState &state, Resources &res) {
    float acc = 2000.0f; 
    this->player.acc = glm::vec2(acc, acc);
    this->loadMap(state, res, "data/testMapMGS.json");
}

void GameState::loadMap(const SDLState& state, Resources& res, const std::string& path) { // loads map info of given json file
    std::ifstream file(path);
    if (!file.is_open()) {
        printf("failed to open map file\n");
        return;
    }

    json mapJson;
    file >> mapJson;

    int width = mapJson["width"];
    int height = mapJson["height"];

    res.tileSetCols = mapJson["tilesets"][0]["columns"].get<int>(); // get amount of columns in tileSet for splitting
    for (auto& layer : mapJson["layers"])
    {
        //
        for (int r = 0; r < height; r++) {
            
            for (int c = 0; c < width; c++) {
                int id = layer["data"][r * width + c].get<int>();
                if (id == 0) { // don't make objects for blank tiles
                    continue;
                }
                // get position based on row/col
                Object o(glm::vec2(c * TILE_SIZE, r * TILE_SIZE), id - 1);
                if (layer["name"] == "Foreground") {
                    this->fgTiles.push_back(o);
                } else {
                    this->mapTiles.push_back(o);
                }
            }          
        }
    }
}

