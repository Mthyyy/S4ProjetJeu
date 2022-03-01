#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <time.h>
#include <string.h>

void GameLoop();

struct Actor
{
    int posX;
    int posY;
    int actorId;
}

main()
{
    // Ces deux variables servent a prendre en compte le temps pris par la boucle de jeu pour l'appel de sleep pour etre a 60hz
    clock_t before;
    clock_t now;
    struct Actor actorList[8];
    int codeJoystick; // 1 = droite, 2 = gauche, 3 = haut, 4 = bas, 5 = droite+btn, 6 = gauche+btn, 7 = haut+btn, 8 = bas+btn,

    while (1)
    {
        before = clock() / CLOCKS_PER_SEC * 1000; // Pour avoir le temps en ms

        GameLoop(actorList);

        now = clock() / CLOCKS_PER_SEC * 1000;

        // 60Hz - delta entre quand on a commence et quand on a fini les operations avant sleep
        printf("Execution time: %f\n", (now - before));
        // Sleep(16.6666666 - (now - before)); C'est pete, on dirait qu'il attend au debut avant de faire le reste genre before = ... jcomprend pas mais dans vitis sleep est diff so on est good
    }
}

// Va chercher l'etat du joystick
int GetJoystick()
{
    /**
       int codeJoystick;
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
}

// Boucle dans laquelle tous les acteurs bougent et on appelle la methode de verification de collisions
void GameLoop(struct Actor actorList[8])
{
    int salut = 1000 * 100 + 32 * 24;
}