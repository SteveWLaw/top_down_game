#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;

    screenPos = {
        static_cast<float>(winWidth) / 2.f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);

    Vector2 direction{};
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos - direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
        texture = idle;

}
