#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

struct Actor
{
    int posX;
    int posY;
    int actorId; // 100 = innocuper
};

struct Camion
{

    struct Actor acteur[1];
    int tuileid[1];
};

struct Rondin
{

    struct Actor acteur[1];
    int tuileid[1];
};

// variable Global
#define NOMBREACTEUR 32

struct Rondin listRondin[3]; // grandeur peut varier si vous voulez plus d'Acteur
struct Camion listCamion[4]; // grandeur peut varier si vous voulez plus d'Acteur
struct Actor actorList[NOMBREACTEUR];

float speedligne2 = 1;
float speedligne3 = 1;
float speedligne5 = 1;
float speedligne6 = 1;
float speedligne7 = 1;
float speedligne8 = 1;
float speedligne9 = 1;
float speedligne10 = 1;
float speedligne11 = 1;
float speedligne12 = 1;

void ActorPositionUpdate(struct Actor actorList[8], int codeJoystick, bool nextLineJump, bool lastLineJump, bool rightLineJump, bool leftLineJump);
void GameLoop();
void InitializeActors(struct Actor actorList[8]);

int GetJoystick();

void updateObstacle()
{
    for (int i = 1; i <= 4; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne2;
    }

    for (int i = 5; i <= 8; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne3;
    }

    for (int i = 9; i <= 11; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne5;
    }
    for (int i = 12; i <= 13; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne6;
    }
    for (int i = 14; i <= 17; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne7;
    }
    for (int i = 18; i <= 21; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne8;
    }

    for (int i = 22; i <= 23; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne9;
    }

    for (int i = 24; i <= 27; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne10;
    }

    for (int i = 28; i <= 29; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne11;
    }

    for (int i = 30; i <= 31; i++)
    {
        actorList[i].posX = actorList[i].posX + 1 * speedligne12;
    }

    for (int i = 0; i < NOMBREACTEUR; i++)
    {
        if (actorList[i].posX = -1)
        {
            actorList[i].posX = 256;
        }
    }
}

int main()
{
    GameLoop();
    return 0;
}

void GameLoop()
{
    // Ces deux variables servent a prendre en compte le temps pris par la boucle de jeu pour l'appel de sleep pour etre a 60hz
    clock_t before;
    clock_t now;

    int codeJoystick;   // 1 = droite, 2 = gauche, 3 = haut, 4 = bas, 5 = droite+btn, 6 = gauche+btn, 7 = haut+btn, 8 = bas+btn, 0 =err
    bool nextLineJump;  // Sert a savoir s'il faut sauter avec le bouton pour avancer (nenuphar)
    bool lastLineJump;  // Sert a savoir s'il faut sauter avec le bouton pour reculer (nenuphar)
    bool rightLineJump; // Sert a savoir s'il faut sauter avec le bouton pour aller a droite (nenuphar)
    bool leftLineJump;  // Sert a savoir s'il faut sauter avec le bouton pour aller a gauche (nenuphar)

    InitializeActors(actorList);

    // On va pouvoir se mettre une condition de fin de la loop
    while (1)
    {
        before = clock() / CLOCKS_PER_SEC * 1000; // Pour avoir le temps en ms

        codeJoystick = GetJoystick();
        ActorPositionUpdate(actorList, codeJoystick, nextLineJump, lastLineJump, rightLineJump, leftLineJump);

        now = clock() / CLOCKS_PER_SEC * 1000;

        // 60Hz - delta entre quand on a commence et quand on a fini les operations avant sleep
        // Sleep(16.6666666 - (now - before)); C'est pete, on dirait qu'il attend au debut avant de faire le reste genre before = ... jcomprend pas mais dans vitis sleep est diff so on est good
    }
}

/**
Carte du jeu:
(0,224)
    Y
    |
    |
    |
    |
    |
    |
    |
    |
    |
    |
 0,0------------------------------->(256,0)   X

liste Acteur ligne pars de 0
0 Grenouille   partout
1-2   voiture2x1  1 ligne 2
3-4   voirute2x1  2 ligne 2
5-6   voiture2x1  1 ligne 3
7-8   voiture2x1  2 ligne 3
9     buche1x1    1 ligne 5
10-11  buche2x1    2 ligne 5
12-13 buche3x1   1 ligne 6
14-15 buche2x1   1 ligne 7
16-17 buche2x1   2 ligne 7
18-19 voiture2x1  1 ligne 8
20-21 voiture2x1  2 ligne 8
22-23 voiture3x1  1 ligne 9
24-25 voiture2x1  1 ligne 10
26-27 voiture2x1  2 ligne 10
28    buche 1x1   1 ligne 11
29    buche 1x1   1 ligne 11
30    buche 1x1   1 ligne 12
31    buche 1x1   1 ligne 12

**/

// Sert a initiliser tous les acteurs
void InitializeActors(struct Actor actorList[8])
{
    for (int i = 0; i < NOMBREACTEUR; i++)
    {
        actorList->actorId = 100; // 100 = innocupé besoin pour ma logique
        actorList->posX = 0;
        actorList->posY = 0;
    }

    // joueur
    actorList->actorId = 1;
}

// Va chercher l'etat du joystick
int GetJoystick()
{
    int codeJoystick = 0;
    /**
       int deadZone = 15;
       int centre = 128;

       double percentX = 100.0*positionX/255;
       double percentY = 100.0*positionY/255;

       if((positionX < (centre + deadZone) && positionX > (centre - deadZone)) && (positionY < (centre + deadZone) && positionY > (centre - deadZone)))
       {
           xil_printf("Position: Centre\r\n");
       }

       else
       {
           if(positionX > positionY)
           {
               if(positionX + positionY > 255)
               {
                   codeJoystick = 1;
               }

               else
               {
                   codeJoystick = 4;
               }

           }

           else
           {
               if(positionX + positionY > 255)
               {
                   codeJoystick = 3;
               }

               else
               {
                   codeJoystick = 2;
               }

           }
       }

       if(JSTK2_getBtns(&joystick) == 2)
       {
           if(codeJoystick = 1)
           {
               codeJoystick = 5
           }

           else if(codeJoystick = 2)
           {
               codeJoystick = 6
           }

           else if(codeJoystick = 3)
           {
               codeJoystick = 7
           }

           else
           {
               codeJoystick = 8
           }
       }
     **/

    return codeJoystick;
}

// Boucle dans laquelle tous les acteurs bougent et on appelle la methode de verification de collisions
void ActorPositionUpdate(struct Actor actorList[8], int codeJoystick, bool nextLineJump, bool lastLineJump, bool rightLineJump, bool leftLineJump)
{
    // Mouvements du joueur
    switch (codeJoystick)
    {
    case 1:
        if (rightLineJump == false)
        {
            actorList[0].posX += 1;
        }
        break;
    case 2:
        if (leftLineJump == false)
        {
            actorList[0].posX -= 1;
        }
        break;
    case 3:
        if (nextLineJump == false)
        {
            actorList[0].posY += 1;
        }
        break;
    case 4:
        if (lastLineJump == false)
        {
            actorList[0].posY -= 1;
        }
        break;
    case 5:
        actorList[0].posX += 1;
        break;
    case 6:
        actorList[0].posX -= 1;
        break;
    case 7:
        actorList[0].posY += 1;
        break;
    case 8:
        actorList[0].posY -= 1;
        break;
    }

    // Mouvements des obstacles
    updateObstacle();

    // Gestion des collisions
}