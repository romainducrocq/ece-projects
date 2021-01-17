#include "capitaine.h"

capitaine::capitaine() : grille(VARG::TAILLE_GRILLE, std::vector<unsigned short>(VARG::TAILLE_GRILLE, VARG::MER)), m_tourneCuirasse(false), m_pseudo("")
{
	this->majGrille();
}

capitaine::~capitaine() {}


void capitaine::majGrille()
{
	for(unsigned short i = 0; i<VARG::TAILLE_GRILLE; i++)
	{
		for(unsigned short j = 0; j<VARG::TAILLE_GRILLE; j++)
		{
			if(grille[i][j]!=VARG::MER)
				grille[i][j]=VARG::MER;
		}
	}

	for(unsigned short i = 0; i<armadaPirate.m_flotte.size(); i++)
	{
		for(unsigned short j = 0; j<armadaPirate.m_flotte[i]->getTaille(); j++)
		{
			grille[armadaPirate.m_flotte[i]->getX(j)][armadaPirate.m_flotte[i]->getY(j)] = i;
		}
	}

}

unsigned short capitaine::getCaseGrille(unsigned short x, unsigned short y)
{
	if(x<VARG::TAILLE_GRILLE&&y<VARG::TAILLE_GRILLE)
		return grille[x][y];
	return VARG::MER;
}

bateau* capitaine::getBateau(unsigned short i)
{
	if(i<armadaPirate.m_flotte.size())
		return armadaPirate.m_flotte[i];
	return NULL;
}

bool capitaine::moveBateau(unsigned short selectBoat, unsigned short selectDir)
{

	/*std::cout << "Direction : 0 DROITE, 1 GAUCHE, 2 BAS, 3 HAUT";
	unsigned short selectDir; ///= rand()%4;
	std::cin >> selectDir;
	std::cout << "slct bateau";
	unsigned short selectBoat; ///= rand()%10;
	std::cin >> selectBoat;*/

	///sous marins deplaceable independemment de l'orientation
	switch(selectDir)
	{
		case 77 : ///x+
		{
			if(armadaPirate.m_flotte[selectBoat]->getOrientation()==VARG::HORIZONTAL||armadaPirate.m_flotte[selectBoat]->getTaille()==1) ///horizontal
			{
				if(armadaPirate.m_flotte[selectBoat]->getX(armadaPirate.m_flotte[selectBoat]->getTaille()-1) + 1 < VARG::TAILLE_GRILLE ) ///si pas contre le bord 
				{
					if(grille[armadaPirate.m_flotte[selectBoat]->getX(armadaPirate.m_flotte[selectBoat]->getTaille()-1) + 1][armadaPirate.m_flotte[selectBoat]->getY(armadaPirate.m_flotte[selectBoat]->getTaille()-1)] == VARG::MER)
					{
						armadaPirate.m_flotte[selectBoat]->setXplus();
						return true;
					}
				}
			}
			///si deplacer bateau sur le coté en mode créneau
			/*else if(armadaPirate.m_flotte[selectBoat]->getOrientation()==VARG::VERTICAL) ///vertical
			{
				if(armadaPirate.m_flotte[selectBoat]->getX(0) + 1 < VARG::TAILLE_GRILLE ) ///si pas contre le bord 
				{
					for(unsigned short i = 0; i<armadaPirate.m_flotte[selectBoat]->getTaille(); i++)
					{
						if(grille[armadaPirate.m_flotte[selectBoat]->getX(i) + 1][armadaPirate.m_flotte[selectBoat]->getY(i)] != VARG::MER) ///si toutes les cases x+ sont libres
							return false;
					}
					armadaPirate.m_flotte[selectBoat]->setXplus();
						return true;
				}
			}*/
			break;
		}
		case 75 : ///x-
		{
			if(armadaPirate.m_flotte[selectBoat]->getOrientation()==VARG::HORIZONTAL||armadaPirate.m_flotte[selectBoat]->getTaille()==1) ///horizontal
			{
				if(armadaPirate.m_flotte[selectBoat]->getX(0) > 0 ) ///si pas contre le bord 
				{
					if(grille[armadaPirate.m_flotte[selectBoat]->getX(0) - 1][armadaPirate.m_flotte[selectBoat]->getY(0)] == VARG::MER)
					{
						armadaPirate.m_flotte[selectBoat]->setXmoins();
						return true;
					}
				}
			}
			break;
		}
		case 80 : ///y+
		{
			if(armadaPirate.m_flotte[selectBoat]->getOrientation()==VARG::VERTICAL||armadaPirate.m_flotte[selectBoat]->getTaille()==1) ///vertical
			{
				if(armadaPirate.m_flotte[selectBoat]->getY(armadaPirate.m_flotte[selectBoat]->getTaille()-1) + 1 < VARG::TAILLE_GRILLE ) ///si pas contre le bord 
				{
					if(grille[armadaPirate.m_flotte[selectBoat]->getX(armadaPirate.m_flotte[selectBoat]->getTaille()-1)][armadaPirate.m_flotte[selectBoat]->getY(armadaPirate.m_flotte[selectBoat]->getTaille()-1) + 1] == VARG::MER)
					{
						armadaPirate.m_flotte[selectBoat]->setYplus();
						return true;
					}
				}
			}
			break;
		}
		case 72 : ///y-
		{
			if(armadaPirate.m_flotte[selectBoat]->getOrientation()==VARG::VERTICAL||armadaPirate.m_flotte[selectBoat]->getTaille()==1) ///vertical
			{
				if(armadaPirate.m_flotte[selectBoat]->getY(0) > 0 ) ///si pas contre le bord 
				{
					if(grille[armadaPirate.m_flotte[selectBoat]->getX(0)][armadaPirate.m_flotte[selectBoat]->getY(0) - 1] == VARG::MER)
					{
						armadaPirate.m_flotte[selectBoat]->setYmoins();
						return true;
					}
				}
			}
			break;
		}

		default:
			break;
		
	}
	return false;
}

