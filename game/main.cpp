#include "raylib.h"
#include <iostream>

using namespace std;

const int width = 1920;
const int height = 1080;


int main()
{
	InitWindow(width, height, "Chemistry game");
	SetTargetFPS(60);

	Texture2D background = LoadTexture("../assets/background.png");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		DrawTexture(background, 0, 0, WHITE);

		EndDrawing();
	}

	CloseWindow();

}