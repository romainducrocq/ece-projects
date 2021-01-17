#include "wallet.h"
#include<sstream>
#include<math.h>

wallet::wallet()
: A(800,600,32), m_date(1), m_liquidites(0), m_capital(0), m_tabPoids(0), m_nbActionN(0), m_tabActions(0), m_tabActionsDispos(0), m_tabActionsDisposPoids(0)
{}

wallet::~wallet()
{
    A.DeInit();
}

//////////////////////////////////////////MENUS

bool wallet::Go()
{
    if (A.Init())
    {
        return true;
    }
    return false;
}

void wallet::Appli()
{
    if(EnterDate())
    {
        GetListAction();
        GetAllAction();
        GetListActionsDispos();
        GetListActionsDisposPoids();
        GetLiquidites();
        GetCapital();
        Menu();
    }
}

bool wallet::EnterDate()
{
    InitScreen();
    while(true)
    {
        if (A.De4dMouse(SCREEN_W/2,SCREEN_H/2,(SCREEN_W/2)+50,(SCREEN_H/2)+50)==true)
        {
            m_date++;
            if (m_date>31)
                m_date=1;
            InitScreen();
            REST();
        }
        if (A.De4dMouse((SCREEN_W/2)-50,SCREEN_H/2,SCREEN_W/2,(SCREEN_H/2)+50)==true)
        {
            m_date=m_date+10;
            if (m_date>31)
                m_date=1;
            InitScreen();
            REST();
        }
        if (A.De4dMouse(SCREEN_W/2,(SCREEN_H/2)+55,(SCREEN_W/2)+50,(SCREEN_H/2)+105)==true)
        {
            m_date--;
            if (m_date<1)
                m_date=31;
            InitScreen();
            REST();
        }
        if (A.De4dMouse((SCREEN_W/2)-50,(SCREEN_H/2)+55,SCREEN_W/2,(SCREEN_H/2)+105)==true)
        {
            m_date=m_date-10;
            if (m_date<1)
                m_date=31;
            InitScreen();
            REST();
        }

        if (A.De4dMouse(325,435,475,500)==true)
        {
            REST();
            return true;
        }
        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
            return false;
    }
}

void wallet::Menu()
{
    MainScreen();
    while(true)
    {
        if (A.De4dMouse(275,175,525,260)==true)
        {
            REST();
            ActionMenu();
            MainScreen();
        }

        if (A.De4dMouse(250,315,550,415)==true)
        {
            REST();
            ReequilibrageMenu();
            MainScreen();
        }
        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
        {
            REST();
            return;
        }

    }
}

void wallet::ActionMenu()
{
    ActionMenuScreen();
while(true)
    {
        if (A.De4dMouse(250,(SCREEN_H / 4)-35,550,(SCREEN_H / 4)+65)==true)
        {
            REST();
            LiquiditesMenu();
            ActionMenuScreen();
        }

        if (A.De4dMouse(250,2*(SCREEN_H / 4)-35,550,2*(SCREEN_H / 4)+65)==true)
        {
            REST();
            ActionDisplayMenu();
            ActionMenuScreen();
        }

        if (A.De4dMouse(150,3*(SCREEN_H / 4)-35,650,3*(SCREEN_H / 4)+65)==true)
        {
            REST();
            GererActionsMenu();
            ActionMenuScreen();
        }

        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
           {
               REST();
               return;
           }
    }
}

void wallet::ActionDisplayMenu()
{
    bool total=false;
    ActionScreen(false, total);
    while(true)
    {
        if(A.De4dMouse((SCREEN_W/2)-25,SCREEN_H-50,(SCREEN_W/2)+25,SCREEN_H)==true)
        {
            REST();
            if(total==true)
                total=false;
            else
                total=true;
            ActionScreen(false, total);
        }

        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
        {
            REST();
            return;
        }
    }
}

void wallet::LiquiditesMenu()
{
    int LiquidModif = 0;
    LiquiditesMenuScreen(LiquidModif);
while(true)
    {
     for (int i=0; i<6; i++)
        {
            if (A.De4dMouse((SCREEN_W/2)-150+(i*50),(SCREEN_H / 2)-100,(SCREEN_W/2)-150+((i+1)*50),(SCREEN_H / 2)-50)==true)
        {
            LiquidModif = LiquidModif + PUISSANCE10(5-i);
            if (LiquidModif+m_capital>1000000)
                LiquidModif=1000000-m_capital;
            LiquiditesMenuScreen(LiquidModif);
            REST();
            break;
        }
            if (A.De4dMouse((SCREEN_W/2)-150+(i*50),(SCREEN_H / 2)-45,(SCREEN_W/2)-150+((i+1)*50),(SCREEN_H / 2)+5)==true)
        {
            LiquidModif = LiquidModif - PUISSANCE10(5-i);
            if (m_liquidites+LiquidModif<0)
                LiquidModif=0-m_liquidites;
            LiquiditesMenuScreen(LiquidModif);
            REST();
            break;
        }
        }

        if (A.De4dMouse(325,470,475,535)==true)
        {
            REST();
            if (LiquidModif!=0)
            {
                m_liquidites = m_liquidites+LiquidModif;
                SetFileActionsNombres();
                GetCapital();
            }
            return;
        }

        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
           {
               REST();
               return;
           }
    }
}

