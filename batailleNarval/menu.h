#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "fight.h"
#include "console.h"
#include "VARG.h"

class menu
{
private :
	Console* pConsole = NULL;

public : 
	menu();
	~menu();
	void ecranAccueil();
	unsigned short curseur();
	void howToPlay();
};

#endif