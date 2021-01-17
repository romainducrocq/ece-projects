/************************************************************
Sokoban project - Maze file
Copyright Florent DIEDLER
Date : 27/02/2016

Please do not remove this header, if you use this file !
************************************************************/

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include "utils/coord.h"

#include <vector>
#include <string>

// Max size for the field
#define NB_MAX_WIDTH     30
#define NB_MAX_HEIGHT    30

class Graphic;

enum
{
    SPRITE_GROUND = 0, SPRITE_WALL = 1, SPRITE_BOX = 2,
    SPRITE_BOX_PLACED = 3, SPRITE_GOAL = 4, SPRITE_MARIO = 5, SPRITE_BOX_ON_DEADLOCK = 8,
    SPRITE_DEADLOCK = 9
};

class Maze
{
    private:
        unsigned char m_lig, m_col;
        unsigned short m_pos_player;
        char m_dir_player;
        std::string m_level_path;

        std::vector<unsigned char> m_field; // field
        std::vector<unsigned short> m_pos_boxes; // box positions
        std::vector<unsigned short> m_pos_goals; // goal positions

        friend std::ostream& operator << (std::ostream& O, const Maze& n);

        bool _load(const std::string& path);
        bool _isInit; ///

        bool _canPushBox(unsigned short posBox, char dir, unsigned short& newPosBox) const; ///was private (why)
        bool _isCompleted() const; ///was private (why)

    public:
        Maze(const std::string& path);
        ~Maze();

        bool init();
        void setisInit (bool init); ///
        bool getisInit (); ///
        bool reload(const std::string& path); ///
        bool updatePlayer(char dir);
        void draw(const Graphic& g) const;
        bool isWinningNode() const;

        // Specific getters for field
        bool isSquareWalkable(unsigned short pos) const;
        bool isSquareGround(unsigned short pos) const;
        bool isSquareBox(unsigned short pos) const;
        bool isSquareGoal(unsigned short pos) const;
        bool isSquareWall(unsigned short pos) const;
        bool isSquareBoxPlaced(unsigned short pos) const;
        bool isSquareBoxOnDeadlock (unsigned short pos) const; ///
        bool isSquareDeadlock (unsigned short pos) const; ///
        bool isSquareNormalBox (unsigned short pos) const;

        // Other getters
        const std::string& getLevelPath() const;
        unsigned short getPosPlayer() const;
        unsigned int getSize() const;
        void setSquare(unsigned short pos, unsigned char s);
        const std::vector<unsigned char>& getField() const;
        const std::vector<unsigned short>& getGoals() const;
        std::vector<unsigned short> getPosBoxes() const;

        // Setters
        void setDirPlayerPos(char pos); ///
        void setPlayerPos(unsigned short pos);
        void setField(unsigned int i, unsigned char p); ///
        void setPos_Goals(unsigned int i, unsigned short p); ///
        void setPos_Boxes(unsigned int i, unsigned short p); ///

};

// Inline implementation of getters and setters (DO NOT TOUCH !)
inline bool Maze::isWinningNode() const
{
    return this->_isCompleted();
}


inline void Maze::setDirPlayerPos(char pos)
{
    if(pos == TOP || pos == BOTTOM || pos == RIGHT || pos == LEFT)
    {
        m_dir_player=pos;
    }
}

inline void Maze::setPlayerPos(unsigned short pos) {
    if (pos < this->getSize()) // NB: p always > 0 because unsigned short
        this->m_pos_player = pos;
}

inline void Maze::setField(unsigned int i, unsigned char p)
{
    if(i<m_field.size())
    {
        m_field[i]=p;
    }
}

inline void Maze::setPos_Goals(unsigned int i, unsigned short p)
{
    if(i<m_pos_goals.size())
    {
        m_pos_goals[i]=p;
    }
}

inline void Maze::setPos_Boxes(unsigned int i, unsigned short p)
{
    if(i<m_pos_boxes.size())
    {
        m_pos_boxes[i]=p;
    }
}

inline const std::string& Maze::getLevelPath() const { return this->m_level_path; }
inline const std::vector<unsigned short>& Maze::getGoals() const { return this->m_pos_goals; }
inline const std::vector<unsigned char>& Maze::getField() const { return this->m_field; }

inline unsigned int Maze::getSize() const { return this->m_field.size(); }
inline std::vector<unsigned short> Maze::getPosBoxes() const { return m_pos_boxes; }
inline unsigned short Maze::getPosPlayer() const { return m_pos_player;}

inline void Maze::setSquare(unsigned short pos, unsigned char s)
{
    if (pos < (this->m_lig*this->m_col))
    {
        this->m_field[pos] = s;
    }
}

inline bool Maze::isSquareWalkable(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_GROUND || this->m_field[pos] == SPRITE_GOAL || this->m_field[pos] == SPRITE_DEADLOCK || this->m_field[pos] == SPRITE_BOX_ON_DEADLOCK) ? true : false);
}

inline bool Maze::isSquareGround(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_GROUND) ? true : false);
}

inline bool Maze::isSquareBox(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_BOX || this->m_field[pos] == SPRITE_BOX_PLACED) ? true : false);
}

inline bool Maze::isSquareNormalBox(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_BOX) ? true : false);
}

inline bool Maze::isSquareGoal(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_GOAL ? true : false);
}

inline bool Maze::isSquareWall(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_WALL ? true : false);
}

inline bool Maze::isSquareBoxPlaced(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_BOX_PLACED ? true : false);
}

inline bool Maze::isSquareBoxOnDeadlock(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_BOX_ON_DEADLOCK ? true : false);
}

inline bool Maze::isSquareDeadlock(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_DEADLOCK ? true : false);
}

#endif // MAZE_H_INCLUDED