void wallet::GererActionsMenu()
{
      GererActionsMenuScreen();
while(true)
    {
        if (A.De4dMouse(275,(SCREEN_H / 3)-35,525,(SCREEN_H / 3)+65)==true)
        {
            REST();
            ActionsDisposChoiceMenu();
            GererActionsMenuScreen();
        }


        if (A.De4dMouse(275,(2*(SCREEN_H / 3))-35,525,(2*(SCREEN_H / 3))+65)==true)
        {
            REST();
            ActionDisplayChoiceMenu();
            GererActionsMenuScreen();
        }

        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
           {
               REST();
               return;
           }
}
}

void wallet::ActionsDisposChoiceMenu()
{
    ActionsDisposChoiceMenuScreen();
while(true)
    {
        if (A.De4dMouse(275,(SCREEN_H / 3)-35,525,(SCREEN_H / 3)+65)==true)
        {
            REST();
            ActionsDisposADDMenu();
            ActionsDisposChoiceMenuScreen();
        }


        if (A.De4dMouse(275,(2*(SCREEN_H / 3))-35,525,(2*(SCREEN_H / 3))+65)==true)
        {
            REST();
            ActionsDisposREMOVEMenu();
            ActionsDisposChoiceMenuScreen();
        }

        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
           {
               REST();
               return;
           }
    }
}

void wallet::ActionsDisposADDMenu()
{
    bool ajouter=true;
    std::vector<std::string> ActionsDisposModif(0);
    ActionsDisposADDMenuScreen(ActionsDisposModif);
    while(true)
    {
        for(unsigned int i = 0; i<m_tabActionsDispos.size(); i++)
        {
           if (A.De4dMouse((SCREEN_W / 6)-50, 50+((SCREEN_H-200)/m_tabActionsDispos.size())*i,(SCREEN_W / 6)-20,80+((SCREEN_H-200)/m_tabActionsDispos.size())*i)==true)
        {
                ajouter=true;
                for(unsigned int j = 0; j<ActionsDisposModif.size(); j++)
                {
                    if(m_tabActionsDispos[i]==ActionsDisposModif[j])
                    {
                    ActionsDisposModif.erase(ActionsDisposModif.begin()+j);
                    ajouter=false;
                    break;
                    }
                }
                if(ajouter==true)
                    ActionsDisposModif.push_back(m_tabActionsDispos[i]);
            ActionsDisposADDMenuScreen(ActionsDisposModif);
            REST();
            }
            }

            if (A.De4dMouse(325,520,475,585)==true)
            {
                REST();
                if (!ActionsDisposModif.empty())
                {
                    for(unsigned int i = 0; i<ActionsDisposModif.size(); i++)
                    {
                        m_tabActions.push_back(ActionsDisposModif[i]);
                        m_nbActionN.push_back(0);
                    }
                    SetFileActions();
                    SetFileActionsNombres();
                    GetListAction();
                    GetAllAction();
                    GetListActionsDispos();
                    GetListActionsDisposPoids();
                    GetLiquidites();
                    GetCapital();
                }
            return;
            }
        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
           {
               REST();
               return;
           }
    }
}

void wallet::ActionsDisposREMOVEMenu()
{
    bool ajouter=true;
    std::vector<std::string> ActionsModif(0);
    ActionsDisposREMOVEMenuScreen(ActionsModif);
    while(true)
    {
        for(unsigned int i = 0; i<m_tabActions.size(); i++)
        {
           if (A.De4dMouse((SCREEN_W / 6)-50, 50+((SCREEN_H-200)/m_tabActions.size())*i, (SCREEN_W / 6)-20, 80+((SCREEN_H-200)/m_tabActions.size())*i)==true)
        {
            ajouter=true;
                for(unsigned int j = 0; j<ActionsModif.size(); j++)
                {
                    if(m_tabActions[i]==ActionsModif[j])
                    {
                    ActionsModif.erase(ActionsModif.begin()+j);
                    ajouter=false;
                    break;
                    }
                }
                if(ajouter==true)
                    ActionsModif.push_back(m_tabActions[i]);
            ActionsDisposREMOVEMenuScreen(ActionsModif);
            REST();
        }
        }

        if (A.De4dMouse(325,520,475,585)==true)
            {
                REST();
                if (!ActionsModif.empty())
                {
                    for(unsigned int i = 0; i<ActionsModif.size(); i++)
                    {
                        for(unsigned int j =0; j<m_tabActions.size(); j++)
                        {
                            if(ActionsModif[i]==m_tabActions[j])
                            {
                                m_liquidites=m_liquidites+(m_tabPoids[j]*m_nbActionN[j]);
                                m_tabActions.erase(m_tabActions.begin()+j);
                                m_tabPoids.erase(m_tabPoids.begin()+j);
                                m_nbActionN.erase(m_nbActionN.begin()+j);
                            }
                        }
                    }

                    SetFileActions();
                    SetFileActionsNombres();
                    GetListAction();
                    GetAllAction();
                    GetListActionsDispos();
                    GetListActionsDisposPoids();
                    GetLiquidites();
                    GetCapital();
                }
            return;
            }
        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
           {
               REST();
               return;
           }
    }

}

