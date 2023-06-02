#ifndef __GJENSTAND_H
#define __GJENSTAND_H

#include <iostream>
#include <string>
#include "enumer.h"

class Gjenstand {
protected:
	int gjenstandsNummer;
	gjenstandType type;
public:
    void skrivData();
	char hentType();        // Returnerer bare en char om hva slags type en gjendstand er
	virtual int hentID()const; // henter gjenstands nummer
	Gjenstand(const int nr, char valg); // Setter eget nummer/ID (ut fra parameters verdi)
	~Gjenstand();
};


#endif
