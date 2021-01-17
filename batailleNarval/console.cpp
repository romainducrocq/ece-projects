#include "console.h"

Console* Console::m_instance = NULL;

Console::Console()
{
    m_instance = NULL;
}

Console::~Console()
{

}

void Console::deleteInstance()
{
    delete m_instance;
    m_instance = NULL;
}

Console* Console::getInstance()
{
    if (!Console::m_instance)
    {
        m_instance = new Console();
    }

    return m_instance;
}

void Console::gotoLigCol(short int lig, short int col)
{
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

int Console::GetterX()
    {
         CONSOLE_SCREEN_BUFFER_INFO csbi;
         if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
            return csbi.dwCursorPosition.X;
         else
            return 0;
    }

int Console::GetterY()
    {
         CONSOLE_SCREEN_BUFFER_INFO csbi;
         if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
            return csbi.dwCursorPosition.Y;
         else
            return 0;
    }

int Console::getInputKey()
{
    return getch();
}

bool Console::isKeyboardPressed()
{
    return kbhit();
}

/*
0: noir
1: bleu foncé
2: vert
3: bleu-gris
4: marron
5: pourpre
6: kaki
7: gris clair
8: gris
9: bleu
10: vert fluo
11: turquoise
12: rouge
13: rose fluo
14: jaune fluo
15: blanc
*/
void Console::_setColor(short unsigned int back, short unsigned int front)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,front*16+back);
}

void Console::setColor(Color col)
{
    switch (col)
    {
        case _COLOR_BLACK:
            this->_setColor(0, 0);
            break;
        case _COLOR_DARK_BLUE:
            this->_setColor(1, 0);
            break;
        case _COLOR_GREEN_LIGHT:
            this->_setColor(2, 0);
            break;
        case _COLOR_BLUE_GREY:
            this->_setColor(3, 0);
            break;
        case _COLOR_BROWN:
            this->_setColor(4, 0);
            break;
        case _COLOR_PURPLE_RED:
            this->_setColor(5, 0);
            break;
        case _COLOR_KAKI:
            this->_setColor(6, 0);
            break;
        case _COLOR_GREY:
            this->_setColor(8, 0);
            break;
        case _COLOR_LIGHT_BLUE:
            this->_setColor(9, 0);
            break;
        case _COLOR_GREEN:
            this->_setColor(10, 0);
            break;
        case _COLOR_BLUE:
            this->_setColor(11, 0);
            break;
        case _COLOR_RED:
            this->_setColor(12, 0);
            break;
        case _COLOR_PURPLE:
            this->_setColor(13, 0);
            break;
        case _COLOR_YELLOW:
            this->_setColor(14, 0);
            break;
        case _COLOR_WHITE:
            this->_setColor(15, 0);
            break;
        default:
            this->_setColor(7, 0);
    }
}
