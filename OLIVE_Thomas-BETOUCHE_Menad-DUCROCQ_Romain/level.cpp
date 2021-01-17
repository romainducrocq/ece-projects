#include "level.h"
#include "Snoopy.h"
#include "console.h"
#include "windows.h"
#include "Enemy.h"
#include "Timer_Score.h"

Level::Level()
    : m_nbLevelMax(3),m_nbBirds(4),m_nbActualLevel(1), m_nbL(10), m_nbC(20), m_chrono(60), m_pause(false),  m_name(""),  m_tab(10, std::vector<Block>(20))
{


}

///LOAD LEVEL
Level::Level(int _actualLevel,int nbL,int nbC,std::string _pseudo,int nbLevel)
    : m_nbLevelMax(3),m_nbBirds(4),m_nbActualLevel(_actualLevel), m_nbL(nbL), m_nbC(nbC), m_chrono(60), m_pause(false),  m_name(_pseudo),  m_tab(nbL, std::vector<Block> (nbC) )
{
    int number (0);

    /// Declaration of the input / output of the files
    std::ifstream file1("level 1.txt");
    std::ifstream file2("level 2.txt");
    std::ifstream file3("level 3.txt");
    std::ifstream save("save.txt");

    switch (nbLevel)
    {

    /// LEVEL 1 ///
    case 1 :

        /// we create the matrix thanks to the reading of the related file
        if (file1)
        {
            file1 >> m_nbC;
            file1 >> m_nbL;

            for (int i = 0; i<nbL; i++)
            {
                for (int j=0; j<nbC; j++)
                {
                    /// reading of the various number of the text file
                    file1 >> number;

                    /// switch of the different numbers
                    switch (number)
                    {
                    case 0 :
                        /// space
                        m_tab[i][j] = Block(j,i,' ');
                        break;

                    case 1 :
                        /// block pushable
                        m_tab[i][j] = Pushable(j,i,'P');
                        break;

                    case 2 :
                        /// block breakable
                        m_tab[i][j] = Breakable(j,i,'C');
                        break;

                    case 3 :
                        /// block trapped
                        m_tab[i][j] = Block(j,i,'T');
                        break;

                    case 4 :
                        /// block fixed
                        m_tab[i][j] = Block(j,i,'*');
                        break;

                    case 5 :
                        /// birds
                        m_tab[i][j] = Block (j,i,'O');
                        break;

                    case 6 :
                        /// life block
                        m_tab[i][j] = Block (j,i,'V');
                        break;

                        /// time block
                         case 7 :
                           m_tab[i][j] = Block (j,i,'H');
                           break;

                    default :
                        /// not default block here !
                        break;
                    }

                }
            }

            /// Closing file
            file1.close();
        }

        else std::cout << "Error, impossible to find the file" << std::endl;
        break;

    /// LEVEL 2 ///
    // we are going to use the same procedure in levels 2 and 3 //
    case 2 :
        if (file2)
        {
            file2 >> m_nbC;
            file2 >> m_nbL;
            for (int i = 0; i<nbL; i++)
            {
                for (int j=0; j<nbC; j++)
                {
                    file2 >> number;
                    switch (number)
                    {
                    case 0 :
                        m_tab[i][j] = Block(j,i,' ');
                        break;

                    case 1 :
                        m_tab[i][j] = Pushable(j,i,'P');
                        break;

                    case 2 :
                        m_tab[i][j] = Breakable(j,i,'C');
                        break;

                    case 3 :
                        m_tab[i][j] = Block(j,i,'T');
                        break;

                    case 4 :
                        m_tab[i][j] = Block(j,i,'*');
                        break;
                    case 5 :
                        m_tab[i][j] = Block (j,i,'O');
                        break;

                    case 6 :
                        m_tab[i][j] = Block (j,i,'V');
                        break;

                         case 7 :
                           m_tab[i][j] = Block (j,i,'H');
                           break;

                    default :
                        break;
                    }

                }
            }

            file2.close();
        }

        else std::cout << "Error, impossible to find the file" << std::endl;
        break;

    /// LEVEL 3 ///
    case 3 :
        if (file3)
        {
            file3 >> m_nbC;
            file3 >> m_nbL;
            for (int i = 0; i<nbL; i++)
            {
                for (int j=0; j<nbC; j++)
                {
                    file3 >> number;
                    switch (number)
                    {
                    case 0 :
                        m_tab[i][j] = Block(j,i,' ');
                        break;

                    case 1 :
                        m_tab[i][j] = Pushable(j,i,'P');
                        break;

                    case 2 :
                        m_tab[i][j] = Breakable(j,i,'C');
                        break;

                    case 3 :
                        m_tab[i][j] = Block(j,i,'T');
                        break;

                    case 4 :
                        m_tab[i][j] = Block(j,i,'*');
                        break;
                    case 5 :
                        m_tab[i][j] = Block (j,i,'O');
                        break;

                    case 6 :
                        m_tab[i][j] = Block (j,i,'V');
                        break;

                         case 7 :
                           m_tab[i][j] = Block (j,i,'H');
                           break;

                    default :
                        break;
                    }

                }
            }

            file3.close();
        }

        else std::cout << "Error, impossible to find the file" << std::endl;
        break;

    /// Case of the SAVE
    case 4 :

        /// Verification of opening
        if (save)
        {
            /// Declaration of variables
            int tmp, life, snoopyX, snoopyY;

            /// Reading of the number of lines and columns
            save >> m_nbC;
            save >> m_nbL;

            /// Then, the same procedure to save your level (case 2 of the menu)
            for (int i = 0; i<nbL; i++)
            {
                for (int j=0; j<nbC; j++)
                {
                    save >> number;

                    switch (number)
                    {
                    case 0 :
                        m_tab[i][j] = Block(j,i,' ');
                        break;

                    case 1 :
                        m_tab[i][j] = Pushable(j,i,'P');
                        break;

                    case 2 :
                        m_tab[i][j] = Breakable(j,i,'C');
                        break;

                    case 3 :
                        m_tab[i][j] = Block(j,i,'T');
                        break;

                    case 4 :
                        m_tab[i][j] = Block(j,i,'*');
                        break;

                    case 5 :
                        m_tab[i][j] = Block (j,i,'O');
                        break;

                    case 6 :
                        m_tab[i][j] = Block (j,i,'V');
                        break;

                         case 7 :
                           m_tab[i][j] = Block (j,i,'H');
                           break;

                    default :
                        break;
                    }

                }
            }

            /// Now, we save all the remaining parameters
            save >> tmp;
            save >> m_nbLevelMax;
            save >> life;
            save >> m_nbBirds;
            save >> m_chrono;
            save >> snoopyX;
            save >> snoopyY;

            m_player.saveSetLife(life);
            m_player.setPosX(snoopyX);
            m_player.setPosY(snoopyY);

            /// Finally, closing the file
            save.close();
        }

        else std::cout << "Error, impossible to find the file" << std::endl;
        break;
    }
}

