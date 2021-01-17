#include "Deck.h"
#include "pConsole.h"

Deck::Deck() : m_Deck1 (27), m_Deck2 (27), m_Deck3 (27) {}

Deck::~Deck() {}

void Deck::load(Console* pConsole)
{

    std::ifstream file("Deck.txt");
    std::vector<std::string> DeckInit(27);
    if (file)
    {
    for(int i=0; i<27; i++)
    {
        file >> DeckInit[i];
    }
    file.close();
    }
    displayDeck(DeckInit, pConsole);
    std::cout << "CHOISIS UN CARACTERE !" << std::endl;
    std::cout << "En quelle position doit-il reapparaitre ? : ";
    do{std::cin >> m_N;}while(m_N>27||m_N<1);
    system("cls");

    int alea ;
    for(int i=0; i<27; i++)
    {
        alea = rand()%(27-i);
        m_Deck1[i]=DeckInit[alea];
        DeckInit.erase(DeckInit.begin() + alea);
    }
}

 void Deck::displayDeck(std::vector<std::string> Deck, Console* pConsole)
{
    int k=0;
    for(int i=0; i<9; i++)
    {
        std::cout << "******************************************" << std::endl ;
        for(int j=0; j<3; j++)
        {
        pConsole->gotoLigCol((i*3)+1,(j*14)+1);
        std::cout << "* " << Deck[k];
        k=k+1;
        }
        std::cout << std::endl;
    }
    std::cout << "******************************************" << std::endl << std::endl ;

}

void Deck::Jeu(Console* pConsole)
{
    int col = 0;
    int pos = 0;

    load(pConsole);
    displayDeck(m_Deck1, pConsole);
    std::cout << "Dans quelle colonne se trouve ton choix ? : ";
    do{std::cin >> col;}while(col>3||col<1);
    system("cls");
    if(m_N==3||m_N==6||m_N==9||m_N==12||m_N==15||m_N==18||m_N==21||m_N==24||m_N==27)
        pos = 3;
    else
    pos = m_N%3; ///3-((-m_N)%3)
    m_Deck2 = redistribuer(m_Deck1, col-1, (pos-1)*9);
    displayDeck(m_Deck2, pConsole);
    std::cout << "Dans quelle colonne se trouve ton choix ? : ";
    do{std::cin >> col;}while(col>3||col<1);
    system("cls");
    if (m_N==19)
        pos = 1;
    else
    pos = ((((m_N/10)+(m_N%10))-1)/3)+1;
    m_Deck3 = redistribuer(m_Deck2, col-1, (pos-1)*9);
    displayDeck(m_Deck3, pConsole);
    std::cout << "Dans quelle colonne se trouve ton choix ? : ";
    do{std::cin >> col;}while(col>3||col<1);
    system("cls");
    pos = ((m_N-1)/9)+1;
    std::vector<std::string> DeckFin(27);
    DeckFin = redistribuer(m_Deck3, col-1, (pos-1)*9);

     std::cout << "La position choisie etait : " << m_N << std::endl << std::endl;

    for (int i=0; i<m_N; i++)
    {
        Sleep(50);
        std::cout << i+1 << " : " << DeckFin[i] << std::endl;
    }



}

std::vector<std::string> Deck::redistribuer(std::vector<std::string> Deck1, int col, int pos)
{
    std::vector<std::string> Deck2(27);
    for(int i=0; i<9; i++)
    {
        Deck2[pos]=Deck1[col];
        pos=pos+1;
        col=col+3;
    }
    pos=pos-9;
    col=col-27;

    int posalea1;
    int colalea1;
    do{posalea1 = (rand()%3)*9;}while(posalea1==pos);
    do{colalea1 = rand()%3;}while(colalea1==col);

    for(int i=0; i<9; i++)
    {
        Deck2[posalea1]=Deck1[colalea1];
        posalea1=posalea1+1;
        colalea1=colalea1+3;
    }
    posalea1=posalea1-9;
    colalea1=colalea1-27;

    int posalea2;
    int colalea2;
    do{posalea2 = (rand()%3)*9;}while(posalea2==pos||posalea2==posalea1);
    do{colalea2 = rand()%3;}while(colalea2==col||colalea2==colalea1);

    for(int i=0; i<9; i++)
    {
        Deck2[posalea2]=Deck1[colalea2];
        posalea2=posalea2+1;
        colalea2=colalea2+3;
    }

    return Deck2;

}



