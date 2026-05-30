#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "object.h"

void loadMap(SDLState& state, GameState& gs, const Resources& res, const std::string& path);