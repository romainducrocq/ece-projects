#include <iostream>
#include "graphepondere.h"

using std::endl;using std::cout;


int main()
{
    graphepondere * myGraph = new graphepondere();
    myGraph->readSaveFileGraph("save2.txt");
    myGraph->Dijkstra();
    cout<<"\n"<<endl;
    myGraph->Kruskal();
    return 0;
}