Level::~Level()
{
    /// Nothing to do here !
}

void Level::setSave()
{
    /// Declaration of variables
    int number;

    /// Declaration of the input / output of the files
    std::ofstream save("save.txt", std::ios::trunc);

    /// Verification of the opening
    if(save)
    {
        /// Writing of the number of lines and columns
        save << m_nbC << " ";
        save << m_nbL << " ";

        /// Scanning the matrix
        for (int i = 0; i<m_nbL; i++)
        {
            for (int j=0; j<m_nbC; j++)
            {
                /// Association with a number of a type to a number : it's the inverse operation of the reading of the text file

                if (m_tab[i][j].getType() == ' ')       /// space
                    number=0;

                else if (m_tab[i][j].getType() == 'P')  /// pushable block
                    number=1;

                else if (m_tab[i][j].getType() == 'C')  /// breakable block
                    number=2;

                else if (m_tab[i][j].getType() == 'T')  /// trapped block
                    number=3;

                else if (m_tab[i][j].getType() == '*')  /// fixed
                    number=4;

                else if (m_tab[i][j].getType() == 'O')  /// birds
                    number=5;

                else if (m_tab[i][j].getType() == 'V')  /// life block
                    number=6;

                else if (m_tab[i][j].getType() == 'H')  /// time block
                    number=7;
                else                                    /// case default : space
                    number=0;
                save << number << " ";
            }
        }

        /// Writing all the remaining parameter
        save << m_nbActualLevel << " ";
        save << m_nbLevelMax << " ";
        save << m_player.getLife() << " ";
        save << m_nbBirds << " ";
        save << m_timer.getchrono() << " ";
        save << m_player.getPosX() << " ";
        save << m_player.getPosY() << " ";

        /// Closing file
        save.close();
    }

}

bool Level::getPause() const
{
    return m_pause;
}

void Level::setPause()
{

    if (m_pause == false)
    {
        m_pause = true;
    }
    else
    {
        m_pause = false;
    }

}

