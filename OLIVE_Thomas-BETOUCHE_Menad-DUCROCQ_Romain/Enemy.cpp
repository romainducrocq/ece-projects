#include "Enemy.h"
#include "console.h"
#include <windows.h>
#include <ctime>

Enemy::Enemy()
    : m_posX(0),m_posY(5), m_direction(1),m_nc(20), m_nl(10), m_obstacle(4)
{
}

Enemy::Enemy(int posX, int posY, int direction, int nc, int nl)
: m_posX(posX), m_posY(posY), m_direction(direction), m_nc(nc), m_nl(nl), m_obstacle(4)
{
}


Enemy::~Enemy()
{
}

///getters
int Enemy::getposX() const
{
    return m_posX;
}

int Enemy::getposY() const
{
    return m_posY;
}

int Enemy::getdirection() const
{
    return m_direction;
}


///setters
void Enemy::setdiaghg() ///deplacement diagonal haut gauche
{
    m_posX=m_posX-1;
    m_posY=m_posY-1;

}
void Enemy::setdiaghd() ///haut droite
{
    m_posX=m_posX+1;
    m_posY=m_posY-1;
}
void Enemy::setdiagbg() ///bas gauche
{
    m_posX=m_posX-1;
    m_posY=m_posY+1;
}
void Enemy::setdiagbd() ///bas droite
{
    m_posX=m_posX+1;
    m_posY=m_posY+1;
}

void Enemy::moveball(int obstacle)
{
    m_obstacle=obstacle;

    if(m_obstacle!=4)

    {
        if(m_obstacle==0)
    {
            do{
        m_direction=rand()%4;}while(m_direction==0);
    }
    if(m_obstacle==1)
        {
         do{
        m_direction=rand()%4;}while(m_direction==1);
        }
    if(m_obstacle==2)
    {
       do{
        m_direction=rand()%4;}while(m_direction==2);
    }
    if(m_obstacle==3)
    {
      do{
        m_direction=rand()%4;}while(m_direction==4);
    }

    m_obstacle=4;
    }

    else
    {

    if(m_direction==0&&m_posX>1&&m_posY>1)
    {
        setdiaghg();
    }
     if(m_direction==1&&m_posX<m_nc&&m_posY>1)
    {
        setdiaghd();
    }
     if(m_direction==2&&m_posX>1&&m_posY<m_nl)
    {
        setdiagbg();
    }
     if(m_direction==3&&m_posX<m_nc&&m_posY<m_nl)
    {
        setdiagbd();
    }
    }



  if(m_posX==1) ///rebond bord
    {
        do{
        m_direction=rand()%4;
        }while((m_direction!=1)&&(m_direction!=3));
    }
    if(m_posY==1)
        {
        m_direction=(rand()%2)+2;
    }
    if(m_posX==m_nc)

    {
        do{
        m_direction=rand()%4;
        }while((m_direction!=0)&&(m_direction!=2));
    }

    if(m_posY==m_nl)
      m_direction=rand()%2;

}
