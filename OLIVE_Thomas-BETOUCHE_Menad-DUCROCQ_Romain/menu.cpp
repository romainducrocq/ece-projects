#include "menu.h"

Menu::Menu (bool _is_in_menu)
    : m_is_in_menu (_is_in_menu)
{
    ///  nothing to do here !
}

Menu::~Menu ()
{
    ///  nothing to do here !
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

void Menu::sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void Menu::anim (Console* pConsole)
{
    /// Allocation of memory
    pConsole = Console::getInstance();

    /// Various displays of graphic menu
    std::cout << "\n\n\n\n\n\n\n\t\t\tWELCOME IN THE REVENGE OF :\n\n\n" << std::endl;
    pConsole->setColor(COLOR_RED);

    std::cout << "\t    ______    __      __    ____     ____     ____    _       _    " << std::endl;
    std::cout << "\t   |   ___|  |   \\   | |  |     |  |     |  |  _  |  \\ \\    / /   " << std::endl;
    std::cout << "\t   |  |__    | |\\ \\  | |  |  _  |  |  _  |  | |_| |   \\ \\__/ /    " << std::endl;
    std::cout << "\t   |__   |   | | \\ \\ | |  | |_| |  | |_| |  |  __/     \\    /     " << std::endl;
    std::cout << "\t    __|  |   | |  \\ \\| |  |     |  |     |  | |         |  |      " << std::endl;
    std::cout << "\t   |_____|   |_|   \\___|  |_____|  |_____|  |_|         |__|      " << std::endl;

    sleep (400);
    system ("cls");
    pConsole->setColor(COLOR_DEFAULT);
    std::cout << "\n\n\n\n\n\n\n\t\t\tWELCOME IN THE REVENGE OF :\n\n\n" << std::endl;
    pConsole->setColor(COLOR_GREEN);

    std::cout << "\t    ______    __      __    ____     ____     ____    _       _    " << std::endl;
    std::cout << "\t   |######|  |   \\   | |  |     |  |     |  |  _  |  \\ \\    / /   " << std::endl;
    std::cout << "\t   |##|__    | |\\ \\  | |  |  _  |  |  _  |  | |_| |   \\ \\__/ /    " << std::endl;
    std::cout << "\t   |#####|   | | \\ \\ | |  | |_| |  | |_| |  |  __/     \\    /     " << std::endl;
    std::cout << "\t    __|##|   | |  \\ \\| |  |     |  |     |  | |         |  |      " << std::endl;
    std::cout << "\t   |#####|   |_|   \\___|  |_____|  |_____|  |_|         |__|      " << std::endl;

    sleep (400);
    system ("cls");
    pConsole->setColor(COLOR_DEFAULT);
    std::cout << "\n\n\n\n\n\n\n\t\t\tWELCOME IN THE REVENGE OF :\n\n\n" << std::endl;
    pConsole->setColor(COLOR_BLUE);

    std::cout << "\t    ______    __      __    ____     ____     ____    _       _    " << std::endl;
    std::cout << "\t   |######|  |###\\   |#|  |     |  |     |  |  _  |  \\ \\    / /   " << std::endl;
    std::cout << "\t   |##|__    |#|\\#\\  |#|  |  _  |  |  _  |  | |_| |   \\ \\__/ /    " << std::endl;
    std::cout << "\t   |#####|   |#| \\#\\ |#|  | |_| |  | |_| |  |  __/     \\    /     " << std::endl;
    std::cout << "\t    __|##|   |#|  \\#\\|#|  |     |  |     |  | |         |  |      " << std::endl;
    std::cout << "\t   |#####|   |#|   \\###|  |_____|  |_____|  |_|         |__|      " << std::endl;

    sleep (400);
    system ("cls");
    pConsole->setColor(COLOR_DEFAULT);
    std::cout << "\n\n\n\n\n\n\n\t\t\tWELCOME IN THE REVENGE OF :\n\n\n" << std::endl;
    pConsole->setColor(COLOR_YELLOW);

    std::cout << "\t    ______    __      __    ____     ____     ____    _       _    " << std::endl;
    std::cout << "\t   |######|  |###\\   |#|  |#####|  |     |  |  _  |  \\ \\    / /   " << std::endl;
    std::cout << "\t   |##|__    |#|\\#\\  |#|  |#####|  |  _  |  | |_| |   \\ \\__/ /    " << std::endl;
    std::cout << "\t   |#####|   |#| \\#\\ |#|  |#|_|#|  | |_| |  |  __/     \\    /     " << std::endl;
    std::cout << "\t    __|##|   |#|  \\#\\|#|  |#####|  |     |  | |         |  |      " << std::endl;
    std::cout << "\t   |#####|   |#|   \\###|  |#####|  |_____|  |_|         |__|      " << std::endl;

    sleep (400);
    system ("cls");
    pConsole->setColor(COLOR_DEFAULT);
    std::cout << "\n\n\n\n\n\n\n\t\t\tWELCOME IN THE REVENGE OF :\n\n\n" << std::endl;
    pConsole->setColor(COLOR_RED);

    std::cout << "\t    ______    __      __    ____     ____     ____    _       _    " << std::endl;
    std::cout << "\t   |######|  |###\\   |#|  |#####|  |#####|  |  _  |  \\ \\    / /   " << std::endl;
    std::cout << "\t   |##|__    |#|\\#\\  |#|  |#####|  |#####|  | |_| |   \\ \\__/ /    " << std::endl;
    std::cout << "\t   |#####|   |#| \\#\\ |#|  |#|_|#|  |#|_|#|  |  __/     \\    /     " << std::endl;
    std::cout << "\t    __|##|   |#|  \\#\\|#|  |#####|  |#####|  | |         |  |      " << std::endl;
    std::cout << "\t   |#####|   |#|   \\###|  |#####|  |#####|  |_|         |__|      " << std::endl;

    sleep (400);
    system ("cls");
    pConsole->setColor(COLOR_DEFAULT);
    std::cout << "\n\n\n\n\n\n\n\t\t\tWELCOME IN THE REVENGE OF :\n\n\n" << std::endl;
    pConsole->setColor(COLOR_BLUE);

    std::cout << "\t    ______    __      __    ____     ____     ____    _       _    " << std::endl;
    std::cout << "\t   |######|  |###\\   |#|  |#####|  |#####|  |#####|  \\ \\    / /   " << std::endl;
    std::cout << "\t   |##|__    |#|\\#\\  |#|  |#####|  |#####|  |#|_|#|   \\ \\__/ /    " << std::endl;
    std::cout << "\t   |#####|   |#| \\#\\ |#|  |#|_|#|  |#|_|#|  |####/     \\    /     " << std::endl;
    std::cout << "\t    __|##|   |#|  \\#\\|#|  |#####|  |#####|  |#|         |  |      " << std::endl;
    std::cout << "\t   |#####|   |#|   \\###|  |#####|  |#####|  |#|         |__|      " << std::endl;

    sleep (400);
    system ("cls");
    pConsole->setColor(COLOR_DEFAULT);
    std::cout << "\n\n\n\n\n\n\n\t\t\tWELCOME IN THE REVENGE OF :\n\n\n" << std::endl;
    pConsole->setColor(COLOR_GREEN);

    std::cout << "\t    ______    __      __    ____     ____     ____    _       _    " << std::endl;
    std::cout << "\t   |######|  |###\\   |#|  |#####|  |#####|  |#####|  \\#\\    /#/   " << std::endl;
    std::cout << "\t   |##|__    |#|\\#\\  |#|  |#####|  |#####|  |#|_|#|   \\#\\__/#/    " << std::endl;
    std::cout << "\t   |#####|   |#| \\#\\ |#|  |#|_|#|  |#|_|#|  |####/     \\####/     " << std::endl;
    std::cout << "\t    __|##|   |#|  \\#\\|#|  |#####|  |#####|  |#|         |##|      " << std::endl;
    std::cout << "\t   |#####|   |#|   \\###|  |#####|  |#####|  |#|         |##|      " << std::endl;

    pConsole->setColor(COLOR_DEFAULT);
    sleep (400);

    /// Obtaining the pseudo of the gamer
    std::cout << "\n\n\n\n\t\t\t  YOUR NAME IS : ";
    std::getline (std::cin, m_pseudo);
    system("cls");
}

void Menu::gamerDecision (Console* pConsole)
{
    /// Declaration of variables
    int choice=0;
    int i;
    int nbLevelMax=3;
    int scoreTotal;
    std::string password;
    std::vector <int> score(nbLevelMax*2);
    std::vector <std::string> sName(nbLevelMax);

    /// Construction of the 3 levels
    Level level1(1,10,20,m_pseudo,1);
    Level level2(2,10,20,m_pseudo,2);
    Level level3(3,10,20,m_pseudo,3);
    m_level1=level1;
    m_level2=level2;
    m_level3=level3;

    do
    {
        /// Display of the 7 choices of the menu
        std::cout << "\n\n\t\t Welcome to the revenge of Snoopy : " << m_pseudo << " !\n" << std::endl << std::endl;
        std::cout << "\t\t\t 1. Game" << std::endl;
        std::cout << "\t\t\t 2. Load" << std::endl;
        std::cout << "\t\t\t 3. Password" << std::endl;
        std::cout << "\t\t\t 4. Scores" << std::endl;
        std::cout << "\t\t\t 5. Player" << std::endl;
        std::cout << "\t\t\t 6. Rules" << std::endl;
        std::cout << "\t\t\t 7. Exit" << std::endl;

        /// Recovery of the user choice
        std::cin >> choice;
        setMenu_choice(choice);

        /// Switch of tihs choice
        switch (getMenu_choice())
        {
            while (getIs_in_menu()==true)
            {
            /// Launch the game, each says the first level
            case 1:
                system("cls");
                launchGame(pConsole, m_level1);
                if(m_winLevel==true)
                {
                    /// Then the second level
                    launchGame(pConsole, m_level2);

                    if(m_winLevel==true)
                    {
                        /// To finish, the third level
                        launchGame(pConsole, m_level3);

                        if(m_winLevel==true)
                        {
                            /// If you win our game, we write your best scores
                            /// Declaration of the input / output of the file
                            std::ifstream scoreBest("score.txt");

                            /// Verification of the opening
                            if(scoreBest)
                            {
                                /// Writing of the best scores
                                scoreTotal=0;
                                for(i=0; i<(nbLevelMax); i++)
                                {
                                    scoreBest >> score[i];
                                    scoreTotal=scoreTotal+score[i];
                                }

                                /// Closing of the file
                                scoreBest.close();
                                std::cout << "YOU WIN THE GAME !!" << std::endl;
                                std::cout << "TOTAL SCORE : " << scoreTotal << std::endl;
                            }
                        }
                    }
                }
                system("cls");
                break;

            case 2:
                /// Load a saved level
                system("cls");

                /// Call of the function to save some parameters
                saveParameter();

                /// Launch the saved level. After that, we have the same procedure that the case 1
                launchGame(pConsole, m_saveLevel);
                if(m_saveNbActualLevel==1&&m_winLevel==true)
                    launchGame(pConsole, m_level2);
                if(m_saveNbActualLevel<=2&&m_winLevel==true)
                    launchGame(pConsole, m_level3);
                if(m_winLevel==true)
                {
                    std::ifstream scoreBest("score.txt");
                    if(scoreBest)
                    {
                        scoreTotal=0;
                        for(i=0; i<(nbLevelMax); i++)
                        {
                            scoreBest >> score[i];
                            scoreTotal=scoreTotal+score[i];
                        }
                        scoreBest.close();
                        std::cout << "YOU WIN THE GAME !!" << std::endl;
                        std::cout << "TOTAL SCORE : " << scoreTotal << std::endl;
                    }
                }

                system("cls");
                break;

            case 3:
                /// Use a password to access quickly in the level you want
                choice=5;
                system ("cls");

                /// User input and recovery
                std::cout << "Enter the password : " << std::endl;
                std::cin >> password;

                /// Verification of the input and access of the level if the password is right
                if(password=="niv1")
                    choice=1;
                if(password=="niv2")
                    choice=2;
                if(password=="niv3")
                    choice=3;

                /// Switch of the choice to launch the good level
                switch (choice)
                {
                case 1 :
                    launchGame(pConsole, m_level1);
                    break;

                case 2 :
                    launchGame(pConsole, m_level2);
                    break;

                case 3 :
                    launchGame(pConsole, m_level3);
                    break;

                default:
                    /// Case default : return to menu if your password is wrong
                    std::cout << "\nWrong password ! Please press a key to return to the menu \n" << std::endl;
                    pConsole -> getInputKey ();
                    break;
                }
                system("cls");
                break;

            case 4:
            {
                /// Read of the file score.txt to see what are you best scores
                system("cls");

                /// Declaration of the input / output of the file
                std::ifstream scoreBest("score.txt");

                /// Verification of the opening
                if(scoreBest)
                {
                    /// Writing of your best scores
                    for(i=0; i<(nbLevelMax*2); i++)
                    {
                        scoreBest >> score[i];
                    }

                    /// Writing of the pseudo associated to this best score
                    for(i=0; i<nbLevelMax; i++)
                    {
                        scoreBest >> sName[i];
                    }

                    /// Closing the file
                    scoreBest.close();
                }

                /// Display in the menu destined to the player
                std::cout << "Best scores : " << std::endl << std::endl;
                for(i=0; i<nbLevelMax; i++)
                {
                    std::cout << "Niveau " << i+1 << " : " << score[i+nbLevelMax] << " / Player : "<< sName[i] <<std::endl;
                }
                std::cout << "\nPlease press a key to return to the menu \n" << std::endl;
                pConsole->getInputKey();
                system("cls");
            }
            break;

            case 5:
            {
                /// To change your pseudo !
                system("cls");

                /// User input
                std::cout << "New Player : " ;
                std::cin.ignore();
                std::getline (std::cin, m_pseudo);

                /// Change the pseudo in your level creation
                Level level1New(1,10,20,m_pseudo,1);
                Level level2New(2,10,20,m_pseudo,2);
                Level level3New(3,10,20,m_pseudo,3);
                m_level1=level1New;
                m_level2=level2New;
                m_level3=level3New;
                system("cls");
            }
            break;


            case 6 :
                /// Display of the rules of our game
                system ("cls");
                std::cout << "Welcome in the rule's informative screen of \"The revenge of Snoopy\" ! \n\n" << std::endl;
                std::cout << "Your mission : to collect the 4 birds 'O' located on the corner of the matrix.\n" << std::endl;
                std::cout << "But be careful of the timer and bad balls !\n" << std::endl;
                std::cout << "Moreover, there are trapped blocks and a lot of obstacles to arrest you ...\n" << std::endl;

                std::cout << "You must move Snoopy and push blocks 'P' using \"z/q/s/d\" (or still \"2/4/6/8\").\n" << std::endl;
                std::cout << "You can break blocks 'C' using \"a\".\n" << std::endl;
                std::cout << "Initially, you have 3 lives but if you lose one, take the 'V' health pack.\n" << std::endl;
                std::cout << "Finally, you can use 'm' to save your level, 'm' to pause and 'ESC' to quit" << std::endl;
                std::cout << "\n\nHave fun playing !\n" << std::endl;

                std::cout << "(Press a key to return to the menu)" << std::endl;

                pConsole->getInputKey();
                system("cls");
                break;

            case 7:
                /// Quit the game
                system ("cls");
                std::cout << "\n\t Thank you for using our game !" << std::endl;
                setIs_in_menu(false);
                break;

            default :
                /// Case default : still missing here !
                system ("cls");
                std::cout << "\n\t Sorry, we don't understand your choice ..." << std::endl;
                setIs_in_menu(false);
                break;
            }
        }
    } while(getMenu_choice()!=7);
}

void Menu::display_menu (Console* pConsole)
{
    /// Call of the 2 functions implemented below
    anim (pConsole);
    gamerDecision(pConsole);
}

void Menu::saveParameter()
{
    /// Declaration of variables
    int nbC, nbL, tmp;

    /// Declaration of the input / output of the file
    std::ifstream save("save.txt");

    /// Verification of the opening
    if(save)
    {
        /// Reading of the size of your matrix
        save >> nbC;
        save >> nbL;

        for (int i = 0; i<nbL; i++)
        {
            for (int j=0; j<nbC; j++)
            {
                /// Then save the disposition of this matrix
                save >> tmp;
            }
        }

        /// Now we save the number of your actual level
        save >> m_saveNbActualLevel;

        /// Closing the file
        save.close();

        /// To finish, we create a object of the class level with the precedent saved parameters
        Level saveLevel(m_saveNbActualLevel,nbL,nbC,m_pseudo,4);
        m_saveLevel=saveLevel;
    }
}

void Menu::launchGame(Console* pConsole,Level m_level)
{
    /// This function is the most important because she managed the calls of a lot of functions in the game ("boucle de jeu" in French)
    system("cls");
    //system("tetris.mp3");

    /// Declaration of variables
    m_winLevel = false;
    bool quit = false;
    int Chrono, Score;
    bool allBirdsTaken;
    m_level.displayMatrix(pConsole);
    m_level.setTimer();
    m_level.setEnemy();

   /// Game loop
    do
    {
        /// If the game is not in pause
        if (m_level.getPause() == false)
        {
            /// Enemy can move and timer can pass
            m_level.afficheMoveEnemy(pConsole);
            Chrono=m_level.afficheChrono(pConsole);
        }

        /// If we press a touch of the keyboard
        if (pConsole->isKeyboardPressed())
        {
            /// Recovery of the ASCII value of this touch
            int key = pConsole->getInputKey();

            if (key == 27) /// 27 =  escape (quit)
            {
                quit = true;
            }

            if(key==112)  /// 112 = p (pause)
            {
                m_level.setPause();
            }

            if(key == 109) /// 109 = m (save)
            {
                m_level.setSave();
            }

            /// One more time, if we are not in pause
            if (m_level.getPause()== false)
            {
                /// We managed all the elements of the game : movement of the player, interactions wit blocks
                m_level.movePlayer(key,pConsole);
                m_level.pushBlock(key,pConsole);
                m_level.trapedBlock(pConsole);
                m_level.lifeBlock (pConsole);
                m_level.clockBlock(pConsole);
                m_level.breakBlock(key,pConsole);
            }
        }

        /// Recovery of the number of birds taken
        allBirdsTaken=m_level.birdBlock(pConsole);
        sleep (200);
    } while (m_level.getIsPlayerAlive()==true && Chrono>0 && allBirdsTaken==false && quit==false);

    system("cls");

    /// If all the birds are taken
    if(allBirdsTaken==true)
    {
        /// Calcul of the score
        Score=Chrono*100;
        m_level.score();

        /// Display that you are a winner :)
        pConsole -> setColor (COLOR_GREEN);
        std::cout << " __      ___      __  ______  ___    __ ___    __ ______ _____     " << std::endl;
        std::cout << "  __     _ _     __     __    __ _   __ __ _   __ __     _   __    " << std::endl;
        std::cout << "   __   _   _   __      __    __  _  __ __  _  __ ____   ____      " << std::endl;
        std::cout << "    __ _     _ __       __    __   _ __ __   _ __ __     _   __    " << std::endl;
        std::cout << "     __       __      ______  __    ___ __    ___ _____  _    __   " << std::endl << std::endl;
        pConsole -> setColor (COLOR_DEFAULT);

        /// Display your score in THIS level
        std::cout << "Score : " << Score << std::endl;
        m_winLevel=true;
    }

    else
    {
        /// Display that you are a looser :(
        pConsole -> setColor (COLOR_RED);
        std::cout << "    ____       ____     __      __  _____            ____   __       __ _____ _____    " << std::endl;
        std::cout << "  __          __  __    __ _  _ __  __             __    __  __     __  __    _   __   " << std::endl;
        std::cout << " __          __    __   __  __  __  ____          __      __  __   __   ____  ____     " << std::endl;
        std::cout << "  __   ___  __ _  _ __  __      __  __             __    __    __ __    __    _   __   " << std::endl;
        std::cout << "   _____|  __        __ __      __  _____            ____       ___     _____ _    __  " << std::endl <<std::endl;
        pConsole -> setColor (COLOR_DEFAULT);
        m_winLevel=false;
    }

    /// Press a key to return to the menu
    pConsole->getInputKey();
    system("cls");
}
