#pragma once

struct SDLState;
struct GameState;
struct Resources;
class Camera;

void draw(const SDLState& state, GameState& gs, Resources& res, Camera& cam);