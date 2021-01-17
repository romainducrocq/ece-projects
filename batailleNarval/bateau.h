#ifndef BATEAU_H_INCLUDED
#define BATEAU_H_INCLUDED

#include <fstream>
#include <vector>
#include "VARG.h"

typedef struct caseNavire ///coordonnes + coule ou pas 
{
	unsigned short x;
	unsigned short y;
	bool touche;
}caseNavire;

///reste plein de trucs à implementer ptain

class bateau
{
protected:
	bool m_coule, m_orientation; 
	std::vector<caseNavire> m_tabCaseNavire;
	bool m_fuseeDispo;

public:
	bateau(bool orientation, unsigned short x, unsigned short y, unsigned short taille);
	bateau(bool orientation, unsigned short x, unsigned short y, unsigned short taille, std::vector<bool> tabTouche, bool fuseeDispo);
	virtual ~bateau();
	virtual unsigned short getPuissance() const = 0;
	virtual unsigned short getTaille() const = 0;
	virtual std::string getType() const = 0;

	unsigned short getX(unsigned short i) const;
	unsigned short getY(unsigned short i) const;
	bool getTouche(unsigned short i) const;

	bool getToucheCoule() const;
	bool getOrientation() const;
	bool isNavireCoule() const;

	void setXplus();
	void setXmoins();
	void setYplus(); 
	void setYmoins();
	void setTouche(unsigned short i);
	void setToucheCoule(); 
	void setOrientation();

	///destroyer seulement
	virtual bool getFuseeDispo() const = 0;
	virtual void setFuseePasDispo() = 0;
};

class cuirasse : public bateau 
{
public:
	cuirasse(bool orientation, unsigned short x, unsigned short y);
	cuirasse(bool orientation, unsigned short x, unsigned short y, std::vector<bool> tabTouche);
	virtual ~cuirasse(); 
	virtual unsigned short getPuissance() const;
	virtual unsigned short getTaille() const;
	virtual std::string getType() const;

	virtual bool getFuseeDispo() const;
	virtual void setFuseePasDispo();
};

class croiseur : public bateau 
{
public:
	croiseur(bool orientation, unsigned short x, unsigned short y);
	croiseur(bool orientation, unsigned short x, unsigned short y, std::vector<bool> tabTouche);
	virtual ~croiseur(); 
	virtual unsigned short getPuissance() const;
	virtual unsigned short getTaille() const;
	virtual std::string getType() const;

	virtual bool getFuseeDispo() const;
	virtual void setFuseePasDispo();
};

class destroyer : public bateau 
{
public:
	destroyer(bool orientation, unsigned short x, unsigned short y);
	destroyer(bool orientation, unsigned short x, unsigned short y, std::vector<bool> tabTouche, bool fuseeDispo);
	virtual ~destroyer(); 
	virtual unsigned short getPuissance() const;
	virtual unsigned short getTaille() const;
	virtual std::string getType() const;

	virtual bool getFuseeDispo() const;
	virtual void setFuseePasDispo();
};

class sous_marin : public bateau 
{
public:
	sous_marin(bool orientation, unsigned short x, unsigned short y);
	sous_marin(bool orientation, unsigned short x, unsigned short y, std::vector<bool> tabTouche);
	virtual ~sous_marin(); 
	virtual unsigned short getPuissance() const;
	virtual unsigned short getTaille() const;
	virtual std::string getType() const;

	virtual bool getFuseeDispo() const;
	virtual void setFuseePasDispo();
};

#endif 
