#pragma once

#include <SDL3/SDL.h>
#include <stdio.h>
#include <vector>
#include "../ext/glm/glm.hpp"
#include "animation.h"
#include "resources.h"
#include "globals.h"

struct SDLState;
struct GameState;
struct Resources;



class Object { // generic obj type    
    public:
        glm::vec2 pos, vel, acc;
        SDL_FRect collider; // rectangle for collision
        float width, height; // size for drawing
        bool debug; // should draw debug?
        int type;

        int tileId; // what sprite of the tile sheet should this object use?
        Object() {           
            pos = vel = acc = glm::vec2(0);
            collider = {
                .x = 0,
                .y = 0,
                .w = (float)TILE_SIZE,
                .h = (float)TILE_SIZE
            };
            width = height = TILE_SIZE;
            tileId = BLANK_TILE;
            debug = true;
        }
        Object(glm::vec2 pos_) {
            pos = pos_;
            vel = acc = glm::vec2(0);
            collider = {
                .x = 0,
                .y = 0,
                .w = (float)TILE_SIZE,
                .h = (float)TILE_SIZE
            };
            width = height = TILE_SIZE;
            tileId = BLANK_TILE;
            debug = true;
        }

        Object(glm::vec2 pos_, int tileID_) {
            pos = pos_;
            vel = acc = glm::vec2(0);
            tileId = tileID_;
            collider = {
                .x = 0,
                .y = 0,
                .w = (float)TILE_SIZE,
                .h = (float)TILE_SIZE
            };
            width = height = TILE_SIZE;
            debug = true;
        }

        Object(glm::vec2 pos_, SDL_FRect colliderRect) {
            pos = pos_;       
            collider = colliderRect;
            vel = acc = glm::vec2(0);
            debug = true;
        }
        virtual ~Object() {}
        virtual void draw(const SDLState &state, GameState &gs, const Resources &res);
        void drawDebug(const SDLState &state, GameState &gs); 
        void update(const SDLState &state, GameState &gs, const Resources &res, float deltaTime);
};
