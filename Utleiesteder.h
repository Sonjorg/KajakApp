#ifndef __UTLEIESTEDER_H
#define __UTLEIESTEDER_H

#include <iostream>
#include <map>
#include <string>
#include "Sted.h"


class Utleiesteder {
private:
	int sisteNr;	// Opptelling av steder
	std::map <std::string, Sted*> Steder;

public:
	// STED
	Utleiesteder();							// Constructor starter opptelling av antall steder
	~Utleiesteder();						// Tom destructor
	void handling(char valg);				// Handling av brukerforesp�rsel
	void skrivAlleSteder() const;			// Skriver generell info om alle steder
	bool finnSted(std::string nvn);
	Sted* finnSted2(std::string nvn);		// Peker til �nsket sted om det finnes
	void skrivInntjent() const;				// Skriver inntjente penger fra alle steder
	void skrivAltOmEtSted() const;			// Skriver detaljert info om ett sted
	void skrivGjenstandAntall() const;		// Skriver gjenv�rende antall gjenstand av en type for alle steder
	void nyttSted();						// Oppretter nytt sted
	void slettSted();						// Sletter sted
	void lesFraFil();						// Leser sted data fra fil
	void skrivTilFil();						// Skriver sted data til fil

	// GJENSTAND
	void nyGjenstand();                     //oppretter ny gjenstand
	void gjenstandSok();					// S�ker etter en gjenstand hos Kunder og Steder
	void oppdaterSisteNr(int ant);
	bool finnGjenstand(int nr);             //returnerer true om gjenstand finnes
	void slettGjenstand();                  // sletter vallgt gjenstand p� valgt sted
	void flyttGjenstand();					// Overf�r gjenstand mellom steder
	std::vector <Gjenstand*> hentGjenstandTilKunde(std::string nvn, gjenstandType typ, int ant);	// Henter en vector med gjenstander fra et sted

};

#endif

