#pragma once
#include <iostream>
#include "raylib.h"

class Game
{
public:
    ~Game();
    Game();

    void loop();
    void moveCharacter();
    void drawBackground();
    void drawCharacterAnimations();
    void drawWalls();
    void drawInventory();
    void isMusicPaused();
    void drawMusicPlayer();
    void drawPeriodicTable();
    void drawReactor();
    void drawChemistryShelf();
    void drawPackageMenu();
    void drawOrderMenu();
    void drawMailbox();
    void drawOnFireAnimation();
    void load();
    void unload();

private:

    bool interaction, isMenuOpened;
    bool periodicTable, chemistryShelf, reactor, musicPlayer, mailbox;
    bool pauseMusic, repeatMusic;
    bool packaging, packageClosed, isCarryingBox, isCarryingExtinguisher;
    bool onFire;
    bool inventoryElementTypes[6];
    bool inCollision = 0;
    float animationTimer, timePlayed;
    float extinguishTime;
    int frame;
    int reaction[3];
    int mouseX, mouseY;
    int selectedElement, elementPosition;
    int inventoryElements[6], inventoryIndex;
    int packageElement, orderElement;
    int musicIndex, randomMusic;

    Vector2 character;
    Color fire[7];
    Music music[5];

    Texture2D onFireTextures[7];
    Texture2D elements[22];
    Texture2D idle[8];
    Texture2D idleBox[8];
    Texture2D fireExtinguisher[8];
    Texture2D interact[8];
    Texture2D moveRight[8];
    Texture2D moveLeft[8];
    Texture2D moveUp[8];
    Texture2D moveDown[8];
    Texture2D moveDownLeft[8];
    Texture2D moveUpLeft[8];
    Texture2D moveDownRight[8];
    Texture2D moveUpRight[8];
    Texture2D react[2];
    Texture2D inventory;
    Texture2D yourOrder;
    Texture2D chemistryShelfTexture;
    Texture2D background;
    Texture2D walls;
    Texture2D periodicTableTexture;
    Texture2D repeat;
    Texture2D viewMolecule;
    Texture2D packageMenu[2];
    Texture2D musicCovers[2][5];
    Texture2D mailboxOrderTexture;

