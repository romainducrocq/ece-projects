#include "menu.h"

menu::menu() 
{
	pConsole = Console::getInstance();

	zeMenu : 
	system("cls");
	system("mode con LINES=25 COLS=80");
	this->ecranAccueil();

	switch(this->curseur()) 
		{
			case 0 : 
			{
				system("mode con LINES=10 COLS=20");
				system("cls");
				pConsole->gotoLigCol(3,4); std::cout << "PLAYER ONE :";
				pConsole->gotoLigCol(5,4); getline(std::cin, VARG::CAPTN1);
				system("cls");
				pConsole->gotoLigCol(3,4); std::cout << "PLAYER TWO :";
				pConsole->gotoLigCol(5,4); getline(std::cin, VARG::CAPTN2);
				system("mode con LINES=50 COLS=80");
				fight pearlHarbor; ///+ finir trucs de schlags chelous des bateaux
				goto zeMenu;
				break;
			}
			case 1 :
			{
				std::ifstream fileSave ("Save.txt");
				if(fileSave)
				{
					VARG::SAVE = true;
					getline(fileSave,VARG::CAPTN1);
					getline(fileSave,VARG::CAPTN2);
					fileSave.close();
					system("mode con LINES=50 COLS=80");
					fight pearlHarbor;
					std::cout<< "yo";
					VARG::SAVE = false;
				}
				else 
				{
					system("mode con LINES=10 COLS=20");
					system("cls");
					pConsole->gotoLigCol(4,3); std::cout << "NO SAVE FILE !";
					pConsole->getInputKey();
				}
				goto zeMenu;
				break;
			}
			case 2 :
			{
				system("mode con LINES=50 COLS=120");
					system("cls");
					this->howToPlay();
					pConsole->getInputKey();
				goto zeMenu;
				break;
			}
			case 3 :
				break;
			default : 
				break;
		}
}

menu::~menu() 
{
	Console::deleteInstance();
}

void menu::ecranAccueil()
{
pConsole->setColor(_COLOR_PURPLE_RED); 

	pConsole->gotoLigCol(5,10); std::cout << "#####   ####  #####  #####  #      #      #####";
    pConsole->gotoLigCol(6,10); std::cout << "#   #  #   #    #      #    #      #      #";
    pConsole->gotoLigCol(7,10); std::cout << "#  #   #   #    #      #    #      #      #";
    pConsole->gotoLigCol(8,10); std::cout << "#####  #####    #      #    #      #      ###";
    pConsole->gotoLigCol(9,10); std::cout << "#   #  #   #    #      #    #      #      #";
    pConsole->gotoLigCol(10,10);std::cout << "#   #  #   #    #      #    #      #      #";
    pConsole->gotoLigCol(11,10);std::cout << "####   #   #    #      #    #####  #####  #####";

    pConsole->gotoLigCol(15,45);std::cout << "#####  #   #  #  #####";
    pConsole->gotoLigCol(16,45);std::cout << "#      #   #  #  #   #";
    pConsole->gotoLigCol(17,45);std::cout << "#      #   #  #  #   #";
    pConsole->gotoLigCol(18,45);std::cout << "#####  #####  #  ####";
    pConsole->gotoLigCol(19,45);std::cout << "    #  #   #  #  #";
    pConsole->gotoLigCol(20,45);std::cout << "    #  #   #  #  #";
    pConsole->gotoLigCol(21,45);std::cout << "#####  #   #  #  #";

pConsole->setColor(_COLOR_DEFAULT);

	pConsole->gotoLigCol(15,20);std::cout << "PLAY GAME";
	pConsole->gotoLigCol(17,20);std::cout << "LOAD GAME";	
	pConsole->gotoLigCol(19,20);std::cout << "HOW TO PLAY";
	pConsole->gotoLigCol(21,20);std::cout << "EXIT GAME";
}

