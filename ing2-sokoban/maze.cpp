/************************************************************
Sokoban project - Maze file
Copyright Florent DIEDLER
Date : 27/02/2016

Please do not remove this header, if you use this file !
************************************************************/

#include "maze.h"
#include "graphic.h"
//#include "utils/console.h"
#include "utils/coord.h"
#include <fstream>
#include <iomanip>

Maze::Maze(const std::string& path)
    : m_lig(0), m_col(0), m_pos_player(0), m_dir_player(TOP), m_level_path(path), _isInit (false)
{
}

Maze::~Maze()
{
}

void Maze::setisInit (bool init)
{
   _isInit=init;
}

bool Maze::getisInit ()
{
    return _isInit;
}

bool Maze::init()
{
    bool res = this->_load(this->m_level_path);
    if (!res)
    {
        std::cerr << "Cannot load maze... Check file : " << this->m_level_path << std::endl;
        return false;
    }
    setisInit (true);
    return res;
}

// Check if all boxes are on a goal
bool Maze::_isCompleted() const
{
    for (unsigned int i=0; i<this->m_pos_boxes.size(); ++i)
    {
        if (!this->isSquareBoxPlaced(this->m_pos_boxes[i]))
            return false;
    }
    return true;
}

// Check if we can push a box in a direction
// INPUT: position of the box to check, direction,
// OUTPUT : the position of the box after pushing
//      TRUE if all goes right otherwise FALSE
bool Maze::_canPushBox(unsigned short posBox, char dir, unsigned short& newPosBox) const
{
    // Check if this position is a box !
    if (!this->isSquareBox(posBox))
        return false;

    // Compute new position according to push direction
    newPosBox = Coord::getDirPos(posBox, dir);

    // Can we push the box ?
    if(this->isSquareWalkable(newPosBox)==true&&this->isSquareDeadlock(newPosBox)==false&&this->isSquareBoxOnDeadlock(newPosBox)==false)
        return true;
    else
        return false;
}

// Load a maze from a file (DO NOT TOUCH)
bool Maze::_load(const std::string& path)
{
    std::vector<unsigned short> tmpPosBoxes;
    std::ifstream ifs(path.c_str());
    if (ifs)
    {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(ifs, line))
        {
            lines.push_back(line);
            this->m_lig++;
            this->m_col = (this->m_col < line.size() ? line.size() : this->m_col);
        }
        ifs.close();

        if (this->m_col > NB_MAX_WIDTH || this->m_lig > NB_MAX_HEIGHT)
        {
            std::cerr << "Maze::load => Bad formatting in level data..." << std::endl;
            return false;
        }

        Coord::m_nb_col = this->m_col;
        for (unsigned int i=0; i<lines.size(); i++)
        {
            //LDebug << "Maze::load => Reading : " << lines[i];
            for (unsigned int j=0; j<this->m_col; j++)
            {
                if (j < lines[i].size())
                {
                    bool both = false;
                    unsigned short pos = Coord::coord1D(i, j);
                    unsigned char s = (unsigned char)(lines[i][j] - '0');

                    // Need to add a goal and a box ;)
                    if (s == SPRITE_BOX_PLACED)
                    {
                       both = true;
                    }

                    if (s == SPRITE_GOAL || both)
                    {
                        this->m_pos_goals.push_back(pos);
                    }
                    if (s == SPRITE_BOX || both)
                    {
                        tmpPosBoxes.push_back(pos);
                    }

                    // Assign player position
                    if (s == SPRITE_MARIO)
                    {
                        this->m_pos_player = pos;
                        //LDebug << "\tAdding player pos (" << pos << ")";
                        s = SPRITE_GROUND;
                    }

                    // Add this value in the field
                    this->m_field.push_back(s);
                }
                else
                {
                    // Here - Out of bound
                    this->m_field.push_back(SPRITE_GROUND);
                }
            }
        }

        // Copy box position
        this->m_pos_boxes.resize(tmpPosBoxes.size());
        for (unsigned int i=0; i<tmpPosBoxes.size(); ++i)
        {
            this->m_pos_boxes[i] = tmpPosBoxes[i];
        }

        return (this->m_pos_boxes.size() == this->m_pos_goals.size());
    }
    else
    {
        std::cerr << "Maze::load => File does not exist..." << std::endl;
    }

    return false;
}

