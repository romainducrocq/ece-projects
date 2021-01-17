#ifndef FIGHT_H_INCLUDED
#define FIGHT_H_INCLUDED

#include "capitaine.h"
#include "console.h"
#include "VARG.h"

class fight
{
	private :
		Console* pConsole = NULL;
		capitaine Luffy, Sparrow;

		
	public : 
	fight();
	~fight();

	void affichageGrille(capitaine& captn1, capitaine& captn2);
	void affichageMenu();
	void affichageCurseur(unsigned short x, unsigned short y, unsigned short xrm, unsigned short yrm, unsigned short taille, bool shoot, bool justErase);
	bool deplacerCurseur(capitaine& captn1, capitaine& captn2, unsigned short& x, unsigned short& y, bool shoot, bool fuseeEclairante);
	unsigned short deplacerFleche(capitaine& captn1, capitaine& captn2);
	void tourDeJeu(capitaine& captn1, capitaine& captn2, bool& win, bool& quit);
	void SAVE(capitaine& captn1, capitaine& captn2);

	void affichageFuseeEclairante(capitaine& captn2, unsigned short x, unsigned short y);
};

inline void fight::affichageGrille(capitaine& captn1, capitaine& captn2/*, unsigned short x0, unsigned short y0*/)
{

	unsigned short x0 = 5, y0 = 5;

	for(unsigned short i = 0; i < VARG::TAILLE_GRILLE; i++)
    {
		for(unsigned short j = 0; j < VARG::TAILLE_GRILLE; j++)
        {
        	if(captn1.getCaseGrille(j,i)==VARG::MER)
        		pConsole->setColor(_COLOR_BLUE_GREY);
			else
			{
			if((captn1.getBateau(captn1.getCaseGrille(j,i))->getOrientation() == VARG::HORIZONTAL && captn1.getBateau(captn1.getCaseGrille(j,i))->getTouche(j - captn1.getBateau(captn1.getCaseGrille(j,i))->getX(0))==true)
        	||(captn1.getBateau(captn1.getCaseGrille(j,i))->getOrientation() == VARG::VERTICAL && captn1.getBateau(captn1.getCaseGrille(j,i))->getTouche(i - captn1.getBateau(captn1.getCaseGrille(j,i))->getY(0))==true))
        			pConsole->setColor(_COLOR_DEFAULT);
			else if(captn1.getBateau(captn1.getCaseGrille(j,i))->getType() == VARG::TYPE_CUIRASSE)
        		pConsole->setColor(_COLOR_PURPLE_RED);
        	else if(captn1.getBateau(captn1.getCaseGrille(j,i))->getType() == VARG::TYPE_CROISEUR)
        		pConsole->setColor(_COLOR_KAKI);
        	else if(captn1.getBateau(captn1.getCaseGrille(j,i))->getType() == VARG::TYPE_DESTROYER)
        		pConsole->setColor(_COLOR_BROWN);
        	else if(captn1.getBateau(captn1.getCaseGrille(j,i))->getType() == VARG::TYPE_SOUS_MARIN)
        		pConsole->setColor(_COLOR_YELLOW);
        	else
        		pConsole->setColor(_COLOR_DEFAULT);
        	}
			pConsole->gotoLigCol(y0 + i*2, x0 + j*2); 
			std::cout << (unsigned char) 219 ;
		}
	}


	for(unsigned short i = 0; i < VARG::TAILLE_GRILLE; i++)
    {
		for(unsigned short j = 0; j < VARG::TAILLE_GRILLE; j++)
        {
        	if(captn2.getCaseGrille(j,i)==VARG::MER)
        		pConsole->setColor(_COLOR_BLUE_GREY);
        	else 
        	{
        		if((captn2.getBateau(captn2.getCaseGrille(j,i))->getOrientation() == VARG::HORIZONTAL && captn2.getBateau(captn2.getCaseGrille(j,i))->getTouche(j - captn2.getBateau(captn2.getCaseGrille(j,i))->getX(0))==false)
        		||(captn2.getBateau(captn2.getCaseGrille(j,i))->getOrientation() == VARG::VERTICAL && captn2.getBateau(captn2.getCaseGrille(j,i))->getTouche(i - captn2.getBateau(captn2.getCaseGrille(j,i))->getY(0))==false))
        			pConsole->setColor(_COLOR_BLUE_GREY);
        		else 
        			pConsole->setColor(_COLOR_DEFAULT);
        	}
        	pConsole->gotoLigCol(y0 + i*2, x0 + j*2 + 40); 
			std::cout << (unsigned char) 219 ;	
        }
    }

	pConsole->setColor(_COLOR_PURPLE_RED);
	pConsole->gotoLigCol(36, 24); std::cout << VARG::TYPE_CUIRASSE ;
	pConsole->setColor(_COLOR_KAKI);
	pConsole->gotoLigCol(38, 24); std::cout << VARG::TYPE_CROISEUR ;
	pConsole->setColor(_COLOR_BROWN);
	pConsole->gotoLigCol(40, 24); std::cout << VARG::TYPE_DESTROYER ;
	pConsole->setColor(_COLOR_YELLOW);
	pConsole->gotoLigCol(42, 24); std::cout << VARG::TYPE_SOUS_MARIN;
	pConsole->setColor(_COLOR_DEFAULT);


	affichageMenu();

	pConsole->gotoLigCol(39, 50); 
	std::cout<<"SAVE GAME : SPACE BAR";
} 

