#ifndef WALLET_H_INCLUDED
#define WALLET_H_INCLUDED

#include "allezGros.h"
#include <fstream>
#include <vector>

class wallet
{
private :
    allezGros A;
    int m_date;
    int m_liquidites;
    int m_capital;
    std::vector<int> m_tabPoids;
    std::vector<int> m_nbActionN;
    std::vector<std::string> m_tabActions;
    std::vector<std::string> m_tabActionsDispos;
    std::vector<int> m_tabActionsDisposPoids;

public :
    wallet();
    ~wallet();

    bool Go();
    void Appli();
    void Menu();
    void ActionDisplayMenu();
    void ActionMenu();
    void LiquiditesMenu();
    void GererActionsMenu();
    void ActionsDisposChoiceMenu();
    void ActionsDisposADDMenu();
    void ActionsDisposREMOVEMenu();
    void ActionDisplayChoiceMenu();
    void ActionChangeQuantityMenu(int i);
    void ReequilibrageMenu();

    void ActionMenuScreen();
    void InitScreen();
    void MainScreen();
    void ActionScreen(bool choice, bool total);
    void LiquiditesMenuScreen(int ModifLiquidites);
    void GererActionsMenuScreen();
    void ActionsDisposChoiceMenuScreen();
    void ActionsDisposADDMenuScreen(std::vector<std::string> ActionsDisposModif);
    void ActionsDisposREMOVEMenuScreen(std::vector<std::string> ActionsModif);
    void ActionChangeQuantityMenuScreen(int ModifNbActions, int i);
    void ReequilibrageMenuScreen(int PLiqu);

    bool EnterDate();
    int GetOneAction(std::string action);
    void GetOneNbAction(std::string action);
    void GetListAction();
    void GetAllAction();
    void GetListActionsDispos();
    void GetListActionsDisposPoids();
    void GetLiquidites();
    void GetCapital();

    void SetFileActionsNombres();
    void SetFileActions();

    void DEFAULTBACKGROUND();
    std::string intToSTring(int toString);
    void PLUS(int xBegin, int yBegin, int LargeRect, int LargePLUS, int quantity);
    void MOINS(int xBegin, int yBegin, int LargeRect, int LargePLUS, int quantity);
    void PLUSMOINS(int xBegin, int yBegin, int LargeRect, int LargePLUS, int quantity);
    void BUTTON(int xBegin, int yBegin, int xEnd, int yEnd);
    void REST();
    int PUISSANCE10(int puissance);

    void REEQUILIBRAGE(int PLiqu);

};


#endif // WALLET_H_INCLUDED
