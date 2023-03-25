#include "raylib.h"
#include <iostream>

using namespace std;

const int width = 1920;
const int height = 1080;


int main()
{
	InitWindow(width, height, "Chemistry game");
	SetTargetFPS(60);

	Texture2D idle[8] = { LoadTexture("../assets/animations/idle1.png"), LoadTexture("../assets/animations/idle1.png"), LoadTexture("../assets/animations/idle1.png"), LoadTexture("../assets/animations/idle1.png"), LoadTexture("../assets/animations/idle2.png"), LoadTexture("../assets/animations/idle2.png"), LoadTexture("../assets/animations/idle2.png"), LoadTexture("../assets/animations/idle2.png") };

	Texture2D right[8] = { LoadTexture("../assets/animations/right1.png"), LoadTexture("../assets/animations/right2.png"), LoadTexture("../assets/animations/right3.png"), LoadTexture("../assets/animations/right4.png"), LoadTexture("../assets/animations/right5.png"), LoadTexture("../assets/animations/right6.png"), LoadTexture("../assets/animations/right7.png"), LoadTexture("../assets/animations/right8.png") };
	Texture2D left[8] = { LoadTexture("../assets/animations/left1.png"), LoadTexture("../assets/animations/left2.png"), LoadTexture("../assets/animations/left3.png"), LoadTexture("../assets/animations/left4.png"), LoadTexture("../assets/animations/left5.png"), LoadTexture("../assets/animations/left6.png"), LoadTexture("../assets/animations/left7.png"), LoadTexture("../assets/animations/left8.png") };
	Texture2D up[8] = { LoadTexture("../assets/animations/up1.png"), LoadTexture("../assets/animations/up2.png"), LoadTexture("../assets/animations/up3.png"), LoadTexture("../assets/animations/up4.png"), LoadTexture("../assets/animations/up5.png"), LoadTexture("../assets/animations/up6.png"), LoadTexture("../assets/animations/up7.png"), LoadTexture("../assets/animations/up8.png") };
	Texture2D down[8] = { LoadTexture("../assets/animations/down1.png"), LoadTexture("../assets/animations/down2.png"), LoadTexture("../assets/animations/down3.png"), LoadTexture("../assets/animations/down4.png"), LoadTexture("../assets/animations/down5.png"), LoadTexture("../assets/animations/down6.png"), LoadTexture("../assets/animations/down7.png"), LoadTexture("../assets/animations/down8.png") };

	Texture2D background = LoadTexture("../assets/background.png");

	float timer = 0.0f;
	int frame = 0;
	int x = 100, y = 400;

	int last = 0;
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


			if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W))
			{
				if (x <= 1650)
				{
					x += 15;
				}
				if (y >= -75)
				{
					y -= 15;
				}
				last = 5;
			}
			else if (IsKeyDown(KEY_D) && IsKeyDown(KEY_S))
			{
				if (x <= 1650)
				{
					x += 15;
				}
				if (y <= 750)
				{
					y += 15;
				}
				last = 4;
			}
			else if (IsKeyDown(KEY_D))
			{
				if (x <= 1650)
				{
					x += 20;
				}
				last = 1;
			}
			else if (IsKeyDown(KEY_A))
			{
				if (x >= -150)
				{
					x -= 20;
				}
				last = 2;
			}
			else if (IsKeyDown(KEY_S))
			{
				if (y <= 900)
				{
					y += 20;
				}
				last = 0;
			}
			else if (IsKeyDown(KEY_W))
			{
				if (y >= -75)
				{
					y -= 20;
				}
				last = 3;
			}
		}


		if (IsKeyDown(KEY_D))
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

		DrawText(TextFormat("X: %08i \nY: %08i", mouseX, mouseY), 100, 100, 30, RED);

		EndDrawing();
	}

	CloseWindow();
}