void wallet::ActionDisplayChoiceMenu()
{
    bool total = false;
    ActionScreen(true, total);
    while(true)
    {
        if(A.De4dMouse((SCREEN_W/2)-25,SCREEN_H-50,(SCREEN_W/2)+25,SCREEN_H)==true)
        {
            REST();
            if(total==true)
                total=false;
            else
                total=true;
            ActionScreen(true, total);
        }

        for(unsigned int i = 0; i<m_tabActions.size(); i++)
        {
            if (A.De4dMouse((SCREEN_W / 6)-50,50+((SCREEN_H-50)/m_tabActions.size())*i,(SCREEN_W / 6)-20,80+((SCREEN_H-50)/m_tabActions.size())*i)==true)
            {
                REST();
                ActionChangeQuantityMenu(i);
                ActionScreen(true, total);
                break;
            }
        }
        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
           {
               REST();
               return;
           }
    }
}

void wallet::ActionChangeQuantityMenu(int k)
{
    int ModifNbActions=0;
    ActionChangeQuantityMenuScreen(ModifNbActions, k);
    while(true)
    {
        for (int i=0; i<4; i++)
        {
            if (A.De4dMouse((SCREEN_W/2)-100+(i*50),(SCREEN_H / 2)-100,(SCREEN_W/2)-100+((i+1)*50),(SCREEN_H / 2)-50)==true)
        {
            ModifNbActions = ModifNbActions + pow(10,(3-i));
            if (((ModifNbActions+m_nbActionN[k])*m_tabPoids[k])>m_liquidites)
                ModifNbActions=(m_liquidites/m_tabPoids[k])-m_nbActionN[k];
            ActionChangeQuantityMenuScreen(ModifNbActions, k);
            REST();
            break;
        }
            if (A.De4dMouse((SCREEN_W/2)-100+(i*50),(SCREEN_H / 2)-45,(SCREEN_W/2)-100+((i+1)*50),(SCREEN_H / 2)+5)==true)
        {
            ModifNbActions = ModifNbActions - pow(10,(3-i));
            if (ModifNbActions+m_nbActionN[k]<0)
                ModifNbActions=0-m_nbActionN[k];
            ActionChangeQuantityMenuScreen(ModifNbActions, k);
            REST();
            break;
        }
        }

        if (A.De4dMouse(325,470,475,535)==true)
        {
            REST();
            if (ModifNbActions!=0)
            {
                m_nbActionN[k] = m_nbActionN[k]+ModifNbActions;
                m_liquidites = m_liquidites-(ModifNbActions*m_tabPoids[k]);
                SetFileActions();
                SetFileActionsNombres();
                GetListAction();
                GetAllAction();
                GetLiquidites();
                GetCapital();
            }
            return;
        }

        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
           {
               REST();
               return;
           }
    }
}

void wallet::ReequilibrageMenu()
{
    int PLiqu = 25;
    ReequilibrageMenuScreen(PLiqu);
    while(true)
    {
        for (int i=0; i<2; i++)
        {
            if (A.De4dMouse((SCREEN_W/2)-50+(i*50),(SCREEN_H/2),(SCREEN_W/2)-50+((i+1)*50),(SCREEN_H / 2)+50)==true)
        {
            PLiqu = PLiqu + PUISSANCE10(1-i);
            if (PLiqu>100)
                PLiqu=100;
            ReequilibrageMenuScreen(PLiqu);
            REST();
            break;
        }
            if (A.De4dMouse((SCREEN_W/2)-50+(i*50),(SCREEN_H / 2)+55,(SCREEN_W/2)-50+((i+1)*50),(SCREEN_H / 2)+105)==true)
        {
            PLiqu = PLiqu - PUISSANCE10(1-i);
            if (PLiqu<0)
                PLiqu=0;
            ReequilibrageMenuScreen(PLiqu);
            REST();
            break;
        }
        }

        if (A.De4dMouse(100,470,700,535)==true)
        {
            REST();
            REEQUILIBRAGE(PLiqu);
            ActionDisplayMenu();
            return;
        }

        if (A.De4dMouse(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H)==true)
           {
               REST();
               return;
           }
    }

}

////////////////////////////////////////ECRANS

