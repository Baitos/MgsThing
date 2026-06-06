#pragma once

struct SDLState;
struct GameState;
struct Resources;
class Camera;

void update(const SDLState& state, GameState& gs, const Resources& res, Camera& cam, double tickRate);