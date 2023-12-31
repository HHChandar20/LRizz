#include "Game.hpp"

Game::Game()
{
	//Initialize variables with default values

	for (int i = 0; i < 3; i++)
	{
		reaction[i] = -1;
	}
	animationTimer = 0.0f;
	timer = 0.0f;
	timePlayed = 0.0f;
	timerSeconds = 0;
	timerMinutes = 2;
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
	streak = 0;
	highestStreak = 0;
	slides = -1;

	if (FileExists("highscore.txt"))
	{
		highscore.open("highscore.txt", std::ios::in);
		getline(highscore, data);
		if (data != "")
		{
			highestStreak = stoi(data);
		}
		highscore.close();
	}

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
	orderElement = rand() % 16 + 6; //Pick a random element from 6 - 22
	inCollision = 0;

	character = { 130, 500 }; //character position (x, y)
	//character2 = { 400, 500 }; //character 2 position (x, y)
	fireArea = { 260, 850, 30, 370 }; //Coordinates for the fire extinguishing area
	
	//Initialize filter colors for on-fire
	for (int i = 0; i < 7; i++)
	{
		fire[i] = RED;
		if (i < 4)
			fire[i] = MAROON;
	}
	std::string path; // File path of the tracks
	for (int i = 0; i < 5; i++)
	{
		path = "assets/musicPlayer/tracks/" + tracks[i] + ".mp3";
		music[i] = LoadMusicStream(path.c_str());
	}

	extinguishTime = 0.0f;

	load();
	PlayMusicStream(music[musicIndex]); // Play Music
}

Game::~Game()
{
	unload();
}

void Game::load()
{
	//Load elements textures
	elements[0] = LoadTexture("assets/elements/H2.png");
	elements[1] = LoadTexture("assets/elements/Na.png");
	elements[2] = LoadTexture("assets/elements/O2.png");
	elements[3] = LoadTexture("assets/elements/S.png");
	elements[4] = LoadTexture("assets/elements/N2.png");
	elements[5] = LoadTexture("assets/elements/Cl2.png");
	elements[6] = LoadTexture("assets/products/H2O.png");
	elements[7] = LoadTexture("assets/products/HCl.png");
	elements[8] = LoadTexture("assets/products/H2S.png");
	elements[9] = LoadTexture("assets/products/SO2.png");
	elements[10] = LoadTexture("assets/products/SO3.png");
	elements[11] = LoadTexture("assets/products/H2SO3.png");
	elements[12] = LoadTexture("assets/products/H2SO4.png");
	elements[13] = LoadTexture("assets/products/NO2.png");
	elements[14] = LoadTexture("assets/products/NH3.png");
	elements[15] = LoadTexture("assets/products/HNO3.png");
	elements[16] = LoadTexture("assets/products/Na2S.png");
	elements[17] = LoadTexture("assets/products/Na2SO4.png");
	elements[18] = LoadTexture("assets/products/NaCl.png");
	elements[19] = LoadTexture("assets/products/NaH.png");
	elements[20] = LoadTexture("assets/products/NaOH.png");
	elements[21] = LoadTexture("assets/products/NH4Cl.png");

	//Load onFire effect textures
	for (int i = 0; i < 7; i++)
	{
		onFireTextures[i] = LoadTexture(TextFormat("assets/onFire/onFire%d.png", i + 1));
		fireExtinguisher[i] = LoadTexture(TextFormat("assets/characterAnimations/fireExtinguish%d.png", i + 1));
	}

	fireExtinguisher[7] = LoadTexture("assets/characterAnimations/fireExtinguish1.png");
	onFireTextures[7] = LoadTexture("assets/onFire/onFire7.png");

	for (int i = 0; i < 4; i++)
	{
		idle[i] = LoadTexture(TextFormat("assets/characterAnimations/idle1.png"));
		idleBox[i] = LoadTexture(TextFormat("assets/characterAnimations/idleBox1.png"));
		interact[i] = LoadTexture(TextFormat("assets/characterAnimations/interact1.png"));
	}

	for (int i = 4; i < 8; i++)
	{
		idle[i] = LoadTexture(TextFormat("assets/characterAnimations/idle2.png"));
		idleBox[i] = LoadTexture(TextFormat("assets/characterAnimations/idleBox2.png"));
		interact[i] = LoadTexture(TextFormat("assets/characterAnimations/interact2.png"));
	}

	//Load character moving animation textures
	for (int i = 0; i < 8; i++)
	{
		moveUpRight[i] = LoadTexture(TextFormat("assets/characterAnimations/upRight%d.png", i + 1));
		moveUpLeft[i] = LoadTexture(TextFormat("assets/characterAnimations/upLeft%d.png", i + 1));
		moveDownRight[i] = LoadTexture(TextFormat("assets/characterAnimations/downRight%d.png", i + 1));
		moveDownLeft[i] = LoadTexture(TextFormat("assets/characterAnimations/downLeft%d.png", i + 1));
		moveUp[i] = LoadTexture(TextFormat("assets/characterAnimations/up%d.png", i + 1));
		moveDown[i] = LoadTexture(TextFormat("assets/characterAnimations/down%d.png", i + 1));
		moveRight[i] = LoadTexture(TextFormat("assets/characterAnimations/right%d.png", i + 1));
		moveLeft[i] = LoadTexture(TextFormat("assets/characterAnimations/left%d.png", i + 1));
	}

	for (int i = 0; i < 7; i++)
	{
		rules[i] = LoadTexture(TextFormat("assets/rules/rules%d.png", i + 1));
	}

	react[0] = LoadTexture("assets/reactor/react1.png");
	react[1] = LoadTexture("assets/reactor/react2.png");

	inventory = LoadTexture("assets/chemistryShelf/inventory.png");
	yourOrder = LoadTexture("assets/orderMenu/yourOrder.png");
	chemistryShelfTexture = LoadTexture("assets/chemistryShelf/chemistry-shelf.png");
	background = LoadTexture("assets/background.png");
	walls = LoadTexture("assets/walls.png");
	periodicTableTexture = LoadTexture("assets/periodic-table.png");
	repeat = LoadTexture("assets/musicPlayer/repeat.png");
	mailboxOrderTexture = LoadTexture("assets/orderMenu/mailboxOrderMenu.png");

	packageMenu[0] = LoadTexture("assets/packageMenu/package.png");
	packageMenu[1] = LoadTexture("assets/packageMenu/packageClosed.png");

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::string path = "assets/musicPlayer/" + tracks[j];

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

	elementSound = LoadSound("assets/sounds/element.mp3");
	emergencySound = LoadSound("assets/sounds/emergency.mp3");
	glassSound = LoadSound("assets/sounds/glass.mp3");
	liquidSound = LoadSound("assets/sounds/liquid.mp3");
	submitSound = LoadSound("assets/sounds/submit.mp3");
	packagingSound = LoadSound("assets/sounds/packaging.mp3");
	reactorSound = LoadSound("assets/sounds/reactor.mp3");
}

