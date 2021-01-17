#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "console.h"
#include "level.h"
#include "Timer_Score.h"

class Menu
{
private :
    /// Attributes
    bool m_is_in_menu;
    int m_menu_choice;
    int m_saveNbActualLevel;
    std::string m_pseudo;
    Level m_level1;
    Level m_level2;
    Level m_level3;
    Level m_saveLevel;
    bool m_winLevel;

public :
    /// Constructor and Destructor
    Menu (bool _is_in_menu);
    ~Menu ();

    /// Getters and setters
    bool getIs_in_menu ();
    int getMenu_choice ();
    void setIs_in_menu (bool _is_in_menu);
    void setMenu_choice (int _menu_choice);

    /// Methods
    void sleep(unsigned int mseconds);
    void anim (Console* pconsole);
    void gamerDecision (Console* pConsole);
    void display_menu (Console* pConsole);
    void launchGame(Console* pConsole,Level m_level);
    void saveParameter();

};

#endif // MENU_H_INCLUDED