    Rectangle collisions[8][35] =
    {
        //W+A
        {
            -150, -100, 50, 1200,
            755, 630, 475, 60,
            -150, 380, 240, 80,
            100, -75, 200, 55,
            1460, 600, 460, 50,
            1500, 0, 420, 320,
            1450, 0, 50, 280,
            50, 220, 20, 170,
            50, 160, 40, 140,
            50, 330, 70, 140,
            110, -100, 90, 250,
            50, 120, 140, 40,
            190, 380, 280, 80,
            1520, 550, 10, 100,
            1510, 840, 10, 110,
            -130, 510, 170, 190,
            1520, -100, 10, 1080,
            1340, -100, 360, 110,
            1120, -100, 220, 90,
            830, -100, 330, 150,
            400, -100, 185, 150,
            550, -100, 450, 90,
            400, -100, 135, 420,
            760, 250, 460, 75,
            1220, 220, 15, 80,
            900, 340, 170, 20,
            950, 280, 150, 60,
            840, 0, 290, 180,
            500, 340, 70, 10,
            390, 860, 110, 370,
            -120, 730, 100, 400
        },

        //S+A
        {
            -150, -100, 50, 1200,
            -100, 900, 2050, 200,
            -100, 240, 170, 150,
            -100, 160, 195, 80,
            -100, 350, 220, 100,
            160, 320, 290, 120,
            110, -100, 90, 250,
            1510, 840, 10, 90,
            -100, 510, 160, 130,
            830, -100, 330, 150,
            400, -100, 185, 150,
            400, -100, 135, 390,
            760, 200, 460, 60,
            1220, 220, 15, 80,
            950, 280, 150, 60,
            840, -100, 360, 270,
            760, 550, 490, 30,
            750, 560, 475, 20,
            1455, 450, 465, 130,
            1510, 840, 10, 110,
            280, 830, 230, 370,
            -120, 730, 100, 400
        },

        //S+D
        {
            -100, 900, 2050, 200,
            740, 550, 485, 110,
            140, 280, 310, 160,
            375, 270, 95, 220,
            310, -100, 160, 410,
            1445, 500, 75, 170,
            1440, 840, 80, 90,
            1460, 820, 50, 130,
            1440, -100, 460, 380,
            1320, -100, 380, 110,
            805, -100, 195, 150,
            760, 200, 460, 60,
            740, 220, 30, 80,
            880, 300, 70, 40,
            840, -100, 270, 270,
            1460, 450, 460, 100,
            -100, 510, 160, 130,
            1440, -100, 460, 380,
            270, 830, 230, 300,
            -120, 730, 100, 400
        },

        //W+D
        {
            1760, -100, 200, 1200,
            80, 140, 110, 20,
            140, 380, 330, 80,
            320, 200, 150, 130,
            310, -100, 130, 300,
            -130, 510, 160, 190,
            1450, 500, 470, 150,
            1440, 840, 80, 110,
            1440, 100, 60, 200,
            1435, -100, 265, 250,
            1320, -100, 380, 110,
            1120, -100, 220, 90,
            830, -100, 170, 150,
            550, -100, 450, 90,
            760, 250, 460, 75,
            740, 220, 30, 80,
            900, 340, 170, 20,
            880, 300, 70, 40,
            840, -100, 270, 280,
            500, 10, 70, 120,
            500, 340, 70, 10,
            500, 10, 70, 100,
            500, 340, 70, 10,
            270, 750, 30, 370,
            750, 640, 475, 50,
            -150, 380, 240, 80,
            100, -75, 200, 55,
            1460, 600, 460, 50,
            805, -100, 195, 150,
            1340, -100, 360, 110,
            1500, -100, 419, 420
        },

        //S
        {
            -100, 900, 2050, 200,
            750, 560, 475, 20,
            160, 320, 290, 50,
            40, 320, 40, 80,
            50, 320, 30, 80,
            1460, 450, 460, 150,
            -120, 510, 140, 140,
            1460, 820, 50, 130,
            760, 200, 455, 60,
            280, 830, 210, 300,
            -120, 720, 100, 200
        },

        //A
        {
            -150, -100, 50, 1200,
            1215, 580, 15, 100,
            -100, 200, 170, 150,
            -100, 160, 200, 80,
            -100, 250, 220, 200,
            110, -100, 90, 260,
            1520, 550, 10, 110,
            1510, 840, 20, 110,
            375, 200, 95, 220,
            -100, 530, 150, 130,
            950, -100, 210, 150,
            400, -100, 185, 150,
            400, -100, 135, 450,
            1220, 220, 15, 80,
            950, 280, 150, 60,
            1050, -100, 80, 270,
            390, 850, 130, 370,
            -100, 760, 100, 400
        },

        //D
        {
            1760, -100, 200, 1200,
            740, 580, 485, 80,
            140, 340, 300, 100,
            375, 200, 50, 220,
            300, -100, 140, 350,
            1440, 490, 80, 170,
            1440, 840, 80, 90,
            1475, 100, 425, 200,
            1440, -100, 460, 380,
            1320, -100, 380, 110,
            830, -100, 170, 150,
            740, 220, 30, 80,
            880, 300, 70, 40,
            840, -100, 160, 270,
            270, 850, 30, 370
        },

        //W
        {
            755, 630, 470, 70,
            -150, 380, 240, 80,
            70, 140, 120, 20,
            50, 230, 40, 30,
            160, 380, 320, 80,
            330, -100, 70, 340,
            100, -75, 300, 55,
            1460, 600, 460, 40,
            -130, 510, 150, 190,
            1460, 500, 60, 170,
            1500, -100, 419, 420,
            1460, -100, 160, 380,
            1340, -100, 360, 110,
            1120, -100, 220, 90,
            550, -100, 450, 90,
            760, 250, 455, 75,
            900, 340, 180, 20,
            850, 100, 280, 80,
            500, 10, 100, 100,
            400, 240, 170, 110
        }
    };

    std::string tracks[5];

};