/// Reload the maze after a game loop
bool Maze::reload(const std::string& path)
{
    if(_isInit)
    {
        /// Temporary variables
        std::vector<unsigned char> _field; // field
        std::vector<unsigned short> _pos_boxes; // box positions
        std::vector<unsigned short> _pos_goals; // goal positions

        /// Clear all data
        m_field.clear();
        m_pos_boxes.clear();
        m_pos_goals.clear();

        /// Swap new data
        m_field.swap(_field);
        m_pos_boxes.swap(_pos_boxes);
        m_pos_goals.swap(_pos_goals);

        /// Clear data
        m_field.clear();
        m_pos_boxes.clear();
        m_pos_goals.clear();

        /// Reinitialization
        m_lig=0;
        m_col=0;
        m_pos_player=TOP;
        m_dir_player=TOP;

    }

    /// Load the new path
    m_level_path=path;
    return(init());
}

bool Maze::updatePlayer(char dir)
{

    unsigned short newPosBox;
    if (dir < 0 || dir > MAX_DIR)
    {
        if (dir==NONE) return false;
        std::cerr << "Maze::updatePlayer => Direction not correct... " << +dir << std::endl;
        return false;
    }

    // Implement player moving and pushing here
    else if ((dir==TOP&&isSquareWalkable(m_pos_player-Coord::m_nb_col)==true)||(dir==BOTTOM&&isSquareWalkable(m_pos_player+Coord::m_nb_col)==true)||(dir==LEFT&&isSquareWalkable(m_pos_player-1)==true)
             ||(dir==RIGHT&&isSquareWalkable(m_pos_player+1)==true)||(dir==TOP&&_canPushBox(m_pos_player-Coord::m_nb_col,dir,newPosBox)==true)||(dir==BOTTOM&&_canPushBox(m_pos_player+Coord::m_nb_col,dir,newPosBox)==true)
             ||(dir==LEFT&&_canPushBox(m_pos_player-1,dir,newPosBox)==true)||(dir==RIGHT&&_canPushBox(m_pos_player+1,dir,newPosBox)==true)
             )
        {
            if ((dir==TOP&&isSquareBox(m_pos_player-Coord::m_nb_col)==true)||(dir==BOTTOM&&isSquareBox(m_pos_player+Coord::m_nb_col)==true)||(dir==LEFT&&isSquareBox(m_pos_player-1)==true)||(dir==RIGHT&&isSquareBox(m_pos_player+1)==true))
            {
            unsigned int i=0;
            bool box = false;
                do
                   {
                    if ((dir==TOP&&m_pos_boxes[i]==m_pos_player-Coord::m_nb_col)||(dir==BOTTOM&&m_pos_boxes[i]==m_pos_player+Coord::m_nb_col)||(dir==LEFT&&m_pos_boxes[i]==m_pos_player-1)||(dir==RIGHT&&m_pos_boxes[i]==m_pos_player+1))
                       {
                           unsigned short old_field = m_pos_boxes[i];
                            m_pos_boxes[i]=Coord::getDirPos(m_pos_boxes[i], dir);
                            if (m_field[m_pos_boxes[i]]==SPRITE_GOAL)
                            {
                                m_field[m_pos_boxes[i]]=SPRITE_BOX_PLACED;
                            if (m_field[old_field]==SPRITE_BOX)
                                m_field[old_field]=SPRITE_GROUND;
                            else if (m_field[old_field]==SPRITE_BOX_PLACED)
                                m_field[old_field]=SPRITE_GOAL;
                            }
                            else if (m_field[m_pos_boxes[i]]==SPRITE_GROUND)
                                 {
                                    m_field[m_pos_boxes[i]]=SPRITE_BOX;
                                     if (m_field[old_field]==SPRITE_BOX_PLACED)
                                        m_field[old_field]=SPRITE_GOAL;
                                    else if (m_field[old_field]==SPRITE_BOX)
                                        m_field[old_field]=SPRITE_GROUND;

                                 }
                            box = true;
                       }
                    i++;

                   }
                while(i<m_pos_boxes.size()&&box==false);
            }
            m_pos_player=Coord::getDirPos(m_pos_player, dir);
        }
        m_dir_player=dir;
        ///
       /* int k=0;
        for(unsigned int i=0; i<m_field.size();i++)
        {
        ///
                std::cout<<+m_field[i];
                k++;
                if(k==Coord::m_nb_col)
                        {
                             k=0;
                        std::cout<< " "<< std::endl;
                        }
                }
                ///*/


    return(_isCompleted());
}

