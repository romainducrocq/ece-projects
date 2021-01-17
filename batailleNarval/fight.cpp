#include "fight.h"

fight::fight() 
{
	system("cls");
    pConsole = Console::getInstance();
    bool win = false, quit = false;
    unsigned short i = 0;
    Luffy.setPseudo(VARG::CAPTN1);
    Sparrow.setPseudo(VARG::CAPTN2);
    while(win == false && quit == false)
    {
    	pConsole->gotoLigCol(3,5); std::cout << "                              "; pConsole->gotoLigCol(3,45); std::cout << "                              ";
    	i++;
		if(i%2==1)
		{
			if(!Luffy.getTourne())
			{
				pConsole->gotoLigCol(3,5); std::cout << VARG::CAPTN1; pConsole->gotoLigCol(3,45); std::cout << VARG::CAPTN2;
				this->tourDeJeu(Luffy, Sparrow, win, quit); 
			}
			else
			{
				Luffy.setTourne();
				system("mode con LINES=10 COLS=30");
				system("cls");  
				pConsole->gotoLigCol(4,3); std::cout << VARG::CAPTN1 << " :";
				pConsole->gotoLigCol(6,3); std::cout<<"UN CUIRASSE MANOEUVRE";
				unsigned short key = pConsole->getInputKey();
				if(key == ARROW_UP || key == ARROW_BOTTOM || key == ARROW_LEFT || key == ARROW_RIGHT)
					pConsole->getInputKey();
				if(!Sparrow.getTourne())
					system("mode con LINES=50 COLS=80");
			}

		}
		else if(i%2==0)
		{
			if(!Sparrow.getTourne())
			{
			pConsole->gotoLigCol(3,5); std::cout << VARG::CAPTN2; pConsole->gotoLigCol(3,45); std::cout << VARG::CAPTN1;
			this->tourDeJeu(Sparrow, Luffy, win, quit);
			}
			else
			{
				Sparrow.setTourne();
				system("mode con LINES=10 COLS=30");
				system("cls");  
				pConsole->gotoLigCol(4,3); std::cout << VARG::CAPTN2 << " :";
				pConsole->gotoLigCol(6,3); std::cout<<"UN CUIRASSE MANOEUVRE";
				unsigned short key = pConsole->getInputKey();
				if(key == ARROW_UP || key == ARROW_BOTTOM || key == ARROW_LEFT || key == ARROW_RIGHT)
					pConsole->getInputKey();
				if(!Luffy.getTourne())
					system("mode con LINES=50 COLS=80");
			}
		} 
	}
	system("mode con LINES=10 COLS=20");
	system("cls");  
	pConsole->gotoLigCol(4,3); 
	if(win) 
	{
		if(i%2==1)
			std::cout << VARG::CAPTN1 << " WINS !";	
		else if(i%2==0)
			std::cout << VARG::CAPTN2 << " WINS !";	
	}
	else if(quit) 
		std::cout << "EXIT GAME";	

	pConsole->getInputKey();
}
 
fight::~fight() 
{
	Console::deleteInstance();
}

void fight::tourDeJeu(capitaine& captn1, capitaine& captn2, bool& win, bool& quit)
{
	this->affichageGrille(captn1, captn2);
	unsigned short x, y;
	newTry :
	///unsigned short selectBoat = this->deplacerCurseur(captn1, xrm, yrm, 1);
	if(this->deplacerCurseur(captn1, captn2, x, y, false, false))///(selectBoat != VARG::MER )
	{
		switch(this->deplacerFleche(captn1, captn2)) 
		{
		case 1 : ///TURN
		{
			if(captn1.turnBateau(captn1.getCaseGrille(x,y))==false) 
			{	this->affichageCurseur(0,0,x,y,1,false,false);
				this->affichageMenu();
				goto  newTry; }
				break;
		}
		case 2 : ///MOVE
		{
			unsigned short key;
			while((key = pConsole->getInputKey()))
			{
				if(key==224||key==0)
				{
					if(captn1.moveBateau(captn1.getCaseGrille(x,y), key = pConsole->getInputKey())==false) 
						{	this->affichageCurseur(0,0,x,y,1,false,false);
							this->affichageMenu();
							goto newTry; }
					else
						break;
				}
			}
			break;
		case 3 : ///SHOOT
		{
			unsigned short xtmp = x, ytmp = y;
			bool fuseeEclairante = false;

			if(captn1.getBateau(captn1.getCaseGrille(x,y))->getType()==VARG::TYPE_DESTROYER)
				fuseeEclairante = captn1.getBateau(captn1.getCaseGrille(x,y))->getFuseeDispo();

			if(this->deplacerCurseur(captn1, captn2, xtmp, ytmp, true, fuseeEclairante)==false)
				{	this->affichageCurseur(0,0,xtmp,ytmp,captn1.getBateau(captn1.getCaseGrille(x,y))->getPuissance(),true,true);
					this->affichageCurseur(0,0,x,y,1,false,false);
					this->affichageMenu();
					goto newTry; }	
			else if(fuseeEclairante)
			{ 
				unsigned short xDestroyer = x, yDestroyer = y;
				this->affichageCurseur(0,0,xtmp,ytmp,4,true,true);
				this->affichageFuseeEclairante(captn2, xtmp, ytmp);
				captn1.getBateau(captn1.getCaseGrille(x,y))->setFuseePasDispo();

				while(!(this->deplacerCurseur(captn1, captn2, xDestroyer, yDestroyer, true, false))) 
					{	this->affichageCurseur(0,0,xDestroyer,yDestroyer,VARG::PUISSANCE_DESTROYER,true,true);
						xDestroyer = x;
						yDestroyer = y;	}
				captn2.shootBateau(xDestroyer, yDestroyer, VARG::PUISSANCE_DESTROYER, VARG::TYPE_DESTROYER);
				this->affichageCurseur(0,0,xDestroyer,yDestroyer,VARG::PUISSANCE_DESTROYER,true,true);
			}
			else 
			{
				captn2.shootBateau(xtmp, ytmp, captn1.getBateau(captn1.getCaseGrille(x,y))->getPuissance(), captn1.getBateau(captn1.getCaseGrille(x,y))->getType());
				this->affichageCurseur(0,0,xtmp,ytmp,captn1.getBateau(captn1.getCaseGrille(x,y))->getPuissance(),true,true);
			}
			break;   
		} 
		}  
		case 0 :
		{
			this->affichageCurseur(0,0,x,y,1,false,false);
			this->affichageMenu();
			goto newTry;
			break;
		}
		default : 
		break;
	}
	}
	else
	{	quit = true;
		return;		}
	captn1.majGrille(); 
	this->affichageCurseur(0,0,x,y,1,false,false);
	this->affichageGrille(captn1, captn2);
	pConsole->getInputKey();
	win = captn2.isFlotteCoulee();
}

void fight::SAVE(capitaine& captn1, capitaine& captn2)
{
    std::ofstream fileSave("Save.txt", std::ios::trunc);
    if(captn1.getPseudo()==VARG::CAPTN1&&captn2.getPseudo()==VARG::CAPTN2)
    {
    	fileSave << VARG::CAPTN1 << '\n';
    	fileSave << VARG::CAPTN2 << '\n';
    }
    else if(captn1.getPseudo()==VARG::CAPTN2&&captn2.getPseudo()==VARG::CAPTN1)
    {
    	fileSave << VARG::CAPTN2 << '\n';
    	fileSave << VARG::CAPTN1 << '\n';
    }
    fileSave.close();
    captn1.flotteSAVE("DEBUT_FLOTTE_1");
    captn2.flotteSAVE("DEBUT_FLOTTE_2");
}