void Game::unload()
{

	//Unload all textures
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

	UnloadSound(elementSound);
	UnloadSound(emergencySound);
	UnloadSound(glassSound);
	UnloadSound(liquidSound);
	UnloadSound(submitSound);
	UnloadSound(packagingSound);
	UnloadSound(reactorSound);
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


		/*if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT) && IsKeyUp(KEY_DOWN) && IsKeyUp(KEY_RIGHT) && !isMenuOpened)
		{
			for (int i = 0; i < 35; i++)
			{
				if (CheckCollisionPointRec(character2, collisions[0][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character2.x -= 15;
				character2.y -= 15;
			}
		}
		else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT) && IsKeyUp(KEY_UP) && IsKeyUp(KEY_RIGHT) && !isMenuOpened)
		{
			for (int i = 0; i < 30; i++)
			{
				if (CheckCollisionPointRec(character2, collisions[1][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character2.x -= 15;
				character2.y += 15;
			}
		}
		else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT) && IsKeyUp(KEY_UP) && IsKeyUp(KEY_LEFT) && !isMenuOpened)
		{
			for (int i = 0; i < 30; i++)
			{
				if (CheckCollisionPointRec(character2, collisions[2][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character2.x += 15;
				character2.y += 15;
			}
		}
		else if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_RIGHT) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_DOWN) && !isMenuOpened)
		{
			for (int i = 0; i < 35; i++)
			{
				if (CheckCollisionPointRec(character2, collisions[3][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character2.x += 15;
				character2.y -= 15;
			}
		}
		else if (IsKeyDown(KEY_DOWN) && IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_UP) && !isMenuOpened)
		{
			for (int i = 0; i < 20; i++)
			{
				if (CheckCollisionPointRec(character2, collisions[4][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character2.y += 20;
			}
		}
		else if (IsKeyDown(KEY_LEFT) && IsKeyUp(KEY_DOWN) && IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_UP) && !isMenuOpened)
		{
			for (int i = 0; i < 26; i++)
			{
				if (CheckCollisionPointRec(character2, collisions[5][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character2.x -= 20;
			}
		}
		else if (IsKeyDown(KEY_RIGHT) && IsKeyUp(KEY_DOWN) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_UP) && !isMenuOpened)
		{
			for (int i = 0; i < 25; i++)
			{
				if (CheckCollisionPointRec(character2, collisions[6][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character2.x += 20;
			}
		}
		else if (IsKeyDown(KEY_UP) && IsKeyUp(KEY_DOWN) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT) && !isMenuOpened)
		{
			for (int i = 0; i < 30; i++)
			{
				if (CheckCollisionPointRec(character2, collisions[7][i]))
				{
					inCollision = 1;
				}
			}
			if (!inCollision)
			{
				character2.y -= 20;
			}
		}
		*/
		
		inCollision = 0;
	
	}
}

