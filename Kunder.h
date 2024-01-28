#ifndef __KUNDER_H
#define __KUNDER_H

#include <string>
#include <list>
#include <iostream>
#include "Kunde.h"

class Kunder {
protected:
	int sisteNr;
	std::list <Kunde*> kundeListe;
public:
    void nyKunde();                     // oppretter kunde og legger i listen
    void handling(char valg);           // valg for kundebase
    Kunde* finnKunde(const int nr);     // returnerer peker til kunde
    void leverGjenstander();            // lever gjenstander fra kunde til valgt sted
	void finnGjenstand(int nr);         // finner hvilken kunde gjenstanden ligger hos
    void SkrivData1();                  // skriver data om en kunde og deres gjenstander
    void dataOmAlle();                  // skriver utvalgt data om alle kunder
	void hentGjenstand();               //
    void slettKunde();                  // sletter kunde
	void lesFraFil();                   // data om kunde fra fil
	void skrivTilFil();                 //  skriver data om kunde fra fil
    int kundeStorrelse();               //  hjelpefunksjon
    void finnKundeNr();

};


#endif

