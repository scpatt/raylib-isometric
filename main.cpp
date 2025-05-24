#include <iostream>
#include "src/utils/iso.h"
#include "src/constants.h"
#include "src/core/entity.h"
#include "raymath.h"

void Update(Camera2D& camera, Vector2& selectedTile);
void UpdateRenderRect();
void InitializeRenderTarget();
void Render(const Camera2D& camera, const Texture2D& baseTile, const Vector2& selectedTile);
void DrawSelectedTile(Vector2 tilePos);
Camera2D SetupCamera();

RenderTexture2D gameTarget;
Rectangle renderRect;

auto entity = Entity(4, 4, 1, TILE_LOGICAL_HEIGHT, "assets/player.png");

int main() {
    InitWindow(TARGET_SCREEN_WIDTH, TARGET_SCREEN_HEIGHT, "Game");
    SetTargetFPS(60);

    InitializeRenderTarget();

    Camera2D camera = SetupCamera();

    const Texture2D slab = LoadTexture("assets/slab_small.png");

    Vector2 selected = { -1, -1 };

    while (!WindowShouldClose()) {
        Update(camera, selected);
        Render(camera, slab, selected);
    }

    UnloadRenderTexture(gameTarget);
    UnloadTexture(slab);
    CloseWindow();

    return 0;
}

Camera2D SetupCamera() {
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    camera.offset = {
        std::floor(TARGET_SCREEN_WIDTH / 2.0f),
        std::floor(TARGET_SCREEN_HEIGHT / 2.0f)
    };

    return camera;
}

/* Update */
void Update(Camera2D& camera, Vector2& selectedTile) {
    const float delta = GetFrameTime();

    Vector2 velocity = { 0 };

    if (IsKeyDown(KEY_RIGHT)) velocity = Vector2Add(velocity, ISO_RIGHT);
    if (IsKeyDown(KEY_LEFT)) velocity = Vector2Add(velocity, ISO_LEFT);
    if (IsKeyDown(KEY_DOWN)) velocity = Vector2Add(velocity, ISO_DOWN);
    if (IsKeyDown(KEY_UP)) velocity = Vector2Add(velocity, ISO_UP);

    const Vector2 playerPosition = entity.GetScreenPosition();

    if (Vector2Length(velocity) > 0.0f) {
        velocity = Vector2Normalize(velocity);

        const Vector2 newPlayerPosition = Vector2Add(playerPosition, Vector2Scale(velocity, ENTITY_MOVE_SPEED * delta));

        entity.SetScreenPosition(newPlayerPosition);
    }

    const float lerp = 1.0f * delta;

    camera.target.x += (playerPosition.x - camera.target.x) * lerp;
    camera.target.y += (playerPosition.y - camera.target.y) * lerp;
}

void InitializeRenderTarget() {
    gameTarget = LoadRenderTexture(TARGET_SCREEN_WIDTH, TARGET_SCREEN_HEIGHT);

    UpdateRenderRect();
}

void UpdateRenderRect() {
    const auto screenWidth = static_cast<float>(GetScreenWidth());
    const auto screenHeight = static_cast<float>(GetScreenHeight());
    const float actualAspectRatio = screenWidth / screenHeight;

    if (actualAspectRatio > TARGET_ASPECT_RATIO) {
        const float width = screenHeight * TARGET_ASPECT_RATIO;

        renderRect = {
            (screenWidth - width) * 0.5f,
            0,
            width,
            screenHeight
        };
    } else {
        const float height = screenWidth / TARGET_ASPECT_RATIO;

        renderRect = {
            0,
            (screenHeight - height) * 0.5f,
            screenWidth,
            height
        };
    }
}

/* Render */
void Render(const Camera2D& camera, const Texture2D& baseTile, const Vector2& selectedTile) {
    BeginTextureMode(gameTarget);
    ClearBackground(BLACK);

    BeginMode2D(camera);

    // Draw map tiles
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            const Vector2 tilePos = GridToScreen(x, y, 0, TILE_LOGICAL_HEIGHT);

            DrawTextureEx(baseTile, tilePos, 0.0f, 1.0f, WHITE);
        }
    }

    // Draw player
    const Vector2 playerPosition = entity.GetScreenPosition();

    DrawTextureEx(baseTile, playerPosition, 0.0f, 1.0f, entity.GetTint());
    EndMode2D();

    DrawFPS(10, 10);

    EndTextureMode();

    BeginDrawing();

    ClearBackground(BLACK);
    DrawTexturePro(
        gameTarget.texture,
        (Rectangle) {
            0,
            0,
            static_cast<float>(gameTarget.texture.width),
            -static_cast<float>(gameTarget.texture.height)
        },
        renderRect,
        (Vector2) {
            0,
            0
        },
        0.0f,
        WHITE
    );

    EndDrawing();
}

void DrawSelectedTile(const Vector2 tilePos) {
    DrawLine(tilePos.x + TILE_HALF_WIDTH, tilePos.y, tilePos.x + TILE_WIDTH, tilePos.y + TILE_HALF_HEIGHT, RED);
    DrawLine(tilePos.x + TILE_WIDTH, tilePos.y + TILE_HALF_HEIGHT, tilePos.x + TILE_HALF_WIDTH, tilePos.y + TILE_HEIGHT, RED);
    DrawLine(tilePos.x + TILE_HALF_WIDTH, tilePos.y + TILE_HEIGHT, tilePos.x, tilePos.y + TILE_HALF_HEIGHT, RED);
    DrawLine(tilePos.x, tilePos.y + TILE_HALF_HEIGHT, tilePos.x + TILE_HALF_WIDTH, tilePos.y, RED);
}
