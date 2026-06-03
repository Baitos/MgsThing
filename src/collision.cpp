
#include "../include/collision.h"
#include "../include/gameState.h"
#include "../include/object.h"
#include "../include/player.h"
#include "../include/globals.h"

Object GameState::getTileOnTileMap(int x, int y) {
    if (x < 0 || x >= this->mapWidth || y < 0 || y >= this->mapHeight) { // error bound
        return Object();
    }
    return this->collidableTiles[y * this->mapWidth + x];    
}

void GameState::getNearbyTilesOnTileMap(Player &p) {
    this->nearTiles.clear();
    int left = (int)p.pos.x / TILE_SIZE;
    int right = (int)(p.pos.x + p.collider.w) / TILE_SIZE;
    int top = (int)p.pos.y / TILE_SIZE;
    int bottom = (int)(p.pos.y + p.collider.h) / TILE_SIZE;

    for (int ty = top; ty <= bottom; ty++) {
        for (int tx = left; tx <= right; tx++) {
            this->nearTiles.push_back(this->getTileOnTileMap(tx, ty));
        }
    }
}

bool intersectAABB(const SDL_FRect &a, const SDL_FRect &b, glm::vec2 &overlap)
{
	const float minXA = a.x;
	const float maxXA = a.x + a.w;
	const float minYA = a.y;
	const float maxYA = a.y + a.h;
	const float minXB = b.x;
	const float maxXB = b.x + b.w;
	const float minYB = b.y;
	const float maxYB = b.y + b.h;

	if ((minXA < maxXB && maxXA > minXB) &&
		(minYA < maxYB && maxYA > minYB))
	{
		overlap.x = std::min(maxXA - minXB, maxXB - minXA);
		overlap.y = std::min(maxYA - minYB, maxYB - minYA);
		return true;
	}
	return false;
}

void Player::checkCollision(GameState &gs, const Resources &res, double tickRate)
{
    SDL_FRect rectA {
		.x = this->pos.x + this->collider.x,
		.y = this->pos.y + this->collider.y,
		.w = this->collider.w,
		.h = this->collider.h
	};
	glm::vec2 resolution{ 0 };
	for (auto &o : gs.nearTiles) { 
		SDL_FRect rectB {
			.x = o.pos.x + o.collider.x,
			.y = o.pos.y + o.collider.y,
			.w = o.collider.w,
			.h = o.collider.h
		};
		if (intersectAABB(rectA, rectB, resolution) && o.solid) {
			this->collisionResponse(gs, res, o, rectA, rectB, resolution, tickRate);
		}
    }
}

void Player::collisionResponse(GameState &gs, const Resources &res,
 	                           Object &o, SDL_FRect &rectA, SDL_FRect &rectB, glm::vec2 &resolution, double tickRate) {
    if (resolution.x < resolution.y) {	
        if (rectA.x < rectB.x) {
            this->pos.x -= resolution.x;
        } else {
            this->pos.x += resolution.x;
        }	
        this->vel.x = 0;
    } else {
        if (rectA.y < rectB.y) {
            this->pos.y -= resolution.y;
        } else {
            this->pos.y += resolution.y;
        }
        this->vel.y = 0;
    }
}
	