#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include <string>

class Entity {
protected:
    int gridX;
    int gridY;
    int gridZ;
    int logicalHeight;

    Vector2 screenPosition;

    Texture2D texture;
    Color tint;
    float rotation;
    float scale;

public:
    Entity(int x, int y, int z, int logicalHeight, const std::string& texturePath);
    virtual ~Entity() = default;

    virtual void UpdateScreenPosition();
    virtual void SetScreenPosition(const Vector2& position) { screenPosition = position; }

    virtual void Render() const;

    Vector2 GetScreenPosition() const { return screenPosition; }
    Color GetTint() const { return tint; }

    void SetGridPosition(int x, int y, int z);
    void GetGridPosition(int& x, int& y, int& z) const;

    int GetRenderOrder() const;
};

#endif //ENTITY_H
