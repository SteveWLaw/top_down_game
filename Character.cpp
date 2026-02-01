#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
    : windowWidth{winWidth}, windowHeight{winHeight}
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.f - scale * (0.5f * height)};
}
void Character::tick(float deltaTime)
{

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        velocity.y += 1.0;
    BaseCharacter::tick(deltaTime);
}
