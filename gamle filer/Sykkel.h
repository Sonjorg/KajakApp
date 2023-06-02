#ifndef __SYKKEL_H
#define __SYKKEL_H


#include <iostream>
#include <string>
#include "Gjenstand.h"


//Sykkel er subklasse av Gjenstand
class Sykkel : public Gjenstand {
private:
	bool tilhenger;
public:
	virtual void skrivData();
	bool harTilhenger();			// Sjekker om har tilhenger
	
	~Sykkel() {std::cout<<"\nSykkel slettet\n\n";}

	Sykkel(const int nr, char sykkel, bool tilhngr);//constructor, som bare sender parameter til baseklassen.
};


#endif
