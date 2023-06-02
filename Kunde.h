#ifndef __KUNDE_H
#define __KUNDE_H

#include <iostream>
#include <string>
#include <vector>
#include <list> 
#include "Gjenstand.h"
#include "conster.h"
#include "Padletur.h"

class Kunde {
protected:
    int IDnummer, mobilNummer;
    std::string navn;
    std::vector <Gjenstand*> gjenstander;
    std::list <Padletur*> padleTurer;
    float antKm;

public:
    void startPadletur();
    void avsluttPadletur();
    void salg(int pris);                        //For å regne ut steds inntjente kroner
    void visTur();
    Kunde(int nr, std::string nvn);
	Kunde(int ID, std::string nvn, int tlf);		   // Constructor for lesing fra fil
	int faktura();
    void skrivData();                     // Skriver data om valgt kunde og deres gjenstander
    void skrivDataALL()const;                  // Skriver data om alle kunder(forekorte data)
    int lesFraFil(std::ifstream& inn);        // Leser objektets data/
    void skrivTilFil(std::ofstream& ut);       // Skriver ALT til fil:
	void settInnGjenstand(Gjenstand* gjstnd);  // Pusher en gjenstand bakerst i vector
	std::string hentNvn() { return navn; }
    int hentID();
    void leverAlleGjenstander();            // Lever alle gjenstander fra kunde til sted
    void settID(int nr);
    bool finnGjenstand(int gjenstandNr); //// returner true om gjenstand er funnet hos kunde eller false
};


#endif

