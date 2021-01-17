#ifndef CAPITAINE_H_INCLUDED
#define CAPITAINE_H_INCLUDED

#include <vector>

#include "flotte.h"
#include "VARG.h"

class capitaine
{
private :
	flotte armadaPirate;
	std::vector<std::vector<unsigned short> > grille;
	bool m_tourneCuirasse;
	std::string m_pseudo;

public :
	capitaine();
	~capitaine();



	void majGrille();
	unsigned short getCaseGrille(unsigned short x, unsigned short y);
	bateau* getBateau(unsigned short i);
	bool moveBateau(unsigned short selectBoat, unsigned short selectDir); ///
	bool turnBateau(unsigned short selectBoat); ///
	void shootBateau(unsigned short x, unsigned short y, unsigned short puissance, std::string type);
	bool isFlotteCoulee() const;
	void flotteSAVE(std::string debutFlotte);

	bool getTourne() const;
	void setTourne();

	std::string getPseudo() const;
	void setPseudo(std::string pseudo);
};



#endif