void Level::score()
{
    int i;
    std::vector<int> score(m_nbLevelMax*2);
    std::vector<std::string> sName(m_nbLevelMax);

    /// Declaration of the input / output of the file
    std::ifstream scoreRead("score.txt");

    /// Verification of opening
    if(scoreRead)
    {
        for(i=0; i<(m_nbLevelMax*2); i++)
        {
            /// Read of the scores
            scoreRead >> score[i];
        }
        for(i=0; i<m_nbLevelMax; i++)
        {
            /// Read of the pseudos
            scoreRead >> sName[i];
        }

        /// Closing the file
        scoreRead.close();
    }

    for(i=0; i<m_nbLevelMax; i++)
    {
        /// Obtain the scores
        if(m_nbActualLevel==i+1)
            score[i]=m_timer.getchrono()*100;

        /// Do a selecting of the best scores
        if(score[i]>score[i+m_nbLevelMax])
        {
            score[i+m_nbLevelMax]=score[i];
            sName[i]=m_name;
        }
    }

    /// Ecriture du fichier score
    std::ofstream scoreWrite("score.txt", std::ios::trunc);

    /// Verification of opening
    if(scoreWrite)
    {
        for(i=0; i<(m_nbLevelMax*2); i++)
        {
            /// Writing these scores
            scoreWrite << score[i] << " ";
        }

        for(i=0; i<m_nbLevelMax; i++)
        {
            /// Writing these pseudos
            scoreWrite << sName[i] << " ";
        }

        /// Closing file
        scoreWrite.close();
    }
}


void Level::movePlayer(int _key,Console* pConsole)
{
    /// Place the cursor at the right place. We have some spaces for more brightness
    pConsole->gotoLigCol(m_player.getPosY()*2,m_player.getPosX()*3);
    std::cout <<' ' << ' ';

    /// Recovery of the key to move Snoopy
    m_player.moveSnoopy(_key);

    /// If Snoopy can move = if the adjacent box is a space
    if (m_tab[m_player.getPosY()][m_player.getPosX()].getType() == ' ')
    {
        /// You can move Snoopy and display its 'S' symbol
        pConsole->gotoLigCol(m_player.getPosY()*2,m_player.getPosX()*3);
        std::cout << 'S' << ' ';
    }
}


Enemy Level::getEnemyDepart() const
{
    /// Declaration of variables
    int x,y;

    /// Choose an aleatory initial position for the balls
    do
    {
        x=rand()%(m_nbC-2);
        y=rand()%(m_nbL-2);
    }
    while(m_tab[y][x].getType() != ' ');    /// while the box is a space

    Enemy ballDepart(x,y, rand()%4, (m_nbC-2), (m_nbL-2));
    return ballDepart;  /// returning this position
}

void Level::setEnemy()
{
    /// Creation of a variable number of balls, according to the related level
    m_ball1=getEnemyDepart();
    m_ball2=getEnemyDepart();
    if(m_nbActualLevel>1)
        m_ball3=getEnemyDepart();
    if(m_nbActualLevel>2)
        m_ball4=getEnemyDepart();
}

Enemy Level::moveEnemy(Enemy ball, Console* pConsole)
{
    /// Declaration of variables
    Block b;

    /// Place the cursor for the movement of the ball
    pConsole->gotoLigCol(ball.getposY()*2,ball.getposX()*3);
    std::cout <<' ' << ' ';

    /// Select a choice of direction according to the number of obstacles next to the ball
    if(ball.getdirection()==0)
    {
        if(m_tab[ball.getposY()-1][ball.getposX()-1].getType() == ' ')
        {
            b = m_tab[ball.getposY()-1][ball.getposX()-1];
            m_tab[ball.getposY()-1][ball.getposX()-1] = m_tab[ball.getposY()][ball.getposX()] ;
            m_tab[ball.getposY()][ball.getposX()] = b;
            m_obstacle=4;
        }
        else
            m_obstacle=0;
    }
    if(ball.getdirection()==1)
    {
        if(m_tab[ball.getposY()-1][ball.getposX()+1].getType() == ' ')
        {
            b =  m_tab[ball.getposY()-1][ball.getposX()+1];
            m_tab[ball.getposY()-1][ball.getposX()+1] = m_tab[ball.getposY()][ball.getposX()] ;
            m_tab[ball.getposY()][ball.getposX()] = b;
            m_obstacle=4;
        }
        else
            m_obstacle=1;
    }
    if(ball.getdirection()==2)
    {
        if(m_tab[ball.getposY()+1][ball.getposX()-1].getType() == ' ')
        {
            b =  m_tab[ball.getposY()+1][ball.getposX()-1];
            m_tab[ball.getposY()+1][ball.getposX()-1] = m_tab[ball.getposY()][ball.getposX()] ;
            m_tab[ball.getposY()][ball.getposX()] = b;
            m_obstacle=4;
        }
        else
            m_obstacle=2;
    }
    if(ball.getdirection()==3)
    {
        if(m_tab[ball.getposY()+1][ball.getposX()+1].getType() == ' ')
        {
            b =  m_tab[ball.getposY()+1][ball.getposX()+1];
            m_tab[ball.getposY()+1][ball.getposX()+1] = m_tab[ball.getposY()][ball.getposX()] ;
            m_tab[ball.getposY()][ball.getposX()] = b;
            m_obstacle=4;
        }
        else
            m_obstacle=3;
    }
    ball.moveball(m_obstacle);

    pConsole->gotoLigCol(ball.getposY()*2,ball.getposX()*3);
    std::cout << 'B' << ' ';

    /// Collision between a ball and the player
    if (ball.getposX()==m_player.getPosX() && ball.getposY()==m_player.getPosY())
    {
        /// Call of the function which decrement one life
        perdreUneVie(pConsole);
    }

    /// Return this object
    return ball;
}

