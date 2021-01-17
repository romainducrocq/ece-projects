/************************************************************
Sokoban project - Main file
Copyright Florent DIEDLER
Date : 27/02/2016

Please do not remove this header, if you use this file !
************************************************************/
#include "maze.h"
#include "graphic.h"
//#include "utils/console.h"
#include "utils/coord.h"
#include "solver.h"
#include "menu.h"
#include <iostream>

// Init allegro with 800x600 (resolution)
Graphic g(800,600,32);

int main()
{
    // Do not touch !
    //Console::getInstance()->setColor(_COLOR_DEFAULT);

/*

    pathSolution solverSolution;
    std::string path = "./levels/easy/easy_2.dat";

    // Load a level-to-solve
    Solver mySolver (path);

    // Load level from a file
    Maze m(path);
    if (!m.init()) return -1;
    std::cout << m << std::endl;
*/
    if (g.init())
    { /*
        /// Compute path solution
        solverSolution=mySolver.Solver_Manager(path,0);
        ///
        ///heuristic tests
        std::cout<<"par ordre croissant"<<std::endl;
        std::vector<unsigned short> test;
        for(unsigned int i = 0; i<mySolver.airm.getPosBoxes().size(); i++)
            { test.push_back(mySolver.airm.getPosBoxes()[i]); }
        std::cout<<mySolver.ManhattanCost(test)<<" heuristique"<<std::endl;
        ///
        /// Display solution on console
       // std::cout << "*****  SOLUTION ******" << std::endl;
       // for(unsigned int i=0;i<Result.Solution.size();i++)
       // {
         //   std::cout << Glados.DisplayDir(Result.Solution[i]) << std::endl;
        //}
        //std::cout << "**********************" << std::endl;
        /// Display solution with allegro
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
        /// Normal game loop
        m.reload(path);
        mySolver.setDeadlocks(m);

        // While playing...
        while (!g.keyGet(KEY_ESC) && !g.keyGet(KEY_A))
        {
            // Check if user has pressed a key
            if (g.keyPressed())
            {
                bool win = false;
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

                if (win) std::cout << "Win ! " << std::endl;
            }

            // Display on screen
            g.clear();
            m.draw(g);
            g.display(Coord::m_nb_col);

            //Debug
            //if(key[KEY_1]) std::cout << m << std::endl;
        }*/

    Menu Sokoban;
    Sokoban.launchMenu();}
    // Free memory
    g.deinit();
    //Console::deleteInstance();

    return 0;
}
END_OF_MAIN()
