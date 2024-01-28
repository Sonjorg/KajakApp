#ifndef __KANO_H
#define __KANO_H


#include <iostream>
#include <string>
#include "Gjenstand.h"


//Sykkel er subklasse av Gjenstand
class Kano : public Gjenstand {
private:
	bool tilhenger;
public:
	virtual void skrivData();
	bool harTilhenger();			// Sjekker om har tilhenger

	~Kano() {std::cout<<"\nSykkel slettet\n\n";}

	Kano(const int nr, char sykkel, bool tilhngr);//constructor, som bare sender parameter til baseklassen.
};


#endif
