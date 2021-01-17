#ifndef ARETE_H
#define ARETE_H


class arete
{
    public:
        arete();
        arete(int val1, int val2, int poids);
        ~arete();
        int Getm_sommet1();
        void Setm_sommet1(int val1);
        int Getm_sommet2() ;
        void Setm_sommet2(int val2);
        int Getm_poids() ;
        void Setm_poids(int poids);
    private:
        int m_sommet1;
        int m_sommet2;
        int m_poids;
};

#endif // ARETE_H
