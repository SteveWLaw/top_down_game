#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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

    Enemy goblins[2]{
        Enemy{Vector2{500.f, 200.f},
              LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
              LoadTexture("textures/characters/goblin_run_spritesheet.png")},
        Enemy{Vector2{1200.f, 800.f},
              LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
              LoadTexture("textures/characters/goblin_run_spritesheet.png")}};

    Enemy slimes[2]{
        Enemy{Vector2{800.f, 600.f},
              LoadTexture("textures/characters/slime_idle_spritesheet.png"),
              LoadTexture("textures/characters/slime_run_spritesheet.png")},
        Enemy{Vector2{1000.f, 1200.f},
              LoadTexture("textures/characters/slime_idle_spritesheet.png"),
              LoadTexture("textures/characters/slime_run_spritesheet.png")}};

    Enemy *enemies[] = {&goblins[0], &goblins[1], &slimes[0], &slimes[1]};

    // set enemy targets
    for (auto &enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

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

        // check if all enemies are dead
        int enemiesLeft{0};
        for (auto &enemy : enemies)
        {
            if (enemy->getAlive())
                enemiesLeft++;
        }
        // if no enemies left, display win text
        if (enemiesLeft == 0)
        {
            DrawText("You Win!", windowWidth / 2 - MeasureText("You Win!", 40) / 2, windowHeight / 2 - 60, 40, GREEN);
            EndDrawing();
            continue;
        }

        // draw and update enemies
        for (auto &enemy : enemies)
        {
            // skip dead enemies
            if (!enemy->getAlive())
                continue;
            enemy->tick(GetFrameTime());
        }

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

        // attack enemies
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))
        {
            for (auto &enemy : enemies)
            {
                // skip dead enemies
                if (!enemy->getAlive())
                    continue;

                if (CheckCollisionRecs(enemy->getCollissionRec(), knight.getWeaponRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        // draw health or death messageS
        if (!knight.getAlive())
        {
            DrawText("You Died!", windowWidth / 2 - MeasureText("You Died!", 40) / 2, windowHeight / 2 - 20, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string healthText = "Health: " + std::to_string(static_cast<int>(knight.getHealth()));
            DrawText(healthText.c_str(), 20, 20, 20, DARKGREEN);
        }

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}