inline void fight::affichageMenu()
{
	pConsole->setColor(_COLOR_DEFAULT);

	pConsole->gotoLigCol(36, 5);std::cout<<"***************";
	pConsole->gotoLigCol(37, 5);std::cout<<"*             *";
	pConsole->gotoLigCol(38, 5);std::cout<<"*    TURN     *";
	pConsole->gotoLigCol(39, 5);std::cout<<"*    MOVE     *";
	pConsole->gotoLigCol(40, 5);std::cout<<"*    SHOOT    *";
	pConsole->gotoLigCol(41, 5);std::cout<<"*             *";
	pConsole->gotoLigCol(42, 5);std::cout<<"***************";
}

inline unsigned short fight::deplacerFleche(capitaine& captn1, capitaine& captn2)
{
	unsigned short key, i = 0;
	pConsole->gotoLigCol(38, 7); std::cout<<">>";
	pConsole->gotoLigCol(38, 16); std::cout<<"<<";

	while((key = pConsole->getInputKey()) != ESC)
	{
		if(key==224||key==0)
		{
		switch(key = pConsole->getInputKey())
		{
			case ARROW_UP :
			{
				if(i>0)
				{
					pConsole->gotoLigCol(38 + i, 7); std::cout<<"  ";
					pConsole->gotoLigCol(38 + i, 16); std::cout<<"  ";

					i--;

					pConsole->gotoLigCol(38 + i, 7); std::cout<<">>";
					pConsole->gotoLigCol(38 + i, 16); std::cout<<"<<";
				}
				break;
			}
			case ARROW_BOTTOM :
			{
				if(i<2)
				{
					pConsole->gotoLigCol(38 + i, 7); std::cout<<"  ";
					pConsole->gotoLigCol(38 + i, 16); std::cout<<"  ";


					i++;

					pConsole->gotoLigCol(38 + i, 7); std::cout<<">>";
					pConsole->gotoLigCol(38 + i, 16); std::cout<<"<<";
				}
				break;
			}
			default :
			break;
		}
	}
	else if(key == ENTER)
		return i+1;
	else if(key == SPACE)
		{
			SAVE(captn1, captn2);
			pConsole->gotoLigCol(39, 50);std::cout<<"SAVE GAME : COMPLETE ";
			pConsole->getInputKey();
			pConsole->gotoLigCol(39, 50);std::cout<<"SAVE GAME : SPACE BAR";
		}
}
return 0;
}

inline void fight::affichageCurseur(unsigned short x, unsigned short y, unsigned short xrm, unsigned short yrm, unsigned short taille, bool shoot, bool justErase)
{
	unsigned short x0 = 5, y0 = 5;
	if(shoot)
		x0+=40;

	pConsole->setColor(_COLOR_BLACK);
for(unsigned short i = 0; i<taille; i++)
{

	pConsole->gotoLigCol(yrm*2+y0-1, xrm*2+x0+i*2); std::cout << (unsigned char) 219 ; ///h
	pConsole->gotoLigCol(yrm*2+y0+i*2, xrm*2+x0-1); std::cout << (unsigned char) 219 ; ///g
	pConsole->gotoLigCol(yrm*2+y0+i*2, xrm*2+x0+1+(taille-1)*2); std::cout << (unsigned char) 219 ; ///d 
	pConsole->gotoLigCol(yrm*2+y0+1+(taille-1)*2, xrm*2+x0+i*2); std::cout << (unsigned char) 219 ; ///b
}

	pConsole->gotoLigCol(yrm*2+y0-1, xrm*2+x0-1); std::cout << (unsigned char) 219 ;
	pConsole->gotoLigCol(yrm*2+y0-1, xrm*2+x0+1+(taille-1)*2); std::cout << (unsigned char) 219 ;
	pConsole->gotoLigCol(yrm*2+y0+1+(taille-1)*2, xrm*2+x0-1); std::cout << (unsigned char) 219 ;
	pConsole->gotoLigCol(yrm*2+y0+1+(taille-1)*2, xrm*2+x0+1+(taille-1)*2); std::cout << (unsigned char) 219 ;
	pConsole->setColor(_COLOR_DEFAULT);

if(!justErase)
{
	pConsole->setColor(_COLOR_RED);


for(unsigned short i = 0; i<taille; i++)
{
	pConsole->gotoLigCol(y*2+y0-1, x*2+x0+i*2); std::cout << (unsigned char) 194 ; ///h
	pConsole->gotoLigCol(y*2+y0+i*2, x*2+x0-1); std::cout << (unsigned char) 195 ; ///g
	pConsole->gotoLigCol(y*2+y0+i*2, x*2+x0+1+(taille-1)*2); std::cout << (unsigned char) 180 ;  ///d
	pConsole->gotoLigCol(y*2+y0+1+(taille-1)*2, x*2+x0+i*2); std::cout << (unsigned char) 193 ;  ///b
}

pConsole->gotoLigCol(y*2+y0-1, x*2+x0-1); std::cout << (unsigned char) 218 ; ///hg
pConsole->gotoLigCol(y*2+y0-1, x*2+x0+1+(taille-1)*2); std::cout << (unsigned char) 191 ; ///hd
pConsole->gotoLigCol(y*2+y0+1+(taille-1)*2, x*2+x0-1); std::cout << (unsigned char) 192 ; ///bg
pConsole->gotoLigCol(y*2+y0+1+(taille-1)*2, x*2+x0+1+(taille-1)*2); std::cout << (unsigned char) 217 ; ///bd

}

	pConsole->setColor(_COLOR_DEFAULT);

}

