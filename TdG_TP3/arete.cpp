#include "arete.h"
    arete::arete()
    :m_sommet1(0),m_sommet2(0),m_poids(0)
    {

    }
    arete::arete(int val1, int val2, int poids)
    :m_sommet1(val1),m_sommet2(val2),m_poids(poids)
    {

    }
    arete::~arete()
    {

    }

    int arete::Getm_sommet1()
    {
        return m_sommet1;
    }

    int arete::Getm_sommet2()
    {
        return m_sommet2;
    }

    int arete::Getm_poids()
    {
        return m_poids;
    }

    void arete::Setm_sommet1(int val1)
    {
        m_sommet1=val1;
    }

     void arete::Setm_sommet2(int val2)
    {
        m_sommet2=val2;
    }
    void arete::Setm_poids(int poids)
    {
        m_poids=poids;
    }