bool capitaine::turnBateau(unsigned short selectBoat) 
{
	/*//rmv
	std::cout << "slct bateau";
	unsigned short selectBoat                                                                                                                                                                                                                                                                                                                                                                                 
	; ///= rand()%10;
	std::cin >> selectBoat;*/

	if(armadaPirate.m_flotte[selectBoat]->getTaille()==1)
		return false;

/*horizontal => y cst     
( x(f) + x(0) )/ 2
y(0) - taille/2 + i*/

	///sous marins return false direct
	if(armadaPirate.m_flotte[selectBoat]->getOrientation() == VARG::HORIZONTAL)
	{	///si pas de depasseement quand on tourne
		if(armadaPirate.m_flotte[selectBoat]->getY(0) >= armadaPirate.m_flotte[selectBoat]->getTaille()/2 
		&& armadaPirate.m_flotte[selectBoat]->getY(0) + armadaPirate.m_flotte[selectBoat]->getTaille() - 1 < VARG::TAILLE_GRILLE + (armadaPirate.m_flotte[selectBoat]->getTaille())/2 ) 
		{///si pas de bateau dans le passage
			for(unsigned short i = 0; i<armadaPirate.m_flotte[selectBoat]->getTaille(); i++)
			{ ///grille[(x(d)+x(f))/2][y(0)-taille/2+i]
				////////////////////
				///std::cout << (armadaPirate.m_flotte[selectBoat]->getX(0)+armadaPirate.m_flotte[selectBoat]->getX(armadaPirate.m_flotte[selectBoat]->getTaille()-1))/2 << " / ";
				///std::cout << armadaPirate.m_flotte[selectBoat]->getY(0)-armadaPirate.m_flotte[selectBoat]->getTaille()/2+i << std::endl;
				///////////////////
				if(!(grille[(armadaPirate.m_flotte[selectBoat]->getX(0)+armadaPirate.m_flotte[selectBoat]->getX(armadaPirate.m_flotte[selectBoat]->getTaille()-1))/2][armadaPirate.m_flotte[selectBoat]->getY(0)-armadaPirate.m_flotte[selectBoat]->getTaille()/2+i] == VARG::MER
				|| grille[(armadaPirate.m_flotte[selectBoat]->getX(0)+armadaPirate.m_flotte[selectBoat]->getX(armadaPirate.m_flotte[selectBoat]->getTaille()-1))/2][armadaPirate.m_flotte[selectBoat]->getY(0)-armadaPirate.m_flotte[selectBoat]->getTaille()/2+i] == selectBoat))
					return false;
			}
			armadaPirate.m_flotte[selectBoat]->setOrientation();
			if(armadaPirate.m_flotte[selectBoat]->getType()==VARG::TYPE_CUIRASSE)
				this->setTourne(); 
			return true;
		}
	}
	else if(armadaPirate.m_flotte[selectBoat]->getOrientation() == VARG::VERTICAL)
	{
		if(armadaPirate.m_flotte[selectBoat]->getX(0) >= armadaPirate.m_flotte[selectBoat]->getTaille()/2 
		&& armadaPirate.m_flotte[selectBoat]->getX(0) + armadaPirate.m_flotte[selectBoat]->getTaille() - 1 < VARG::TAILLE_GRILLE + (armadaPirate.m_flotte[selectBoat]->getTaille())/2 ) 
		{///si pas de bateau dans le passage
			for(unsigned short i = 0; i<armadaPirate.m_flotte[selectBoat]->getTaille(); i++)
			{ ///grille[(x(d)+x(f))/2][y(0)-taille/2+i]
				//////////////////
				///std::cout << armadaPirate.m_flotte[selectBoat]->getX(0)-armadaPirate.m_flotte[selectBoat]->getTaille()/2+i << std::endl;
				///std::cout << (armadaPirate.m_flotte[selectBoat]->getY(0)+armadaPirate.m_flotte[selectBoat]->getY(armadaPirate.m_flotte[selectBoat]->getTaille()-1))/2 << " / ";
				//////////////////
				if(!(grille[armadaPirate.m_flotte[selectBoat]->getX(0)-armadaPirate.m_flotte[selectBoat]->getTaille()/2+i][(armadaPirate.m_flotte[selectBoat]->getY(0)+armadaPirate.m_flotte[selectBoat]->getY(armadaPirate.m_flotte[selectBoat]->getTaille()-1))/2] == VARG::MER
				|| grille[armadaPirate.m_flotte[selectBoat]->getX(0)-armadaPirate.m_flotte[selectBoat]->getTaille()/2+i][(armadaPirate.m_flotte[selectBoat]->getY(0)+armadaPirate.m_flotte[selectBoat]->getY(armadaPirate.m_flotte[selectBoat]->getTaille()-1))/2] == selectBoat))
					return false;
			}
			armadaPirate.m_flotte[selectBoat]->setOrientation();
			if(armadaPirate.m_flotte[selectBoat]->getType()==VARG::TYPE_CUIRASSE)
				this->setTourne(); 
			return true;
		}

	}
	return false;
}

