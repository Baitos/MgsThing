#include "../include/map.h"

#include "../ext/json.hpp"
#include <fstream>
#include <iostream>
#include "../include/state.h"
#include "../include/gameState.h"
#include "../include/resources.h"

using json = nlohmann::json;

void loadMap(SDLState& state, GameState& gs, const Resources& res, const std::string& path) { // loads map info of given json file
    std::ifstream file(path);
    if (!file.is_open()) {
        printf("failed to open map file\n");
        return;
    }

    json mapJson;
    file >> mapJson;

    int width = mapJson["width"];
    int height = mapJson["height"];

    for (auto& layer : mapJson["layers"])
    {
        std::cout << layer["data"].dump() << std::endl;
        //
        for (int c = 0; c < height; c++) {
            
            for (int r = 0; r < width; r++) {
                int id = layer["data"][c * width + r].get<int>();
                if (id == 0) { // don't make objects for blank tiles
                    continue;
                }

                // get position based on row/col, get tileID from data
                Object l(glm::vec2(r * TILE_SIZE, c * TILE_SIZE), id - 1);
                gs.mapTiles_.push_back(l);
            }          
        }
        std::cout << std::endl;
    }
}

