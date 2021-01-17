#include "Snoopy.h"
#include "console.h"

Snoopy::Snoopy()
    : m_pseudo(""), m_posX(8), m_posY(5),  m_life(3), m_score(0), m_alive(true)
{

}

Snoopy::Snoopy(std::string _pseudo)
    :  m_pseudo(_pseudo),m_posX(10), m_posY(5), m_life(3),m_score(0), m_alive(true)
{

}

Snoopy::~Snoopy()
{

}

/// GETTERS

int Snoopy::getPosX() const
{
    return m_posX;
}

int Snoopy::getPosY() const
{
    return m_posY;
}

int Snoopy::getLife() const
{
    return m_life;
}

int Snoopy::getScore() const
{
    return m_score;
}

bool Snoopy::getAlive() const
{
    return m_alive;
}


///SETTERS

void Snoopy::setPosX(int _posX)
{
    m_posX = _posX;
}

void Snoopy::setPosY(int _posY)
{
    m_posY = _posY;
}

void Snoopy::setPosXplus()
{
    m_posX+=1;
}

void Snoopy::setPosXless()
{
    m_posX-=1;
}

void Snoopy::setPosYplus()
{
    m_posY+=1;
}

void Snoopy::setPosYless()
{
    m_posY-=1;
}

void Snoopy::setLife()
{
    m_life-=1;
    if (m_life == 0)
        m_alive = false;
}

void Snoopy::setLifePlus ()
{
    if (m_life!=3)
        m_life+=1;
}

void Snoopy::saveSetLife(int life)
{
    m_life=life;
}

void Snoopy::setAlive()
{
    m_alive = false;
}

///METHODS

void Snoopy::moveSnoopy(int _key)
{
    switch(_key)
    {
    case 56 :
        setPosYless();
        if (m_posY < 1) m_posY = 1;
        break;
    case 122:
        setPosYless();
        if (m_posY < 1) m_posY = 1;
        break;

    case 54 :
        setPosXplus();
        if (m_posX > 19) m_posX = 19;
        break;
    case 100 :
        setPosXplus();
        if (m_posX> 19) m_posX = 19;
        break;

    case 52 :
        setPosXless();
        if (m_posX< 1) m_posX = 1;
        break;
    case 113:
        setPosXless();
        if (m_posX< 1) m_posX = 1;
        break;

    case 50 :
        setPosYplus();
        if (m_posY > 9) m_posY = 9;
        break;
    case 115 :
        setPosYplus();
        if (m_posY > 9) m_posY = 9;
    default :
        break;
    }

}



