#include <SDL3/SDL.h>
#include <format>

#include "../include/draw.h"
#include "../include/state.h"
#include "../include/gameState.h"


void draw(const SDLState& state, GameState& gs, Resources& res) {
    SDL_SetRenderDrawColor(state.renderer, 64, 51, 83, 255); // draw background
    SDL_RenderClear(state.renderer);

    for (Object &obj : gs.mapTiles) { // render map tiles
        obj.draw(state, gs, res);
    }
    gs.player.draw(state, gs, res);    
    for (Object &obj : gs.fgTiles) { // render fg tiles
        obj.draw(state, gs, res);
    }
    if (gs.debugMode) {
    // debug info
        SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(state.renderer, 5, 5,
                        std::format("FPS: {} X: {} Y: {}",  
                        static_cast<int>(state.fs.FPS), gs.player.pos.x, gs.player.pos.y).c_str());
        for (Object &obj : gs.nearTiles) { // render near tiles
            obj.drawDebugNearby(state, gs);
        }                   
    }



    //swap buffers and present
    SDL_RenderPresent(state.renderer);
}