void Game::drawBackground()
{
	ClearBackground(WHITE);
	DrawTexture(background, 0, 0, WHITE);
}

//Draw background parts which should be over the character
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
	else if (isCarryingExtinguisher && IsKeyDown(KEY_E))
	{
		DrawTexture(fireExtinguisher[frame], character.x, character.y, WHITE);

		if (CheckCollisionPointRec(character, fireArea))
			extinguishTime += GetFrameTime();

		if (extinguishTime >= 4.0f)
		{
			isCarryingExtinguisher = 0;
			onFire = 0;
			extinguishTime = 0.0f;
			pauseMusic = 0;
			StopSound(emergencySound);
		}
	}
	else
	{
		if (character.x >= 800 && character.x <= 920 && character.y >= 580 && character.y <= 700)
		{
			DrawTexture(interact[frame], character.x, character.y, WHITE);

			if (IsKeyPressed(KEY_E))
			{
				periodicTable = !periodicTable;
			}
		}
		else if (character.x >= 1400 && character.x <= 1500 && character.y >= 60 && character.y <= 120)
		{
			DrawTexture(interact[frame], character.x, character.y, WHITE);

			if (IsKeyPressed(KEY_E))
			{
				musicPlayer = !musicPlayer;
			}
		}
		else if (character.x >= 1000 && character.x <= 1190 && character.y >= 580 && character.y <= 720)
		{
			DrawTexture(interact[frame], character.x, character.y, WHITE);

			if (IsKeyPressed(KEY_E))
			{
				chemistryShelf = !chemistryShelf;
			}
		}
		else if (character.x >= -50 && character.x <= 50 && character.y >= 650 && character.y <= 720)
		{
			DrawTexture(interact[frame], character.x, character.y, WHITE);

			if (IsKeyPressed(KEY_E))
			{
				reactor = !reactor;
			}
		}
		else if (character.x >= 880 && character.x <= 1080 && character.y >= 250 && character.y <= 370)
		{
			DrawTexture(interact[frame], character.x, character.y, WHITE);

			if (IsKeyPressed(KEY_E))
			{
				packaging = !packaging;
			}
		}
		else if (character.x >= 500 && character.x <= 560 && character.y >= 900 && character.y <= 1180)
		{
			DrawTexture(interact[frame], character.x, character.y, WHITE);

			if (IsKeyPressed(KEY_E))
			{
				mailbox = !mailbox;
			}
		}
		else
		{
			DrawTexture(idle[frame], character.x, character.y, WHITE);
		}
	}
}

