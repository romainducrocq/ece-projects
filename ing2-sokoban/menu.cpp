 #include "menu.h"
extern Graphic g;   /// The unique way to use the the global variable defined in main.cpp

Menu::Menu ()
    : m("./levels/test/test_1.dat"),mySolver("./levels/test/test_1.dat"),m_is_in_menu (false)
{
        m_niveaux.clear();
        m_solver.clear();

}

Menu::~Menu ()
{
}

void Menu::Solver(const std::string& path, const unsigned int& choice)
{
    if(!m.reload(path))
        return;
    //std::cout << m << std::endl;
    pathSolution solverSolution = mySolver.Solver_Manager(path, choice);
    if(solverSolution.IsPathPossible==true)
    {
        mySolver.setDeadlocks(m);
        for(unsigned int i=0; i<solverSolution.path_to_solution.size();i++)
        {
            ///std::cout<<"coup n "<< i <<std::endl;
            ///std::cout<<+solverSolution.path_to_solution[i]<<std::endl;
                m.updatePlayer(solverSolution.path_to_solution[i]);
                g.clear();
                m.draw(g);
                g.display(Coord::m_nb_col);
                rest(50);
        }
        rest(2000);
    ///Solver mySolver (path);
    }
}

void Menu::Player(const std::string& path)
{
    if(!m.reload(path))
        return;
    //std::cout << m << std::endl;
    mySolver.setDeadlocks(m);
        // While playing...
    bool win = false;
    while (!g.keyGet(KEY_ESC) && !g.keyGet(KEY_A) && win==false)
    {
        // Check if user has pressed a key
        if (g.keyPressed())
        {
            switch (g.keyRead())
            {
                case ARROW_UP:
                    win = m.updatePlayer(TOP);
                    break;
                case ARROW_BOTTOM:
                    win = m.updatePlayer(BOTTOM);
                    break;
                case ARROW_RIGHT:
                    win = m.updatePlayer(RIGHT);
                    break;
                case ARROW_LEFT:
                    win = m.updatePlayer(LEFT);
                    break;
            }


        }

            // Display on screen
        g.clear();
        m.draw(g);
        g.display(Coord::m_nb_col);

        if (win)
        {std::cout << "Win ! " << std::endl;
        rest(2000); }
    }
}



bool Menu::getIs_in_menu ()
{
    return m_is_in_menu;
}

int Menu::getMenu_choice ()
{
    return m_menu_choice;
}

void Menu::setIs_in_menu (bool _is_in_menu)
{
    m_is_in_menu = _is_in_menu;
}

void Menu::setMenu_choice (int _menu_choice)
{
        m_menu_choice = _menu_choice;
}

void Menu::launchMenu()
{
    if (!m.init())
        return;
    m_is_in_menu = GetInfos();
    if(m_is_in_menu == true)
    {
        launchMUSIC();
        initMenuScreen();
        while(true)
        {
            if(g.De4dMouse(0,50,SCREEN_W,SCREEN_H)==true)
            {
                DifficultyMenu();
                initMenuScreen();
                REST();
            }

            if (g.De4dMouse(0,0,50,50)==true)
            {
                pauseMUSIC();
                REST();
            }

            if (g.De4dMouse(SCREEN_W-50, 0,SCREEN_W,50)==true)
                return;

        }
        releaseMUSIC();
    }
}


void Menu::DifficultyMenu()
{
    REST();
    DifficultyScreen();
    while(true)
    {

        for(unsigned int i = 0; i<m_niveaux.size(); i+=2)
        {
           if (g.De4dMouse(SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_niveaux.size())*i -5, SCREEN_W / 6 - 10, 150+((SCREEN_H-150)/m_niveaux.size())*i + 25)==true)
            {
            NiveauMenu(i);
            DifficultyScreen();
            REST();
            break;
            }

            if (g.De4dMouse(SCREEN_W / 2 + SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_niveaux.size())*i -5, SCREEN_W / 2 + SCREEN_W / 6 - 10, 150+((SCREEN_H-150)/m_niveaux.size())*i + 25)==true)
            {
                if((i+2)<=m_niveaux.size())
                {
                    NiveauMenu(i+1);
                    DifficultyScreen();
                    REST();
                    break;
                }
            }

        }

        if (g.De4dMouse(0,0,50,50)==true)
            {
                pauseMUSIC();
                REST();
            }

        if (g.De4dMouse(SCREEN_W-50, 0,SCREEN_W,50)==true)
        {
            REST();
            return;
        }

    }

}

