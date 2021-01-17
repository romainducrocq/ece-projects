#ifndef FLOTTE_H_INCLUDED
#define FLOTTE_H_INCLUDED

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

#include "bateau.h"
#include "VARG.h"

class flotte 
{
private:
	

public:
	flotte();
	~flotte();
	void flotteConstructeur();
 	void flotteConstructeurSAVE();
	std::vector<bateau*> m_flotte; ///puclic parce que flemme de faire des setters / getters

};

#endif