#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <windows.h>

enum Input
{
    ARROW_UP = 72,
    ARROW_BOTTOM = 80,
    ARROW_LEFT = 75,
    ARROW_RIGHT = 77,
    ENTER =  13,
    ESC = 27,
    SPACE = 32
};

enum Color
{
    _COLOR_BLACK = 0,
    _COLOR_WHITE = 1,
    _COLOR_RED = 2,
    _COLOR_GREEN = 3,
    _COLOR_BLUE = 4,
    _COLOR_YELLOW = 5,
    _COLOR_PURPLE = 6,
    _COLOR_DEFAULT = 7, // gris couleur de base de la console
    _COLOR_DARK_BLUE = 8,
    _COLOR_GREEN_LIGHT = 9,
    _COLOR_BLUE_GREY = 10,
    _COLOR_BROWN = 11,
    _COLOR_PURPLE_RED = 12,
    _COLOR_KAKI = 13,
    _COLOR_GREY = 14,
    _COLOR_LIGHT_BLUE = 15


};

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

class Console
{
    private:
        // Empecher la création
        __attribute__((no_instrument_function))
        Console();

        __attribute__((no_instrument_function))
        ~Console();

        // Empecher la copie d'objet...
        Console& operator= (const Console&){ return *this;}
        Console (const Console&){}

        // Attributs
        static Console* m_instance;

        // Méthodes privées
        __attribute__((no_instrument_function))
        void _setColor(short unsigned int front, short unsigned int back);
    public:
        // Méthodes statiques (publiques)
        __attribute__((no_instrument_function))
        static Console* getInstance();

        __attribute__((no_instrument_function))
        static void deleteInstance();

        // Méthodes publiques
        __attribute__((no_instrument_function))
        void gotoLigCol(short int lig, short int col);

        __attribute__((no_instrument_function))
        int GetterX();

        __attribute__((no_instrument_function))
        int GetterY();

        __attribute__((no_instrument_function))
        bool isKeyboardPressed();

        __attribute__((no_instrument_function))
        int getInputKey();

        __attribute__((no_instrument_function))
        void setColor(Color col);
};

#endif // CONSOLE_H_INCLUDED
