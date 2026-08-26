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
class Camera;

enum objectType {
    NO_OBJ_TYPE = 0,
    OBJ_PLAYER,
    OBJ_LAND
};

class Object { // generic obj type    
    public:
        glm::vec2 pos, vel, acc = glm::vec2(0.0f);
        SDL_FRect collider = {
            .x = 0,
            .y = 0,
            .w = (float)TILE_SIZE,
            .h = (float)TILE_SIZE
        }; // rectangle for collision
        float width = TILE_SIZE;
        float height = TILE_SIZE; // size for drawing
        bool debug = true; // should draw debug?
        objectType type = NO_OBJ_TYPE;   
        bool solid = false; // should player collide with them


        int tileId; // what sprite of the tile sheet should this object use?
        int tileIdOffset = 0; // if animated, how far off from the original sprite should we move?
        Object() {           
            tileId = BLANK_TILE;
        }
        Object(glm::vec2 pos_) {
            pos = pos_;
            tileId = BLANK_TILE;
        }

        Object(glm::vec2 pos_, int tileID_, objectType type_) {
            pos = pos_;
            tileId = tileID_;
            type = type_;
        }

        Object(glm::vec2 pos_, int tileID_) {
            pos = pos_;
            tileId = tileID_;
        }
        virtual ~Object() {}
        virtual void draw(const SDLState &state, GameState &gs, const Resources &res, Camera& cam);
        void drawDebug(const SDLState &state, GameState &gs, Camera& cam); 
        void update(GameState &gs, const Resources &res, double tickRate);
};