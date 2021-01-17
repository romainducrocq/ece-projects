#ifndef SNOOPY_H_INCLUDED
#define SNOOPY_H_INCLUDED

#include <string>
#include <iostream>
#include "block.h"

class Snoopy
{
private :

    std::string m_pseudo;
    int m_posX;
    int m_posY;
    int m_life;
    int m_score;
    bool m_alive;

public:

    ///Constructor/Destructor
    Snoopy();
    Snoopy(std::string pseudo);
    ~Snoopy();

    ///Getter
    int getPosX() const;
    int getPosY() const;
    int getLife() const;
    int getScore() const;
    bool getAlive() const;

    ///Setters
    void setPosX(int);
    void setPosY(int);
    void  setPosXplus() ;
    void  setPosXless() ;
    void  setPosYplus() ;
    void  setPosYless() ;
    void  setLife();
    void  setLifePlus ();
    void saveSetLife(int life);
    void  setAlive();



    ///Methods
    void moveSnoopy(int _key);

};




#endif // SNOOPY_H_INCLUDED
