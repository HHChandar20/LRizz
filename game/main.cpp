#include <raylib.h>
#include "GameManager.hpp"

int main()
{
	GameManager* game = new GameManager;
	game->drawMainLoop();
	delete game;
}