/*void Game::drawCharacter2Animations()
{
	if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_RIGHT))
	{
		DrawTexture(moveUpRight[frame], character2.x, character2.y, RED);
	}
	else if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT))
	{
		DrawTexture(moveUpLeft[frame], character2.x, character2.y, RED);
	}
	else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT))
	{
		DrawTexture(moveDownRight[frame], character2.x, character2.y, RED);
	}
	else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT))
	{
		DrawTexture(moveDownLeft[frame], character2.x, character2.y, RED);
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		DrawTexture(moveRight[frame], character2.x, character2.y, RED);
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		DrawTexture(moveLeft[frame], character2.x, character2.y, RED);
	}
	else if (IsKeyDown(KEY_UP))
	{
		DrawTexture(moveUp[frame], character2.x, character2.y, RED);
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		DrawTexture(moveDown[frame], character2.x, character2.y, RED);
	}
	else if (isCarryingBox)
	{
		if (character2.x >= 500 && character2.x <= 560 && character2.y >= 900 && character2.y <= 1180)
		{
			DrawTexture(interact[frame], character2.x, character2.y, RED);

			if (IsKeyPressed(KEY_E))
			{
				mailbox = !mailbox;
			}
		}
		DrawTexture(idleBox[frame], character2.x, character2.y, RED);
	}
	else if (isCarryingExtinguisher && IsKeyDown(KEY_P))
	{
		DrawTexture(fireExtinguisher[frame], character2.x, character2.y, RED);

		if (CheckCollisionPointRec(character2, fireArea))
			extinguishTime += GetFrameTime();

		if (extinguishTime >= 4.0f)
		{
			isCarryingExtinguisher = 0;
			onFire = 0;
			extinguishTime = 0.0f;
			pauseMusic = 0;
			StopSound(emergencySound);
		}
	}
	else
	{
		if (character2.x >= 800 && character2.x <= 920 && character2.y >= 580 && character2.y <= 700)
		{
			DrawTexture(interact[frame], character2.x, character2.y, RED);

			if (IsKeyPressed(KEY_E))
			{
				periodicTable = !periodicTable;
			}
		}
		else if (character2.x >= 1400 && character2.x <= 1500 && character2.y >= 60 && character2.y <= 120)
		{
			DrawTexture(interact[frame], character2.x, character2.y, RED);

			if (IsKeyPressed(KEY_E))
			{
				musicPlayer = !musicPlayer;
			}
		}
		else if (character2.x >= 1000 && character2.x <= 1190 && character2.y >= 580 && character2.y <= 720)
		{
			DrawTexture(interact[frame], character2.x, character2.y, RED);

			if (IsKeyPressed(KEY_E))
			{
				chemistryShelf = !chemistryShelf;
			}
		}
		else if (character2.x >= -50 && character2.x <= 50 && character2.y >= 650 && character2.y <= 720)
		{
			DrawTexture(interact[frame], character2.x, character2.y, RED);

			if (IsKeyPressed(KEY_E))
			{
				reactor = !reactor;
			}
		}
		else if (character2.x >= 880 && character2.x <= 1080 && character2.y >= 250 && character2.y <= 370)
		{
			DrawTexture(interact[frame], character2.x, character2.y, RED);

			if (IsKeyPressed(KEY_E))
			{
				packaging = !packaging;
			}
		}
		else if (character2.x >= 500 && character2.x <= 560 && character2.y >= 900 && character2.y <= 1180)
		{
			DrawTexture(interact[frame], character2.x, character2.y, RED);

			if (IsKeyPressed(KEY_E))
			{
				mailbox = !mailbox;
			}
		}
		else
		{
			DrawTexture(idle[frame], character2.x, character2.y, RED);
		}
	}
}
*/
void Game::isMusicPaused()
{
	if (pauseMusic) PauseMusicStream(music[musicIndex]);
	else ResumeMusicStream(music[musicIndex]);
}

void Game::drawMusicPlayer()
{
	isMenuOpened = 1; // Disable character moving while a menu is opened

	DrawTexture(musicCovers[pauseMusic][musicIndex], 0, 0, WHITE);

	//Get the time the track has been playing 
	timePlayed = GetMusicTimePlayed(music[musicIndex]) / GetMusicTimeLength(music[musicIndex]);

	//Pause music
	if (IsKeyPressed(KEY_P))
	{
		pauseMusic = !pauseMusic;
	}
	if (IsKeyPressed(KEY_RIGHT) || (timePlayed >= 0.999f && !repeatMusic))
	{
		//Next track

		StopMusicStream(music[musicIndex]);
		if (musicIndex != 4)
		{
			musicIndex++;
		}
		else
		{
			musicIndex = 0;
		}
		pauseMusic = 0;
		PlayMusicStream(music[musicIndex]);
	}
	if (IsKeyPressed(KEY_LEFT))
	{
		//Previous track

		StopMusicStream(music[musicIndex]);
		if (musicIndex != 0)
		{
			musicIndex--;
		}
		else
		{
			musicIndex = 4;
		}
		pauseMusic = 0;
		PlayMusicStream(music[musicIndex]);
	}
	if (IsKeyPressed(KEY_R))
	{
		repeatMusic = !repeatMusic; // Enable/disable music repeat functionality
	}
	if (IsKeyPressed(KEY_Q))
	{
		// Choose a random track
		StopMusicStream(music[musicIndex]);
		randomMusic = rand() % 5;

		while (randomMusic == musicIndex)
		{
			randomMusic = rand() % 5;
		}
		musicIndex = randomMusic;
		pauseMusic = 0;

		PlayMusicStream(music[musicIndex]);
	}

	if (repeatMusic)
	{
		DrawTexture(repeat, 0, 0, WHITE);
	}
}

