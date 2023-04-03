#include "Game.hpp"

Game::Game()
{
	for (int i = 0; i < 3; i++)
	{
		reaction[i] = -1;
	}
	animationTimer = 0.0f;
	timePlayed = 0.0f;
	frame = 0;
	periodicTable = 0;
	chemistryShelf = 0;
	reactor = 0;
	musicPlayer = 0;
	onFire = 0;
	interaction = 0;
	isMenuOpened = 0;
	pauseMusic = 1;
	repeatMusic = 0;
	packaging = 0;
	packageClosed = 0;
	isCarryingBox = 0;
	isCarryingExtinguisher = 0;
	mailbox = 0;

	tracks[0] = "lo-fi";
	tracks[1] = "superhero";
	tracks[2] = "phonk";
	tracks[3] = "tourner-dans-le-vide";
	tracks[4] = "tokyo-drift";

	for (int i = 0; i < 6; i++)
	{
		inventoryElementTypes[i] = 0; // 0 - basic element, 1 - product
		inventoryElements[i] = -1; // Set inventory to empty
	}

	musicIndex = 0;
	randomMusic = 0;
	selectedElement = -1;
	elementPosition = -1;
	inventoryIndex = -1;
	packageElement = -1;
	orderElement = rand() % 22;
	inCollision = 0;

	character = { 130, 500 }; //character position (x, y)

	for (int i = 0; i < 7; i++)
	{
		fire[i] = RED;
		if (i < 4)
			fire[i] = MAROON;
	}
	std::string path;
	for (int i = 0; i < 5; i++)
	{
		path = tracks[i] + ".mp3";
		music[i] = LoadMusicStream(path.c_str());
	}

	extinguishTime = 0.0f;

	load();
	PlayMusicStream(music[musicIndex]);
}

Game::~Game()
{
	unload();
}

void Game::load()
{
	elements[0] = LoadTexture("H2.png");
	elements[1] = LoadTexture("Na.png");
	elements[2] = LoadTexture("O2.png");
	elements[3] = LoadTexture("S.png");
	elements[4] = LoadTexture("N2.png");
	elements[5] = LoadTexture("Cl2.png");
	elements[6] = LoadTexture("products/H2O.png");
	elements[7] = LoadTexture("products/HCl.png");
	elements[8] = LoadTexture("products/H2S.png");
	elements[9] = LoadTexture("products/SO2.png");
	elements[10] = LoadTexture("products/SO3.png");
	elements[11] = LoadTexture("products/H2SO3.png");
	elements[12] = LoadTexture("products/H2SO4.png");
	elements[13] = LoadTexture("products/NO2.png");
	elements[14] = LoadTexture("products/NH3.png");
	elements[15] = LoadTexture("products/HNO3.png");
	elements[16] = LoadTexture("products/Na2S.png");
	elements[17] = LoadTexture("products/Na2SO4.png");
	elements[18] = LoadTexture("products/NaCl.png");
	elements[19] = LoadTexture("products/NaH.png");
	elements[20] = LoadTexture("products/NaOH.png");
	elements[21] = LoadTexture("products/NH4Cl.png");

	for (int i = 0; i < 7; i++)
	{
		onFireTextures[i] = LoadTexture(TextFormat("onFire%d.png", i));
	}

	for (int i = 0; i < 4; i++)
	{
		idle[i] = LoadTexture(TextFormat("idle1.png"));
		idleBox[i] = LoadTexture(TextFormat("idleBox1.png"));
		interact[i] = LoadTexture(TextFormat("interact1.png"));
	}

	for (int i = 4; i < 8; i++)
	{
		idle[i] = LoadTexture(TextFormat("idle2.png"));
		idleBox[i] = LoadTexture(TextFormat("idleBox2.png"));
		interact[i] = LoadTexture(TextFormat("interact2.png"));
	}

	for (int i = 0; i < 8; i++)
	{
		moveUpRight[i] = LoadTexture(TextFormat("upRight%d.png", i + 1));
		moveUpLeft[i] = LoadTexture(TextFormat("upLeft%d.png", i + 1));
		moveDownRight[i] = LoadTexture(TextFormat("downRight%d.png", i + 1));
		moveDownLeft[i] = LoadTexture(TextFormat("downLeft%d.png", i + 1));
		moveUp[i] = LoadTexture(TextFormat("up%d.png", i + 1));
		moveDown[i] = LoadTexture(TextFormat("down%d.png", i + 1));
		moveRight[i] = LoadTexture(TextFormat("right%d.png", i + 1));
		moveLeft[i] = LoadTexture(TextFormat("left%d.png", i + 1));
	}

	react[0] = LoadTexture("react1.png");
	react[1] = LoadTexture("react2.png");

	inventory = LoadTexture("inventory.png");
	yourOrder = LoadTexture("yourOrder.png");
	chemistryShelfTexture = LoadTexture("chemistry-shelf.png");
	background = LoadTexture("background.png");
	walls = LoadTexture("walls.png");
	periodicTableTexture = LoadTexture("periodic-table.png");
	repeat = LoadTexture("repeat.png");
	mailboxOrderTexture = LoadTexture("mailboxOrderMenu.png");

	packageMenu[0] = LoadTexture("package.png");
	packageMenu[1] = LoadTexture("packageClosed.png");

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::string path = tracks[j];

			if (i == 0)
			{
				path += "-play.png";
			}
			else
			{
				path += "-pause.png";
			}

			musicCovers[i][j] = LoadTexture(path.c_str());
		}
	}
}

