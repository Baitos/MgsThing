#include "../include/update.h"
#include "../include/gameState.h"
#include "../include/collision.h"
#include "../include/camera.h"

#include <iostream>

void update(const SDLState& state, GameState& gs, const Resources& res, Camera& cam, double tickRate) {
    gs.getNearbyTilesOnTileMap(gs.player);
    gs.player.update(state.im.inputState, gs, res, tickRate);
    // set viewport based on player pos
    cam.x = (gs.player.pos.x + TILE_SIZE / 2) - (cam.w / 2); 
    cam.y = (gs.player.pos.y + TILE_SIZE / 2) - (cam.h / 2); 
    //std::cout << cam.x << " " << cam.y << std::endl;
}