void Menu::NiveauMenu(unsigned int difficulty)
{
    REST();
    NiveauScreen(difficulty);
    while(true)
    {
        for(unsigned int i = 0; i<m_niveaux[difficulty].second; i+=2)
        {
           if (g.De4dMouse(SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_niveaux[difficulty].second)*i -5, SCREEN_W / 6 - 10, 150+((SCREEN_H-150)/m_niveaux[difficulty].second)*i + 25)==true)
            {
            SolverMenu(difficulty, i+1);
            NiveauScreen(difficulty);
            REST();
            break;
            }

            if (g.De4dMouse(SCREEN_W / 2 + SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_niveaux[difficulty].second)*i -5, SCREEN_W / 2 + SCREEN_W / 6 - 10, 150+((SCREEN_H-150)/m_niveaux[difficulty].second)*i + 25)==true)
            {
                if((i+2)<=m_niveaux[difficulty].second)
                {
                    SolverMenu(difficulty, i+2);
                    NiveauScreen(difficulty);
                    REST();
                    break;
                }
            }

        }

        if (g.De4dMouse(0,0,50,50)==true)
            {
                pauseMUSIC();
                REST();
            }

        if (g.De4dMouse(SCREEN_W-50, 0,SCREEN_W,50)==true)
        {
            REST();
            return;
        }
    }

}

void Menu::SolverMenu(unsigned int difficulty, unsigned int level)
{
    REST();
    std::string path = "./levels/" + m_niveaux[difficulty].first + "/" + m_niveaux[difficulty].first + "_" + intToSTring(level) + ".dat";
    std::cout<<path<<std::endl;
    SolverScreen();
    while(true)
    {
        for(unsigned int i = 0; i<m_solver.size(); i+=2)
        {
           if (g.De4dMouse(SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_solver.size())*i -5, SCREEN_W / 6 - 10, 150+((SCREEN_H-150)/m_solver.size())*i + 25)==true)
            {
            if(i==0)
                Player(path);
            else
                Solver(path,i);
            SolverScreen();
            REST();
            break;
            }

            if (g.De4dMouse(SCREEN_W / 2 + SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_solver.size())*i -5, SCREEN_W / 2 + SCREEN_W / 6 - 10, 150+((SCREEN_H-150)/m_solver.size())*i + 25)==true)
            {
                if((i+2)<=m_solver.size())
                {
                    Solver(path,i+1);
                    SolverScreen();
                    REST();
                    break;
                }
            }

        }

        if (g.De4dMouse(0,0,50,50)==true)
            {
                pauseMUSIC();
                REST();
            }

        if (g.De4dMouse(SCREEN_W-50, 0,SCREEN_W,50)==true)
        {
            REST();
            return;
        }
    }
}









void Menu::initMenuScreen()
{
    g.clear();
    defaultBackground();
    g.Texte(2, "SUPER SOKO BROS", SCREEN_W / 2, 150, COLOR_BLACK, -1, true);
    g.Texte(2, "Click On Screen To Start", SCREEN_W / 2, 250, COLOR_BLACK, -1, true);
    g.OnScreen();
}


void Menu::DifficultyScreen()
{
    g.clear();
    defaultBackground();
    g.Texte(2, "DIFFICULTY", SCREEN_W / 2, 50, COLOR_BLACK, -1, true);
    for(unsigned int i = 0; i<m_niveaux.size(); i+=2)
        {
                g.Texte(1, m_niveaux[i].first, SCREEN_W/6 ,150+((SCREEN_H-150)/m_niveaux.size())*i, COLOR_BLACK, -1, false);
                g.drawT(g.getSprite(11), SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_niveaux.size())*i -5, false);
            if((i+2)<=m_niveaux.size())
            {
                g.Texte(1, m_niveaux[i+1].first, SCREEN_W/6 + SCREEN_W/2 ,150+((SCREEN_H-150)/m_niveaux.size())*i, COLOR_BLACK, -1, false);
                g.drawT(g.getSprite(11),SCREEN_W / 2 + SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_niveaux.size())*i -5, false);
            }
        }
    g.OnScreen();
}

