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

    this->tiles.mapWidth = width;
    this->tiles.mapHeight = height;

    this->tiles.fgTiles.resize(width * height);
    this->tiles.collidableTiles.resize(width * height);


    res.tileSetCols = mapJson["tilesets"][0]["columns"].get<int>(); // get amount of columns in tileSet for splitting
    for (auto& layer : mapJson["layers"])
    {
        //
        bool isBackgroundTile = false; // 
        std::vector<Object> tileLayer;
        tileLayer.resize(width * height);
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                int id = layer["data"][r * width + c].get<int>();
                if (id == 0) { // don't make objects for blank tiles
                    continue;
                }
                // get position based on row/col
                Object o(glm::vec2(c * TILE_SIZE, r * TILE_SIZE), id - 1, OBJ_LAND);
                if (layer["name"] == "Foreground") {
                    this->tiles.fgTiles[r * width + c] = o; // only allows one fg layer for now but can be changed
                } else {
                    if (layer["name"] == "Walls") {
                        o.solid = true;
                        this->tiles.collidableTiles[r * width + c] = o;
                    } else {
                        tileLayer[r * width + c] = o;
                        isBackgroundTile = true;
                    }
                }
            }          
        }
        if (isBackgroundTile) {
            this->tiles.mapTiles.push_back(tileLayer);
        }
    }
}