void capitaine::shootBateau(unsigned short x, unsigned short y, unsigned short puissance, std::string type)
{
	if(type == VARG::TYPE_SOUS_MARIN && armadaPirate.m_flotte[grille[x][y]]->getType() != VARG::TYPE_SOUS_MARIN)
		return;

	for(unsigned short j = 0; j<puissance; j++)
	{
		for(unsigned short i =0; i<puissance; i++)
		{
			if(grille[x+i][y+j] != VARG::MER)
			{
				if(armadaPirate.m_flotte[grille[x+i][y+j]]->getOrientation() == VARG::HORIZONTAL && armadaPirate.m_flotte[grille[x+i][y+j]]->getTouche(x+i - armadaPirate.m_flotte[grille[x+i][y+j]]->getX(0)) == false)
					{
						armadaPirate.m_flotte[grille[x+i][y+j]]->setTouche(x+i - armadaPirate.m_flotte[grille[x+i][y+j]]->getX(0));
						if(armadaPirate.m_flotte[grille[x+i][y+j]]->isNavireCoule())
							armadaPirate.m_flotte[grille[x+i][y+j]]->setToucheCoule();
					}

				else if(armadaPirate.m_flotte[grille[x+i][y+j]]->getOrientation() == VARG::VERTICAL && armadaPirate.m_flotte[grille[x+i][y+j]]->getTouche(y+j - armadaPirate.m_flotte[grille[x+i][y+j]]->getY(0)) == false) 
					{
						armadaPirate.m_flotte[grille[x+i][y+j]]->setTouche(y+j - armadaPirate.m_flotte[grille[x+i][y+j]]->getY(0));
						if(armadaPirate.m_flotte[grille[x+i][y+j]]->isNavireCoule())
							armadaPirate.m_flotte[grille[x+i][y+j]]->setToucheCoule();  
					}
			}

		}
	}
}

bool capitaine::isFlotteCoulee() const
{
	for(unsigned short i=0; i<this->armadaPirate.m_flotte.size(); i++)
	{
		if(armadaPirate.m_flotte[i]->getToucheCoule() == false)
			return false;
	}
	return true;
}

void capitaine::flotteSAVE(std::string debutFlotte)
{
	std::ofstream fileSave("Save.txt", std::ios::app);

		fileSave << debutFlotte << '\n';

	for(unsigned short i=0; i<this->armadaPirate.m_flotte.size(); i++)
	{

		std::string strtouche = "";
		for(unsigned j = 0; j<this->armadaPirate.m_flotte[i]->getTaille(); j++)
			strtouche = strtouche + (char)((unsigned short) this->armadaPirate.m_flotte[i]->getTouche(j) + 48);

		fileSave << armadaPirate.m_flotte[i]->getType() << '\n';
		fileSave << (unsigned short) armadaPirate.m_flotte[i]->getOrientation() << '\n';
		fileSave << armadaPirate.m_flotte[i]->getX(0) << '\n';
		fileSave << armadaPirate.m_flotte[i]->getY(0) << '\n';
		fileSave << strtouche << '\n';
		if(armadaPirate.m_flotte[i]->getType()==VARG::TYPE_DESTROYER)
			fileSave << (unsigned short) armadaPirate.m_flotte[i]->getFuseeDispo() << '\n';
	}
	fileSave << "FIN_FLOTTE" << '\n';
	fileSave.close();
}

bool capitaine::getTourne() const { return this->m_tourneCuirasse; }

void capitaine::setTourne() { this->m_tourneCuirasse = !(this->m_tourneCuirasse); }

std::string capitaine::getPseudo() const { return this->m_pseudo; }

void capitaine::setPseudo(std::string pseudo) { this->m_pseudo = pseudo; }