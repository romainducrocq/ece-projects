#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "maze.h"
#include "solver.h"
#include "graphic.h"
#include<utility>
#include<vector>
#include<string>
#include <fstream>
#include<sstream>
#include <iomanip>
#include <fmod.h>

class Menu
{
private :
    /// Attributes
    Maze m;
    Solver mySolver;
    bool m_is_in_menu;
    int m_menu_choice;
    std::vector<std::pair<std::string,unsigned short>> m_niveaux;
    std::vector<std::string> m_solver;
    FMOD_SYSTEM *system;
    FMOD_SOUND *music = NULL;

public :
    /// Constructor and Destructor
    Menu ();
    ~Menu ();

    /// Getters and setters
    bool GetInfos();
    bool getIs_in_menu ();
    int getMenu_choice ();
    void setIs_in_menu (bool _is_in_menu);
    void setMenu_choice (int _menu_choice);

    /// Methods
    void launchMenu();
    void DifficultyMenu();
    void NiveauMenu(unsigned int difficulty);
    void SolverMenu(unsigned int difficulty, unsigned int level);

    void Solver(const std::string& path, const unsigned int& choice);
    void Player(const std::string& path);

    void initMenuScreen();
    void DifficultyScreen();
    void NiveauScreen(unsigned int k);
    void SolverScreen();

    void defaultBackground();
    void REST();
    std::string intToSTring(int toString);

    void launchMUSIC();
    void releaseMUSIC();
    void pauseMUSIC();
    //void gamerDecision (Console* pConsole);
    //void display_menu (Console* pConsole);
    //void launchGame(Console* pConsole,Level m_level);

};

#endif // MENU_H_INCLUDED
