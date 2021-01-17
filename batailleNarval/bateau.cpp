#include "bateau.h"
///class bateau ///heritage + polymorphisme

bateau::bateau(bool orientation, unsigned short x, unsigned short y, unsigned short taille) 
	: m_coule(false), m_orientation(orientation), m_fuseeDispo(true)
	{
		for(unsigned short i = 0; i<taille; i++)
		{
			caseNavire tmp;
			if(orientation == VARG::VERTICAL)
			{
				tmp.x = x;
				tmp.y = y+i;
			}
			else if(orientation == VARG::HORIZONTAL)
			{
				tmp.x = x+i;
				tmp.y = y;
			}

			tmp.touche = false;

			this->m_tabCaseNavire.push_back(tmp); 
		} 
	}   

bateau::bateau(bool orientation, unsigned short x, unsigned short y, unsigned short taille, std::vector<bool> tabTouche, bool fuseeDispo) 
	: m_coule(false), m_orientation(orientation), m_fuseeDispo(fuseeDispo)
	{
		for(unsigned short i = 0; i<taille; i++)
		{
			caseNavire tmp;
			if(orientation == VARG::VERTICAL)
			{
				tmp.x = x;
				tmp.y = y+i;
			}
			else if(orientation == VARG::HORIZONTAL)
			{
				tmp.x = x+i;
				tmp.y = y;
			}

			tmp.touche = tabTouche[i];

			this->m_tabCaseNavire.push_back(tmp); 
		} 
		if(this->isNavireCoule())
			this->setToucheCoule();
	}

bateau::~bateau() {}
bool bateau::getToucheCoule() const { return this->m_coule; }
bool bateau::getOrientation() const { return this->m_orientation; }

unsigned short bateau::getX(unsigned short i) const 
	{ 
		if(i<this->m_tabCaseNavire.size())
			return this->m_tabCaseNavire[i].x; 
		return 0;
	}

unsigned short bateau::getY(unsigned short i) const 
	{ 
		if(i<this->m_tabCaseNavire.size())
			return this->m_tabCaseNavire[i].y;
		return 0;
	}

bool bateau::getTouche(unsigned short i) const
{
	if(i<this->m_tabCaseNavire.size())
		return this->m_tabCaseNavire[i].touche;
	return 0;
}

bool bateau::isNavireCoule() const
{
	for(unsigned short i = 0; i<this->m_tabCaseNavire.size(); i++)
		{
		if(this->m_tabCaseNavire[i].touche == false)
			return false;
		}
	return true;
}

///tout le blindage est à faire avant l'appel des fonctions
void bateau::setXplus() 
{ 
	for(unsigned short i = 0; i<this->m_tabCaseNavire.size(); i++)
		this->m_tabCaseNavire[i].x++; 
}

void bateau::setXmoins() 
{ 
	for(unsigned short i = 0; i<this->m_tabCaseNavire.size(); i++)
		this->m_tabCaseNavire[i].x--; 
}

void bateau::setYplus() 
{ 
	for(unsigned short i = 0; i<this->m_tabCaseNavire.size(); i++)
		this->m_tabCaseNavire[i].y++; 
}

void bateau::setYmoins() 
{ 
	for(unsigned short i = 0; i<this->m_tabCaseNavire.size(); i++)
		this->m_tabCaseNavire[i].y--; 
}

void bateau::setTouche(unsigned short i)
{
	if(i<this->m_tabCaseNavire.size())
		this->m_tabCaseNavire[i].touche = true;
}

void bateau::setToucheCoule()
	{ this->m_coule=true; }

void bateau::setOrientation()
{
	unsigned short x0 = this->m_tabCaseNavire[0].x, y0 = this->m_tabCaseNavire[0].y;

	if(this->m_orientation==VARG::HORIZONTAL)  ///horizontal
	{
		for(unsigned short i = 0; i<this->m_tabCaseNavire.size(); i++)
		{
			this->m_tabCaseNavire[i].x = (x0 + this->m_tabCaseNavire.back().x) / 2;
			this->m_tabCaseNavire[i].y = (y0 - this->m_tabCaseNavire.size()/2 +i);
		}
		this->m_orientation=VARG::VERTICAL; 
	}

 	else if(this->m_orientation==VARG::VERTICAL) ///vertical
 	{
 		for(unsigned short i = 0; i<this->m_tabCaseNavire.size(); i++)
		{
			this->m_tabCaseNavire[i].x = (x0 - this->m_tabCaseNavire.size()/2 +i);
			this->m_tabCaseNavire[i].y = (y0 + this->m_tabCaseNavire.back().y) / 2;
		}
		this->m_orientation=VARG::HORIZONTAL;
 	}
}

	


