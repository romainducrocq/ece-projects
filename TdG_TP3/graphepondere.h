#ifndef GRAPHEPONDERE_H
#define GRAPHEPONDERE_H
#include "graphe.h"
#include "arete.h"

class graphepondere: public Graph
{
    public:
        graphepondere();
        ~graphepondere();
        int Getm_nbAretes() { return m_nbAretes; }
        void Setm_nbAretes(int val) { m_nbAretes = val; }
        void setUpGraph(int taille);
        void readSaveFileGraph(std::string file_name);
        void Kruskal(void);
        void Dijkstra(void);
    protected:
    private:
        int m_nbAretes;
        std::vector <arete*> m_aretes;

};

#endif // GRAPHEPONDERE_H