void wallet::InitScreen()
{
        DEFAULTBACKGROUND();
        A.Texte(2, "PORTE-FEUILLE INTELLIGENT", SCREEN_W / 2, 50, BLACK, -1, true);
        A.Texte(2, "VEUILLEZ ENTRER LA DATE DU JOUR :", SCREEN_W / 2, 150, BLACK, -1, true);
        A.Texte(2, intToSTring(m_date) + " / 05 / 2016", SCREEN_W / 2, (SCREEN_H / 2)-50, BLACK, -1, true);
        PLUSMOINS(SCREEN_W/2, SCREEN_H/2, 50, 15, 2);
        BUTTON(325,435,475,500);
        A.Texte(2, "OK", SCREEN_W / 2, 450, BLACK, -1, true);
        A.Graphic();
}

void wallet::MainScreen()
{
        DEFAULTBACKGROUND();
        A.Texte(2, "PORTE-FEUILLE INTELLIGENT", SCREEN_W / 2, 50, BLACK, -1, true);
        BUTTON(275,175,525,260);
        A.Texte(2, "ACTIONS", SCREEN_W / 2, 200, BLACK, -1, true);
        BUTTON(250,315,550,415);
        A.Texte(2, "REEQUILIBRAGE", SCREEN_W / 2, 350, BLACK, -1, true);
        A.Texte(2, "CAPITAL : " + intToSTring(m_capital) + " EUROS", SCREEN_W / 2, 500, BLACK, -1, true);
        A.Texte(2, "LIQUIDITES : " + intToSTring(m_liquidites) + " EUROS", SCREEN_W / 2, 550, BLACK, -1, true);
        A.Graphic();
}

void wallet::ActionMenuScreen()
{
        DEFAULTBACKGROUND();
        BUTTON(250,(SCREEN_H / 4)-35,550,(SCREEN_H / 4)+65);
        A.Texte(2, "LIQUIDITES", SCREEN_W / 2, SCREEN_H / 4, BLACK, -1, true);
        BUTTON(250,2*(SCREEN_H / 4)-35,550,2*(SCREEN_H / 4)+65);
        A.Texte(2, "MES ACTIONS", SCREEN_W / 2, 2*(SCREEN_H / 4), BLACK, -1, true);
        BUTTON(150,3*(SCREEN_H / 4)-35,650,3*(SCREEN_H / 4)+65);
        A.Texte(2, "GERER MES ACTIONS", SCREEN_W / 2, 3*(SCREEN_H / 4), BLACK, -1, true);
        A.Graphic();
}

void wallet::ActionScreen(bool choice, bool total)
{
        DEFAULTBACKGROUND();
        A.Texte(2, "ACTIONS", SCREEN_W / 6, 10, BLACK, -1, true);
        for(unsigned int i = 0; i<m_tabActions.size(); i++)
        {
            A.Texte(1, m_tabActions[i], SCREEN_W / 6,50+((SCREEN_H-50)/m_tabActions.size())*i, BLACK, -1, false);
        }

        if(total==false)
        {
            A.Texte(2, "VALEURS", (SCREEN_W/2)+(SCREEN_W/3), 10, BLACK, -1, true);
            A.Texte(2, "QUANTITES", (SCREEN_W/2)+(SCREEN_W/10), 10, BLACK, -1, true);
            for(unsigned int i = 0; i<m_tabActions.size(); i++)
            {
                A.Texte(1, intToSTring(m_tabPoids[i]) + " E",(SCREEN_W/2)+(SCREEN_W/3),50+((SCREEN_H-50)/m_tabActions.size())*i, BLACK, -1, true);
            }
            for(unsigned int i = 0; i<m_tabActions.size(); i++)
            {
                A.Texte(1, intToSTring(m_nbActionN[i]),(SCREEN_W/2)+(SCREEN_W/10),50+((SCREEN_H-50)/m_tabActions.size())*i, BLACK, -1, true);
            }
        }
        if(total==true)
        {
            A.Texte(2, "TOTAUX", (SCREEN_W/2)+(SCREEN_W / 6), 10, BLACK, -1, true);
            for(unsigned int i = 0; i<m_tabActions.size(); i++)
            {
            A.Texte(1, intToSTring(m_nbActionN[i]*m_tabPoids[i]) + " EUROS",(SCREEN_W/2)+(SCREEN_W / 6),50+((SCREEN_H-50)/m_tabActions.size())*i, BLACK, -1, false);
            }
        }

        if(choice==true)
        {
            for(unsigned int i = 0; i<m_tabActions.size(); i++)
        {
            A.Rectangle((SCREEN_W / 6)-50,50+((SCREEN_H-50)/m_tabActions.size())*i,(SCREEN_W / 6)-20,80+((SCREEN_H-50)/m_tabActions.size())*i,BLACK,true);
            A.Rectangle((SCREEN_W / 6)-45,55+((SCREEN_H-50)/m_tabActions.size())*i,(SCREEN_W / 6)-25,75+((SCREEN_H-50)/m_tabActions.size())*i,BLUE,true);
        }
        }
         A.Rectangle((SCREEN_W/2)-25,SCREEN_H-50,(SCREEN_W/2)+25,SCREEN_H,BLACK,true);
         A.Cercle(SCREEN_W/2,SCREEN_H-25,15,BLUE,1);
         A.Graphic();
}

