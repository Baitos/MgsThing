#include <SDL3/SDL.h>
#include <format>

#include "../include/draw.h"
#include "../include/state.h"
#include "../include/gameState.h"
#include "../include/camera.h"


void draw(const SDLState& state, GameState& gs, Resources& res, Camera& cam) {
    SDL_SetRenderDrawColor(state.renderer, 64, 51, 83, 255); // draw background
    SDL_RenderClear(state.renderer);

    // render regular, onScreen tiles
    for (auto& layer : gs.tiles.mapTiles) {
        cam.renderOnscreenTiles(state, gs, res, layer, gs.tiles.mapWidth, gs.tiles.mapHeight); 
    }

    // draw collidable onscreen tiles
    cam.renderOnscreenTiles(state, gs, res, gs.tiles.collidableTiles, gs.tiles.mapWidth, gs.tiles.mapHeight);

    gs.player.draw(state, gs, res, cam);    

    // draw fg, onscreen tiles
    cam.renderOnscreenTiles(state, gs, res, gs.tiles.fgTiles, gs.tiles.mapWidth, gs.tiles.mapHeight);

    if (gs.debugMode) {
    // debug info
        SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(state.renderer, 5, 5,
                        std::format("FPS: {} X: {} Y: {}",  
                        static_cast<int>(state.fs.FPS), gs.player.pos.x, gs.player.pos.y).c_str());
        /*for (Object &obj : gs.nearTiles) { // render near tiles
            obj.drawDebugNearby(state, gs, cam);
        } */                  
    }



    //swap buffers and present
    SDL_RenderPresent(state.renderer);
}

