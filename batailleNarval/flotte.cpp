#include "flotte.h"

flotte::flotte() ///remplir alea les navires dans la
{
	if(VARG::SAVE==false)
		this->flotteConstructeur();
	else if(VARG::SAVE==true)
		this->flotteConstructeurSAVE();
}

flotte::~flotte()
{
	for(unsigned short i=0; i<this->m_flotte.size(); i++)
    {
        delete this->m_flotte[i];
        this->m_flotte[i]=NULL;
    }
}

void flotte::flotteConstructeur()
{
	std::vector<std::vector<bool> > tLibre(VARG::TAILLE_GRILLE,std::vector<bool>(VARG::TAILLE_GRILLE,true));

for(unsigned short type = 0; type < VARG::NB_TYPE_NAVIRES; type++)
{
	unsigned short taille, nombre;
	switch(type)
	{
		case 0 : ///cuirasse
		{
			taille = VARG::TAILLE_CUIRASSE;
			nombre = VARG::NB_CUIRASSES;
			break;
		}
		case 1 : ///croiseur
		{
			taille = VARG::TAILLE_CROISEUR;
			nombre = VARG::NB_CROISEURS;
			break;
		}
		case 2 : ///destroyer
		{
			taille = VARG::TAILLE_DESTROYER;
			nombre = VARG::NB_DESTROYERS;
			break;
		}
		case 3 : ///sous marin
		{
			taille = VARG::TAILLE_SOUS_MARIN;
			nombre = VARG::NB_SOUS_MARINS;
			break;
		}
}
	for(unsigned short i = 0; i < nombre; i++)
	{
		tryagain:
		bool orientation = rand()%2;
		unsigned short x = rand()%(VARG::TAILLE_GRILLE), y = rand()%(VARG::TAILLE_GRILLE);
			for(unsigned short j=0; j < taille; j++)
			{
				if(orientation == VARG::VERTICAL&&y+j<VARG::TAILLE_GRILLE)
				{
					if(tLibre[x][y+j]==false)
						goto tryagain;
				}
				else if(orientation == VARG::HORIZONTAL&&x+j<VARG::TAILLE_GRILLE)
				{
					if(tLibre[x+j][y]==false)
						goto tryagain;
				}
				else
                    goto tryagain;
			}
		for(unsigned short j=0; j < taille; j++)
			{
				if(orientation == VARG::VERTICAL)
					tLibre[x][y+j]=false;
				else if(orientation == VARG::HORIZONTAL)
					tLibre[x+j][y]=false;
			}

			///appeler les constructeurs des bateaux #Francky
			switch(type)
	{
		case 0 : ///cuirasse
		{
			this->m_flotte.push_back(new cuirasse(orientation, x, y));
			break;
		}
		case 1 : ///croiseur
		{
			this->m_flotte.push_back(new croiseur(orientation, x, y));
			break;
		}
		case 2 : ///destroyer
		{
			this->m_flotte.push_back(new destroyer(orientation, x, y));
			break;
		}
		case 3 : ///sous marin
		{
			this->m_flotte.push_back(new sous_marin(orientation, x, y));
			break;
		}
	}
    }
}
}

void flotte::flotteConstructeurSAVE()
{
    std::string ligne;

    std::ifstream fileSave ("Save.txt");

    if(!VARG::SAVE_SWITCH_FLOTTE)
    	while(getline(fileSave,ligne) && ligne!="DEBUT_FLOTTE_1") {}
    else
    	while(getline(fileSave,ligne) && ligne!="DEBUT_FLOTTE_2") {}

    VARG::SAVE_SWITCH_FLOTTE = !(VARG::SAVE_SWITCH_FLOTTE);

    while(getline(fileSave,ligne) && ligne!="FIN_FLOTTE")
    {
    unsigned short x, y, orientation, fuseeEclairante;
    std::string infos;
    std::vector<bool> touche;

    getline(fileSave,infos);
   	orientation = atoi(infos.c_str());
	getline(fileSave,infos);
	x = atoi(infos.c_str());
   	getline(fileSave,infos);
   	y = atoi(infos.c_str());
	getline(fileSave,infos);

	for(unsigned short i = 0; i < infos.length(); i++)
		touche.push_back((bool) (((unsigned short) infos[i] - 48)));

	if(ligne == VARG::TYPE_DESTROYER)
	{	getline(fileSave,infos);
		fuseeEclairante = atoi(infos.c_str());	}

    if(ligne == VARG::TYPE_CUIRASSE)
			this->m_flotte.push_back(new cuirasse((bool) orientation, x, y, touche));
	else if(ligne == VARG::TYPE_CROISEUR)
			this->m_flotte.push_back(new croiseur((bool) orientation, x, y, touche));
	else if(ligne == VARG::TYPE_DESTROYER)
			this->m_flotte.push_back(new destroyer((bool) orientation, x, y, touche, (bool) fuseeEclairante));
	else if(ligne == VARG::TYPE_SOUS_MARIN)
			this->m_flotte.push_back(new sous_marin((bool) orientation, x, y, touche));


	}
    fileSave.close();
}
