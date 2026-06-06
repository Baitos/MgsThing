#pragma once

#include <SDL3/SDL.h>
#include <stdio.h>
#include <vector>
#include "../ext/glm/glm.hpp"
#include "animation.h"
#include "resources.h"
#include "globals.h"
#include "object.h"

struct SDLState;
struct GameState;
struct Resources;
class Camera;

enum direction {
    U,
    UR,
    R,
    DR,
    D,
    DL,
    L,
    UL
};

struct directionTable {
    int tileID;
    bool flipSprite;
};

class Player : public Object {   
    public:
        float maxSpeed = 250.0f;
        bool isBeingMoved = false; // set to true if an input is being held
        direction dir = U; // which way to face sprite
        float angle = 0.0f; // angle player is facing
        bool flipSprite = false; // should we flip the sprite?
        float rotationSpeed = 360.0f; // how many degrees should the player character rotate in a second?
        // should be half a second at 360 to turn around
        Player() : Object() {
            type = OBJ_PLAYER;
            solid = true;
            collider = {
                .x = 3,
                .y = 0,
                .w = 26,
                .h = (float)TILE_SIZE
            };
        }
        Player(glm::vec2 pos_, int tileID_) : Object(pos_, tileID_) {
            type = OBJ_PLAYER;
            collider = {
                .x = 3,
                .y = 0,
                .w = 26,
                .h = (float)TILE_SIZE
            };
            solid = true;
        }
        virtual ~Player() {}
        virtual void update(InputState inputs, GameState &gs, const Resources &res, double tickRate);
        void draw(const SDLState &state, GameState &gs, const Resources &res, Camera& cam);
        void handleRotation(float angle, double tickRate, bool isStrafing);
        void checkCollision(GameState &gs, const Resources &res,
 	                        double tickRate);
        void collisionResponse(GameState &gs, const Resources &res,
 	                           Object &o, SDL_FRect &rectA, SDL_FRect &rectB, glm::vec2 &resolution, double tickRate);
};