void Menu::NiveauScreen(unsigned int k)
{
    g.clear();
    defaultBackground();
    g.Texte(2, "LEVEL", SCREEN_W / 2, 50, COLOR_BLACK, -1, true);
    for(unsigned short i = 0; i<m_niveaux[k].second; i+=2)
        {
                g.Texte(1, m_niveaux[k].first + " " + intToSTring(i+1), SCREEN_W / 6,150+((SCREEN_H-150)/m_niveaux[k].second)*i, COLOR_BLACK, -1, false);
                g.drawT(g.getSprite(11),SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_niveaux[k].second)*i -5, false);
             if((i+2)<=m_niveaux[k].second)
             {
                 g.Texte(1, m_niveaux[k].first + " " + intToSTring(i+2), SCREEN_W / 2 + SCREEN_W / 6,150+((SCREEN_H-150)/m_niveaux[k].second)*i, COLOR_BLACK, -1, false);
                 g.drawT(g.getSprite(11),SCREEN_W / 2 + SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_niveaux[k].second)*i -5, false);
             }

        }

    g.OnScreen();
}

void Menu::SolverScreen()
{
    g.clear();
    defaultBackground();
    g.Texte(2, "SOLVER", SCREEN_W / 2, 50, COLOR_BLACK, -1, true);
    for(unsigned int i = 0; i<m_solver.size(); i+=2)
        {
            g.Texte(1, m_solver[i], SCREEN_W / 6,150+((SCREEN_H-150)/m_solver.size())*i, COLOR_BLACK, -1, false);
            g.drawT(g.getSprite(11),SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_solver.size())*i -5, false);
        if((i+2)<=m_solver.size())
        {
            g.Texte(1, m_solver[i+1], SCREEN_W / 2 + SCREEN_W / 6,150+((SCREEN_H-150)/m_solver.size())*i, COLOR_BLACK, -1, false);
            g.drawT(g.getSprite(11),SCREEN_W / 2 + SCREEN_W / 6 - 40, 150+((SCREEN_H-150)/m_solver.size())*i -5, false);
        }
        }
    g.OnScreen();
}

void Menu::defaultBackground()
{
    g.drawT(g.getSprite(10), 0, 0, false);
    g.drawT(g.getSprite(13), 0, 0, false);
    g.drawT(g.getSprite(12), SCREEN_W-50, 0, false);
}


bool Menu::GetInfos() ///liste des infos
{
    std::ifstream fichierInfos ("Infos.txt");
    if(fichierInfos)
    {
        std::pair<std::string,unsigned short> unePaire;
        std::string ligne;

        int compt=0;
        while(true)
        {
            if(getline(fichierInfos,ligne) && ligne!="FIN")
                unePaire.first = ligne;
            else
                break;
            if(getline(fichierInfos,ligne) && ligne!="FIN")
                unePaire.second = atoi(ligne.c_str());
            else
                break;
            m_niveaux.push_back(unePaire);
            compt++;
        }
        m_niveaux.resize(compt);
        compt = 0;
        while(getline(fichierInfos,ligne) && ligne!="FIN")
        {
            m_solver.push_back(ligne);
            compt++;
        }
         m_solver.resize(compt);
        fichierInfos.close();
        return true;
        }
    return false;
}

std::string Menu::intToSTring(int toString)
{
      std::ostringstream os ;
      os << toString ;
      return os.str() ;
}

void Menu::REST()
{
    rest(200);
}

void Menu::launchMUSIC()
{
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_CHANNELGROUP *FMOD_CHANNEL_FREE=NULL;
    FMOD_System_CreateSound(system, "music.mp3", FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &music);
    FMOD_Sound_SetLoopCount(music, -1);
    FMOD_System_PlaySound(system, music, FMOD_CHANNEL_FREE, 0, NULL);
}

void Menu::releaseMUSIC()
{
    FMOD_Sound_Release(music);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
}

void Menu::pauseMUSIC()
{
    FMOD_CHANNELGROUP *canal;
    FMOD_BOOL etat;
    FMOD_System_GetMasterChannelGroup(system, &canal);
    FMOD_ChannelGroup_GetPaused(canal, &etat);
    if (etat) // Si la chanson est en pause
        FMOD_ChannelGroup_SetPaused(canal, 0); // On enl�ve la pause
    else // Sinon, elle est en cours de lecture
        FMOD_ChannelGroup_SetPaused(canal, 1); // On active la pause
}
