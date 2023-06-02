#ifndef __Kajakk_H
#define __Kajakk_H


#include <iostream>
#include <string>
#include "Gjenstand.h"

//Kajakk er subklasse av Gjenstand
class Kajakk : public Gjenstand {
private:
	bool draSele;
public:
    bool dSele();
    void lesData();
	virtual void skrivData();
	Kajakk(const int nr, char Kajakk, bool dSele);




};


#endif
