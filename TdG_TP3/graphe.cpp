#include "graphe.h"
#include <fstream>

    Graph::Graph():my_order(0){} //constructeur par d�faut

    Graph::~Graph(){
     sommets.clear();//on supprime tour � tour les �l�ments de sommets
        }

    void Graph::setUp(int order){
        my_order=order;
        /*matrice_adj=new int*[order]; //on cr�e la matrice d'adjacence dynamique
    for(int i=0; i<order; i++){
        matrice_adj[i]=new int[order];
    }*/
    sommets.resize(order); //on donne la taille appropri�e au vecteur
        for(int j=0; j<order; j++){
            sommets[j]= new sommet(); //on instance le vecteur de sommets
        }
    }

    void Graph::readSaveFile(std::string save){//lecture du fichier de sauvegarde

    std::ifstream myFile (save);
    if(!myFile){std::cout<<"\n Le fichier n'existe pas! Nom du fichier : save.txt";}
    std::string line; int i = 0;
    while(getline(myFile,line)){ //on r�cup�re le nombre de sommets
        i++;
    }
    myFile.close();
    setUp(i); //on instancie la matrice et le vecteur
    //ici nous utilisons Kruskal donc pas de matrice d'adjacence
    i=0;
    std::ifstream myFile2 (save);
    while(getline(myFile2,line)){ //on r�cup�re une � une les lignes
        if(i<my_order){ //si c'est un nom on le r�cup�re
            sommets[i]->m_nom = line;
        }
        i++;
    }
    myFile2.close();

    }


