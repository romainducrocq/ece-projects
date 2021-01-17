#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <string>
#include <iostream>
#include "Snoopy.h"

class Block
{
    ///ATTRIBUTS
private :

protected :
    int m_posX;
    int m_posY;
    char m_type;
    bool m_isPushed;

public:
    ///CONSTRUCTORS AND DESTRUCTORS
    Block();
    Block(int _posX,int _posY, char type);
    ~Block();

    ///GETTERS AND SETTERS
    int getPosx() const;
    int getPosY() const;
    char getType() const;
    bool getPushed() const;

    void setPosX(int _posX);
    void setPosY(int _posY);
    void setType(char _type);
    void setPushed();


    void setPosXplus();
    void setPosXless();
    void setPosYplus();
    void setPosYless();


    ///METHODS
    void blow_up();
};


class Breakable : public Block
{
private :
    bool m_isDestroyed;

public:
    Breakable();
    Breakable(int _posX, int _posY, char _type);
    ~Breakable();

    bool getDestroyed() const;
    void setDestroyed();


};


class Pushable : public Block
{
private :
    bool m_isPushed;

public :
    Pushable();
    Pushable(int _posX, int _posY, char _type);
    ~Pushable();

    bool getPushed() const;
    void setPushed();
    void setPosXplus();
    void setPosXless();
    void setPosYplus();
    void setPosYless();


};


class Traped : public Block
{
private :
    bool m_isBlownUp;

public :
    Traped();
    Traped(int posX, int posY,char type);
    ~Traped();

    bool getBlownUp() const;
    void setBlownup();

};






#endif // BLOCK_H_INCLUDED
