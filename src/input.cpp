#include <SDL3/SDL.h>

#include "../include/globals.h"
#include "../include/gameState.h"
#include "../include/input.h"
#include "../include/state.h"

void input(SDLState& state, GameState& gs, const Resources& res) {
    SDL_Event event { 0 };
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                {
                    running = false;
                    break;
                }
                case SDL_EVENT_WINDOW_RESIZED: 
                {
                    state.width = event.window.data1;
                    state.height = event.window.data2;
                    
                    //printf("Width = %d, Height = %d", state.width, state.height);
                    break;
                }
                case SDL_EVENT_KEY_DOWN:
                {
                    if (event.key.scancode == SDL_SCANCODE_F12) {
                        gs.debugMode = !gs.debugMode;
                    }
                    else if (event.key.scancode == SDL_SCANCODE_F1) {
                        running = false;
                    }
                    if (event.key.scancode == SDL_SCANCODE_D) {
                        gs.player.pos.x += 32;
                    }
                    if (event.key.scancode == SDL_SCANCODE_A) {
                        gs.player.pos.x -= 32;
                    }
                    if (event.key.scancode == SDL_SCANCODE_S) {
                        gs.player.pos.y += 32;
                    }
                    if (event.key.scancode == SDL_SCANCODE_W) {
                        gs.player.pos.y -= 32;
                    }
                    break;
                }
                case SDL_EVENT_KEY_UP:
                {
                    
                    break;
                }
            }
        }
}