#pragma once

#include <SDL3/SDL.h>
#include <stdio.h>
#include <vector>
#include "../ext/glm/glm.hpp"
#include "animation.h"
#include "resources.h"
#include "globals.h"
#include "object.h"
#include "playerState.h"

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

        PlayerState* playerState; // fsm again, start in idle
        
        Player();
        Player(glm::vec2 pos_, int tileID_);

        virtual ~Player() {}
        virtual void update(InputState &inputs, GameState &gs, const Resources &res, double tickRate);
        void handleState(PlayerState* &pState, GameState &gs, const Resources &res); // calls enter/exit fns and changes
        void draw(const SDLState &state, GameState &gs, const Resources &res, Camera& cam);
        void handleRotation(float angle, double tickRate, bool isStrafing);
        void checkCollision(GameState &gs, const Resources &res,
 	                        double tickRate);
        void collisionResponse(GameState &gs, const Resources &res,
 	                           Object &o, SDL_FRect &rectA, SDL_FRect &rectB, glm::vec2 &resolution, double tickRate);
};