///class cuirasse

cuirasse::cuirasse(bool orientation, unsigned short x, unsigned short y) : bateau(orientation, x, y, VARG::TAILLE_CUIRASSE) {}
cuirasse::cuirasse(bool orientation, unsigned short x, unsigned short y, std::vector<bool> tabTouche) 
		: bateau(orientation, x, y, VARG::TAILLE_CUIRASSE, tabTouche, true) {}
cuirasse::~cuirasse() {}
unsigned short cuirasse::getPuissance() const { return VARG::PUISSANCE_CUIRASSE; }
unsigned short cuirasse::getTaille() const { return VARG::TAILLE_CUIRASSE; }
std::string cuirasse::getType() const { return VARG::TYPE_CUIRASSE; }
///VIRTUELS
bool cuirasse::getFuseeDispo() const {return false;}
void cuirasse::setFuseePasDispo() {return;}
///Tourner = 2 tours

///class  croiseur 

croiseur::croiseur(bool orientation, unsigned short x, unsigned short y) : bateau(orientation, x, y, VARG::TAILLE_CROISEUR) {}
croiseur::croiseur(bool orientation, unsigned short x, unsigned short y, std::vector<bool> tabTouche) 
		: bateau(orientation, x, y, VARG::TAILLE_CROISEUR, tabTouche, true) {}
croiseur::~croiseur() {}
unsigned short croiseur::getPuissance() const { return VARG::PUISSANCE_CROISEUR; }
unsigned short croiseur::getTaille() const { return VARG::TAILLE_CROISEUR; }
std::string croiseur::getType() const { return VARG::TYPE_CROISEUR; }

bool croiseur::getFuseeDispo() const {return false;}
void croiseur::setFuseePasDispo() {return;}


///class destroyer

destroyer::destroyer(bool orientation, unsigned short x, unsigned short y) : bateau(orientation, x, y, VARG::TAILLE_DESTROYER) {}
destroyer::destroyer(bool orientation, unsigned short x, unsigned short y, std::vector<bool> tabTouche, bool fuseeDispo) 
		 : bateau(orientation, x, y, VARG::TAILLE_DESTROYER, tabTouche, fuseeDispo) {}
destroyer::~destroyer() {}
unsigned short destroyer::getPuissance() const { return VARG::PUISSANCE_DESTROYER; }
unsigned short destroyer::getTaille() const { return VARG::TAILLE_DESTROYER; }
std::string destroyer::getType() const { return VARG::TYPE_DESTROYER; }
bool destroyer::getFuseeDispo() const { return this->m_fuseeDispo; }

void destroyer::setFuseePasDispo() { this->m_fuseeDispo=false; }
///1 fusée eclairante

///class sous marin

sous_marin::sous_marin(bool orientation, unsigned short x, unsigned short y) : bateau(orientation, x, y, VARG::TAILLE_SOUS_MARIN) {}
sous_marin::sous_marin(bool orientation, unsigned short x, unsigned short y, std::vector<bool> tabTouche) 
		  : bateau(orientation, x, y, VARG::TAILLE_SOUS_MARIN, tabTouche, true) {}
sous_marin::~sous_marin() {}
unsigned short sous_marin::getPuissance() const { return VARG::PUISSANCE_SOUS_MARIN; }
unsigned short sous_marin::getTaille() const { return VARG::TAILLE_SOUS_MARIN; }
std::string sous_marin::getType() const { return VARG::TYPE_SOUS_MARIN; }

bool sous_marin::getFuseeDispo() const {return false;}
void sous_marin::setFuseePasDispo() {return;}

