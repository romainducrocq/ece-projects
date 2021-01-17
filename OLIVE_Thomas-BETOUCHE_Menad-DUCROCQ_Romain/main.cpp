#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include "console.h"
#include "Snoopy.h"
#include "level.h"
#include "Enemy.h"
#include "Timer_Score.h"
#include "menu.h"

int main()
{
    /// Initialization of clock
    srand (time(NULL));

    /// Instance of console
    Console* pConsole = NULL;
    pConsole = Console::getInstance();
    pConsole->gotoLigCol(0,0);

    /// Creation and display of menu
    Menu menu (true);
    menu.display_menu(pConsole);

    /// Delete instance and end of main
    Console::deleteInstance();
    return 0;
}
