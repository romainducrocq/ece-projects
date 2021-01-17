#include <iostream>
#include "wallet.h"

using namespace std;

int main()
{
    wallet w;
    if(w.Go())
        {
            w.Appli();
        }

    return 0;
}
END_OF_MAIN();


///////////////////////////////////////////////////////////////////////////////////////////
///INSTRUCTIONS POUR LE PEUPLE
///Manipulation des fichiers txt
///Actions.txt : liste des actions que possede l'utilisateur
///ActionsNombres.txt : la quantite de chaque action que possede l'utilisateur
///ActionsDispos.txt : Toutes les actions qui existent dans la base de donnée
///ActionsPoids.txt : Les poids des actions sur 1 mois de 31 jours (donc 31 valeurs)

///IMPORTANT
///Normalement, pas besoin de toucher au code, on peut gérer toutes les actions dispos depuis l'appli
///Si besoin, on peut rajouter des actions directement dans les fichiers textes

///Toutes les actions doivent etre dans ActionsDispos.txt, et leurs poids dans ActionsPoids.txt
///Pas besoin d'ecrire dans Actions.txt et ActionsNombres.txt

///PAYE TON KEBAB SI T'AS LU JUSQUE LA


