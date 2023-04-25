#include "GameManager.hpp"
#include "time.h"

GameManager::GameManager()
{
    srand(time(NULL));
    // Initialize window and settings
    InitWindow(1920, 1080, "Chemistry Game");
    SetTargetFPS(60);

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
        game->loop(); // Start game loop
        EndDrawing();
    }

    game->highscore.open("highscore.txt", std::ios::out);
    game->highscore << std::to_string(game->highestStreak);

    game->highscore.close();

    delete game;
}