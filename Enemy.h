#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollissionRec();

private:
    Vector2 worldPos{};
    Texture2D texture{LoadTexture("textures/characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("textures/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("textures/characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPosLastFrame{};

    // 1: facing right, -1 facing left
    float rightLeft{1.f};
    // anmimation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.f};
};