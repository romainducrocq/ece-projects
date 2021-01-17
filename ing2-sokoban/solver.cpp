#include "solver.h"
extern Graphic g;   /// The unique way to use the the global variable defined in main.cpp

Solver::Solver(const std::string& path) ///le constructeur prend le niveau en parametre
        :airm(path) ///Maze ///airm : Artificial Intelligence resolution maze
{
    m_init=false;
    m_count=0;
    m_situations_tables.clear();
    m_ConnX.clear();
}

Solver::~Solver()
{
}


/// Methods
void Solver::Display()
{
    g.clear();
    airm.draw(g);
    g.display(Coord::m_nb_col);
}

void Solver::Display(const Maze& m)
{
    g.clear();
    m.draw(g);
    g.display(Coord::m_nb_col);
}

std::string Solver::DisplayDir(char p)
{
    std::string dir;
    switch(p)
    {
    case TOP:
        dir="TOP";
        break;

    case BOTTOM:
        dir="BOTTOM";
        break;

    case LEFT:
        dir="LEFT";
        break;

    case RIGHT:
        dir="RIGHT";
        break;

    default:
        dir="NONE";
        break;
    }
    return dir;
}

/// Load the informations of the airm maze to another maze called sairm, which will be simplified later to search the linked component
simplifiedMaze Solver::Load_simplifiedMaze()
{
    simplifiedMaze sairm; ///struct de la map simplifiee
    sairm.pos_player=airm.getPosPlayer(); ///struct prend valeur de posPlayer de maze

    sairm.field.resize(airm.getField().size()); ///taille field de struct = taille field de maze
    sairm.pos_boxes.resize(airm.getPosBoxes().size()); ///taille vector posBox de struct = taille vector posBox de maze
    sairm.pos_goals.resize(airm.getGoals().size()); ///taille vector posGoals de struct = taille vector posGoals de maze

    for (unsigned int i=0; i< airm.getField().size(); i++)
    {
        sairm.field[i]=airm.getField()[i]; ///on remplit vector field de struct avec les valeurs field de Maze
    }
    for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
    {
        sairm.pos_boxes[i]=airm.getPosBoxes()[i]; ///on remplit vector posBox de struct avec les valeurs posBox de Maze
    }
    for(unsigned int i=0; i< airm.getGoals().size(); i++)
    {
        sairm.pos_goals[i]=airm.getGoals()[i]; ///on remplit vector posGoals de struct avec les valeurs posGoals de Maze
    }
    return sairm;
}


/// Functions of the counter
unsigned long Solver::getCount()
{
    return m_count;
}

void Solver::setCount(unsigned long &counter)
{
    m_count=counter;
}

// Start of counter
void Solver::chrono_Start()
{
    m_Start=std::chrono::high_resolution_clock::now();
    m_count=0;
}

// End of counter
void Solver::chrono_End()
{
    m_End=std::chrono::high_resolution_clock::now();
    float chronoresult= std::chrono::duration<double, std::milli>(m_End-m_Start).count();   // the value of the chrono is computed

    //std::cout << "***********************************************************" << std::endl << std::endl;
    std::cout << "Resolution time : " << chronoresult*0.001 << " seconds." << std::endl;    // convert msec to sec
    std::cout << "Number of moves : " << m_count << " ." << std::endl << std::endl;
   // std::cout << "***********************************************************" << std::endl;

}



/// Functions which search the linked component in the maze
bool Solver::isAccessibleArea(unsigned short pos) ///composante connexe (postion perso)
{
    if(pos > m_simplified_field.size())
    {
        return false; ///on sait pas comment mais t es a l exterieur du jeu BOLOSS
    }

    /// If there are squares which are marked
    if(m_accessible_area[pos]!=0)
    {
        return true; ///si pos == marquee; on quitte le SP
    }
    ///si pos != marquee
    if(m_simplified_field[pos]==SPRITE_GROUND)
    {
        m_accessible_area[pos]=1; ///si pos == sol. accessible = 1
    }

    else
    {
        m_accessible_area[pos]=2; ///si pos != sol. accessible = 2
        return false; ///on quitte le SP
    }
    ///si pos!=marquee && pos == sol, recursitivite pour les 4 directions
    for(unsigned char i=0; i<4; i++)
    {
        isAccessibleArea(Coord::getDirPos(pos,i));
    }

    return true;    /// There is always at least two squares which form a linked component
}

void Solver::Accessible_Area() ///cree la composante connexe
{
    m_accessible_area.clear(); ///on vide le vector composante connexe
    m_accessible_area.resize(airm.getField().size()); ///taille vector composante connexe == taille field Maze

    // Initialization of the linked component
    for(unsigned short i=0; i<m_accessible_area.size(); i++)
    {
        m_accessible_area[i]=0; ///on demarque la composante connexe
    }

    m_simplified_field.clear();
    m_simplified_field.resize(airm.getField().size());

    /// Transpose the maze airm into a simplified maze with only walls and ground
    for(unsigned short i=0; i<airm.getField().size(); i++)
    {
        if(airm.isSquareBox(i) || airm.isSquareBoxPlaced(i) || airm.isSquareWalkable(i) || airm.isSquareDeadlock(i))
        {
            m_simplified_field[i]=SPRITE_GROUND;
        }
        else
        {
            m_simplified_field[i]=SPRITE_WALL;
        }
    }

    ///Creation of the linked component from the position of the player
    isAccessibleArea(airm.getPosPlayer());

    /// Display
    for(unsigned int i=0 ; i<m_accessible_area.size(); i++)
    {
        if(i%7==0) std::cout << std::endl;
        std::cout << m_accessible_area[i] << " ";
    }
}

