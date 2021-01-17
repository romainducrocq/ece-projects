#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <string>
#include <iostream>
#include <ctime>
#include "block.h"

class Enemy
{
private:
    int m_posX, m_posY, m_direction, m_nc, m_nl;
    int m_obstacle;

public:
    Enemy();
    Enemy(int posX, int posY, int direction, int nc, int nl);
    ~Enemy();

    ///getters

    int getposX() const;
    int getposY() const;
    int getdirection() const;

    ///setters
    void setdiaghg();
    void setdiaghd();
    void setdiagbg();
    void setdiagbd();

    ///methods

    void moveball(int obstacle);

};
#endif // ENEMY_H_INCLUDED
