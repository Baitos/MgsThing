#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "../ext/glm/glm.hpp"
#include "state.h"
#include "object.h"
#include "player.h"

// for future reference, make sure to not put raw points, file handlers, or non-copyables
// we need to be able to restore previous gameStates for rollback to work

struct TileMap {
    std::vector<std::vector<Object>> mapTiles; // vector of width x height vectors (per layer)
    std::vector<Object> collidableTiles;
    std::vector<Object> fgTiles;
    int mapWidth = 0; // width of map in tiles
    int mapHeight = 0; // height of map in tiles
};

struct GameState {    
    bool debugMode;

    Player player;
    TileMap tiles; // width * height for spatial access for collision purposes
    
    std::vector<Object> nearTiles;
    
    GameState(const SDLState &state, Resources &res) 
        :
        debugMode(false),
        player(glm::vec2(0.f), 4)
    {
        init(state, res);
    }
    GameState() = default;
    void init(const SDLState &state, Resources &res);
    void loadMap(const SDLState& state, Resources& res, const std::string& path);
    Object getTileOnTileMap(int x, int y); // get a tile at a position (on the tileMap)
    void getNearbyCollidableTilesOnTileMap(Player &p); // get tiles that are close to p
};