void wallet::LiquiditesMenuScreen(int ModifLiquidites)
{
        DEFAULTBACKGROUND();
        A.Texte(2, "LIQUIDITES : " + intToSTring(m_liquidites) + " EUROS", SCREEN_W / 2, 50, BLACK, -1, true);
        A.Texte(2, "MODIFIER DE : " + intToSTring(ModifLiquidites) + " EUROS", SCREEN_W / 2, (SCREEN_H / 2)-150, BLACK, -1, true);
        PLUSMOINS(SCREEN_W/2, (SCREEN_H / 2)-100, 50, 15, 6);
        A.Texte(2, "NOUVELLES LIQUIDITES : ", SCREEN_W / 2, (SCREEN_H / 2)+50, BLACK, -1, true);
        A.Texte(2,intToSTring(m_liquidites + ModifLiquidites) + " EUROS ?", SCREEN_W / 2, (SCREEN_H / 2)+100, BLACK, -1, true);
        BUTTON(325,470,475,535);
        A.Texte(2, "OK", SCREEN_W / 2, 485, BLACK, -1, true);
        A.Texte(2, "CAPITAL : " + intToSTring(ModifLiquidites+m_capital) + " EUROS", SCREEN_W / 2, (SCREEN_H / 2)+250, BLACK, -1, true);
        A.Graphic();
}

void wallet::GererActionsMenuScreen()
{
        DEFAULTBACKGROUND();
        BUTTON(275,(SCREEN_H / 3)-35,525,(SCREEN_H / 3)+65);
        A.Texte(2, "DOMAINES", SCREEN_W / 2, SCREEN_H / 3, BLACK, -1, true);
        BUTTON(275,(2*(SCREEN_H / 3))-35,525,(2*(SCREEN_H / 3))+65);
        A.Texte(2, "QUANTITES", SCREEN_W / 2, 2*(SCREEN_H / 3), BLACK, -1, true);
        A.Graphic();
}

void wallet::ActionsDisposChoiceMenuScreen()
{
        DEFAULTBACKGROUND();
        BUTTON(275,(SCREEN_H / 3)-35,525,(SCREEN_H / 3)+65);
        A.Texte(2, "AJOUTER", SCREEN_W / 2, SCREEN_H / 3, BLACK, -1, true);
        BUTTON(275,(2*(SCREEN_H / 3))-35,525,(2*(SCREEN_H / 3))+65);
        A.Texte(2, "SUPPRIMER", SCREEN_W / 2, 2*(SCREEN_H / 3), BLACK, -1, true);
        A.Graphic();
}

void wallet::ActionsDisposADDMenuScreen(std::vector<std::string> ActionsDisposModif)
{
        DEFAULTBACKGROUND();
        A.Texte(2, "ACTIONS", SCREEN_W / 6, 10, BLACK, -1, true);
        A.Texte(2, "VALEURS", (SCREEN_W / 2) + (SCREEN_W / 3), 10, BLACK, -1, true);
        for(unsigned int i = 0; i<m_tabActionsDispos.size(); i++)
        {
            A.Texte(1, m_tabActionsDispos[i],SCREEN_W / 6,50+((SCREEN_H-200)/m_tabActionsDispos.size())*i, BLACK, -1, false);
        }
        for(unsigned int i = 0; i<m_tabActionsDispos.size(); i++)
        {
            A.Texte(1, intToSTring(m_tabActionsDisposPoids[i]) + " E",(SCREEN_W/2)+(SCREEN_W/3),50+((SCREEN_H-200)/m_tabActionsDispos.size())*i, BLACK, -1, true);
        }
        bool ajouter=true;
        for(unsigned int i = 0; i<m_tabActionsDispos.size(); i++)
        {
            ajouter=true;
            for(unsigned int j = 0; j<ActionsDisposModif.size(); j++)
            {
                if(m_tabActionsDispos[i]==ActionsDisposModif[j])
                {
                    MOINS((SCREEN_W / 6)-50, 50+((SCREEN_H-200)/m_tabActionsDispos.size())*i, 30, 8, 1);
                    ajouter=false;
                    break;
                }
            }
            if(ajouter==true)
                PLUS((SCREEN_W / 6)-50, 50+((SCREEN_H-200)/m_tabActionsDispos.size())*i, 30, 8, 1);
        }
        A.Texte(2, "AJOUTER : ", SCREEN_W / 2, (SCREEN_H / 2)+100, BLACK, -1, true);
        std::string StringActionsDisposModif;
        for(unsigned int i = 0; i<ActionsDisposModif.size(); i++)
        {
            if(i<(ActionsDisposModif.size())-1)
                StringActionsDisposModif = StringActionsDisposModif + ActionsDisposModif[i] + ", ";
            else
                StringActionsDisposModif = StringActionsDisposModif + ActionsDisposModif[i] + " ?";
        }
        A.Texte(2, StringActionsDisposModif, SCREEN_W / 2, (SCREEN_H / 2)+150, BLACK, -1, true);
        BUTTON(325,520,475,585);
        A.Texte(2, "OK", SCREEN_W / 2, 535, BLACK, -1, true);
        A.Graphic();
}