void Game::drawPeriodicTable()
{
	isMenuOpened = 1;

	if (IsKeyPressed(KEY_RIGHT)) // Next slide
	{
		if (slides != 6)
			slides++;
	}
	else if (IsKeyPressed(KEY_LEFT)) // Previous slide
	{
		if (slides != -1)
			slides--;
	}

	if (slides == -1)
	{
		DrawTexture(periodicTableTexture, 0, 0, WHITE);
	}
	else
	{
		DrawTexture(rules[slides], 0, 0, WHITE);
	}

	DrawText(TextFormat("%d/8", slides + 2), 1770, 100, 70, BLACK);

}

void Game::drawInventory()
{
	DrawTexture(inventory, 0, 0, WHITE);

	// Display inventory elements
	for (int i = 0; i < 6; i++)
	{
		if (inventoryElements[i] != -1)
		{
			DrawTexture(elements[inventoryElements[i]], 483 + i * 171, 895, WHITE);
		}
	}
}

void Game::drawChemistryShelf()
{
	isMenuOpened = 1;
	DrawTexture(chemistryShelfTexture, 0, 0, WHITE);

	// Drag and drop elements
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < 6; i++)
		{
			if (GetMouseX() >= 475 + i * 171 && GetMouseX() <= 590 + i * 171 && GetMouseY() >= 400 && GetMouseY() <= 510 && selectedElement == -1)
			{
				PlaySound(elementSound);
				selectedElement = i;
			}
		}
	}
	else
	{
		isMenuOpened = 1;

		// Place selected element
		if (selectedElement != -1)
		{
			for (int i = 0; i < 6; i++)
			{
				if (GetMouseX() >= 460 + i * 171 && GetMouseX() <= 600 + i * 171 && GetMouseY() >= 850 && GetMouseY() <= 970)
				{
					inventoryElements[i] = selectedElement;
				}
			}
		}

		selectedElement = -1;
	}

	for (int i = 0; i < 6; i++)
	{
		if (i != selectedElement)
		{
			DrawTexture(elements[i], 483 + i * 171, 428, WHITE);
		}
	}

	drawInventory();

	// Draw the selected element
	if (selectedElement != -1)
	{
		DrawTexture(elements[selectedElement], GetMouseX() - 70, GetMouseY() - 20, WHITE);
	}
}

