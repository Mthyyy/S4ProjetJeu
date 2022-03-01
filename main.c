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
    int actorId; // Mtn que j'y pense, est-ce que c'est vrm necessaire d'avoir un id si on a des index?
};

void ActorPositionUpdate(struct Actor actorList[8], int codeJoystick, bool nextLineJump, bool lastLineJump, bool rightLineJump, bool leftLineJump);
void GameLoop();
void InitializeActors(struct Actor actorList[8]);

int GetJoystick();

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

    struct Actor actorList[8];

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

// Sert a initiliser tous les acteurs
void InitializeActors(struct Actor actorList[8])
{
    actorList[0].actorId = 0;
    actorList[0].posX = 0;
    actorList[0].posY = 0;

    actorList[1].actorId = 1;
    actorList[1].posX = 0;
    actorList[1].posY = 0;

    actorList[2].actorId = 2;
    actorList[2].posX = 0;
    actorList[2].posY = 0;

    actorList[3].actorId = 3;
    actorList[3].posX = 0;
    actorList[3].posY = 0;

    actorList[4].actorId = 4;
    actorList[4].posX = 0;
    actorList[4].posY = 0;

    actorList[5].actorId = 5;
    actorList[5].posX = 0;
    actorList[5].posY = 0;

    actorList[6].actorId = 6;
    actorList[6].posX = 0;
    actorList[6].posY = 0;

    actorList[7].actorId = 7;
    actorList[7].posX = 0;
    actorList[7].posY = 0;
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
    // Mouvements de l'acteur
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

    // Gestion des collisions
}