void Level::afficheMoveEnemy(Console* pConsole)
{
    /// Balls are in blue
    pConsole->setColor(COLOR_BLUE);

    /// Manage the number of balls according to the related level
    m_ball1=moveEnemy(m_ball1, pConsole);
    m_ball2=moveEnemy(m_ball2, pConsole);
    if (m_nbActualLevel>1)
        m_ball3=moveEnemy(m_ball3, pConsole);
    if (m_nbActualLevel>2)
        m_ball4=moveEnemy(m_ball4, pConsole);

    /// Now, color is white
    pConsole->setColor(COLOR_DEFAULT);
}

void Level::setTimer()
{
    timer_score timer(m_chrono, time(NULL));
    m_timer=timer;
}

int Level::afficheChrono(Console* pConsole)
{
    m_timer.timer(pConsole);
    return m_timer.getchrono();
}


void Level::pushBlock(int key,Console* pConsole)
{
    /// Declaration of variables
    Block b;

    /// If the type of block is 'P' and not yet pushed
    if ( ((m_tab[m_player.getPosY()][m_player.getPosX()].getType() == 'P')) && (m_tab[m_player.getPosY()][m_player.getPosX()].getPushed() == false)  )
    {
        /// Push the block according to the direction of the movement of the player
        switch(key)
        {
        case 56 : /// case '8'
            if (m_tab[m_player.getPosY()-1][m_player.getPosX()].getType() == ' ')
            {
                /// Now the block is pushed
                m_tab[m_player.getPosY()][m_player.getPosX()].setPushed();

                /// Swap the position of the block P and the player, thanks to a third temporary variable
                b =  m_tab[m_player.getPosY() -1][m_player.getPosX()];
                m_tab[m_player.getPosY()-1][m_player.getPosX()] = m_tab[m_player.getPosY()][m_player.getPosX()] ;
                m_tab[m_player.getPosY()][m_player.getPosX()] = b;

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY() -1)*2,m_player.getPosX()*3);

                /// Display the P in green
                pConsole->setColor(COLOR_GREEN);
                std::cout << m_tab[m_player.getPosY()-1][m_player.getPosX()].getType();

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);

                /// Display the S in white
                pConsole->setColor(COLOR_DEFAULT);
                std::cout << 'S' << ' ';

            }

            else
            {
                /// We cannot move Snoopy
                m_player.setPosYplus();
                pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
                std::cout << 'S' << ' ';
            }

            break;
        case 122: /// case 'z'
            if (m_tab[m_player.getPosY()-1][m_player.getPosX()].getType() == ' ')
            {
                /// Now the block is pushed
                m_tab[m_player.getPosY()][m_player.getPosX()].setPushed();

                /// Swap the position of the block P and the player, thanks to a third temporary variable
                b =  m_tab[m_player.getPosY() -1][m_player.getPosX()];
                m_tab[m_player.getPosY()-1][m_player.getPosX()] = m_tab[m_player.getPosY()][m_player.getPosX()] ;
                m_tab[m_player.getPosY()][m_player.getPosX()] = b;

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY() -1)*2,m_player.getPosX()*3);

                /// Display the P in green
                pConsole->setColor(COLOR_GREEN);
                std::cout << m_tab[m_player.getPosY()-1][m_player.getPosX()].getType();

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);

                /// Display the S in white
                pConsole->setColor(COLOR_DEFAULT);
                std::cout << 'S' << ' ';
            }
            else
            {
                /// We cannot move Snoopy
                m_player.setPosYplus();
                pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
                std::cout << 'S' << ' ';
            }
            break;



        case 54 : /// case '6'
            if (m_tab[m_player.getPosY()][m_player.getPosX()+1].getType() == ' ')
            {
                /// Now the block is pushed
                m_tab[m_player.getPosY()][m_player.getPosX()].setPushed();

                /// Swap the position of the block P and the player, thanks to a third temporary variable
                b =  m_tab[m_player.getPosY()][m_player.getPosX()+1];
                m_tab[m_player.getPosY()][m_player.getPosX()+1] = m_tab[m_player.getPosY()][m_player.getPosX()] ;
                m_tab[m_player.getPosY()][m_player.getPosX()] = b;

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX()+1)*3);

                /// Display the P in green
                pConsole->setColor(COLOR_GREEN);
                std::cout << m_tab[m_player.getPosY()][m_player.getPosX()+1].getType();

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX())*3);

                /// Display the S in white
                pConsole->setColor(COLOR_DEFAULT);
                std::cout << 'S' << ' ';

            }
            else
            {
                /// We cannot move Snoopy
                m_player.setPosXless();
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX())*3);
                std::cout << 'S' << ' ';
            }
            break;
        case 100 : /// case 'd'
            if (m_tab[m_player.getPosY()][m_player.getPosX()+1].getType() == ' ')
            {
                /// Now the block is pushed
                m_tab[m_player.getPosY()][m_player.getPosX()].setPushed();

                /// Swap the position of the block P and the player, thanks to a third temporary variable
                b =  m_tab[m_player.getPosY()][m_player.getPosX()+1];
                m_tab[m_player.getPosY()][m_player.getPosX()+1] = m_tab[m_player.getPosY()][m_player.getPosX()] ;
                m_tab[m_player.getPosY()][m_player.getPosX()] = b;

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX()+1)*3);

                /// Display the P in green
                pConsole->setColor(COLOR_GREEN);
                std::cout << m_tab[m_player.getPosY()][m_player.getPosX()+1].getType();

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX())*3);

                /// Display the S in white
                pConsole->setColor(COLOR_DEFAULT);
                std::cout << 'S' << ' ';
            }
            else
            {
                /// We cannot move Snoopy
                m_player.setPosXless();
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX())*3);
                std::cout << 'S' << ' ';
            }
            break;


        case 52 : /// case '4'
            if (m_tab[m_player.getPosY()][m_player.getPosX()-1].getType() == ' ')
            {
                /// Now the block is pushed
                m_tab[m_player.getPosY()][m_player.getPosX()].setPushed();

                /// Swap the position of the block P and the player, thanks to a third temporary variable
                b =  m_tab[m_player.getPosY()][m_player.getPosX()-1];
                m_tab[m_player.getPosY()][m_player.getPosX()-1] = m_tab[m_player.getPosY()][m_player.getPosX()] ;
                m_tab[m_player.getPosY()][m_player.getPosX()] = b;

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX()-1)*3);

                /// Display the P in green
                pConsole->setColor(COLOR_GREEN);
                std::cout << m_tab[m_player.getPosY()][m_player.getPosX()-1].getType();

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX())*3);

                /// Display the S in white
                pConsole->setColor(COLOR_DEFAULT);
                std::cout << 'S' << ' ';
            }
            else
            {
                /// We cannot move Snoopy
                m_player.setPosXplus();
                pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
                std::cout << 'S' << ' ';
            }
            break;

        case 113: /// case 'q'
            if (m_tab[m_player.getPosY()][m_player.getPosX()-1].getType() == ' ')
            {
                /// Now the block is pushed
                m_tab[m_player.getPosY()][m_player.getPosX()].setPushed();

                /// Swap the position of the block P and the player, thanks to a third temporary variable
                b =  m_tab[m_player.getPosY()][m_player.getPosX()-1];
                m_tab[m_player.getPosY()][m_player.getPosX()-1] = m_tab[m_player.getPosY()][m_player.getPosX()] ;
                m_tab[m_player.getPosY()][m_player.getPosX()] = b;

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX()-1)*3);

                /// Display the P in green
                pConsole->setColor(COLOR_GREEN);
                std::cout << m_tab[m_player.getPosY()][m_player.getPosX()-1].getType();

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX())*3);

                /// Display the S in white
                pConsole->setColor(COLOR_DEFAULT);
                std::cout << 'S' << ' ';
            }
            else
            {
                /// We cannot move Snoopy
                m_player.setPosXplus();
                pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
                std::cout << 'S' << ' ';
            }
            break;


        case 50 : /// case '2'
            if (m_tab[m_player.getPosY()+1][m_player.getPosX()].getType() == ' ')
            {
                /// Now the block is pushed
                m_tab[m_player.getPosY()][m_player.getPosX()].setPushed();

                /// Swap the position of the block P and the player, thanks to a third temporary variable
                b =  m_tab[m_player.getPosY()+1][m_player.getPosX()];
                m_tab[m_player.getPosY()+1][m_player.getPosX()] = m_tab[m_player.getPosY()][m_player.getPosX()] ;
                m_tab[m_player.getPosY()][m_player.getPosX()] = b;

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY()+1)*2,(m_player.getPosX())*3);

                /// Display the P in green
                pConsole->setColor(COLOR_GREEN);
                std::cout << m_tab[m_player.getPosY()+1][m_player.getPosX()].getType();

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX())*3);

                /// Display the S in white
                pConsole->setColor(COLOR_DEFAULT);
                std::cout << 'S' << ' ';
            }
            else
            {
                /// We cannot move Snoopy
                m_player.setPosYless();
                pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
                std::cout << 'S' << ' ';
            }
            break;

        case 115 : /// case 's'
            if (m_tab[m_player.getPosY()+1][m_player.getPosX()].getType() == ' ')
            {
                /// Now the block is pushed
                m_tab[m_player.getPosY()][m_player.getPosX()].setPushed();

                /// Swap the position of the block P and the player, thanks to a third temporary variable
                b =  m_tab[m_player.getPosY()+1][m_player.getPosX()];
                m_tab[m_player.getPosY()+1][m_player.getPosX()] = m_tab[m_player.getPosY()][m_player.getPosX()] ;
                m_tab[m_player.getPosY()][m_player.getPosX()] = b;

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY()+1)*2,(m_player.getPosX())*3);

                /// Display the P in green
                pConsole->setColor(COLOR_GREEN);
                std::cout << m_tab[m_player.getPosY()+1][m_player.getPosX()].getType();

                /// Place the cursor at the right place
                pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX())*3);

                /// Display the S in white
                pConsole->setColor(COLOR_DEFAULT);
                std::cout << 'S' << ' ';
            }
            else
            {
                /// We cannot move Snoopy
                m_player.setPosYless();
                pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
                std::cout << 'S' << ' ';
            }
            break;

        default :
            /// Not case default here !
            break;

        }


    }

    /// If the block is yet pushed, Snoopy can't move. If the block is breakable or fixed, he can't move too.
    else if( ((m_tab[m_player.getPosY()][m_player.getPosX()].getType() == 'P') && (m_tab[m_player.getPosY()][m_player.getPosX()].getPushed() == true)) ||  ((m_tab[m_player.getPosY()][m_player.getPosX()].getType() == 'C')) ||  ((m_tab[m_player.getPosY()][m_player.getPosX()].getType() == '*')) )
    {
        switch(key)
        {
        case 56 : /// case '8'
            m_player.setPosYplus();
            pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
            std::cout << 'S' << ' ';
            break;
        case 122: /// case 'z'
            m_player.setPosYplus();
            pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
            std::cout << 'S' << ' ';
            break;

        case 54 : /// case '6'
            m_player.setPosXless();
            pConsole->gotoLigCol((m_player.getPosY())*2,(m_player.getPosX())*3);
            std::cout << 'S' << ' ';
            break;
        case 100 : /// case 'd'
            m_player.setPosXless();
            pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
            std::cout << 'S' << ' ';
            break;

        case 52 : /// case '4'
            m_player.setPosXplus();
            pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
            std::cout << 'S' << ' ';
            break;
        case 113 : /// case 'q'
            m_player.setPosXplus();
            pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
            std::cout << 'S' << ' ';
            break;

        case 50 : /// case '2'
            m_player.setPosYless();
            pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
            std::cout << 'S' << ' ';
            break;
        case 115 : /// case 'z'
            m_player.setPosYless();
            pConsole->gotoLigCol((m_player.getPosY())*2,m_player.getPosX()*3);
            std::cout << 'S' << ' ';
            break;

        default :
            break;
        }

    }

}

