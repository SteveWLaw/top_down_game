#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    // window dimensions
    const int windowWidth{384};
    const int windowHeight{384};
    // initialise the game window
    InitWindow(windowWidth, windowHeight, "Top Down!");

    Texture2D map = LoadTexture("textures/nature_tileset/tile_map.png");
    Vector2 mapPos{0, 0};
    const float mapScale{4.f};

    Character knight{windowWidth, windowHeight};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("textures/nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("textures/nature_tileset/Log.png")}};

    Enemy goblin{Vector2{500.f, 400.f},
                 LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
                 LoadTexture("textures/characters/goblin_run_spritesheet.png")};
    goblin.setTarget(&knight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        goblin.tick(GetFrameTime());

        knight.tick(GetFrameTime());
        // check map bounds, (manually shrink right and bottom for cliff edge texture there)
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0 ||
            knight.getWorldPos().x + windowWidth > (map.width - 10.f) * mapScale ||
            knight.getWorldPos().y + windowHeight > (map.height - 10.f) * mapScale)
        {
            knight.undoMovement();
        }

        // check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollissionRec(knight.getWorldPos()), knight.getCollissionRec()))
            {
                knight.undoMovement();
            }
        }

        // attack goblin
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))
        {
            if (CheckCollisionRecs(goblin.getCollissionRec(), knight.getWeaponRec()))
            {
                goblin.setAlive(false);
            }
        }

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}