/// The same function that the precedent but overloaded, not only in the maze of the solver (so the airm)
void Solver::Accessible_Area(Maze &m)
{
    m_accessible_area.clear();
    m_accessible_area.resize(m.getField().size());

    // Initialization of the linked component
    for(unsigned short i=0; i<m_accessible_area.size(); i++)
    {
        m_accessible_area[i]=0;
    }

    m_simplified_field.clear();
    m_simplified_field.resize(m.getField().size());

    /// Transpose the maze m into a simplified maze  with only walls and ground
    for(unsigned short i=0; i<m.getField().size(); i++)
    {
        if(m.isSquareBox(i) || m.isSquareBoxPlaced(i) || m.isSquareWalkable(i) || m.isSquareDeadlock(i))
        {
            m_simplified_field[i]=SPRITE_GROUND;
        }
        else
        {
            m_simplified_field[i]=SPRITE_WALL;
        }
    }
    /// Creation of the linked component from the position of the player
    isAccessibleArea(m.getPosPlayer());

    /// Display
    for(unsigned int i=0 ; i<m_accessible_area.size(); i++)
    {
        if(i%6==0) std::cout << std::endl;
        std::cout << m_accessible_area[i] << " ";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DEADLOCKS DETECTION ///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// Function which searches static deadlocks in the maze
void Solver::setDeadlocks()
{
    /// 0 : unmarked       ---    1 : accessible
    /// 2 : can_go_on_goal ---    3 : deadlock
    /// 4 : marked

    unsigned short adjacent_mov[4];
    bool accessible;

    /// Set of the accessible area to avoid checking squares outside the game (call of the suitable function)
    Accessible_Area();
    Display();

    /// Initialization of the array of deadlocks
    m_static_deadlocks.clear();
    m_static_deadlocks.resize(airm.getField().size());

    for(unsigned int i=0; i<airm.getField().size(); i++)
    {
        if(airm.getField()[i]==SPRITE_GOAL || airm.getField()[i]==SPRITE_BOX_PLACED)
            m_static_deadlocks[i]=2;

        else m_static_deadlocks[i]=0;
    }

    /// We start to detect zones that can go on the goal so no deadlocks
    for(unsigned int k=0; k<airm.getField().size(); k++)
    {
        for(unsigned int i=0; i<airm.getField().size(); i++)
        {
            adjacent_mov[0]=Coord::getDirPos(i,TOP);
            adjacent_mov[1]=Coord::getDirPos(i,BOTTOM);
            adjacent_mov[2]=Coord::getDirPos(i,LEFT);
            adjacent_mov[3]=Coord::getDirPos(i,RIGHT);

            /// If the adjacent positions are allowed : so if we are always inside the maze
            if(adjacent_mov[0]<airm.getField().size() && adjacent_mov[1]<airm.getField().size() && adjacent_mov[2]<airm.getField().size() && adjacent_mov[3]<airm.getField().size())
            {
                /// If the case is accessible
                if(m_accessible_area[i]==1)
                {
                    /// If the case is presently not marked
                    if(m_static_deadlocks[i]==0)
                    {
                        /// Note than we can access to this square
                        accessible=true;

                        /// For all the 4 directions
                        for(unsigned char j=0; j<4; j++)
                        {
                            /// If the box can be pushed in one of the direction, so if the related area is accessible
                            if(m_accessible_area[Coord::getOppositeDirPos(i,j)] == 1)
                            {
                                /// If the box is pushed on a zone that "lead" to a goal
                                if(m_static_deadlocks[adjacent_mov[j]]==2)
                                {
                                    m_static_deadlocks[i]=2;
                                    accessible=false;
                                    j=4;
                                }

                                else
                                {
                                    /// If the box is pushed on ground, it can go somewhere
                                    if(m_simplified_field[adjacent_mov[j]] == SPRITE_GROUND && m_static_deadlocks[adjacent_mov[j]]!=3)
                                    {
                                        accessible=false;
                                    }

                                }

                            }
                        }

                        /// Nevertheless, if the box can't go anywhere
                        if(accessible)
                        {
                            m_static_deadlocks[i]=3;
                        }
                    }
                }

                else
                {
                    m_static_deadlocks[i]=4;
                }
            }
        }
    }

    /// We complete it : all unmarked squares are deadlocks, because once a box is placed on it, it won't be placed on a goal
    for(unsigned int i=0; i<m_static_deadlocks.size(); i++)
    {
        if(m_accessible_area[i]==1 && m_static_deadlocks[i]==0)
        {
            m_static_deadlocks[i]=3;
        }
    }

    /// We draw the deadlocks
    for(unsigned int i=0; i<airm.getField().size(); i++)
    {
        if(m_static_deadlocks[i]==3)
        {
            airm.setField(i,SPRITE_DEADLOCK);
        }
    }

    for(unsigned int i=0; i<m_static_deadlocks.size(); i++)
    {
        if (i%Coord::m_nb_col==0) std::cout <<std::endl;
        std::cout << m_static_deadlocks [i] ;

    }
}

/// The same function that the precedent but overloaded, not only in the maze of the solver (so the airm)
/// This function will be called after the solver because the subject impose that deadlocks are marked during the graphic resolution of the level, but after it also
void Solver::setDeadlocks(Maze &m)
{
    /// 0 : unmarked       ---    1 : accessible
    /// 2 : can_go_on_goal ---    3 : deadlock
    /// 4 : marked

    unsigned short adjacent_mov[4];
    bool accessible;

    /// Set of the accessible area to avoid checking squares outside the game (call of the suitable function)
    Accessible_Area(m);
    Display(m);

    /// Initialization of the array of deadlocks
    m_static_deadlocks.clear();
    m_static_deadlocks.resize(m.getField().size());

    for(unsigned int i=0; i<m.getField().size(); i++)
    {
        if(m.getField()[i]==SPRITE_GOAL || m.getField()[i]==SPRITE_BOX_PLACED)
            m_static_deadlocks[i]=2;

        else m_static_deadlocks[i]=0;
    }

    /// We start to detect zones that can go on the goal so no deadlocks
    for(unsigned int k=0; k<m.getField().size(); k++)
    {
        for(unsigned int i=0; i<m.getField().size(); i++)
        {
            adjacent_mov[0]=Coord::getDirPos(i,TOP);
            adjacent_mov[1]=Coord::getDirPos(i,BOTTOM);
            adjacent_mov[2]=Coord::getDirPos(i,LEFT);
            adjacent_mov[3]=Coord::getDirPos(i,RIGHT);

            /// If the adjacent positions are allowed : so if we are always inside the maze
            if(adjacent_mov[0]<m.getField().size() && adjacent_mov[1]<m.getField().size() && adjacent_mov[2]<m.getField().size() && adjacent_mov[3]<m.getField().size())
            {
                /// If the case is accessible
                if(m_accessible_area[i]==1)
                {
                    /// If the case is presently not marked
                    if(m_static_deadlocks[i]==0)
                    {
                        /// Note than we can access to this square
                        accessible=true;

                        /// For all the 4 directions
                        for(unsigned char j=0; j<4; j++)
                        {
                            /// If the box can be pushed in one of the direction, so if the related area is accessible
                            if(m_accessible_area[Coord::getOppositeDirPos(i,j)] == 1)
                            {
                                /// If the box is pushed on a zone that "lead" to a goal
                                if(m_static_deadlocks[adjacent_mov[j]]==2)
                                {
                                    m_static_deadlocks[i]=2;
                                    accessible=false;
                                    j=4;
                                }

                                else
                                {
                                    /// If the box is pushed on ground, it can go somewhere
                                    if(m_simplified_field[adjacent_mov[j]] == SPRITE_GROUND && m_static_deadlocks[adjacent_mov[j]]!=3)
                                    {
                                        accessible=false;
                                    }

                                }
                            }
                        }

                        /// Nevertheless, if the box can't go anywhere
                        if(accessible)
                        {
                            m_static_deadlocks[i]=3;
                        }
                    }
                }

                else
                {
                    m_static_deadlocks[i]=4;
                }
            }
        }
    }

    /// We complete it : all unmarked squares are deadlocks, because once a box is placed on it, it won't be placed on a goal
    for(unsigned int i=0; i<m_static_deadlocks.size(); i++)
    {
        if(m_accessible_area[i]==1 && m_static_deadlocks[i]==0)
        {
            m_static_deadlocks[i]=3;
        }
    }

    /// We draw the deadlocks
    for(unsigned int i=0; i<m.getField().size(); i++)
    {
        if(m_static_deadlocks[i]==3)
        {
            m.setField(i,SPRITE_DEADLOCK);
        }
    }

    for(unsigned int i=0; i<m_static_deadlocks.size(); i++)
    {
        if (i%Coord::m_nb_col==0) std::cout <<std::endl;
        std::cout << m_static_deadlocks [i] ;

    }
}

/// Dynamic Deadlocks
bool Solver::Dynamic_Deadlocks(Maze &m,unsigned short posBox) ///NOT CONNECTED
{
    std::vector <unsigned short> oreiller;
    /// Initialization
    oreiller.resize(m.getField().size());
    for(unsigned int i=0; i<oreiller.size(); i++)
        { oreiller[i]=0; }

    /// Call of recursive function
        if(find_dynamic_deadlocks(m,posBox,oreiller)) return true;
    return false;
}

bool Solver::find_dynamic_deadlocks(const Maze &m, unsigned short pos,std::vector<unsigned short>& marked_boxes) ///NOT CONNECTED
{
    /// If the box is already marked or on a deadlock position
    if(m.getField()[pos]==SPRITE_DEADLOCK || m.getField()[pos]==SPRITE_BOX_ON_DEADLOCK || marked_boxes[pos]==4)
    {
        return true;
    }

    /// We mark the actual box
    marked_boxes[pos]=4;
    unsigned short adjacent_mov[4];
    bool found;

    adjacent_mov[0]=Coord::getDirPos(pos,TOP);
    adjacent_mov[1]=Coord::getDirPos(pos,BOTTOM);
    adjacent_mov[2]=Coord::getDirPos(pos,LEFT);
    adjacent_mov[3]=Coord::getDirPos(pos,RIGHT);

    /// Check if the adjacent positions are good
    if(adjacent_mov[0]<=m.getField().size() && adjacent_mov[1]<=m.getField().size() && adjacent_mov[2]<=m.getField().size() && adjacent_mov[3]<=m.getField().size())
    {
        found=true;

        for(unsigned int i=0; i<4; i++)
        {
            /// Check if the box can be pushed
            if(m_accessible_area[adjacent_mov[(i+1)%4]] == 1)
            {
                /// If the box is pushed next to an other box, we check if this box can be pushed too
                if(m.getField()[adjacent_mov[i]]==SPRITE_BOX || m.getField()[adjacent_mov[i]]==SPRITE_BOX_PLACED)
                {
                    found = find_dynamic_deadlocks(m,adjacent_mov[i],marked_boxes);

                    /// If the other box can be pushed too

                    if(!found)
                    {
                        return false;
                    }
                }

                /// if the box is pushed on a goal or the ground, the box is not blocked
                if(m.getField()[adjacent_mov[i]]==SPRITE_GOAL || m.getField()[adjacent_mov[i]]==SPRITE_GROUND)
                {
                    return false;
                }

            }

        }

        /// If the program is here still alive, so we can move
        return found;
    }
    return true;
}


/// Check functions
bool Solver::checkSituation(const std::vector<unsigned short>& Posboxes,const unsigned short& PosPlayer)           // A situation = a node (position of boxes)
{
    std::ostringstream stream ; ///on cree un flux marquant les noeuds en string
    std::string situation=""; ///flux vide
    std::priority_queue<unsigned short>  PQ;

    for(unsigned int i=0; i<Posboxes.size(); i++)
         { PQ.push(Posboxes[i]); }
    while(!PQ.empty())
    {
        situation+= PQ.top()+48; ///on convertit le noeud actuel de Maze en string
        PQ.pop();
    }

    stream << PosPlayer ;

    situation+= stream.str();

    if (m_situations_tables.count(situation))
        return false;

    /// Add the new situation
    m_situations_tables.insert(situation); ///on marque le noeud
    return true;
}


bool Solver::checkDeadlocks()
{
    for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
    {
        if(airm.isSquareBoxOnDeadlock(airm.getPosBoxes().at(i)))
            return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Launch the chosen solver
pathSolution Solver::Solver_Manager(const std::string& path, const unsigned int choice)
{
    pathSolution pathway;
    simplifiedMaze smaze;

    if(!airm.reload(path))
    {
        pathway.IsPathPossible=false;
        std::cerr << "Can't load the level " << path << std::endl;
        return pathway;
    }

    //std::cout << airm << std::endl;
    m_situations_tables.clear();

    /// Set the deadlock on the game : later, we have to be able to choose if we want to set or not deadlocks
    setDeadlocks();

    /// Display of the airm with the deadlocks
    Display();

    ///Load the smaze with airm data
    smaze=Load_simplifiedMaze();

    /// Launch the chosen solver (here the brute force solver because it's the single) and the chrono
    chrono_Start();
    switch(choice)
    {
    case 1 :
        pathway=BruteForce_Solver(smaze,NONE,pathway.path_to_solution);
        break;
    case 2 :
        pathway=BFS_Solver();
        break;
    case 3 :
        pathway=DFS_Solver();
        break;
    case 4 :
        pathway=BestFS_Solver();
        break;
    case 5 :
        pathway=Astar_Solver();
        break;
    default :
        break;
    }
    chrono_End();

    return pathway;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///BACKTRACKING & COMPOSANTE CONNEXE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector <unsigned char> Solver::backtracking(std::vector<Node>& nodeList)
{
    Node node = nodeList[nodeList.size()-1]; ///on part du dernier noeud de l'arbre

    std::vector <unsigned char> getSolution; ///vector de directions retourn� au solver

    ///Le backtracking consiste � reconstituer le chemin de directions entre chaque noeuds du bfs principal
    ///Ainsi, on utilise un bfs intermediaire � chaque �tape
    SolutionBacktrack AtoB; ///Noeud du bfs intermediaire
    std::vector <SolutionBacktrack> dirList; ///arbre du bfs intermediaire
    std::queue<SolutionBacktrack> FIFO; ///file du bfs intermediare

    std::vector<bool> Marque(node.ConnX.size()); ///Marquage
    unsigned int index; ///indice pointant le noeud parent

    while(node.dir!=255) ///tant que l'on est pas arriv� au noeud initial, seul noeud dont la direction est NONE = 255
    {
        index=0; ///on remet l'indice � 0
        dirList.clear(); ///on vide l'arbre
         while(!FIFO.empty()) ///on vide la file (fun fact, pour une file, la fonction .clear() n'existe pas car elle est plus gourmande en m�moire que de vider la file �l�ment par �l�ment)
            { FIFO.pop(); }

        for(unsigned int i=0; i<node.ConnX.size(); i++) ///on initialise le marquage
            { Marque[i]=false; }
        Marque[nodeList[node.iNodeParent].pos_player] = true; ///on marque la position de d�part

        ///Noeud initial du bfs interm�diare ///AtoB => du point A au point B
        ///////////////////////////////////////////////////////////
        AtoB.iSolutionBacktrackParent=0;
        AtoB.dirBacktrack = NONE;
        AtoB.pos=nodeList[node.iNodeParent].pos_player; ///on part de la position du joueur dans le noeud parent
        ///////////////////////////////////////////////////////////
        FIFO.push(AtoB); ///on enfile le noeud initial du bfs interm�diaire
        getSolution.insert(getSolution.begin(), node.dir); ///on ins�re la direction du noeud de l'arbre principal

        while(!FIFO.empty()) ///tant que la file du bfs intermediaire n'est pas vide
        {
            index = dirList.size(); ///indice prend la valeur du dernier �l�ment de l'arbre
            dirList.push_back(FIFO.front()); ///on ins�re la t�te de file en fin d'arbre

            if(FIFO.front().pos == Coord::getOppositeDirPos(node.pos_player, node.dir)) ///si la position du joueur du noeud en t�te de file est �gale � la position du joueur dans le noeud de l'arbre principale d�cal�e de la direction de pouss�e dans le noeud de l'arbre principale
                break;                                                     ///on sort de la recherche car on a trouv� la position finale

            ///sinon
            for(int i=0; i<4; i++) ///pour les 4 directions
                {
                if(nodeList[node.iNodeParent].ConnX[Coord::getDirPos(FIFO.front().pos,i)]==true&&Marque[Coord::getDirPos(FIFO.front().pos,i)]==false) ///si la position d�cal�e de la direction est connexe dans la composante du noeud parent du noeud de l'arbre principale
                    {                                                                                                           ///et que la position d�cal�e de la direction est non marqu�e
                    ///Noeud enfant
                    /////////////////////////////////////
                    AtoB.iSolutionBacktrackParent = index;
                    AtoB.dirBacktrack = i;
                    AtoB.pos = Coord::getDirPos(FIFO.front().pos,i);
                    /////////////////////////////////////
                    FIFO.push(AtoB); ///on enfile le noeud enfant
                    Marque[Coord::getDirPos(FIFO.front().pos,i)]=true; ///Marquage
                    }
                }
            FIFO.pop(); ///on d�file la t�te de file
        }
        AtoB=dirList[dirList.size()-1]; ///on part du noeud final

        while(AtoB.dirBacktrack!=255) ///tant que l'on est pas remont� au noeud initial, seul noeud dont la direction est NONE = 255
        {
            getSolution.insert(getSolution.begin(), AtoB.dirBacktrack); ///on ins�re la direction
            AtoB = dirList[AtoB.iSolutionBacktrackParent]; ///on remonte au noeud parent par indice dans l'arbre secondaire
        }
        node = nodeList[node.iNodeParent]; ///on remonte au noeud parent par indice dans l'arbre principale
    }
    return getSolution;
}



unsigned short Solver::composanteConnexe(std::vector<unsigned short>& posBoxes,unsigned short& posPlayer) ///Composante connexe = bfs de bool�en sans backtracking partant de la position du joueur
{
    m_ConnX.clear();
    m_ConnX.resize(airm.getField().size());

    std::vector<unsigned char> simplifiedField;
    std::vector<bool> Marque(airm.getField().size());
    for(unsigned int i = 0; i<airm.getField().size(); i++)
    {
        m_ConnX[i]=false;
        Marque[i]=false;
        if(airm.getField()[i]==SPRITE_WALL)
            simplifiedField.push_back(SPRITE_WALL);
        else
            simplifiedField.push_back(SPRITE_GROUND);
    }
    for(unsigned int i = 0; i<posBoxes.size(); i++)
    {
        simplifiedField[posBoxes[i]]=SPRITE_WALL;
    }
    Marque[posPlayer]=true;

    std::queue<unsigned short> bfsConnX;
    bfsConnX.push(posPlayer);
    while(!bfsConnX.empty())
        {
            for(int i=0; i<4; i++)
            {
                if(Marque[Coord::getDirPos(bfsConnX.front(), i)]==false&&simplifiedField[Coord::getDirPos(bfsConnX.front(), i)]==SPRITE_GROUND)
                    bfsConnX.push(Coord::getDirPos(bfsConnX.front(), i));
                    Marque[Coord::getDirPos(bfsConnX.front(), i)]=true;
            }
            m_ConnX[bfsConnX.front()]=true;
            bfsConnX.pop();
        }
    unsigned short i=0;
    while(m_ConnX[i]==false)
        { i++; }

        return i;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                                /// SET OF SOLVERS ///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///Brute Force
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pathSolution Solver::BruteForce_Solver(simplifiedMaze Predecessor_Datas, char dir, std::vector<unsigned char> Predecessor_Coord) ///struct
{
    pathSolution BF_pathway; ///struct Brute Force
    simplifiedMaze Actual_Data; ///struct

    /// Incrementation of counter
    m_count++;
    if(m_count%1000==0) std::cout << m_count << std::endl;

    /// Verification of load
    if(!airm.getisInit()) ///si chemin d acces impossible
    {
        std::cerr << "Can launch Brute_force Solver, the maze is not loaded..." << std::endl;
        BF_pathway.IsPathPossible=false;
        BF_pathway.path_to_solution=Predecessor_Coord;
        return BF_pathway;
    }
    /// Initialization with Predecessor_Datas
    airm.setDirPlayerPos(dir); ///Maze on definit la direction du joueur
    airm.setPlayerPos(Predecessor_Datas.pos_player); /// Maze le joueur prend la position du joueur predecessor

    for (unsigned int i=0; i<Predecessor_Datas.field.size(); i++)
    {
        airm.setField(i,Predecessor_Datas.field[i]); ///on definit vector field de Maze == vector field de struct predecessor
    }
    for(unsigned int i=0; i<Predecessor_Datas.pos_boxes.size(); i++)
    {
        airm.setPos_Boxes(i,Predecessor_Datas.pos_boxes[i]); ///on definit vector posBox de Maze == vector field de struct posBox
    }
    for(unsigned int i=0; i<Predecessor_Datas.pos_goals.size(); i++)
    {
        airm.setPos_Goals(i,Predecessor_Datas.pos_goals[i]); ///on definit vector posGoals de Maze == vector field de struct posGoals
    }

    /// Update the Solution Path
    BF_pathway.path_to_solution.resize(Predecessor_Coord.size()); ///

    for (unsigned int i=0; i<Predecessor_Coord.size(); i++)
    {
        BF_pathway.path_to_solution[i]=Predecessor_Coord[i];
    }

    /// Construction of the char vector which comprises all the directions that the solver will take
    BF_pathway.path_to_solution.push_back(dir);

    /// Check if the game is completed
    if(airm.updatePlayer(dir))
    {
        BF_pathway.IsPathPossible=true;
        return BF_pathway;
    }


    /// Debug features
    if(key[KEY_P])
    {
        //std::cout << airm << std::endl;
        while(!key[KEY_M]);
    }
    if(key[KEY_ESC]) exit(1);

    /// Check if the player did not move or if a box is on a deadlock position
    if((airm.getPosPlayer()==Predecessor_Datas.pos_player || checkDeadlocks()) && dir!=NONE)
    {
        BF_pathway.IsPathPossible=false;
        BF_pathway.path_to_solution=Predecessor_Coord;
        return BF_pathway;
    }

    /// Check if this situation already exists and add if it's not the case
     if(!checkSituation(airm.getPosBoxes(),airm.getPosPlayer()) && dir!=NONE)
    {
        BF_pathway.IsPathPossible=false;
        BF_pathway.path_to_solution=Predecessor_Coord;
        return BF_pathway;
    }

    /// Load datas on transfer maze
    Actual_Data=Load_simplifiedMaze();

    /// Creation of successors
    // If one of the successors bring a positive result then this node bring a positive result, so the successor that go back and don't push any boxes are not allowed
    for(unsigned int i=0; i<4; i++)
    {
        BF_pathway=BruteForce_Solver(Actual_Data,i,BF_pathway.path_to_solution);

        /// If one of these path is good
        if(BF_pathway.IsPathPossible)
        {
            return BF_pathway;
        }
    }

    /// But if all the successors lead to a negative pathway
    BF_pathway.IsPathPossible=false;
    BF_pathway.path_to_solution=Predecessor_Coord;
    return BF_pathway;
}

///BFS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pathSolution Solver::BFS_Solver() ///struct BFS
{
    ///Noeud initial (voir .h pour d�tails de typedef struct Node)
    //////////////////////////////////////////////////////////////
    Node node;
    node.iNodeParent = 0;
    node.dir=NONE;
    node.pos_player=airm.getPosPlayer();
    for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
        { node.pos_boxes.push_back(airm.getPosBoxes()[i]); }
    node.pos_boxes.resize(airm.getPosBoxes().size());

    pathSolution BFS_pathway; ///chemin solution envoye au solver manager
    unsigned int index; ///indice pointant sur le noeud parent (alternative au pointeur pour �viter les fuites m�moires, mais limite le nombre de noeud � la plage de valeurs d'un unsigned int [0, 4 294 967 295])
    std::vector<Node> nodeList; ///arbre de noeuds
    std::queue<Node> FIFO; ///file du BFS
    if(checkSituation(node.pos_boxes,composanteConnexe(node.pos_boxes,node.pos_player))==true) ///on marque le noeud initial
    {
    ///on calcule la composante connexe du noeud de tete de file
    ///on ajoute la composante connexe du noeud parent pour le backtracking
    //////////////////////////////////////////////////////////////////////////////////
        node.ConnX.clear();
        for(unsigned int i=0; i<m_ConnX.size(); i++)
            { node.ConnX.push_back(m_ConnX[i]); }
        node.ConnX.resize(m_ConnX.size());
    //////////////////////////////////////////////////////////////
    FIFO.push(node); ///on enfile le noeud initial

        while(!FIFO.empty()) ///tant que la file n'est pas vide
        {
            if(g.keyGet(KEY_ESC))
            {
                BFS_pathway.IsPathPossible = false;
                return BFS_pathway;
            }
            index = nodeList.size(); ///indice sur la derni�re case de l'arbre
            nodeList.push_back(FIFO.front()); ///la t�te de liste de la file est ins�r�e en fin d'arbre
            node.iNodeParent = index;
            ///on actualise les attributs de airm
            //////////////////////////////////////////////////////////////////////////////////
            ///airm.setPlayerPos(FIFO.front().pos_player);

            for(unsigned int i=0; i<FIFO.front().pos_boxes.size(); i++)
                { airm.setPos_Boxes(i,FIFO.front().pos_boxes[i]); }

            for(unsigned int i=0; i<airm.getField().size(); i++)
            {
                if(airm.getField()[i]!=SPRITE_WALL&&airm.getField()[i]!=SPRITE_GROUND&&airm.getField()[i]!=SPRITE_DEADLOCK)
                    airm.setField(i,SPRITE_GROUND);
            }
            for(unsigned int i=0; i<airm.getGoals().size(); i++)
            {
                airm.setField(airm.getGoals()[i],SPRITE_GOAL);
            }
            for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
            {
                if(airm.getField()[airm.getPosBoxes()[i]]==SPRITE_GOAL)
                    airm.setField(airm.getPosBoxes()[i],SPRITE_BOX_PLACED);
                else
                    airm.setField(airm.getPosBoxes()[i],SPRITE_BOX);
            }
            //////////////////////////////////////////////////////////////////////////////////

            if(airm.isWinningNode()==true) ///si on a trouv� le noeud gagnant on quitte la boucle
                break;

            ///sinon
            for(unsigned int i=0; i<airm.getPosBoxes().size(); i++) ///pour chaque box
            {
               for(unsigned int j=0; j<4; j++) ///pour chaque direction
                {
                    if(nodeList[index].ConnX[Coord::getOppositeDirPos(airm.getPosBoxes()[i], j)]==true) ///si le noeud est adjacent a la composante connexe dans la direction opposee a j
                    {
                        if(airm.isSquareWalkable(Coord::getDirPos(airm.getPosBoxes()[i], j))==true&&airm.isSquareDeadlock(Coord::getDirPos(airm.getPosBoxes()[i], j))==false) ///si on peut pousser la box dans la direction j
                        {
                            ///Noeud enfant
                            /////////////////////////////////////////////////////////////////////
                            node.pos_player=airm.getPosBoxes()[i];
                            node.pos_boxes.clear();
                            for(unsigned int k=0; k<airm.getPosBoxes().size(); k++) ///les box prennent les pos du noeud parent
                            {
                                if(k==i)
                                    node.pos_boxes.push_back(Coord::getDirPos(airm.getPosBoxes()[i], j)); ///sauf la box deplacee dans la direction j
                                else
                                    node.pos_boxes.push_back(airm.getPosBoxes()[k]);
                            }
                            node.pos_boxes.resize(airm.getPosBoxes().size());

                            if(checkSituation(node.pos_boxes,composanteConnexe(node.pos_boxes,node.pos_player))==true) ///on marque le noeud et on verifie qu il n y a pas de boucle
                            {
                            ///on calcule la composante connexe du noeud de tete de file
                            ///on ajoute la composante connexe du noeud parent pour le backtracking
                            //////////////////////////////////////////////////////////////////////////////////
                            node.ConnX.clear();
                            for(unsigned int i=0; i<m_ConnX.size(); i++)
                                { node.ConnX.push_back(m_ConnX[i]); }
                            node.ConnX.resize(m_ConnX.size());
                                                ////////////////////////////////////////////////////////////////////

                                node.dir=j;
                                FIFO.push(node); ///on enfile le noeud enfant
                            }
                        }
                    }
				}
                }
                FIFO.pop(); ///on defile le noeud de tete
            }
            }
    BFS_pathway.IsPathPossible = true; ///car on est arrive jusque la sans bug
    BFS_pathway.path_to_solution = backtracking(nodeList);///backtracking de l'arbre de noeuds cr�e par le bfs
    return BFS_pathway;
}

///DFS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pathSolution Solver::DFS_Solver() ///struct DFS
{
    ///Noeud initial (voir .h pour d�tails de typedef struct Node)
    //////////////////////////////////////////////////////////////
    Node node;
    node.iNodeParent = 0;
    node.dir=NONE;
    node.pos_player=airm.getPosPlayer();
    for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
        { node.pos_boxes.push_back(airm.getPosBoxes()[i]); }
    node.pos_boxes.resize(airm.getPosBoxes().size());
    //////////////////////////////////////////////////////////////
    pathSolution DFS_pathway; ///chemin solution envoye au solver manager
    unsigned int index; ///indice pointant sur le noeud parent (alternative au pointeur pour �viter les fuites m�moires, mais limite le nombre de noeud � la plage de valeurs d'un unsigned int [0, 4 294 967 295])
    std::vector<Node> nodeList; ///arbre de noeuds
    std::stack<Node> LIFO; ///pile du DFS
    if(checkSituation(node.pos_boxes,composanteConnexe(node.pos_boxes,node.pos_player))==true) ///on marque le noeud initial
        {
    ///on calcule la composante connexe du noeud de tete de file
    ///on ajoute la composante connexe du noeud parent pour le backtracking
    //////////////////////////////////////////////////////////////////////////////////
        node.ConnX.clear();
        for(unsigned int i=0; i<m_ConnX.size(); i++)
            { node.ConnX.push_back(m_ConnX[i]); }
        node.ConnX.resize(m_ConnX.size());
        LIFO.push(node); ///on enpile le noeud initial
        while(!LIFO.empty()) ///tant que la pile n'est pas vide
        {
            LoopBegin :
            if(g.keyGet(KEY_ESC))
            {
                DFS_pathway.IsPathPossible = false;
                return DFS_pathway;
            }
            index = nodeList.size(); ///indice sur la derni�re case de l'arbre

            nodeList.push_back(LIFO.top()); ///la t�te de liste de la pile est ins�r�e en fin d'arbre
            node.iNodeParent = index;
            ///on actualise les attributs de airm
            //////////////////////////////////////////////////////////////////////////////////
            ///airm.setPlayerPos(LIFO.top().pos_player);

            for(unsigned int i=0; i<LIFO.top().pos_boxes.size(); i++)
                { airm.setPos_Boxes(i,LIFO.top().pos_boxes[i]); }

            for(unsigned int i=0; i<airm.getField().size(); i++)
            {
                if(airm.getField()[i]!=SPRITE_WALL&&airm.getField()[i]!=SPRITE_GROUND&&airm.getField()[i]!=SPRITE_DEADLOCK)
                    airm.setField(i,SPRITE_GROUND);
            }
            for(unsigned int i=0; i<airm.getGoals().size(); i++)
            {
                airm.setField(airm.getGoals()[i],SPRITE_GOAL);
            }
            for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
            {
                if(airm.getField()[airm.getPosBoxes()[i]]==SPRITE_GOAL)
                    airm.setField(airm.getPosBoxes()[i],SPRITE_BOX_PLACED);
                else
                    airm.setField(airm.getPosBoxes()[i],SPRITE_BOX);
            }
            //////////////////////////////////////////////////////////////////////////////////

            if(airm.isWinningNode()==true) ///si on a trouv� le noeud gagnant on quitte la boucle
                break;

            ///sinon
            for(unsigned int i=0; i<airm.getPosBoxes().size(); i++) ///pour chaque box
            {
               for(unsigned int j=0; j<4; j++) ///pour chaque direction
                {
                    if(nodeList[index].ConnX[Coord::getOppositeDirPos(airm.getPosBoxes()[i], j)]==true) ///si le noeud est adjacent a la composante connexe dans la direction opposee a j
                    {
                        if(airm.isSquareWalkable(Coord::getDirPos(airm.getPosBoxes()[i], j))==true&&airm.isSquareDeadlock(Coord::getDirPos(airm.getPosBoxes()[i], j))==false) ///si on peut pousser la box dans la direction j
                        {
                            ///Noeud enfant
                            /////////////////////////////////////////////////////////////////////
                            node.pos_player=airm.getPosBoxes()[i];
                            node.pos_boxes.clear();
                            for(unsigned int k=0; k<airm.getPosBoxes().size(); k++) ///les box prennent les pos du noeud parent
                            {
                                if(k==i)
                                    node.pos_boxes.push_back(Coord::getDirPos(airm.getPosBoxes()[i], j)); ///sauf la box deplacee dans la direction j
                                else
                                    node.pos_boxes.push_back(airm.getPosBoxes()[k]);
                            }
                            node.pos_boxes.resize(airm.getPosBoxes().size());
                            /////////////////////////////////////////////////////////////////////
                            if(checkSituation(node.pos_boxes,composanteConnexe(node.pos_boxes,node.pos_player))==true) ///on marque le noeud et on verifie qu il n y a pas de boucle
                            {
                            ///on calcule la composante connexe du noeud de tete de file
                            ///on ajoute la composante connexe du noeud parent pour le backtracking
                            //////////////////////////////////////////////////////////////////////////////////
                            node.ConnX.clear();
                            for(unsigned int i=0; i<m_ConnX.size(); i++)
                                { node.ConnX.push_back(m_ConnX[i]); }
                            node.ConnX.resize(m_ConnX.size());
                                    node.dir=j;
                                    LIFO.push(node); ///on enpile le noeud enfant
                                    goto LoopBegin; ///on retourne a l'indice de debut de boucle
                                }

                        }
                    }
				}
                }
                LIFO.pop(); ///on depile le noeud de tete
            }
            }
    DFS_pathway.IsPathPossible = true; ///car on est arrive jusque la sans bug
    DFS_pathway.path_to_solution = backtracking(nodeList);///backtracking de l'arbre de noeuds cr�e par le dfs
    return DFS_pathway;
}

///Best FS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pathSolution Solver::BestFS_Solver() ///struct Best FS
{
    ///Noeud initial (voir .h pour d�tails de typedef struct Node)
    //////////////////////////////////////////////////////////////
    Node node;
    node.iNodeParent = 0;
    node.dir=NONE;
    node.pos_player=airm.getPosPlayer();
    for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
        { node.pos_boxes.push_back(airm.getPosBoxes()[i]); }
    node.pos_boxes.resize(airm.getPosBoxes().size());
    node.heuristique = ManhattanCost(node.pos_boxes); ///heuristique
    //////////////////////////////////////////////////////////////
    pathSolution BestFS_pathway; ///chemin solution envoye au solver manager
    unsigned int index; ///indice pointant sur le noeud parent (alternative au pointeur pour �viter les fuites m�moires, mais limite le nombre de noeud � la plage de valeurs d'un unsigned int [0, 4 294 967 295])
    std::vector<Node> nodeList; ///arbre de noeuds
    std::priority_queue<Node, std::vector<Node>, compareNode> MWFO; ///Minimum Weight First Out ///voir .h, compareNode = struct operator de comparaison des �l�ments de la file
    if(checkSituation(node.pos_boxes,composanteConnexe(node.pos_boxes,node.pos_player))==true) ///on marque le noeud initial
    {
    ///on calcule la composante connexe du noeud de tete de file
    ///on ajoute la composante connexe du noeud parent pour le backtracking
    //////////////////////////////////////////////////////////////////////////////////
        node.ConnX.clear();
        for(unsigned int i=0; i<m_ConnX.size(); i++)
            { node.ConnX.push_back(m_ConnX[i]); }
        node.ConnX.resize(m_ConnX.size());
        MWFO.push(node); ///on enfile le noeud initial
        while(!MWFO.empty()) ///tant que la file n'est pas vide
        {
            if(g.keyGet(KEY_ESC))
            {
                BestFS_pathway.IsPathPossible = false;
                return BestFS_pathway;
            }
            index = nodeList.size(); ///indice sur la derni�re case de l'arbre
            nodeList.push_back(MWFO.top()); ///la t�te de liste de la file est ins�r�e en fin d'arbre
            ///std::cout<<MWFO.top().heuristique<<" heuristique"<<std::endl;
            node.iNodeParent = index;
            ///on actualise les attributs de airm
            //////////////////////////////////////////////////////////////////////////////////
            ///airm.setPlayerPos(MWFO.top().pos_player);

            for(unsigned int i=0; i<MWFO.top().pos_boxes.size(); i++)
                { airm.setPos_Boxes(i,MWFO.top().pos_boxes[i]); }

            for(unsigned int i=0; i<airm.getField().size(); i++)
            {
                if(airm.getField()[i]!=SPRITE_WALL&&airm.getField()[i]!=SPRITE_GROUND&&airm.getField()[i]!=SPRITE_DEADLOCK)
                    airm.setField(i,SPRITE_GROUND);
            }
            for(unsigned int i=0; i<airm.getGoals().size(); i++)
            {
                airm.setField(airm.getGoals()[i],SPRITE_GOAL);
            }
            for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
            {
                if(airm.getField()[airm.getPosBoxes()[i]]==SPRITE_GOAL)
                    airm.setField(airm.getPosBoxes()[i],SPRITE_BOX_PLACED);
                else
                    airm.setField(airm.getPosBoxes()[i],SPRITE_BOX);
            }

            //////////////////////////////////////////////////////////////////////////////////
            MWFO.pop(); ///on defile le noeud de tete
            //////////////////////////////////////////////////////////////////////////////////

            if(airm.isWinningNode()==true) ///si on a trouv� le noeud gagnant on quitte la boucle
                break;

            ///sinon
            for(unsigned int i=0; i<airm.getPosBoxes().size(); i++) ///pour chaque box
            {
               for(unsigned int j=0; j<4; j++) ///pour chaque direction
                {
                    if(nodeList[index].ConnX[Coord::getOppositeDirPos(airm.getPosBoxes()[i], j)]==true) ///si le noeud est adjacent a la composante connexe dans la direction opposee a j
                    {
                        if(airm.isSquareWalkable(Coord::getDirPos(airm.getPosBoxes()[i], j))==true&&airm.isSquareDeadlock(Coord::getDirPos(airm.getPosBoxes()[i], j))==false/*&&Dynamic_Deadlocks(airm,Coord::getDirPos(airm.getPosBoxes()[i], j))==false*/) ///si on peut pousser la box dans la direction j
                        {
                            ///Noeud enfant
                            /////////////////////////////////////////////////////////////////////
                            node.pos_player=airm.getPosBoxes()[i];
                            node.pos_boxes.clear();
                            for(unsigned int k=0; k<airm.getPosBoxes().size(); k++) ///les box prennent les pos du noeud parent
                            {
                                if(k==i)
                                    node.pos_boxes.push_back(Coord::getDirPos(airm.getPosBoxes()[i], j)); ///sauf la box deplacee dans la direction j
                                else
                                    node.pos_boxes.push_back(airm.getPosBoxes()[k]);
                            }
                            node.pos_boxes.resize(airm.getPosBoxes().size());

                            /////////////////////////////////////////////////////////////////////
                            if(checkSituation(node.pos_boxes,composanteConnexe(node.pos_boxes,node.pos_player))==true) ///on marque le noeud et on verifie qu il n y a pas de boucle
                            {
                            ///on calcule la composante connexe du noeud de tete de file
                            ///on ajoute la composante connexe du noeud parent pour le backtracking
                            //////////////////////////////////////////////////////////////////////////////////
                            node.ConnX.clear();
                            for(unsigned int i=0; i<m_ConnX.size(); i++)
                                { node.ConnX.push_back(m_ConnX[i]); }
                            node.ConnX.resize(m_ConnX.size());
                                    node.dir=j;
                                    node.heuristique = ManhattanCost(node.pos_boxes); ///heuristique
                                    MWFO.push(node); ///on enfile le noeud enfant
                                }

                        }
                    }
				}
                }
            }
            }
        std::cout<<MWFO.size()<<" pq size"<<std::endl;
    BestFS_pathway.IsPathPossible = true; ///car on est arrive jusque la sans bug
    BestFS_pathway.path_to_solution = backtracking(nodeList);///backtracking de l'arbre de noeuds cr�e par le best fs
    return BestFS_pathway;
}


unsigned short Solver::ManhattanCost(std::vector<unsigned short>& posBoxes) ///heuristique de manhattan
{
    unsigned int VCoordBox, HCoordBox, VCoordGoal, HCoordGoal;
    unsigned short ManhattanDistance, Heuristique, cptBoxes, cptGoals;
    std::vector<bool> MarqueBox; for(unsigned int i = 0; i<posBoxes.size(); i++) { MarqueBox.push_back(false); }
    std::vector<bool> MarqueGoal; for(unsigned int i = 0; i<airm.getGoals().size(); i++) { MarqueGoal.push_back(false); }
    Heuristique=0;
    for(unsigned int i = 0; i<posBoxes.size(); i++)///un tableau 2D des caisses / goals, parcouru nombre de caisses fois
    {///Principe : trouver la distance de manhattan minimum du tableau et ne plus parcourir les caisses et goals associ�s
        ManhattanDistance = USHRT_MAX; ///le maximum d'un unsigned short
        cptBoxes=0;
        cptGoals=0;
        for(unsigned int j = 0; j<posBoxes.size(); j++) ///Pour chaque caisse
        {
            if(MarqueBox[j]==true) ///si on a d�j� trouv� la distance de manhattan de cette caisse, on passe � l'op�ration suivante
                continue;
            else
                Coord::coord2D(posBoxes[j], VCoordBox, HCoordBox);
            for(unsigned int k = 0; k<airm.getGoals().size(); k++)///Pour chaque goal
            {
                if(MarqueGoal[k]==true) ///si on a d�j� trouv� la distance de manhattan de ce goal, on passe � l'op�ration suivante
                    continue;
                else
                {
                    Coord::coord2D(airm.getGoals()[k], VCoordGoal, HCoordGoal);
                    if(ManhattanDistance > abs((int)VCoordBox - (int)VCoordGoal)+abs((int)HCoordBox - (int)HCoordGoal)) ///si caisse et goal ont la plus petite distance de manhattan du parcours
                    {
                        ManhattanDistance = abs((int)VCoordBox - (int)VCoordGoal)+abs((int)HCoordBox - (int)HCoordGoal); ///mise � jour de la distance de manhattan
                        cptBoxes = j;
                        cptGoals = k;
                    }
                }

            }
        }
        MarqueBox[cptBoxes]=true; ///on marque la caisse associ�e � la distance minimale du parcours pour ne plus la prendre en compte
        MarqueGoal[cptGoals]=true; ///idem pour le goal
        ///std::cout<<ManhattanDistance<< " distance de manhattan n  "<<i<<std::endl;
        Heuristique = Heuristique + ManhattanDistance; ///on ajoute la nouvelle distance de manhattan � l'heuristique
    }
    ///std::cin.get();
    return Heuristique;
}

///Astar
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pathSolution Solver::Astar_Solver() ///struct Astar
{
    ///Noeud initial (voir .h pour d�tails de typedef struct Node)
    //////////////////////////////////////////////////////////////
    Node node;
    node.iNodeParent = 0;
    node.dir=NONE;
    node.pos_player=airm.getPosPlayer();
    for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
        { node.pos_boxes.push_back(airm.getPosBoxes()[i]); }
    node.pos_boxes.resize(airm.getPosBoxes().size());
    node.profondeur = 0;
    node.heuristique = ManhattanCost(node.pos_boxes) + node.profondeur; ///heuristique
    //////////////////////////////////////////////////////////////
    pathSolution Astar_pathway; ///chemin solution envoye au solver manager
    unsigned int index; ///indice pointant sur le noeud parent (alternative au pointeur pour �viter les fuites m�moires, mais limite le nombre de noeud � la plage de valeurs d'un unsigned int [0, 4 294 967 295])
    std::vector<Node> nodeList; ///arbre de noeuds
    std::priority_queue<Node, std::vector<Node>, compareNode> MWFO; ///Minimum Weight First Out ///voir .h, compareNode = struct operator de comparaison des �l�ments de la file
    if(checkSituation(node.pos_boxes,composanteConnexe(node.pos_boxes,node.pos_player))==true) ///on marque le noeud initial
    {
    ///on calcule la composante connexe du noeud de tete de file
    ///on ajoute la composante connexe du noeud parent pour le backtracking
    //////////////////////////////////////////////////////////////////////////////////
        node.ConnX.clear();
        for(unsigned int i=0; i<m_ConnX.size(); i++)
            { node.ConnX.push_back(m_ConnX[i]); }
        node.ConnX.resize(m_ConnX.size());
        MWFO.push(node); ///on enfile le noeud initial
        while(!MWFO.empty()) ///tant que la file n'est pas vide
        {
            if(g.keyGet(KEY_ESC))
            {
                Astar_pathway.IsPathPossible = false;
                return Astar_pathway;
            }
            index = nodeList.size(); ///indice sur la derni�re case de l'arbre
            nodeList.push_back(MWFO.top()); ///la t�te de liste de la file est ins�r�e en fin d'arbre
            ///std::cout<<MWFO.top().heuristique<<" heuristique"<<std::endl;
            node.iNodeParent = index;
            node.profondeur = MWFO.top().profondeur + 1;
            ///on actualise les attributs de airm
            //////////////////////////////////////////////////////////////////////////////////
            ///airm.setPlayerPos(MWFO.top().pos_player);

            for(unsigned int i=0; i<MWFO.top().pos_boxes.size(); i++)
                { airm.setPos_Boxes(i,MWFO.top().pos_boxes[i]); }

            for(unsigned int i=0; i<airm.getField().size(); i++)
            {
                if(airm.getField()[i]!=SPRITE_WALL&&airm.getField()[i]!=SPRITE_GROUND&&airm.getField()[i]!=SPRITE_DEADLOCK)
                    airm.setField(i,SPRITE_GROUND);
            }
            for(unsigned int i=0; i<airm.getGoals().size(); i++)
            {
                airm.setField(airm.getGoals()[i],SPRITE_GOAL);
            }
            for(unsigned int i=0; i<airm.getPosBoxes().size(); i++)
            {
                if(airm.getField()[airm.getPosBoxes()[i]]==SPRITE_GOAL)
                    airm.setField(airm.getPosBoxes()[i],SPRITE_BOX_PLACED);
                else
                    airm.setField(airm.getPosBoxes()[i],SPRITE_BOX);
            }

            //////////////////////////////////////////////////////////////////////////////////
            MWFO.pop(); ///on defile le noeud de tete
            //////////////////////////////////////////////////////////////////////////////////

            if(airm.isWinningNode()==true) ///si on a trouv� le noeud gagnant on quitte la boucle
                break;

            ///sinon
            for(unsigned int i=0; i<airm.getPosBoxes().size(); i++) ///pour chaque box
            {
               for(unsigned int j=0; j<4; j++) ///pour chaque direction
                {
                    if(nodeList[index].ConnX[Coord::getOppositeDirPos(airm.getPosBoxes()[i], j)]==true) ///si le noeud est adjacent a la composante connexe dans la direction opposee a j
                    {
                        if(airm.isSquareWalkable(Coord::getDirPos(airm.getPosBoxes()[i], j))==true&&airm.isSquareDeadlock(Coord::getDirPos(airm.getPosBoxes()[i], j))==false) ///si on peut pousser la box dans la direction j
                        {
                            ///Noeud enfant
                            /////////////////////////////////////////////////////////////////////
                            node.pos_player=airm.getPosBoxes()[i];
                            node.pos_boxes.clear();
                            for(unsigned int k=0; k<airm.getPosBoxes().size(); k++) ///les box prennent les pos du noeud parent
                            {
                                if(k==i)
                                    node.pos_boxes.push_back(Coord::getDirPos(airm.getPosBoxes()[i], j)); ///sauf la box deplacee dans la direction j
                                else
                                    node.pos_boxes.push_back(airm.getPosBoxes()[k]);
                            }
                            node.pos_boxes.resize(airm.getPosBoxes().size());

                            /////////////////////////////////////////////////////////////////////
                            if(checkSituation(node.pos_boxes,composanteConnexe(node.pos_boxes,node.pos_player))==true) ///on marque le noeud et on verifie qu il n y a pas de boucle
                            {
                            ///on calcule la composante connexe du noeud de tete de file
                            ///on ajoute la composante connexe du noeud parent pour le backtracking
                            //////////////////////////////////////////////////////////////////////////////////
                            node.ConnX.clear();
                            for(unsigned int i=0; i<m_ConnX.size(); i++)
                                { node.ConnX.push_back(m_ConnX[i]); }
                            node.ConnX.resize(m_ConnX.size());
                                    node.dir=j;
                                    node.heuristique = ManhattanCost(node.pos_boxes) + node.profondeur; ///heuristique
                                    MWFO.push(node); ///on enfile le noeud enfant
                                }

                        }
                    }
				}
                }
            }
            }
        std::cout<<MWFO.size()<<" pq size"<<std::endl;
    Astar_pathway.IsPathPossible = true; ///car on est arrive jusque la sans bug
    Astar_pathway.path_to_solution = backtracking(nodeList);/// backtracking de l'arbre de noeuds cr�e par le best fs
    return Astar_pathway;
}


void Solver::MacroTunnel(unsigned short& posBox,unsigned short& posPlayer,unsigned char dir) ///NOT CONNECTED
{
    if(airm.getField()[Coord::get90degreeDirPos(posBox,dir)]==SPRITE_WALL&&airm.getField()[Coord::get270degreeDirPos(posBox,dir)]==SPRITE_WALL)
    {
        while( airm.getField()[Coord::get90degreeDirPos(Coord::getDirPos(posBox,dir),dir)]==SPRITE_WALL&&airm.getField()[Coord::get270degreeDirPos(Coord::getDirPos(posBox,dir),dir)]==SPRITE_WALL&&airm.getField()[Coord::getDirPos(posBox,dir)]==SPRITE_GROUND)
            { posBox=Coord::getDirPos(posBox,dir); }
        posPlayer = Coord::getOppositeDirPos(posBox,dir);
    }
}