void Level::perdreUneVie(Console* pConsole)
{
    /// decrement a life and position the player at the center of the matrix
    m_player.setLife();
    m_player.setPosX(10);
    m_player.setPosY(5);

    /// replace the S at the right place
    pConsole->gotoLigCol(2*m_player.getPosY(),3*m_player.getPosX());
    pConsole->setColor(COLOR_DEFAULT);
    std::cout << 'S' << ' ';

    /// indicate at the player the number of lives left
    pConsole->setColor(COLOR_RED);
    pConsole->gotoLigCol(19,0);

    if(m_player.getLife()==2)
    {
        std::cout <<"    **   **     **   **                  "<<std::endl;
        std::cout <<"   **** ****   **** ****                 "<<std::endl;
        std::cout <<"   *********   *********                 "<<std::endl;
        std::cout <<"    *******     *******                  "<<std::endl;
        std::cout <<"      ***         ***                    "<<std::endl;
    }

    if(m_player.getLife()==1)
    {
        std::cout <<"    **   **                              "<<std::endl;
        std::cout <<"   **** ****                             "<<std::endl;
        std::cout <<"   *********                             "<<std::endl;
        std::cout <<"    *******                              "<<std::endl;
        std::cout <<"      ***                                "<<std::endl;
    }
    pConsole->setColor(COLOR_DEFAULT);

    /// If the player has consumed all his lives, he's dead
    if (m_player.getLife() == 0)
    {
        m_player.setAlive();
    }

}