unsigned short menu::curseur()
{
	pConsole->gotoLigCol(15, 16); std::cout<<">>";
	unsigned short key, i = 0;
	while((key = pConsole->getInputKey()))
	{
		if(key==224||key==0)
		{
		switch(key = pConsole->getInputKey())
		{
			case ARROW_UP :
			{
				if(i>0)
				{
					pConsole->gotoLigCol(15+i*2, 16); std::cout<<"  ";
					i--;
					pConsole->gotoLigCol(15+i*2, 16); std::cout<<">>";	
				}
				break;
			}
			case ARROW_BOTTOM :
			{
				if(i<3)
				{
					pConsole->gotoLigCol(15+i*2, 16); std::cout<<"  ";
					i++;
					pConsole->gotoLigCol(15+i*2, 16); std::cout<<">>";	
				}
				break;
			}
			default : 
			break;
		}
	}
	else if(key == ENTER)
			return i; 
	}
	return i;
}


void menu::howToPlay()
{

	pConsole->gotoLigCol(5,10); std::cout << "WELCOME TO BATTLESHIP !";
	pConsole->gotoLigCol(7,5); std::cout << "Battleship est un jeu opposant 2 joueurs.";
	pConsole->gotoLigCol(8,5); std::cout << "Chaque joueur incarne un capitaine a la tete d'une flotte de navires au sein d'une bataille navale.";
	pConsole->gotoLigCol(9,5); std::cout << "A tour de role, chaque joueur tente de toucher et de couler les navires adverses.";
	pConsole->gotoLigCol(10,5); std::cout << "Chaque navire possede une taille et une puissance differentes.";
	pConsole->gotoLigCol(11,5); std::cout << "Une flotte est composee de 10 navires :";
	pConsole->gotoLigCol(12,15); std::cout << "- 1 CUIRASSE : taille = 7, puissance = 9";
	pConsole->gotoLigCol(13,15); std::cout << "- 2 CROISEURS : taille = 5, puissance = 4";
	pConsole->gotoLigCol(14,15); std::cout << "- 3 DESTROYERS : taille = 3, puissance = 1";
	pConsole->gotoLigCol(15,15); std::cout << "- 4 SOUS-MARINS : taille = 1, puissance = 1";

	pConsole->gotoLigCol(17,5); std::cout << "Lors d'un tour de jeu, il est possible au choix de :";
	pConsole->gotoLigCol(18,15); std::cout << "- Tourner un navire d'un angle de 90d.";
	pConsole->gotoLigCol(19,15); std::cout << "- Deplacer un navire d'une case dans le sens de la longueur.";
	pConsole->gotoLigCol(20,15); std::cout << "- Tirer sur la grille adverse.";

	pConsole->gotoLigCol(22,5); std::cout << "Certains navires possedent des caracteristiques particulieres :";
	pConsole->gotoLigCol(23,15); std::cout << "- Un cuirasse a besoin de 2 tours de jeu pour tourner.";
	pConsole->gotoLigCol(24,15); std::cout << "- Un destroyer devoile une zone de 4*4 cases dans la grille adverse lors de son 1er tir.";
	pConsole->gotoLigCol(25,15); std::cout << "- Un sous-marin ne peut couler qu'un autre sous-marin.";

	pConsole->gotoLigCol(27,5); std::cout << "Les deplacements s'effectuent avec les touches directionnelles.";
	pConsole->gotoLigCol(28,5); std::cout << "Les selections s'effectuent avec la touche entrer.";

	pConsole->gotoLigCol(30,5); std::cout << "A tout moment, un joueur peut :";
	pConsole->gotoLigCol(31,15); std::cout << "- Sauvegarder la partie avec la touche espace.";
	pConsole->gotoLigCol(32,15); std::cout << "- Quitter la partie avec la touche echap.";

	pConsole->gotoLigCol(34,5); std::cout << "Le menu principal permet de lancer :";
	pConsole->gotoLigCol(35,15); std::cout << "- Une nouvelle partie.";
	pConsole->gotoLigCol(36,15); std::cout << "- Une sauvegarde.";

	pConsole->gotoLigCol(38,5); std::cout << "Toutes les cases d'un navire doivent etres touchees pour couler celui-ci.";
	pConsole->gotoLigCol(39,5); std::cout << "Le joueur qui coule tous les navires adverses obtient la victoire.";
}