#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>
#include "sommet.h"

class Graph{
public:
    Graph(); //constructeur et destructeur
    ~Graph();
    void setUp(int order); //méthodes
    void readSaveFile(std::string save);
    void setOrder(int order){my_order=order;}
    int getOrder(void){return my_order;}
protected:
    std::vector <sommet*> sommets; //attributs
    //int **matrice_adj;
    int my_order;
};


#endif // GRAPHE_H
