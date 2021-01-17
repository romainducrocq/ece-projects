#include "graphepondere.h"
#include <fstream>

#define INFINI 1000;

graphepondere::graphepondere()
{
    //ctor
}

graphepondere::~graphepondere()
{
    //dtor
}
        void graphepondere::setUpGraph(int taille){ //on défini la taille du vecteur d'arretes
            m_aretes.resize(taille);
        }

        void graphepondere::readSaveFileGraph(std::string file_name){
            std::ifstream myFile (file_name);
            if(!myFile){std::cout<<"\n Le fichier n'existe pas! Nom du fichier : save2.txt";}
            std::string line; int i = 0;
            while(getline(myFile,line)){ //on récupère le nombre de sommets
                switch(i){  //-48 pour "cast" de char en int
            case 0:
                setOrder(line[0]-48); //on donne l'ordre au graphe
                break;
            case 1:
                Setm_nbAretes((line[0]-48)*10 + line[1]-48); //on donne le nb d'aretes au graphe
                setUpGraph(Getm_nbAretes());
                break;
            default:
                m_aretes[i-2] = new arete(line[0]-48, line[1]-48, line[2]-48); //on met en place toutes les aretes
                break;
                }
                i++;
            }
            myFile.close();
            /*vérification des données
            std::cout<<std::endl;
            std::cout << getOrder()<<std::endl;
            std::cout << Getm_nbAretes()<<std::endl;
            for(int i=0; i< 16; i++){
                std::cout << m_aretes[i]->Getm_sommet1();
                std::cout << m_aretes[i]->Getm_sommet2();
                std::cout << m_aretes[i]->Getm_poids()<<std::endl;
            }
            */
        }


        /// KRUSKAL
        void graphepondere::Kruskal(void){

            arete ** chemin= new arete*[getOrder()-1]; //tableau d'aretes de poids min
            int * connexe=new int[getOrder()]; //numéros de sommets connexes
            int indiceA=0, indiceG=0; //indices de l'arbre et du graphe
            int x, s1, s2; //numéros de sommets intermédiaires
            arete * u; //arete relient deux sommets
            arete * temp; //arete temporaire (classement)

            //initialisation des connexités indicées sur les numéros de sommets
            for(x=0; x<getOrder(); x++){connexe[x]=x;}

            //Trier le graphe par ordre croissant de s poids de ses 'n' aretes
            for(int i = 0; i < Getm_nbAretes(); i++)
            {
                for (int j = 0; j < Getm_nbAretes() ; ++j) {
                    if (m_aretes[i]->Getm_poids() < m_aretes[j]->Getm_poids()) {
                        temp = m_aretes[i];
                        m_aretes[i] = m_aretes[j];
                        m_aretes[j] = temp;
                    }
                }
            }

            // tant que les arêtes de l’arbre et du graphe ne sont pas toutes traitées
            while (indiceA<getOrder()-1 && indiceG<Getm_nbAretes()) {
                u = m_aretes[indiceG] ; // retourner l’arête u numéro indiceG du graphe
                s1 = connexe[u->Getm_sommet1()] ; s2 = connexe[u->Getm_sommet2()] ; // les sommets s1, s2 de l’arête u

                // Tester si les sommets s1 et s2 de l’arête u forment un cycle dans l’arbre
                if (s1==s2) // cycle si s1 et s2 connexes
                    {indiceG++ ;} // passer à l’arête suivante du graphe
                else { // pas de cycle
                 // insérer l’arête u à la position « indiceA » de l’arbre
                chemin[indiceA] = u ;
                indiceA++ ; indiceG++ ; // passer à l’arête suivante de l’arbre et du graphe
                // Indiquer que les sommets s1 et s2 sont connexes
                for (x=0 ; x<getOrder() ; x++){
                if (connexe[x]==s1){connexe[x] = s2 ;}}
                }
            }

            // Le graphe est non connexe si le nombre d’arêtes de l’arbre < nombre de sommets-1
            if (indiceA<getOrder()-1) { std::cout<<"Le graphe n'est pas connexe\n"<<std::endl; }

            //On affiche le chemin
            std::cout<<"\n\t Kruskal :"<<std::endl;
            std::cout<<"Sommet1 Sommet2 Poids"<<std::endl;
            for(int i=0; i<getOrder()-1; i++){
                std::cout<<chemin[i]->Getm_sommet1()<<"      \t"<<chemin[i]->Getm_sommet2()<<"      \t"<<chemin[i]->Getm_poids()<<std::endl;
            }
        }



        /// DIJKSTRA
        void graphepondere::Dijkstra(void){
            int matrice_adj [getOrder()][getOrder()]; //matrice adjacence poids
            int * d_min = new int[getOrder()]; //distances min des sommets depuis s
            int * predecessor = new int[getOrder()]; //tableau des prédecesseurs de sommets
            int s_ref = 0; //numéro de sommet de référence
            int * marques = new int[getOrder()]; //tableau indiquant si les sommets sont marqués
            int x, y, xmin; //numéros des sommets intermédiaires
            int minimum; //distance minimale du prochain sommet à marquer
            int nb=0; //nb de sommets marqués
            arete * temp; //arete temporaire

            for(int i=0; i<getOrder(); i++){ //on initialise le tableau de marquage et les longueurs minimales
                d_min[i]=INFINI;
                marques[i]=0;
            }
            for(int i=0; i<getOrder(); i++){
                for(int j=0; j<getOrder(); j++){ //on met tous les poids à 0
                    matrice_adj[i][j]=0;
                }
            }
            for(int i=0; i<Getm_nbAretes(); i++){ //puis on donne la vraie valeur aux poids
                temp=m_aretes[i];
                matrice_adj[temp->Getm_sommet1()][temp->Getm_sommet2()]=temp->Getm_poids();
                matrice_adj[temp->Getm_sommet2()][temp->Getm_sommet1()]=temp->Getm_poids();
            }
            d_min[s_ref]=nb; //initialisation du sommet de référence

            while(nb<getOrder()){ //tant que les sommets ne sont pas tous marqués
                minimum=INFINI; //on met le minimum du sommet actuel à l'infini

                for(x=0;x<getOrder();x++){ //on stocke le sommet xmin de longueur minimale
                        //pour tous les sommets x non marqués de longueur minimale
                    if(!marques[x] && d_min[x]<minimum){
                        xmin=x;
                        minimum = d_min[x];
                    }
                }

                //on marque le sommet de longueur minimale xmin et on incrémente nb
                marques[xmin]=1;
                nb++;

                //pour tous les sommets adjacents à xmin et non marqués
                for (y=0 ; y<getOrder() ; y++){
                    if (matrice_adj[xmin][y] && !marques[y] && d_min[xmin]+ matrice_adj[xmin][y]<d_min[y]) {
                    //on cherche la plus petite distance de xmin a y
                    //et on stocke le prédécésseur correspondant
                    d_min[y] = d_min[xmin] + matrice_adj[xmin][y] ;
                    predecessor[y] = xmin ;
                    }
                }
            }

            predecessor[s_ref]=0;
            std::cout<<"\n\t Dijkstra :"<<std::endl;
            std::cout<<"Sommet \tPoids \tPredecesseur"<<std::endl;
            for(int i=0; i<getOrder(); i++){
                std::cout<<i<<"     \t"<<d_min[i]<<"    \t"<<predecessor[i]<<std::endl;
            }

        }
