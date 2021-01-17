#ifndef VARG_H_INCLUDED
#define VARG_H_INCLUDED

#include <fstream>
#include <climits>

struct VARG ///variables globales
{
	static unsigned short TAILLE_GRILLE;

	static unsigned short NB_TYPE_NAVIRES;

	static unsigned short NB_CUIRASSES;
	static unsigned short NB_CROISEURS;
	static unsigned short NB_DESTROYERS;
	static unsigned short NB_SOUS_MARINS;

	static unsigned short PUISSANCE_CUIRASSE;
	static unsigned short PUISSANCE_CROISEUR;
	static unsigned short PUISSANCE_DESTROYER;
	static unsigned short PUISSANCE_SOUS_MARIN;

	static unsigned short TAILLE_CUIRASSE;
	static unsigned short TAILLE_CROISEUR;
	static unsigned short TAILLE_DESTROYER;
	static unsigned short TAILLE_SOUS_MARIN;

	static std::string TYPE_CUIRASSE;
	static std::string TYPE_CROISEUR;
	static std::string TYPE_DESTROYER;
	static std::string TYPE_SOUS_MARIN;

	static bool VERTICAL;
	static bool HORIZONTAL;

	static unsigned short MER;

	static bool SAVE;
	static bool SAVE_SWITCH_FLOTTE;

	static std::string CAPTN1;
	static std::string CAPTN2;
};

#endif
