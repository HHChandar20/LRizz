#include "raylib.h"
#include <iostream>

using namespace std;

const int width = 1920;
const int height = 1080;

int main()
{
    InitWindow(width, height, "Chemistry game");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D idle[8] = { LoadTexture("../assets/animations/idle1.png"), LoadTexture("../assets/animations/idle1.png"), LoadTexture("../assets/animations/idle1.png"), LoadTexture("../assets/animations/idle1.png"), LoadTexture("../assets/animations/idle2.png"), LoadTexture("../assets/animations/idle2.png"), LoadTexture("../assets/animations/idle2.png"), LoadTexture("../assets/animations/idle2.png") };

    Texture2D right[8] = { LoadTexture("../assets/animations/right1.png"), LoadTexture("../assets/animations/right2.png"), LoadTexture("../assets/animations/right3.png"), LoadTexture("../assets/animations/right4.png"), LoadTexture("../assets/animations/right5.png"), LoadTexture("../assets/animations/right6.png"), LoadTexture("../assets/animations/right7.png"), LoadTexture("../assets/animations/right8.png") };
    Texture2D left[8] = { LoadTexture("../assets/animations/left1.png"), LoadTexture("../assets/animations/left2.png"), LoadTexture("../assets/animations/left3.png"), LoadTexture("../assets/animations/left4.png"), LoadTexture("../assets/animations/left5.png"), LoadTexture("../assets/animations/left6.png"), LoadTexture("../assets/animations/left7.png"), LoadTexture("../assets/animations/left8.png") };
    Texture2D up[8] = { LoadTexture("../assets/animations/up1.png"), LoadTexture("../assets/animations/up2.png"), LoadTexture("../assets/animations/up3.png"), LoadTexture("../assets/animations/up4.png"), LoadTexture("../assets/animations/up5.png"), LoadTexture("../assets/animations/up6.png"), LoadTexture("../assets/animations/up7.png"), LoadTexture("../assets/animations/up8.png") };
    Texture2D down[8] = { LoadTexture("../assets/animations/down1.png"), LoadTexture("../assets/animations/down2.png"), LoadTexture("../assets/animations/down3.png"), LoadTexture("../assets/animations/down4.png"), LoadTexture("../assets/animations/down5.png"), LoadTexture("../assets/animations/down6.png"), LoadTexture("../assets/animations/down7.png"), LoadTexture("../assets/animations/down8.png") };

    Texture2D background = LoadTexture("../assets/background.png");
    Texture2D walls = LoadTexture("../assets/walls.png");


    Texture2D downLeft[8] = { LoadTexture("../assets/animations/downLeft1.png"), LoadTexture("../assets/animations/downLeft2.png"), LoadTexture("../assets/animations/downLeft3.png"), LoadTexture("../assets/animations/downLeft4.png"), LoadTexture("../assets/animations/downLeft5.png"), LoadTexture("../assets/animations/downLeft6.png"), LoadTexture("../assets/animations/downLeft7.png"), LoadTexture("../assets/animations/downLeft8.png") };
    Texture2D upLeft[8] = { LoadTexture("../assets/animations/upLeft1.png"), LoadTexture("../assets/animations/upLeft2.png"), LoadTexture("../assets/animations/upLeft3.png"), LoadTexture("../assets/animations/upLeft4.png"), LoadTexture("../assets/animations/upLeft5.png"), LoadTexture("../assets/animations/upLeft6.png"), LoadTexture("../assets/animations/upLeft7.png"), LoadTexture("../assets/animations/upLeft8.png") };
    Texture2D downRight[8] = { LoadTexture("../assets/animations/downRight1.png"), LoadTexture("../assets/animations/downRight2.png"), LoadTexture("../assets/animations/downRight3.png"), LoadTexture("../assets/animations/downRight4.png"), LoadTexture("../assets/animations/downRight5.png"), LoadTexture("../assets/animations/downRight6.png"), LoadTexture("../assets/animations/downRight7.png"), LoadTexture("../assets/animations/downRight8.png") };
    Texture2D upRight[8] = { LoadTexture("../assets/animations/upRight1.png"), LoadTexture("../assets/animations/upRight2.png"), LoadTexture("../assets/animations/upRight3.png"), LoadTexture("../assets/animations/upRight4.png"), LoadTexture("../assets/animations/upRight5.png"), LoadTexture("../assets/animations/upRight6.png"), LoadTexture("../assets/animations/upRight7.png"), LoadTexture("../assets/animations/upRight8.png") };


    float timer = 0.0f;
    int frame = 0;
    int x = 800, y = 800;
    int mouseX, mouseY;

    while (!WindowShouldClose())
    {
        mouseX = GetMouseX();
        mouseY = GetMouseY();

        BeginDrawing();
        ClearBackground(WHITE);

        DrawTexture(background, 0, 0, WHITE);

        timer += GetFrameTime();

        if (timer >= 0.04f)
        {
            timer = 0.0f;

            if (frame == 7)
            {
                frame = 0;
            }
            else
            {
                frame++;
            }
            if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
            {
                if (x >= -100 && !(x <= 70 && x >= 50 && y >= 220 && y <= 390) && !(x <= 95 && x >= 50 && y >= 160 && y <= 300) && !(x <= 120 && x >= 50 && y >= 330 && y <= 480))
                {
                    x -= 15;
                }
                if (y >= -75 && !(x >= 755 && x <= 1230 && y >= 630 && y <= 690) && !(x <= 95 && x >= 50 && y >= 160 && y <= 300) && !(x >= -150 && x <= 90 && y >= 380 && y <= 460))
                {
                    y -= 15;
                }
            }
            else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
            {
                if (x >= -100 && !(x <= 70 && y >= 240 && y <= 390) && !(x <= 95 && y >= 160 && y <= 240) && !(x <= 120 && y >= 350 && y <= 450))
                {
                    x -= 15;
                }
                if (y <= 900 && !(x <= 70 && y >= 240 && y <= 390) && !(x <= 95 && y >= 160 && y <= 240) && !(x <= 120 && y >= 350 && y <= 450))
                {
                    y += 15;
                }
            }
            else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
            {
                if (x <= 1760 && !(x >= 740 && x <= 1225 && y >= 550 && y <= 660) && !(x >= 140 && x <= 450 && y <= 440 && y >= 280) && !(x >= 375 && x <= 470 && y >= 270 && y <= 490))
                {
                    x += 15;
                }
                if (y <= 900 && !(x >= 740 && x <= 1225 && y >= 550 && y <= 660) && !(x >= 150 && x <= 450 && y <= 440 && y >= 280) && !(x >= 375 && x <= 470 && y >= 270 && y <= 490))
                {
                    y += 15;
                }
            }
            else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
            {
                if (x <= 1760 && !(x >= 80 && x <= 190 && y >= 140 && y <= 160) && !(x >= 140 && x <= 470 && y >= 380 && y <= 460) && !(y >= 200 && y <= 330 && x >= 320 && x <= 470))
                {
                    x += 15;
                }
                if (y >= -75 && !(x >= 750 && x <= 1225 && y >= 640 && y <= 690) && !(x >= -150 && x <= 90 && y >= 380 && y <= 460) && !(x >= 80 && x <= 190 && y >= 140 && y <= 160) && !(x >= 140 && x <= 470 && y >= 380 && y <= 460) && !(y >= 200 && y <= 330 && x >= 320 && x <= 470))
                {
                    y -= 15;
                }
            }
            else if (IsKeyDown(KEY_S))
            {
                if (y <= 900 && !(x >= 750 && x <= 1225 && y >= 560 && y <= 580) && !(y >= 560 && y <= 580 && x >= 750 && x <= 1225) && !(x >= 160 && x <= 450 && y <= 440 && y >= 320))
                {
                    y += 20;
                }
            }
            else if (IsKeyDown(KEY_A))
            {
                if (x >= -100 && !(y >= 580 && y <= 680 && x >= 1215 && x <= 1230) && !(x <= 70 && y >= 200 && y <= 350) && !(x <= 100 && y >= 160 && y <= 240) && !(x <= 120 && y >= 250 && y <= 450))
                {
                    x -= 20;
                }
            }
            else if (IsKeyDown(KEY_D))
            {
                if (x <= 1760 && !(y >= 580 && y <= 660 && x >= 740 && x <= 1225) && !(x >= 140 && x <= 440 && y >= 340 && y <= 440))
                {
                    x += 20;
                }
            }
            else if (IsKeyDown(KEY_W))
            {
                if (y >= -75 && !(x >= 755 && x <= 1225 && y >= 630 && y <= 700) && !(x >= -150 && x <= 90 && y >= 380 && y <= 460))
                {
                    y -= 20;
                }
            }
        }


        if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
        {
            DrawTexture(upRight[frame], x, y, WHITE);
        }
        else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
        {
            DrawTexture(upLeft[frame], x, y, WHITE);
        }
        else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
        {
            DrawTexture(downRight[frame], x, y, WHITE);
        }
        else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
        {
            DrawTexture(downLeft[frame], x, y, WHITE);
        }
        else if (IsKeyDown(KEY_D))
        {
            DrawTexture(right[frame], x, y, WHITE);
        }
        else if (IsKeyDown(KEY_A))
        {
            DrawTexture(left[frame], x, y, WHITE);
        }
        else if (IsKeyDown(KEY_W))
        {
            DrawTexture(up[frame], x, y, WHITE);
        }
        else if (IsKeyDown(KEY_S))
        {
            DrawTexture(down[frame], x, y, WHITE);
        }
        else
        {
            DrawTexture(idle[frame], x, y, WHITE);
        }

        DrawTexture(walls, 0, 0, WHITE);

        DrawText(TextFormat("X: %08i \nY: %08i", mouseX, mouseY), 100, 100, 30, RED);

        EndDrawing();
    }

    CloseWindow();
}