void Game::drawReactor()
{
	isMenuOpened = 1;
	DrawTexture(react[0], 0, 0, WHITE);

	if (((IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetMouseX() >= 770 && GetMouseX() <= 1000 && GetMouseY() >= 760 && GetMouseY() <= 870) || IsKeyDown(KEY_SPACE)) && selectedElement == -1)
	{
		DrawTexture(react[1], 0, 0, WHITE);
	}
	else if (((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && GetMouseX() >= 770 && GetMouseX() <= 1000 && GetMouseY() >= 760 && GetMouseY() <= 870) || IsKeyReleased(KEY_SPACE)) && selectedElement == -1)
	{
		PlaySound(reactorSound);

		// Reactions
		if ((reaction[0] == 0 && reaction[1] == 1) || (reaction[0] == 1 && reaction[1] == 0))
		{
			reaction[2] = 19; //NaH
		}
		else if ((reaction[0] == 0 && reaction[1] == 2) || (reaction[0] == 2 && reaction[1] == 0))
		{
			reaction[2] = 6; //H2O
		}
		else if ((reaction[0] == 0 && reaction[1] == 3) || (reaction[0] == 3 && reaction[1] == 0))
		{
			reaction[2] = 8; //H2S
		}
		else if ((reaction[0] == 0 && reaction[1] == 4) || (reaction[0] == 4 && reaction[1] == 0))
		{
			reaction[2] = 14; //NH3
		}
		else if ((reaction[0] == 0 && reaction[1] == 5) || (reaction[0] == 5 && reaction[1] == 0))
		{
			reaction[2] = 7; //HCl
		}
		else if ((reaction[0] == 1 && reaction[1] == 3) || (reaction[0] == 3 && reaction[1] == 1))
		{
			reaction[2] = 16; //Na2S
		}
		else if ((reaction[0] == 1 && reaction[1] == 5) || (reaction[0] == 5 && reaction[1] == 1))
		{
			reaction[2] = 18; //NaCl
		}
		else if ((reaction[0] == 2 && reaction[1] == 3) || (reaction[0] == 3 && reaction[1] == 2))
		{
			reaction[2] = 9; //SO2
		}
		else if ((reaction[0] == 2 && reaction[1] == 4) || (reaction[0] == 4 && reaction[1] == 2))
		{
			reaction[2] = 13; //NO2
		}
		else if ((reaction[0] == 6 && reaction[1] == 1) || (reaction[0] == 1 && reaction[1] == 6))
		{
			reaction[2] = 20; //NaOH
		}
		else if ((reaction[0] == 6 && reaction[1] == 3) || (reaction[0] == 3 && reaction[1] == 6))
		{
			reaction[2] = 8; //H2S
		}
		else if ((reaction[0] == 7 && reaction[1] == 1) || (reaction[0] == 1 && reaction[1] == 7))
		{
			reaction[2] = 18; //NaCl
		}
		else if ((reaction[0] == 7 && reaction[1] == 2) || (reaction[0] == 2 && reaction[1] == 7))
		{
			reaction[2] = 6; //H2O
		}
		else if ((reaction[0] == 7 && reaction[1] == 3) || (reaction[0] == 3 && reaction[1] == 7))
		{
			reaction[2] = 8; //H2S
		}
		else if ((reaction[0] == 8 && reaction[1] == 1) || (reaction[0] == 1 && reaction[1] == 8))
		{
			reaction[2] = 16; //Na2S
		}
		else if ((reaction[0] == 8 && reaction[1] == 2) || (reaction[0] == 2 && reaction[1] == 8))
		{
			reaction[2] = 9; //SO2
		}
		else if ((reaction[0] == 8 && reaction[1] == 5) || (reaction[0] == 5 && reaction[1] == 8))
		{
			reaction[2] = 7; //HCl
		}
		else if ((reaction[0] == 9 && reaction[1] == 2) || (reaction[0] == 2 && reaction[1] == 9))
		{
			reaction[2] = 10; //SO3
		}
		else if ((reaction[0] == 10 && reaction[1] == 0) || (reaction[0] == 0 && reaction[1] == 10))
		{
			reaction[2] = 11; //H2SO3
		}
		else if ((reaction[0] == 11 && reaction[1] == 2) || (reaction[0] == 2 && reaction[1] == 11))
		{
			reaction[2] = 12; //H2SO4
		}
		else if ((reaction[0] == 12 && reaction[1] == 1) || (reaction[0] == 1 && reaction[1] == 12))
		{
			reaction[2] = 17; //Na2SO4
		}
		else if ((reaction[0] == 13 && reaction[1] == 0) || (reaction[0] == 0 && reaction[1] == 13))
		{
			reaction[2] = 14; //NH3
		}
		else if ((reaction[0] == 13 && reaction[1] == 6) || (reaction[0] == 6 && reaction[1] == 13))
		{
			reaction[2] = 15; //HNO3
		}
		else if ((reaction[0] == 14 && reaction[1] == 5) || (reaction[0] == 5 && reaction[1] == 14))
		{
			reaction[2] = 21; //NH4Cl
		}
		else if ((reaction[0] == 16 && reaction[1] == 2) || (reaction[0] == 2 && reaction[1] == 16))
		{
			reaction[2] = 17; //Na2SO4
		}
		else if ((reaction[0] == 19 && reaction[1] == 2) || (reaction[0] == 2 && reaction[1] == 19))
		{
			reaction[2] = 20; //NaOH
		}
		else if ((reaction[0] == 19 && reaction[1] == 3) || (reaction[0] == 3 && reaction[1] == 19))
		{
			reaction[2] = 16; //Na2S
		}
		else if ((reaction[0] == 20 && reaction[1] == 5) || (reaction[0] == 5 && reaction[1] == 20))
		{
			reaction[2] = 18; //NaCl
		}
		else if (reaction[0] != -1 || reaction[1] != -1)
		{
			reactor = 0;
			onFire = 1; // Start a fire
			isCarryingExtinguisher = 1; // Pick up the fire extinguisher
			pauseMusic = 1;
		}

		reaction[0] = -1;
		reaction[1] = -1;
	}

	DrawTexture(inventory, 370, -450, WHITE);

	for (int i = 0; i < 6; i++)
	{
		if (i != inventoryIndex && inventoryElements[i] != -1)
		{
			DrawTexture(elements[inventoryElements[i]], 853 + i * 171, 446, WHITE);
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < 6; i++)
		{
			if (GetMouseX() >= 845 + i * 170 && GetMouseX() <= 960 + i * 170 && GetMouseY() >= 400 && GetMouseY() <= 510 && selectedElement == -1 && inventoryElements[i] != -1)
			{
				selectedElement = inventoryElements[i];
				inventoryElements[i] = -1;
				inventoryIndex = i;
			}
		}

		if (GetMouseX() >= 370 && GetMouseX() <= 510 && GetMouseY() >= 725 && GetMouseY() <= 865 && selectedElement == -1)
		{
			selectedElement = reaction[2];
		}

	}
	else
	{
		if (selectedElement != -1)
		{
			for (int i = 0; i < 6; i++)
			{
				if (GetMouseX() >= 360 && GetMouseX() <= 525 && GetMouseY() >= 290 + i * 185 && GetMouseY() <= 425 + i * 185 && (i == 0 || i == 1))
				{
					if (selectedElement >= 6 && selectedElement <= 12)
						PlaySound(glassSound);
					else if (selectedElement != -1)
						PlaySound(elementSound);

					if (selectedElement == reaction[2])
					{
						reaction[2] = -1;
					}
					else
					{
						inventoryElements[inventoryIndex] = -1;
					}
					reaction[i] = selectedElement;
				}
				else if (GetMouseX() >= 830 + i * 170 && GetMouseX() <= 975 + i * 170 && GetMouseY() >= 400 && GetMouseY() <= 510)
				{
					if (selectedElement >= 6 && selectedElement <= 12)
						PlaySound(glassSound);
					else if (selectedElement != -1)
						PlaySound(elementSound);

					if (inventoryElements[i] == -1)
					{
						inventoryElements[i] = selectedElement;
						if (selectedElement == reaction[2])
						{
							reaction[2] = -1;
						}
					}
					else
					{
						inventoryElements[inventoryIndex] = selectedElement;
					}
				}
			}

		}
		selectedElement = -1;
		inventoryIndex = -1;
	}

	// Reset reactor elements
	if (IsKeyDown(KEY_R))
	{
		for (int i = 0; i < 3; i++)
		{
			reaction[i] = -1;
		}
	}

	//Draw reactor elements
	for (int i = 0; i < 2; i++)
	{
		if (reaction[i] != -1)
		{
			DrawTexture(elements[reaction[i]], 392, 328 + i * 185, WHITE);
		}
	}

	if (reaction[2] != -1 && selectedElement != reaction[2])
	{
		DrawTexture(elements[reaction[2]], 392, 765, WHITE);
	}

	if (selectedElement != -1)
	{
		if (inventoryIndex != -1)
		{
			DrawTexture(elements[selectedElement], GetMouseX() - 70, GetMouseY() - 20, WHITE);
		}
		else
		{
			DrawTexture(elements[selectedElement], GetMouseX() - 70, GetMouseY() - 20, WHITE);
		}
	}
}