void Level::trapedBlock(Console* pConsole)
{
    if ( (m_tab[m_player.getPosY()][m_player.getPosX()].getType() == 'T') )
    {
        /// replace the T by a space because the block blown up !
        m_tab[m_player.getPosY()][m_player.getPosX()] = Block (m_player.getPosY(),m_player.getPosX(),' ');
        pConsole->gotoLigCol(m_player.getPosY()*2  ,   m_player.getPosX()*3);
        std::cout <<  m_tab[m_player.getPosY()][m_player.getPosX()].getType() << ' ';

        /// And so, decrement one life
        perdreUneVie(pConsole);

    }

}

bool Level::birdBlock(Console* pConsole)
{
    /// Declaration of variables
    bool nbBirds;

    /// If the block is a O
    if ((m_tab[m_player.getPosY()][m_player.getPosX()].getType() == 'O'))
    {
        /// We do the same treatments as the trapped block ...
        m_tab[m_player.getPosY()][m_player.getPosX()] = Block(m_player.getPosY(),m_player.getPosX(), ' ');
        pConsole->gotoLigCol(m_player.getPosY()*2 , m_player.getPosX()*3);
        std::cout << 'S' << ' ';

        /// ... but we decrement the number of birds, and then you display at the player this number
        m_nbBirds-=1;
        pConsole->gotoLigCol(4,62);
        std::cout << "Birds left : " << m_nbBirds;
    }

    if (m_nbBirds==0)
        nbBirds=true;

    else
        nbBirds=false;

    return nbBirds;
}

