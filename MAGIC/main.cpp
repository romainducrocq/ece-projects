#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include "Deck.h"
#include "pConsole.h"

using namespace std;

int main()
{
        srand (time(NULL));
        system("mode con lines=35 cols=55");

    /// Instance of console
    Console* pConsole = NULL;
    pConsole = Console::getInstance();
    pConsole->gotoLigCol(0,0);
    pConsole->setColor(COLOR_WHITE);

    Deck Magie;
    Magie.Jeu(pConsole);


    Console::deleteInstance();

    return 0;
}