void Game::drawPackageMenu()
{
	isMenuOpened = 1;

	if (!packageClosed) // Check if the package is ready for delivery
	{
		DrawTexture(packageMenu[0], 0, 0, WHITE);
	}
	else
	{
		DrawTexture(packageMenu[1], 0, 0, WHITE);

		// Pick up the package
		if (IsKeyPressed(KEY_R))
		{
			PlaySound(packagingSound);
			isCarryingBox = 1;
			packaging = 0;
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < 6; i++)
		{
			if (GetMouseX() >= 460 + i * 171 && GetMouseX() <= 600 + i * 171 && GetMouseY() >= 850 && GetMouseY() <= 970 && selectedElement == -1 && inventoryElements[i] != -1)
			{
				selectedElement = inventoryElements[i];
				inventoryElements[i] = -1;
				inventoryIndex = i;
			}
		}
	}
	else
	{
		if (selectedElement != -1)
		{
			if (GetMouseX() >= 895 && GetMouseX() <= 1030 && GetMouseY() >= 155 && GetMouseY() <= 290 && !packageClosed)
			{
				inventoryElements[inventoryIndex] = packageElement;
				packageElement = selectedElement;
			}
			else
			{
				inventoryElements[inventoryIndex] = selectedElement;
			}
		}

		selectedElement = -1;
		inventoryIndex = -1;
	}

	drawInventory();

	if (packageElement != -1)
	{
		// Close the package
		if (IsKeyPressed(KEY_F))
		{
			packageClosed = !packageClosed;
		}
		if (!packageClosed)
		{
			DrawTexture(elements[packageElement], 913, 193, WHITE);
		}
	}

	if (selectedElement != -1)
	{
		DrawTexture(elements[selectedElement], GetMouseX() - 70, GetMouseY() - 20, WHITE);
	}
}