void wallet::ActionsDisposREMOVEMenuScreen(std::vector<std::string> ActionsModif)
{
        DEFAULTBACKGROUND();
        A.Texte(2, "ACTIONS", SCREEN_W / 6, 10, BLACK, -1, true);
        A.Texte(2, "VALEURS", (SCREEN_W/2)+(SCREEN_W/3), 10, BLACK, -1, true);
        A.Texte(2, "QUANTITES", (SCREEN_W/2)+(SCREEN_W/10), 10, BLACK, -1, true);
        for(unsigned int i = 0; i<m_tabActions.size(); i++)
        {
            A.Texte(1, m_tabActions[i], SCREEN_W / 6,50+((SCREEN_H-200)/m_tabActions.size())*i, BLACK, -1, false);
        }
        for(unsigned int i = 0; i<m_tabActions.size(); i++)
        {
            A.Texte(1, intToSTring(m_tabPoids[i]) + " E",(SCREEN_W/2)+(SCREEN_W/3),50+((SCREEN_H-200)/m_tabActions.size())*i, BLACK, -1, true);
        }
        for(unsigned int i = 0; i<m_tabActions.size(); i++)
        {
            A.Texte(1, intToSTring(m_nbActionN[i]),(SCREEN_W/2)+(SCREEN_W/10),50+((SCREEN_H-200)/m_tabActions.size())*i, BLACK, -1, true);
        }
        bool ajouter=true;
        for(unsigned int i = 0; i<m_tabActions.size(); i++)
        {
            ajouter=true;
            for(unsigned int j = 0; j<ActionsModif.size(); j++)
            {
                if(m_tabActions[i]==ActionsModif[j])
                {
                    MOINS((SCREEN_W / 6)-50, 50+((SCREEN_H-200)/m_tabActions.size())*i, 30, 8, 1);
                    ajouter=false;
                    break;
                }
            }
            if(ajouter==true)
                PLUS((SCREEN_W / 6)-50, 50+((SCREEN_H-200)/m_tabActions.size())*i, 30, 8, 1);
        }
        A.Texte(2, "SUPPRIMER : ", SCREEN_W / 2, (SCREEN_H / 2)+100, BLACK, -1, true);
        std::string StringActionsModif;
        for(unsigned int i = 0; i<ActionsModif.size(); i++)
        {
            if(i<(ActionsModif.size())-1)
                StringActionsModif = StringActionsModif + ActionsModif[i] + ", ";
            else
                StringActionsModif = StringActionsModif + ActionsModif[i] + " ?";
        }
        A.Texte(2, StringActionsModif, SCREEN_W / 2, (SCREEN_H / 2)+150, BLACK, -1, true);
        BUTTON(325,520,475,585);
        A.Texte(2, "OK", SCREEN_W / 2, 535, BLACK, -1, true);
        A.Graphic();
}

void wallet::ActionChangeQuantityMenuScreen(int ModifNbActions, int i)
{
        DEFAULTBACKGROUND();
        A.Texte(2, m_tabActions[i] + " : " + intToSTring(m_tabPoids[i]) + " EUROS", SCREEN_W / 2, 25, BLACK, -1, true);
        A.Texte(2, intToSTring(m_nbActionN[i]) + " ACTIONS : " + intToSTring(m_tabPoids[i]*m_nbActionN[i]) + " EUROS", SCREEN_W / 2, 75, BLACK, -1, true);
        A.Texte(2, "MODIFIER DE : " + intToSTring(ModifNbActions) + " ACTIONS", SCREEN_W / 2, (SCREEN_H / 2)-150, BLACK, -1, true);
        PLUSMOINS(SCREEN_W/2, (SCREEN_H / 2)-100, 50, 15, 4);
        A.Texte(2, "NOUVELLE QUANTITE : ", SCREEN_W / 2, (SCREEN_H / 2)+50, BLACK, -1, true);
        A.Texte(2,intToSTring(m_nbActionN[i] + ModifNbActions) +  " ACTIONS : " + intToSTring((m_nbActionN[i] + ModifNbActions)*m_tabPoids[i]) + " EUROS ?", SCREEN_W / 2, (SCREEN_H / 2)+100, BLACK, -1, true);
        BUTTON(325,470,475,535);
        A.Texte(2, "OK", SCREEN_W / 2, 485, BLACK, -1, true);
        A.Texte(2, "LIQUIDITES : " + intToSTring(m_liquidites-(ModifNbActions*m_tabPoids[i])) + " EUROS", SCREEN_W / 2, (SCREEN_H / 2)+250, BLACK, -1, true);
        A.Graphic();
}

