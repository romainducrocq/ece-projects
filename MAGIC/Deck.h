#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED

#include "pConsole.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>

class Deck
{
private :
    int m_N;
    std::vector<std::string> m_Deck1;
    std::vector<std::string> m_Deck2;
    std::vector<std::string> m_Deck3;

public :
    Deck();
    ~Deck();

    void load(Console* pConsole);
    void displayDeck(std::vector<std::string> Deck, Console* pConsole);
    void Jeu(Console* pConsole);
    std::vector<std::string> redistribuer(std::vector<std::string> Deck1, int col, int pos);
};


#endif // DECK_H_INCLUDED
