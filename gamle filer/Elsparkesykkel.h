#ifndef __ELSPARKESYKKEL_H
#define __ELSPARKESYKKEL_H

#include <iostream>
#include <string>
#include "Gjenstand.h"

//Elsparkesykkel er subklasse av Gjenstand
class Elsparkesykkel :public Gjenstand {
private:
	int antallWatt;
    int ID;
public:
	virtual void lesData();
	virtual void skrivData();  //skriver ut alle sine data

	int hentWatt();      //Sender tilbake antall watt
	~Elsparkesykkel() {std::cout<<"\nElsparkesykkel slettet\n\n";}

	Elsparkesykkel(const int nr, char elsparkesykkel, int w);//constructor, som bare sender parameter til baseklassen.
};



#endif
