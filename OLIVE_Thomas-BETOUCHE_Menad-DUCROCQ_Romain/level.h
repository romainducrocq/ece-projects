#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include "block.h"
#include "console.h"
#include "Enemy.h"
#include "Timer_Score.h"

class Level
{
private :
    /// Attributes
    int m_nbLevelMax;
    int m_nbBirds;
    int m_nbActualLevel;
    int m_obstacle;
    int m_nbL, m_nbC;
    int m_chrono;
    bool m_pause;
    std::string m_name;

    std::vector <std::vector<Block> >m_tab;
    Snoopy m_player;
    timer_score m_timer;
    Enemy m_ball1, m_ball2, m_ball3, m_ball4;

public :
    /// Constructors and destructor
    Level();
    Level(int _actualLevel,int nbL,int nbC,std::string _pseudo,int nbLevel);
    ~Level();

    /// Setters and getters

    bool getPause() const;
    bool  getIsPlayerAlive() const;
    Enemy getEnemyDepart() const;

    void setPseudo(std::string pseudo);
    void setEnemy();
    void setTimer();
    void setPause();

    /// Methods
    void pause(int _key);
    void score();
    int afficheChrono(Console* pConsole);

    void movePlayer(int _key,Console* pConsole);
    Enemy moveEnemy(Enemy ball, Console* pConsole);
    void afficheMoveEnemy(Console* pConsole);

    void pushBlock (int _key,Console* pConsole);
    void breakBlock(int _key,Console* pConsole);
    void trapedBlock(Console* pConsole);
    bool birdBlock(Console* pConsole);
    void lifeBlock(Console* pConsole);
    void clockBlock(Console* pConsole);

    void isPlayerAlive();
    void perdreUneVie(Console* pConsole);

    void loadLevel (std::ifstream file);
    void setSave();
    void saveLevel ();

    void displayMatrix(Console* pConsole);

};

#endif // LEVEL_H_INCLUDED