void Level::lifeBlock(Console* pConsole)
{
    /// If the block is a V
    if ((m_tab[m_player.getPosY()][m_player.getPosX()].getType() == 'V'))
    {
        /// We do the same treatments as the bird block ...
        m_tab[m_player.getPosY()][m_player.getPosX()] = Block(m_player.getPosY(),m_player.getPosX(), ' ');
        pConsole->gotoLigCol(m_player.getPosY()*2 , m_player.getPosX()*3);
        std::cout << 'S' << ' ';

        /// ... but if you have less than 3 lives, you increase your live counter !
        if (m_player.getLife()!=3)
        {
            m_player.setLifePlus();
            pConsole->setColor(COLOR_RED);

            /// Then display to the player the number of lives left
            pConsole->gotoLigCol(19,0);
            if(m_player.getLife()==3)
            {
                std::cout <<"    **   **     **   **     **   **              "<<std::endl;
                std::cout <<"   **** ****   **** ****   **** ****             "<<std::endl;
                std::cout <<"   *********   *********   *********             "<<std::endl;
                std::cout <<"    *******     *******     *******              "<<std::endl;
                std::cout <<"      ***         ***         ***                "<<std::endl;
            }


            if(m_player.getLife()==2)
            {
                std::cout <<"    **   **     **   **                  "<<std::endl;
                std::cout <<"   **** ****   **** ****                 "<<std::endl;
                std::cout <<"   *********   *********                 "<<std::endl;
                std::cout <<"    *******     *******                  "<<std::endl;
                std::cout <<"      ***         ***                    "<<std::endl;
            }

            pConsole->setColor(COLOR_DEFAULT);

        }
    }
}



void Level::clockBlock(Console* pConsole) ///
{
    /// If the block is a H
    if ((m_tab[m_player.getPosY()][m_player.getPosX()].getType() == 'H'))
    {
        /// We do the same treatments as the bird block ...
        m_tab[m_player.getPosY()][m_player.getPosX()] = Block(m_player.getPosY(),m_player.getPosX(), ' ');
        pConsole->gotoLigCol(m_player.getPosY()*2 , m_player.getPosX()*3);
        std::cout << 'S' << ' ';

        /// ... but if you have less than 50 seconds left, you increase by 10 your time counter !
        if (m_timer.getchrono()<=50)
        {
            /// Then display to the player the amount of time left
            m_timer.setChronoPlus ();

        }
    }
}





