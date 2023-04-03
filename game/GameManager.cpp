#include "GameManager.hpp"
#include "time.h"

GameManager::GameManager()
{
    srand(time(NULL));
    // Initialize window and settings
    InitWindow(1920, 1080, "Chemistry Game");
    SetTargetFPS(60);
    ToggleFullscreen();
    InitAudioDevice();
}

GameManager::~GameManager()
{
    CloseWindow();
}

void GameManager::drawMainLoop()
{
    Game* game = new Game();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        game->loop();

        EndDrawing();
    }

}