// Display maze on screen with Allegro
void Maze::draw(const Graphic& g) const
{
    for(unsigned int i=0; i<this->getSize(); i++)
    {
        unsigned int l = 0, c = 0;
        Coord::coord2D(i, l, c);

        if (i == this->m_pos_player)
        {
            g.drawT(g.getSprite(this->m_field[i]), c, l);
            g.drawT(g.getSpritePlayer(this->m_dir_player), c, l);
        }
        else
        {
            g.drawT(g.getSprite(this->m_field[i]), c, l);
        }
    }
}

// DO NOT TOUCH !
// Overload function for displaying debug information
// about Maze class
/*std::ostream& operator << (std::ostream& O, const Maze& m)
{
    unsigned int l, c;
    int i = 0;

    Coord::coord2D(m.m_pos_player, l, c);

    O << "Player position " << m.m_pos_player << " (" << l << "," << c << ")" << std::endl;
    O << "Field Size " << +m.m_lig << " x " << +m.m_col << " = " << m.getSize() << std::endl;
    O << "Field Vector capacity : " << m.m_field.capacity() << std::endl;
    O << "Field array : " << std::endl << std::endl;
    for(unsigned int l=0; l<m.getSize(); l++)
    {
        if (l == m.m_pos_player) Console::getInstance()->setColor(_COLOR_YELLOW);
        else if (m.isSquareWall(l)) Console::getInstance()->setColor(_COLOR_PURPLE);
        else if (m.isSquareBoxPlaced(l) || m.isSquareGoal(l)) Console::getInstance()->setColor(_COLOR_GREEN);
        else if (m.isSquareBox(l)) Console::getInstance()->setColor(_COLOR_BLUE);
        else if (m.m_field[l] == SPRITE_DEADLOCK) Console::getInstance()->setColor(_COLOR_RED);
        else Console::getInstance()->setColor(_COLOR_WHITE);

        O << std::setw(2) << +m.m_field[l] << " "; // + => print as "int"

        if ((l+1) % m.m_col == 0)
        {
            O << std::endl;
        }
    }
    Console::getInstance()->setColor(_COLOR_DEFAULT);

    O << std::endl;
    O << "Box position : " << std::endl;
    for (unsigned int i=0; i<m.m_pos_boxes.size(); i++)
    {
        Coord::coord2D(m.m_pos_boxes[i], l, c);
        O << "\t" << "Box #" << i << " => " << std::setw(3) << m.m_pos_boxes[i] << std::setw(2) << " (" << l << "," << c << ")" << std::endl;
    }

    O << std::endl;
    O << "Goal position : " << std::endl;
    for (const auto& goal : m.m_pos_goals)
    {
        unsigned int l, c;
        Coord::coord2D(goal, l, c);
        if (m.isSquareBoxPlaced(goal)) Console::getInstance()->setColor(_COLOR_GREEN);
        O << "\t" << "Goal #" << i << " => " << std::setw(3) << goal << std::setw(2) << " (" << l << "," << c << ")" << std::endl;
        if (m.isSquareBoxPlaced(goal)) Console::getInstance()->setColor(_COLOR_DEFAULT);
        i++;
    }

    return O;
}*/
