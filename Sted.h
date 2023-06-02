#ifndef __STED_H
#define __STED_H

#include <iostream>
//#include <functional>
#include <vector>
#include <string>
#include "enumer.h"
#include "KAJAKK.H"
#include "KANO.H"
#include "ANNET.H"
#include "Gjenstand.h"

class Sted {
private:
	std::string IDsted, beskrivelse;
	int telefonnummer, inntjente;
	//std::vector <Gjenstand*> gjenstander;
	std::vector <Kajakk*> kajakker;
	std::vector <Kano*> kanoer;
	std::vector <Annet*> andre;


public:

	Sted();												// Tom constructor
	Sted(std::string nvn);								// Constructor for oppretting av unikt sted(bruker)
	Sted(std::string ID, std::string beskr, int tlf, int tjent);  // Constructor for oppretting av unikt sted(fil)
	~Sted();
	void fortjeneste(int penger);
	void skrivGenerellData() const;						// Skriver ut generell data
	void skrivData() ;								// Skriver ut all data
	void skrivTjent() const;							// Returnerer inntjente og ID
	void skrivGjenstand(gjenstandType type) const;		// Skriver ut ID, tlf og antall gjenstand
	int lesFraFil(std::ifstream &inn);					// Leser gjenstand data fra fil inn i vector
	void skrivTilFil(std::ofstream &ut);				// Leser Sted og Gjenstand data og skriver til fil
	virtual void settInnKajakk(Kajakk* trl);					// Pusher en Kajakk bakerst i vector
	virtual void settInnKano(Kano* sykl);					// Pusher en Kano bakerst i vector
	virtual void settInnAnnet(Annet* els);    // Pusher en elsparkeKano bakerst i vector
	Kajakk* taKajakk();									// Kopierer og popper en Kajakk fra vector
	Kano* taKano();									// Kopierer og popper en Kano fra vector
	Annet* taAnnet();					// Kopierer og popper en elsparkeKano fra vector
	int antKajakker();									// Henter størrelse av Kajakkvector
	int antKanoer();									// Henter størrelse av Kanovector
	int antAnnet();							// Henter størrelse av ElsparkeKanovector
	bool finnGjenstand(int gjenstandNr);                // returner true om gjenstand er funnet eller false
	void slettKajakk(int gjenstandNr);                  // sletter 1 Kajakk av gitt gjNr
	void slettKano(int gjenstandNr);                  // sletter 1 Kano av gitt gjNr
	void slettAnnet(int gjenstandNr);          // sletter 1 elsparkeKano av gitt gjNr
	std::vector <Gjenstand*> leiGjenstand(gjenstandType typ, int ant); // Henter en kopi av gjenstander kunde vil leie
};


#endif