inline bool fight::deplacerCurseur(capitaine& captn1, capitaine& captn2, unsigned short& x, unsigned short& y, bool shoot, bool fuseeEclairante)
{
	unsigned short key, xrm = 0, yrm = 0, taille;
	if(shoot&&fuseeEclairante)
		taille = 4;
	else if(shoot&&!fuseeEclairante)
		taille = captn1.getBateau(captn1.getCaseGrille(x,y))->getPuissance();
	else 
		taille = 1;
	x = 0, y = 0;
	affichageCurseur(x, y, xrm, yrm, taille, shoot, false);

	while((key = pConsole->getInputKey()) != ESC)
	{
		if(key==224||key==0)
		{
		xrm = x;
		yrm = y;	
		switch(key = pConsole->getInputKey())
		{
			case ARROW_UP :
			{
				if(y>0)
				{
					y--;
					affichageCurseur(x, y, xrm, yrm, taille, shoot, false);
				}
				break;
			}
			case ARROW_BOTTOM :
			{
				if(y<VARG::TAILLE_GRILLE-taille)
				{
					y++;
					affichageCurseur(x, y, xrm, yrm, taille, shoot, false);
				}
				break;
			}
			case ARROW_LEFT :
			{
				if(x>0)
				{
					x--;
					affichageCurseur(x, y, xrm, yrm, taille, shoot, false);
				}
				break;
			}
			case ARROW_RIGHT :
			{
				if(x<VARG::TAILLE_GRILLE-taille)
				{
					x++;
					affichageCurseur(x, y, xrm, yrm, taille, shoot, false);
				}
				break;
			}
			default :
			break;	
		}
		}
		else if(key == ENTER)
		{
			if(shoot)
				return true; 
			else if(captn1.getCaseGrille(x,y)!=VARG::MER && captn1.getBateau(captn1.getCaseGrille(x,y))->getToucheCoule()==false && shoot==false)
				return true;
		}
		else if(key == SPACE)
		{
			SAVE(captn1, captn2);
			pConsole->gotoLigCol(39, 50);std::cout<<"SAVE GAME : COMPLETE ";
			pConsole->getInputKey();
			pConsole->gotoLigCol(39, 50);std::cout<<"SAVE GAME : SPACE BAR";
		}
	}
	return false; ///VARG::MER;
}

inline void fight::affichageFuseeEclairante(capitaine& captn2, unsigned short x, unsigned short y)
{
	for(unsigned short j = 0; j < 4; j++)
    {
		for(unsigned short i = 0; i < 4; i++)
        {
        	if(captn2.getCaseGrille(x+j,y+i)==VARG::MER)
        		pConsole->setColor(_COLOR_BLUE_GREY);
			else
			{
			if((captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getOrientation() == VARG::HORIZONTAL && captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getTouche(x+j - captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getX(0))==true)
        	||(captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getOrientation() == VARG::VERTICAL && captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getTouche(y+i - captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getY(0))==true))
        			pConsole->setColor(_COLOR_DEFAULT);
			else if(captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getType() == VARG::TYPE_CUIRASSE)
        		pConsole->setColor(_COLOR_PURPLE_RED);
        	else if(captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getType() == VARG::TYPE_CROISEUR)
        		pConsole->setColor(_COLOR_KAKI);
        	else if(captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getType() == VARG::TYPE_DESTROYER)
        		pConsole->setColor(_COLOR_BROWN);
        	else if(captn2.getBateau(captn2.getCaseGrille(x+j,y+i))->getType() == VARG::TYPE_SOUS_MARIN)
        		pConsole->setColor(_COLOR_YELLOW);
        	else
        		pConsole->setColor(_COLOR_DEFAULT);
        	}
			pConsole->gotoLigCol(5 + (y+i)*2, 45 + (x+j)*2); 
			std::cout << (unsigned char) 219 ;
		}
	}
}

#endif
