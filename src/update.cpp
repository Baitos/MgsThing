#include "../include/update.h"
#include "../include/gameState.h"

void update(const SDLState& state, GameState& gs, const Resources& res) {
    gs.player.update(state, gs, res, state.fs.deltaTime);
    // set viewport based on player pos
    gs.mapViewport.x = (gs.player.pos.x + TILE_SIZE / 2) - (gs.mapViewport.w / 2); 
    gs.mapViewport.y = (gs.player.pos.y + TILE_SIZE / 2) - (gs.mapViewport.h / 2); 
}