#ifndef __ANNET_H
#define __ANNET_H

#include <iostream>
#include <string>
#include "Gjenstand.h"

//Elsparkesykkel er subklasse av Gjenstand
class Annet : public Gjenstand {
private:
	int antallWatt;
    int ID;
public:
	virtual void lesData();
	virtual void skrivData();  //skriver ut alle sine data

	int hentWatt();      //Sender tilbake antall watt
	~Annet() {std::cout<<"\nElsparkesykkel slettet\n\n";}

	Annet(const int nr, char annet, int w);//constructor, som bare sender parameter til baseklassen.
};



#endif