void wallet::ReequilibrageMenuScreen(int PLiqu)
{
    DEFAULTBACKGROUND();
    A.Texte(2, "CAPITAL : " + intToSTring(m_capital), SCREEN_W / 2, (SCREEN_H / 2)-250, BLACK, -1, true);
    A.Texte(2, "POURCENTAGE DE LIQUIDITES", SCREEN_W / 2, (SCREEN_H / 2)-175, BLACK, -1, true);
    A.Texte(2, "APRES OPERATION :", SCREEN_W / 2, (SCREEN_H / 2)-125, BLACK, -1, true);
    A.Texte(2, intToSTring(PLiqu) + " %", SCREEN_W / 2, (SCREEN_H / 2)-50, BLACK, -1, true);
    PLUSMOINS(SCREEN_W/2, (SCREEN_H / 2), 50, 15, 2);
    BUTTON(100,470,700,535);
    A.Texte(2, "APPLIQUER LE REEQUILIBRAGE", SCREEN_W / 2, 485, BLACK, -1, true);
    A.Graphic();
}

///////////////////////////////////////////LECTURE FICHIERS

int wallet::GetOneAction(std::string action) ///Poids d4une action
{
    int temp;
    std::string ligne;
    std::ifstream fichierAction ("ActionsPoids.txt");
    while(getline(fichierAction,ligne) && ligne!=action.c_str())
        {}
    for(int i = 0; i<m_date; i++)
    {
        fichierAction >> temp;
    }
    fichierAction.close();
    return temp;
}

void wallet::GetOneNbAction(std::string action) ///Nb d4une action
{
    int temp;
    std::string ligne;
    std::ifstream fichierAction ("ActionsNombres.txt");
    while(getline(fichierAction,ligne) && ligne!=action.c_str())
        {}
    fichierAction >> temp;
    fichierAction.close();
    m_nbActionN.push_back(temp);
}

void wallet::GetListAction() ///liste des actions
{
    while(!m_tabActions.empty())
    {
        m_tabActions.pop_back();
    }
    int compt=0;
    std::string ligne;
    std::ifstream fichierAction ("Actions.txt");
    while(getline(fichierAction,ligne))
        {
            m_tabActions.push_back(ligne);
            compt++;
        }
    fichierAction.close();
    m_tabActions.resize(compt);
}

void wallet::GetListActionsDispos()
{
    while(!m_tabActionsDispos.empty())
    {
        m_tabActionsDispos.pop_back();
    }
    int compt=0;
    std::string ligne;
    std::ifstream fichierAction ("ActionsDispos.txt");
    while(getline(fichierAction,ligne))
        {
            m_tabActionsDispos.push_back(ligne);
            compt++;
        }
    fichierAction.close();
    m_tabActionsDispos.resize(compt);
    for(unsigned int j = 0; j<m_tabActions.size(); j++)
    {
        for(unsigned int i = 0; i<m_tabActionsDispos.size(); i++)
        {
            if(m_tabActionsDispos[i]==m_tabActions[j])
            {
                m_tabActionsDispos.erase(m_tabActionsDispos.begin()+i);
                compt--;
            }
        }
    }
    m_tabActionsDispos.resize(compt);
}

void wallet::GetListActionsDisposPoids()
{
    while(!m_tabActionsDisposPoids.empty())
    {
        m_tabActionsDisposPoids.pop_back();
    }
    for(unsigned int i = 0; i<m_tabActionsDispos.size(); i++)
    {
        m_tabActionsDisposPoids.push_back(GetOneAction(m_tabActionsDispos[i]));
    }
}

void wallet::GetAllAction()
{
    while(!m_tabPoids.empty())
    {
        m_tabPoids.pop_back();
    }
    while(!m_nbActionN.empty())
    {
        m_nbActionN.pop_back();
    }
    for(unsigned int i = 0; i<m_tabActions.size(); i++)
    {
        m_tabPoids.push_back(GetOneAction(m_tabActions[i]));
        GetOneNbAction(m_tabActions[i]);
    }
}

void wallet::GetLiquidites()
{
    m_liquidites=0;
    std::string ligne;
    std::ifstream fichierAction ("ActionsNombres.txt");
    while(getline(fichierAction,ligne) && ligne!="LIQUIDITES")
        {}
    fichierAction >> m_liquidites;
    fichierAction.close();
}

void wallet::GetCapital()
{
    m_capital=0;
    m_capital=m_liquidites;
    for(unsigned int i = 0; i<m_tabActions.size(); i++)
        {
           m_capital = m_capital + (m_tabPoids[i]*m_nbActionN[i]);
        }
}

//////////////////////////////////ECRITURE FICHIERS

