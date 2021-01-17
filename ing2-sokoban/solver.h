#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED

/// Includes of maze.cpp
#include "maze.h"
#include "graphic.h"
//#include "utils/console.h"
#include "utils/coord.h"
#include <fstream>
#include <iomanip>

/// Other includes
#include <string>
#include <sstream>
#include <unordered_set>
#include <chrono>
#include <queue>
#include <stack>
#include <cstdlib>
#include <climits>

typedef struct pathSolution
{
    bool IsPathPossible;
    std::vector <unsigned char> path_to_solution;

} pathSolution;

typedef struct simplifiedMaze
{
    std::vector <unsigned char> field;
    std::vector <unsigned short> pos_boxes;
    std::vector<unsigned short> pos_goals;
    unsigned short pos_player;

} simplifiedMaze;

typedef struct Node
{
    unsigned int iNodeParent;               ///indice du noeud parent dans l'arbre de recherche
    std::vector <unsigned short> pos_boxes; ///position des Box du noeud
    std::vector <bool> ConnX;               ///Composante connexe du noeud parent
    unsigned short pos_player;              ///position joueur du noeud
    unsigned char dir;                      ///direction de pouss�e
    unsigned short heuristique;             ///heuristque Best FS et A*
    unsigned short profondeur;              ///profondeur Astar

} Node;

typedef struct SolutionBacktrack
{
    unsigned int iSolutionBacktrackParent;
    unsigned char dirBacktrack;
    unsigned short pos;

} SolutionBacktrack;


typedef struct compareNode
{
   bool operator()( const Node& a, const Node& b ) const
   {
    return a.heuristique > b.heuristique;
   }
}compareNode;

class Solver
{
private:
    bool m_init;
    unsigned long m_count;

    std::unordered_set<std::string> m_situations_tables;
    std::vector<unsigned short> m_static_deadlocks;
    std::vector<unsigned short> m_accessible_area;
    std::vector<unsigned char> m_simplified_field;
    std::vector<bool> m_ConnX;

    std::chrono::high_resolution_clock::time_point m_Start;   /// high resolution : real time, function in whichever is the laptop !
    std::chrono::high_resolution_clock::time_point m_End;

public:
    Maze airm;  /// The maze of the solver : all modifications in this maze cannot affect the initial maze !

    Solver(const std::string& path);
    ~Solver();

    /// Methods
    void Display();
    void Display(const Maze& m);
    std::string DisplayDir(char p);
    simplifiedMaze Load_simplifiedMaze(); /// construction of the light maze : just ground or wall, free memory !

    /// Functions of the counter
    unsigned long getCount();
    void setCount(unsigned long &counter);
    void chrono_Start();
    void chrono_End();

    /// Functions which search the linked component in the maze
    bool isAccessibleArea(unsigned short pos);
    void Accessible_Area();
    void Accessible_Area(Maze &m);  // overloaded function : not only in the solver maze
    unsigned short composanteConnexe(std::vector<unsigned short>& posBoxes,unsigned short& posPlayer);

    ///get the final solution using backtracking
    std::vector <unsigned char> backtracking(std::vector<Node>& nodeList);

    /// Functions which search deadlocks in the maze
    void setDeadlocks();
    void setDeadlocks(Maze &m); // overloaded function : not only in the solver maze
    bool Dynamic_Deadlocks(Maze &m,unsigned short posBox);
    bool find_dynamic_deadlocks(const Maze &m,unsigned short pos,std::vector<unsigned short>& marked_boxes);

    ///Heuristique
    unsigned short ManhattanCost(std::vector<unsigned short>& posBoxes);

    ///Macros Tunnels
    void MacroTunnel(unsigned short& posBox,unsigned short& posPlayer,unsigned char dir);

    /// Check functions
    bool checkSituation(const std::vector<unsigned short>& Posboxes,const unsigned short& PosPlayer);     /// avoid cycles
    bool checkDeadlocks();     /// verify that a square is not a deadlock

    /// Launch the chosen solver
    pathSolution Solver_Manager(const std::string& path, const unsigned int choice); // add an integer which represents the chosen solver, because we have only one

    /// Solvers
    pathSolution BruteForce_Solver(simplifiedMaze DataTransfer, char dir, std::vector<unsigned char> sol);
    pathSolution BFS_Solver();
    pathSolution DFS_Solver();
    pathSolution BestFS_Solver();
    pathSolution Astar_Solver();
    // need other solvers !
};

#endif // SOLVER_H_INCLUDED
