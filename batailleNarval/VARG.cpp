#include "VARG.h"

unsigned short VARG::TAILLE_GRILLE = 15;

unsigned short VARG::NB_TYPE_NAVIRES = 4;

unsigned short VARG::NB_CUIRASSES = 1;
unsigned short VARG::NB_CROISEURS = 2;
unsigned short VARG::NB_DESTROYERS = 3;
unsigned short VARG::NB_SOUS_MARINS = 4;

unsigned short VARG::PUISSANCE_CUIRASSE = 3;
unsigned short VARG::PUISSANCE_CROISEUR = 2;
unsigned short VARG::PUISSANCE_DESTROYER = 1;
unsigned short VARG::PUISSANCE_SOUS_MARIN = 1;

unsigned short VARG::TAILLE_CUIRASSE = 7;
unsigned short VARG::TAILLE_CROISEUR = 5;
unsigned short VARG::TAILLE_DESTROYER = 3;
unsigned short VARG::TAILLE_SOUS_MARIN = 1;

std::string VARG::TYPE_CUIRASSE = "CUIRASSE";
std::string VARG::TYPE_CROISEUR = "CROISEUR";
std::string VARG::TYPE_DESTROYER = "DESTROYER";
std::string VARG::TYPE_SOUS_MARIN = "SOUS-MARIN";

bool VARG::VERTICAL = true;
bool VARG::HORIZONTAL = false;

unsigned short VARG::MER = USHRT_MAX;

bool VARG::SAVE = false;
bool VARG::SAVE_SWITCH_FLOTTE = false;

std::string VARG::CAPTN1 = "";
std::string VARG::CAPTN2 = "";