void Game::drawMailbox()
{
	if (isCarryingBox)
	{
		PlaySound(submitSound);

		if (packageElement == orderElement)
		{
			streak++;

			// Set highest streak
			if (streak > highestStreak)
				highestStreak = streak;

			orderElement = rand() % 16 + 6;
		}
		else
		{
			resetStreak();
		}
		isCarryingBox = 0;
		mailbox = 0;
		packageElement = -1;
		packageClosed = 0;
		resetTimer();
	}
	else
	{
		isMenuOpened = 1;
		DrawTexture(mailboxOrderTexture, 0, 0, WHITE);
		DrawTexture(elements[orderElement], 910, 530, WHITE);
	}
}

void Game::drawOrderMenu()
{
	DrawTexture(yourOrder, 0, 0, WHITE);
	DrawTexture(elements[orderElement], 910, 530, WHITE);

	drawInventory();
}

void Game::drawOnFireAnimation()
{
	if(!IsSoundPlaying(emergencySound))
		PlaySound(emergencySound);
	DrawTexture(onFireTextures[frame], 0, 0, fire[frame]);
}

void Game::resetStreak()
{
	streak = 0;
	orderElement = rand() % 16 + 6;
}

void Game::drawStreak()
{
	DrawRectangle(1700, 90, 210, 60, BEIGE);
	DrawText(TextFormat("Streak: %d", streak), 1710, 100, 40, BLACK);

	DrawRectangle(1600, 170, 310, 60, BEIGE);
	DrawText(TextFormat("Highest streak: %d", highestStreak), 1620, 185, 30, BLACK);
}

void Game::drawTimer()
{
	timer += 0.0018f; // Set timer increasing value

	if (timer >= 0.1f) // Make the timer slower
	{
		timer = 0.0f;

		timerSeconds -= 1;
		if (timerSeconds == -1)
		{
			timerMinutes -= 1;
			timerSeconds = 59;
		}

		if (timerSeconds == 0 && timerMinutes == 0)
		{
			resetStreak();
			resetTimer();
		}
	}
	DrawRectangle(30, 90, 175, 70, BLACK);

	if (timerSeconds == 0)
	{
		DrawText(TextFormat("0%d:%d0", timerMinutes, timerSeconds), 50, 100, 60, WHITE);
	}
	else if (timerSeconds < 10)
	{
		DrawText(TextFormat("0%d:0%d", timerMinutes, timerSeconds), 50, 100, 60, WHITE);
	}
	else
	{
		DrawText(TextFormat("0%d:%d", timerMinutes, timerSeconds), 50, 100, 60, WHITE);
	}


}

void Game::resetTimer()
{
	timerMinutes = 2;
	timerSeconds = 0;
}

//Draw game loop
void Game::loop()
{
	UpdateMusicStream(music[musicIndex]);
	if (!onFire)
	{
		drawBackground();
	}
	moveCharacter();
	if (onFire)
	{
		drawOnFireAnimation();
	}
	drawCharacterAnimations();
	//drawCharacter2Animations();
	isMusicPaused();
	isMenuOpened = 0;

	if (!onFire)
	{
		drawWalls();
	}
	if (musicPlayer)
	{
		drawMusicPlayer();
	}
	if (periodicTable)
	{
		drawPeriodicTable();
	}
	if (chemistryShelf)
	{
		drawChemistryShelf();
	}
	if (reactor)
	{
		drawReactor();
	}
	if (packaging)
	{
		drawPackageMenu();
	}
	if (mailbox)
	{
		drawMailbox();
	}

	if (IsKeyDown(KEY_TAB) && !isMenuOpened) // Display inventory
	{
		drawOrderMenu();
		drawStreak();
	}

	drawTimer();
}