void wallet::SetFileActionsNombres()
{
    std::ofstream fichierAction("ActionsNombres.txt", std::ios::trunc);
    for(unsigned int i = 0; i<m_tabActions.size(); i++)
    {
        fichierAction << m_tabActions[i] << '\n';
        fichierAction << m_nbActionN[i] << '\n';
    }
    fichierAction << "LIQUIDITES" << '\n';
    fichierAction << m_liquidites << '\n';
    fichierAction.close();
}

void wallet::SetFileActions()
{
    std::ofstream fichierAction("Actions.txt", std::ios::trunc);
    for(unsigned int i = 0; i<m_tabActions.size(); i++)
    {
        fichierAction << m_tabActions[i] << '\n';
    }
    fichierAction.close();
}

////////////////////////////////////////////FONCTIONS UTILES

void wallet::DEFAULTBACKGROUND()
{
        A.Wallapaper();
        A.Rectangle(SCREEN_W-50,SCREEN_H-50,SCREEN_W,SCREEN_H,BLACK,true);
        A.Rectangle(SCREEN_W-40,SCREEN_H-40,SCREEN_W-10,SCREEN_H-10,WHITE,true);
        A.Rectangle(SCREEN_W-30,SCREEN_H-30,SCREEN_W-20,SCREEN_H-20,BLACK,true);
}

std::string wallet::intToSTring(int toString)
{
      std::ostringstream os ;
      os << toString ;
      return os.str() ;
}

void wallet::BUTTON(int xBegin, int yBegin, int xEnd, int yEnd)
{
    A.Rectangle(xBegin,yBegin,xEnd,yEnd,YELLOW,true);
    A.Rectangle(xBegin-10,yBegin-10,xEnd+10,yEnd+10,BLACK,false);
}


void wallet::PLUS(int xBegin, int yBegin, int LargeRect, int LargePLUS, int quantity)
{
    xBegin = xBegin - ((LargeRect*quantity)/2);
    int xBeginAll = xBegin;
    for(int i=0; i<quantity; i++)
    {
        xBegin = xBeginAll+LargeRect*i;
    A.Rectangle(xBegin,yBegin,xBegin+LargeRect,yBegin+LargeRect,GREEN,true);
    A.Rectangle(xBegin+(LargeRect/2)-(LargePLUS/2),yBegin+5,xBegin+(LargeRect/2)+(LargePLUS/2),yBegin+LargeRect-5,BLACK,true);
    A.Rectangle(xBegin+5,yBegin+(LargeRect/2)-(LargePLUS/2),xBegin+LargeRect-5,yBegin+(LargeRect/2)+(LargePLUS/2),BLACK,true);
    A.Rectangle(xBegin,yBegin,xBegin+LargeRect,yBegin+LargeRect,BLACK,false);
    }
}

void wallet::MOINS(int xBegin, int yBegin, int LargeRect, int LargePLUS, int quantity)
{
    xBegin = xBegin - ((LargeRect*quantity)/2);
    int xBeginAll = xBegin;
    for(int i=0; i<quantity; i++)
    {
        xBegin = xBeginAll+LargeRect*i;
    A.Rectangle(xBegin,yBegin,xBegin+LargeRect,yBegin+LargeRect,CYAN,true);
    A.Rectangle(xBegin+5,yBegin+(LargeRect/2)-(LargePLUS/2),xBegin+LargeRect-5,yBegin+(LargeRect/2)+(LargePLUS/2),BLACK,true);
    A.Rectangle(xBegin,yBegin,xBegin+LargeRect,yBegin+LargeRect,BLACK,false);
    }
}


void wallet::PLUSMOINS(int xBegin, int yBegin, int LargeRect, int LargePLUS, int quantity)
{
    PLUS(xBegin, yBegin, LargeRect, LargePLUS, quantity);
    yBegin = yBegin + LargeRect + 5;
    MOINS(xBegin, yBegin, LargeRect, LargePLUS, quantity);
}

void wallet::REST()
{
    rest(200);
}

int wallet::PUISSANCE10(int puissance)
{
    if(puissance < 0)
        puissance=0;
    if(puissance > 9)
        puissance=9;
    int p10 = 1;
    for(int i=0; i<puissance; i++)
    {
        p10 = p10*10;
    }
    return p10;
}

//////////////////////////////////////////REEQUILIBRAGE

void wallet::REEQUILIBRAGE(int PLiqu)
{
    int tempCap = m_capital;
    m_liquidites = (PLiqu*m_capital)/100;
    for(unsigned int i = 0; i<m_tabActions.size(); i++)
    {
        m_nbActionN[i] = (m_capital-m_liquidites)/(m_tabPoids[i]*m_tabActions.size());
    }
    GetCapital();
    tempCap = tempCap - m_capital;
    m_liquidites = m_liquidites + tempCap;
    SetFileActions();
    SetFileActionsNombres();
    GetListAction();
    GetAllAction();
    GetLiquidites();
    GetCapital();
}