void Game::unload()
{
	for (int i = 0; i < 22; i++)
	{
		UnloadTexture(elements[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		if (i != 7)
		{
			UnloadTexture(onFireTextures[i]);
		}

		UnloadTexture(idle[i]);
		UnloadTexture(idleBox[i]);
		UnloadTexture(fireExtinguisher[i]);
		UnloadTexture(interact[i]);
		UnloadTexture(moveLeft[i]);
		UnloadTexture(moveRight[i]);
		UnloadTexture(moveUp[i]);
		UnloadTexture(moveDown[i]);
		UnloadTexture(moveDownLeft[i]);
		UnloadTexture(moveDownRight[i]);
		UnloadTexture(moveUpRight[i]);
		UnloadTexture(moveUpLeft[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		UnloadTexture(react[i]);
	}

	UnloadTexture(inventory);
	UnloadTexture(yourOrder);
	UnloadTexture(chemistryShelfTexture);
	UnloadTexture(background);
	UnloadTexture(walls);
	UnloadTexture(periodicTableTexture);
	UnloadTexture(repeat);
	UnloadTexture(mailboxOrderTexture);

	for (int i = 0; i < 2; i++)
	{
		UnloadTexture(packageMenu[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			UnloadTexture(musicCovers[i][j]);
		}
	}
}

void Game::moveCharacter()
{

	animationTimer += GetFrameTime();
	if (animationTimer >= 0.04f) // Make the animation slower
	{
		animationTimer = 0.0f;

		if (frame == 7)
		{
			frame = 0;
		}
		else
		{
			frame++;
		}

		if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D) && !isMenuOpened)
		{
			for (int i = 0; i < 35; i++)
			{
				if (CheckCollisionPointRec(character, collisions[0][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character.x -= 15;
				character.y -= 15;
			}
		}
		else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_D) && !isMenuOpened)
		{
			for (int i = 0; i < 30; i++)
			{
				if (CheckCollisionPointRec(character, collisions[1][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character.x -= 15;
				character.y += 15;
			}
		}
		else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_A) && !isMenuOpened)
		{
			for (int i = 0; i < 30; i++)
			{
				if (CheckCollisionPointRec(character, collisions[2][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character.x += 15;
				character.y += 15;
			}
		}
		else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D) && IsKeyUp(KEY_A) && IsKeyUp(KEY_S) && !isMenuOpened)
		{
			for (int i = 0; i < 35; i++)
			{
				if (CheckCollisionPointRec(character, collisions[3][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character.x += 15;
				character.y -= 15;
			}
		}
		else if (IsKeyDown(KEY_S) && IsKeyUp(KEY_D) && IsKeyUp(KEY_A) && IsKeyUp(KEY_W) && !isMenuOpened)
		{
			for (int i = 0; i < 20; i++)
			{
				if (CheckCollisionPointRec(character, collisions[4][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character.y += 20;
			}
		}
		else if (IsKeyDown(KEY_A) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D) && IsKeyUp(KEY_W) && !isMenuOpened)
		{
			for (int i = 0; i < 26; i++)
			{
				if (CheckCollisionPointRec(character, collisions[5][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character.x -= 20;
			}
		}
		else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_W) && !isMenuOpened)
		{
			for (int i = 0; i < 25; i++)
			{
				if (CheckCollisionPointRec(character, collisions[6][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character.x += 20;
			}
		}
		else if (IsKeyDown(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && !isMenuOpened)
		{
			for (int i = 0; i < 30; i++)
			{
				if (CheckCollisionPointRec(character, collisions[7][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character.y -= 20;
			}
		}
		inCollision = 0;
	}
}

void Game::drawBackground()
{
	if (!onFire)
	{
		ClearBackground(WHITE);
		DrawTexture(background, 0, 0, WHITE);
	}
}

void Game::drawWalls()
{
	if (!onFire)
	{
		DrawTexture(walls, 0, 0, WHITE);
	}
}

void Game::drawCharacterAnimations()
{
	if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
	{
		DrawTexture(moveUpRight[frame], character.x, character.y, WHITE);
	}
	else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
	{
		DrawTexture(moveUpLeft[frame], character.x, character.y, WHITE);
	}
	else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
	{
		DrawTexture(moveDownRight[frame], character.x, character.y, WHITE);
	}
	else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
	{
		DrawTexture(moveDownLeft[frame], character.x, character.y, WHITE);
	}
	else if (IsKeyDown(KEY_D))
	{
		DrawTexture(moveRight[frame], character.x, character.y, WHITE);
	}
	else if (IsKeyDown(KEY_A))
	{
		DrawTexture(moveLeft[frame], character.x, character.y, WHITE);
	}
	else if (IsKeyDown(KEY_W))
	{
		DrawTexture(moveUp[frame], character.x, character.y, WHITE);
	}
	else if (IsKeyDown(KEY_S))
	{
		DrawTexture(moveDown[frame], character.x, character.y, WHITE);
	}
	else if (isCarryingBox)
	{
		if (character.x >= 500 && character.x <= 560 && character.y >= 900 && character.y <= 1180)
		{
			DrawTexture(interact[frame], character.x, character.y, WHITE);

			if (IsKeyPressed(KEY_E))
			{
				mailbox = !mailbox;
			}
		}
		DrawTexture(idleBox[frame], character.x, character.y, WHITE);
	}
}