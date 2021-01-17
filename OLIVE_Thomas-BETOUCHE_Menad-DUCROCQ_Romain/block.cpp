#include "block.h"

///CLASS MOTHER BLOCK

///CONSTRUCTORS AND DESTRUCTORS
Block::Block()
    : m_posX(0), m_posY(0), m_type('0'), m_isPushed(false)
{


}

Block::Block(int _posX,int _posY, char _type)
    : m_posX(_posX), m_posY(_posY), m_type(_type),m_isPushed(false)
{

}


Block::~Block()
{

}


///GETTERS
int Block::getPosx() const
{
    return m_posX;
}

int Block::getPosY() const
{
    return m_posY;
}

char Block::getType() const
{
    return m_type;
}

bool Block::getPushed() const
{
    return m_isPushed;
}



///SETTERS

void Block::setPosX(int _posX)
{
    m_posX = _posX;
}

void Block::setPosY(int _posY)
{
    m_posY = _posY;
}

void Block::setType(char _type)
{
    m_type = _type;
}

void Block::setPushed()
{
    m_isPushed = true;
}

void Block::setPosXplus()
{
    m_posX+=1;
}

void Block::setPosXless()
{
    m_posX-=1;
}

void Block::setPosYplus()
{
    m_posY+=1;
}

void Block::setPosYless()
{
    m_posY-=1;
}


///Class BREAKABLE

Breakable::Breakable()
    : Block(), m_isDestroyed(false)
{

}

Breakable::Breakable(int _posX, int _posY, char _type)
    : Block(_posX,_posY,_type), m_isDestroyed(false)
{

}

Breakable::~Breakable()
{

}

bool Breakable::getDestroyed() const
{
    return m_isDestroyed;
}



void Breakable::setDestroyed()
{
    if (m_isDestroyed == false)
        m_isDestroyed = true;
    else m_isDestroyed = false;
}




///Class PUSHABLE

Pushable::Pushable()
    : Block(), m_isPushed(false)
{

}

Pushable::Pushable(int _posX, int _posY, char _type)
    : Block(_posX,_posY,_type), m_isPushed(false)
{

}


Pushable::~Pushable()
{

}


bool Pushable::getPushed() const
{
    return m_isPushed;
}


///Class TRAPED

Traped::Traped() :
    Block(),m_isBlownUp(false)
{

}

Traped::Traped(int _posX, int _posY, char _type)
    :Block(_posX,_posY,_type), m_isBlownUp(false)
{

}

Traped::~Traped()
{

}

bool Traped::getBlownUp() const
{
    return m_isBlownUp;
}

void Traped::setBlownup()
{
    if (m_isBlownUp == false)
        m_isBlownUp = true;
    else m_isBlownUp = false;
}










