#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"

constexpr float TARGET_SCREEN_WIDTH = 1280;
constexpr float TARGET_SCREEN_HEIGHT = 720;
constexpr float TARGET_ASPECT_RATIO = TARGET_SCREEN_WIDTH / TARGET_SCREEN_HEIGHT;
constexpr float CAMERA_MOVE_SPEED = 1.0f;
constexpr float ENTITY_MOVE_SPEED = 100.0f;

constexpr int TILE_WIDTH = 256;
constexpr int TILE_HEIGHT = 128;
constexpr int TILE_HALF_WIDTH = TILE_WIDTH / 2;
constexpr int TILE_HALF_HEIGHT = TILE_HEIGHT / 2;
constexpr int TILE_LOGICAL_HEIGHT = 20;
constexpr int MAP_WIDTH = 10;
constexpr int MAP_HEIGHT = 10;

constexpr Vector2 ISO_RIGHT = { TILE_HALF_WIDTH, TILE_HALF_HEIGHT };
constexpr Vector2 ISO_LEFT  = { -TILE_HALF_WIDTH, -TILE_HALF_HEIGHT };
constexpr Vector2 ISO_UP    = { TILE_HALF_WIDTH, -TILE_HALF_HEIGHT };
constexpr Vector2 ISO_DOWN  = { -TILE_HALF_WIDTH, TILE_HALF_HEIGHT };

#endif //CONSTANTS_H
