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
    int tuileid;
    bool dangereux;
  
};

// variable Global
#define NOMBREACTEUR 32
#define LIGNE 14
#define COLONNE 16
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

void updateCollision()
{
    for(int i =0 ;i < NOMBREACTEUR;i++ )
    {
        if((actorList[0].posX = actorList[i].posX) && (actorList[0].posY = actorList[i].posY) && actorList[i].dangereux == true);
        //gameOver
        actorList[0].posX = COLONNE * 8;
        actorList[0].posY = 0;
        actorList[0].tuileid = 5;

    }
}
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

    InitializeActors();

    // On va pouvoir se mettre une condition de fin de la loop
    while (1)
    {
        before = clock() / CLOCKS_PER_SEC * 1000; // Pour avoir le temps en ms

        codeJoystick = GetJoystick();
        ActorPositionUpdate(&actorList, codeJoystick, nextLineJump, lastLineJump, rightLineJump, leftLineJump);

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
12-14 buche3x1   1 ligne 6
15-16 buche2x1   1 ligne 7
17-18 buche2x1   2 ligne 7
19-20 voiture2x1  1 ligne 8
21-22 voiture2x1  2 ligne 8
23-25 voiture3x1  1 ligne 9
26-27 voiture2x1  1 ligne 10
28-29 voiture2x1  2 ligne 10
30    buche 1x1   1 ligne 11
31    buche 1x1   1 ligne 11
32    buche 1x1   1 ligne 12
33    buche 1x1   1 ligne 12

**/

// Sert a initiliser tous les acteurs
void InitializeActors()
{
    
    // joueur
    actorList[0].posX = COLONNE * 8;
    actorList[0].posY = 0;
    actorList[0].dangereux = false;
    actorList[0].tuileid = 1;
    
   //voiture 1
    actorList[1].posX = COLONNE*15;
    actorList[1].posY = LIGNE * 2;
    actorList[1].dangereux = true;
    actorList[1].tuileid = 2;

    actorList[2].posX = COLONNE*16;
    actorList[2].posY = LIGNE * 2;
    actorList[2].dangereux = true;
    actorList[2].tuileid = 3;

    //voiture 2
    actorList[3].posX = COLONNE*2;
    actorList[3].posY = LIGNE * 2;
    actorList[3].dangereux = true;
    actorList[3].tuileid = 2;

    actorList[4].posX = COLONNE*3;
    actorList[4].posY = LIGNE * 2;
    actorList[4].dangereux = true;
    actorList[4].tuileid = 3;


   //voiture 3
    actorList[5].posX = COLONNE*15;
    actorList[5].posY = LIGNE * 3;
    actorList[5].dangereux = true;
    actorList[5].tuileid = 2;

    actorList[6].posX = COLONNE*16;
    actorList[6].posY = LIGNE * 3;
    actorList[6].dangereux = true;
    actorList[6].tuileid = 3;

    //voiture 4
    actorList[7].posX = COLONNE*2;
    actorList[7].posY = LIGNE * 3;
    actorList[7].dangereux = true;
    actorList[7].tuileid = 2;

    actorList[8].posX = COLONNE*3;
    actorList[8].posY = LIGNE * 3;
    actorList[8].dangereux = true;
    actorList[8].tuileid = 3;

    //Buche1
    actorList[9].posX = COLONNE*9;
    actorList[9].posY = LIGNE * 5;
    actorList[9].dangereux = false;
    actorList[9].tuileid = 4;

     //Buche2
    actorList[10].posX = COLONNE*2;
    actorList[10].posY = LIGNE * 5;
    actorList[10].dangereux = false;
    actorList[10].tuileid = 4;

    actorList[11].posX = COLONNE*3;
    actorList[11].posY = LIGNE * 5;
    actorList[11].dangereux = false;
    actorList[11].tuileid = 4;

    
     //Buche3
    actorList[12].posX = COLONNE*14;
    actorList[12].posY = LIGNE * 6;
    actorList[12].dangereux = false;
    actorList[12].tuileid = 4;

    actorList[13].posX = COLONNE*15;
    actorList[13].posY = LIGNE * 6;
    actorList[13].dangereux = false;
    actorList[13].tuileid = 4;

    actorList[14].posX = COLONNE*16;
    actorList[14].posY = LIGNE * 6;
    actorList[14].dangereux = false;
    actorList[14].tuileid = 4;

     //Buche4
    actorList[15].posX = COLONNE*15;
    actorList[15].posY = LIGNE * 7;
    actorList[15].dangereux = false;
    actorList[15].tuileid = 4;

    actorList[16].posX = COLONNE*16;
    actorList[16].posY = LIGNE * 7;
    actorList[16].dangereux = false;
    actorList[16].tuileid = 4;

    //Buche5
    actorList[17].posX = COLONNE*2;
    actorList[17].posY = LIGNE * 7;
    actorList[17].dangereux = false;
    actorList[17].tuileid = 4;

    actorList[18].posX = COLONNE*3;
    actorList[18].posY = LIGNE * 7;
    actorList[18].dangereux = false;
    actorList[18].tuileid = 4;


    //voiture 5
    actorList[19].posX = COLONNE*15;
    actorList[19].posY = LIGNE * 8;
    actorList[19].dangereux = true;
    actorList[19].tuileid = 2;

    actorList[20].posX = COLONNE*16;
    actorList[20].posY = LIGNE * 8;
    actorList[20].dangereux = true;
    actorList[20].tuileid = 3;
    
    //voiture 6
    actorList[21].posX = COLONNE*2;
    actorList[21].posY = LIGNE * 8;
    actorList[21].dangereux = true;
    actorList[21].tuileid = 2;

    actorList[22].posX = COLONNE*3;
    actorList[22].posY = LIGNE * 8;
    actorList[22].dangereux = true;
    actorList[22].tuileid = 3;

     //voiture 7
    actorList[23].posX = COLONNE*8;
    actorList[23].posY = LIGNE * 9;
    actorList[23].dangereux = true;
    actorList[23].tuileid = 2;

    actorList[24].posX = COLONNE*9;
    actorList[24].posY = LIGNE * 9;
    actorList[24].dangereux = true;
    actorList[24].tuileid = 3;

    actorList[25].posX = COLONNE*10;
    actorList[25].posY = LIGNE * 9;
    actorList[25].dangereux = true;
    actorList[25].tuileid = 3;

        //voiture 8
    actorList[26].posX = COLONNE*15;
    actorList[26].posY = LIGNE * 10;
    actorList[26].dangereux = true;
    actorList[26].tuileid = 2;

    actorList[27].posX = COLONNE*16;
    actorList[27].posY = LIGNE * 10;
    actorList[27].dangereux = true;
    actorList[27].tuileid = 3;

    //voiture 9
    actorList[28].posX = COLONNE*2;
    actorList[28].posY = LIGNE * 10;
    actorList[28].dangereux = true;
    actorList[28].tuileid = 2;

    actorList[29].posX = COLONNE*3;
    actorList[29].posY = LIGNE * 10;
    actorList[29].dangereux = true;
    actorList[29].tuileid = 3;

    //voiture 10
    actorList[28].posX = COLONNE*2;
    actorList[28].posY = LIGNE * 10;
    actorList[28].dangereux = true;
    actorList[28].tuileid = 2;

    actorList[29].posX = COLONNE*3;
    actorList[29].posY = LIGNE * 10;
    actorList[29].dangereux = true;
    actorList[29].tuileid = 3;

        //Buche6
    actorList[30].posX = COLONNE*6;
    actorList[30].posY = LIGNE * 11;
    actorList[30].dangereux = false;
    actorList[30].tuileid = 4;

      //Buche7
    actorList[31].posX = COLONNE*16;
    actorList[31].posY = LIGNE * 11;
    actorList[31].dangereux = false;
    actorList[31].tuileid = 4;

    //Buche8
    actorList[32].posX = COLONNE*14;
    actorList[32].posY = LIGNE * 12;
    actorList[32].dangereux = false;
    actorList[32].tuileid = 4;

    //Buche9
    actorList[32].posX = COLONNE*8;
    actorList[32].posY = LIGNE * 12;
    actorList[32].dangereux = false;
    actorList[32].tuileid = 4;

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
    updateCollision();

    // Gestion des collisions
}