void Level::displayMatrix(Console* pConsole)
{
    /// Declaration of variables
    Block b;
    char c;

    /// Scanning the matrix
    for (int i =0 ; i<10; i++)
    {
        for (int j=0; j<20; j++)
        {
            /// First, display the S of Snoopy
            if((i == m_player.getPosY()) && (j==m_player.getPosX()))
            {
                std::cout << 'S' << ' ' << ' ';
            }
            else
            {
                /// Else, display all the other blocks possibilities
                b = m_tab[i][j];
                c = b.getType();
                switch(c)
                {
                case 'P' :
                    pConsole->setColor(COLOR_GREEN);
                    std::cout << m_tab[i][j].getType() << "  ";
                    pConsole->setColor(COLOR_DEFAULT);
                    break;

                case 'C' :
                    pConsole->setColor(COLOR_PURPLE);
                    std::cout << m_tab[i][j].getType() << "  ";
                    pConsole->setColor(COLOR_DEFAULT);
                    break;

                case 'T' :
                    pConsole->setColor(COLOR_RED);
                    std::cout << m_tab[i][j].getType() << "  ";
                    pConsole->setColor(COLOR_DEFAULT);
                    break;
                case '*' :
                    pConsole->setColor(COLOR_YELLOW);
                    std::cout << m_tab[i][j].getType() << "  ";
                    pConsole->setColor(COLOR_DEFAULT);
                    break;

                case 'V' :
                    pConsole->setColor(COLOR_PINK);
                    std::cout << m_tab[i][j].getType() << "  ";
                    pConsole->setColor(COLOR_DEFAULT);
                    break;

                case 'H' :
                    pConsole->setColor(COLOR_PINK);
                    std::cout << m_tab[i][j].getType() << "  ";
                    pConsole->setColor(COLOR_DEFAULT);
                    break;

                default :
                    std::cout << m_tab[i][j].getType() << "  ";
                    break;
                }
            }

        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    /// Display all the remaining infos to the gamer
    pConsole->gotoLigCol(2, 62);
    std::cout << "Level : " << m_nbActualLevel;
    pConsole->gotoLigCol(4,62);
    std::cout << "Birds left : " << m_nbBirds;
    pConsole->setColor(COLOR_RED);
    pConsole->gotoLigCol(19,0);
    if(m_player.getLife()==3)
    {
        std::cout <<"    **   **     **   **     **   **      "<<std::endl;
        std::cout <<"   **** ****   **** ****   **** ****     "<<std::endl;
        std::cout <<"   *********   *********   *********     "<<std::endl;
        std::cout <<"    *******     *******     *******      "<<std::endl;
        std::cout <<"      ***         ***         ***        "<<std::endl;
    }

    if(m_player.getLife()==2)
    {
        std::cout <<"    **   **     **   **                  "<<std::endl;
        std::cout <<"   **** ****   **** ****                 "<<std::endl;
        std::cout <<"   *********   *********                 "<<std::endl;
        std::cout <<"    *******     *******                  "<<std::endl;
        std::cout <<"      ***         ***                    "<<std::endl;
    }

    if(m_player.getLife()==1)
    {
        std::cout <<"    **   **                              "<<std::endl;
        std::cout <<"   **** ****                             "<<std::endl;
        std::cout <<"   *********                             "<<std::endl;
        std::cout <<"    *******                              "<<std::endl;
        std::cout <<"      ***                                "<<std::endl;
    }
    pConsole->setColor(COLOR_DEFAULT);
}


void Level::breakBlock(int key,Console* pConsole)
{
    /// If the player wants to break and block 'C'
    if (key == 'a')
    {
        /// Verification of the type of the block
        if  (( m_tab[m_player.getPosY()][m_player.getPosX()+1].getType() == 'C' ))
        {
            m_tab[m_player.getPosY()][m_player.getPosX()+1] = Block(m_player.getPosY(),m_player.getPosX()+1,' ');
            pConsole->gotoLigCol(m_player.getPosY()*2,(m_player.getPosX()+1)*3);
            std::cout << m_tab[m_player.getPosY()][m_player.getPosX()+1].getType() << ' ';
        }

        else if (( m_tab[m_player.getPosY()][m_player.getPosX()-1].getType() == 'C' ))
        {
            m_tab[m_player.getPosY()][m_player.getPosX()-1] = Block(m_player.getPosY(),m_player.getPosX()+1,' ');
            pConsole->gotoLigCol(m_player.getPosY()*2,(m_player.getPosX()-1)*3);
            std::cout << m_tab[m_player.getPosY()][m_player.getPosX()-1].getType() << ' ';
        }

        else if (( m_tab[m_player.getPosY()+1][m_player.getPosX()].getType() == 'C' ))
        {
            m_tab[m_player.getPosY()+1][m_player.getPosX()] = Block(m_player.getPosY(),m_player.getPosX()+1,' ');
            pConsole->gotoLigCol((m_player.getPosY()+1)*2,(m_player.getPosX())*3);
            std::cout << m_tab[m_player.getPosY()+1][m_player.getPosX()].getType() << ' ';
        }

        else if (( m_tab[m_player.getPosY()-1][m_player.getPosX()].getType() == 'C' ))
        {
            m_tab[m_player.getPosY()-1][m_player.getPosX()] = Block(m_player.getPosY(),m_player.getPosX()+1,' ');
            pConsole->gotoLigCol((m_player.getPosY()-1)*2,(m_player.getPosX())*3);
            std::cout << m_tab[m_player.getPosY()-1][m_player.getPosX()].getType() << ' ';

        }

    }

}

bool Level::getIsPlayerAlive() const
{
    return m_player.getAlive();
}



