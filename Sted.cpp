#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                 //  FOR � KUNNE BRUKE:  STLs  vector
#include "Sted.h"
#include "LesData3.h"			   // Verdi innlesningsverkt�y
#include "Gjenstand.h"
#include <algorithm>
#include "conster.h"

using namespace std;


/**
 * Tom constructor
 **/
Sted::Sted() {}

/**
 * Constructor bruker stedsnavn som parameter for � lese inn informasjon
 * og opprette et unikt sted
 *
 * @param nvn - Unikt navn til sted
 **/
Sted::Sted(string nvn) {
	IDsted = nvn;					// Unikt identifiserende navn til Sted

	// Beskrivelse av sted leses inn
	cout << "\n\tBeskrivelse: ";
	getline(cin, beskrivelse);

	// Tlf av sted leses inn
	telefonnummer = lesInt("\n\tTelefonnummer: ", 0, 99999999);

	// Inntjente kroner av sted leses inn
	inntjente = lesInt("\n\tInntjente kroner: ", MININNTJENTE,MAXINNTJENTE );
}

/**
 * Constructor bruker stedsnavn, beskrivelse, tlf og tjente penger som parameter for � lese inn informasjon
 * og opprette et unikt sted
 *
 * @param nvn	- Unikt navn til sted
 * @param beskr - Beskrivelse av sted
 * @param tlf	- Stedets telefonnummer
 * @param tjent - Stedets inntjente penger
 **/
Sted::Sted(string nvn, string beskr, int tlf, int tjent) {
	IDsted = nvn;		// Unikt identifiserende navn til Sted
	beskrivelse = beskr;
	telefonnummer = tlf;
	inntjente = tjent;
}

/**
 * Tom destructor
 **/
Sted::~Sted() {}

/**
 * Skriver ut generell data om stedet inkludert
 * Navn, telefonnummer, antall gjenstander til utleie av hver type
 *
 **/
void Sted::skrivGenerellData() const {
	cout << "\nNavn: " << IDsted << "\n\t"
		<< "Beskrivelse: " << beskrivelse << "\n\t"
		<< "Telefonnummer: " << telefonnummer << "\n\t"
		<< "Inntjent: " << inntjente << "\n\t"
		<< "Antall Gjenstander:" << "\n\t\t"
		<< "Kajakkr: " << Kajakkr.size() << "\n\t\t"
		<< "Kanoer: " << Kanoer.size() << "\n\t\t"
		<< "Annet: " << Annet.size() << "\n";
}

/**
 * Skriver ut all data om stedet inkludert
 * Navn, telefonnummer, antall gjenstander til utleie av hver type
 * og unike nummer til hvert gjenstand
 *  @see   sted::finnGjenstand(nr)
 *  @see   gjenstand::hentID()
 *
 **/
void Sted::skrivData() {
	cout << "\nNavn: " << IDsted << "\n\t"
		<< "Beskrivelse: " << beskrivelse << "\n\t"
		<< "Telefonnummer: " << telefonnummer << "\n\t"
		<< "Inntjent: " << inntjente << "\n\t"
		<< "Antall Gjenstander:" << "\n\t\t";
	// Itererer gjennom hvert gjenstandsklasse og skriver ut unikt nummer for
	// lagret gjenstand i dette stedet p� hver sin linje.
	cout << "Kajakkr: " << Kajakkr.size() << "\n\t\t";
	for (int i = 0; i < Kajakkr.size(); i++) {
        if (finnGjenstand(Kajakkr[i]->hentID())) {
            cout << Kajakkr[i]->hentID() << "\n\t\t"; }  else { cout<<""; }
	}
	cout << "Kanoer: " << Kanoer.size() << "\n\t\t";
	for (int i = 0; i < Kanoer.size(); i++) {
        if (finnGjenstand(Kanoer[i]->hentID())) {
            cout << Kanoer[i]->hentID() << "\n\t\t"; }  else { cout<<""; }
	}
	cout << "Annet: " << Annet.size() << "\n\t\t";
	for (int i = 0; i < Annet.size(); i++) {
	    if (finnGjenstand(Annet[i]->hentID())) {
            cout << Annet[i]->hentID() << "\n\t\t"; }  else { cout<<""; }
	}
}

/**
 * Skriver ut data om inntjente penger og ID stedet inkludert
 *
 **/
void Sted::skrivTjent() const {
	cout << "\nNavn: " << IDsted << "\tInntjente: " << inntjente;
}

/**
*   @see int Kunde::faktura()
*   @see void Kunde::leverAllegjenstander()
*/
void Sted::fortjeneste(int penger) {
    inntjente += penger;

}
//
/**
 * Skriver ut ID av stedet, telefon og antall gjenstander p� lager
 * etter �nsket gjenstandstype
 *
 **/
void Sted::skrivGjenstand(gjenstandType type) const {
	switch (type) { // sjekker �nsket gjenstandstype
	case Kajakk:
		if (!Kajakkr.empty()) { // Kajakkvector har gjenstander
			// Skriver ut antall og info
			cout << "\nNavn: " << IDsted << "\tTelefonnummer: " << telefonnummer << "\tAntall Kajakkr: " << Kajakkr.size();
		}
		break;
	case Kano:
		if (!Kanoer.empty()) { // Kanovector har gjenstander
			// Skriver ut antall og info
			cout << "\nNavn: " << IDsted << "\tTelefonnummer: " << telefonnummer << "\tAntall Kanoer: " << Kanoer.size();
		}
		break;
	case elsparkeKano:
		if (!Annet.empty()) { // ElsparkeKanovector har gjenstander
			// Skriver ut antall og info
			cout << "\nNavn: " << IDsted << "\tTelefonnummer: " << telefonnummer << "\tAntall Annet: " << Annet.size();
		}
		break;
	default:
		break;
	}
}

/**
 * Leser steddata fra fil
 * og setter de inn i gjenstand vectorer (Kajakkr, Kanoer, Annet).
 * Teller ogs� opp antall gjenstander for oppdatering av 'sisteNr' i Utleiested objekt
 * gjID for gjenstander
 *
 * @param inn - fil parameter for innlesning av gjenstander
 * @return siste gjenstandsnummer telt
 **/
int Sted::lesFraFil(ifstream &inn) {
	char charBuffer = '.';	// tegnbuffer for innlesning fra fil init med '.' for ingen endring i sted
	int intBuffer;			// tallbuffer for innlesning fra fil
	int gjAntall = 0;		// Antall gjenstander talt opp for dette stedet
	int gjID;				// gjenstandsID hentet fra fil
	int watt;				// Antall watt p� elsparkeKano
	bool dSele, tilhenger;	// Tilbeh�r for Kajakk eller Kano


	while (charBuffer != '_') {	// Ikke slutt av gjenstandinnhenting
		switch (charBuffer) {
		case 'T':
		{
			inn >> intBuffer; gjID = intBuffer;		 // leser inn gjenstandsID
			inn >> intBuffer; dSele = intBuffer;	 // leser inn tilbeh�r/spec
			Kajakkr.push_back(new Kajakk(gjID, charBuffer, dSele));	// Setter inn Kajakk
		}
		break;
		case 'S':
		{
			inn >> intBuffer; gjID = intBuffer;		 // leser inn gjenstandsID
			inn >> intBuffer; tilhenger = intBuffer; // leser inn tilbeh�r/spec
			Kanoer.push_back(new Kano(gjID, charBuffer, tilhenger));	// Setter inn Kano
		}
		break;
		case 'E':
		{
			inn >> intBuffer; gjID = intBuffer;		 // leser inn gjenstandsID
			inn >> intBuffer; watt = intBuffer;		 // leser inn tilbeh�r/spec
			Annet.push_back(new ElsparkeKano(gjID, charBuffer, watt)); // Setter inn elsparkeKano
		}
		break;

		default:
			break;
		}
		if (charBuffer == 'T' || charBuffer == 'S' || charBuffer == 'E') {	// Sjekker at en gjenstand er lagt inn
			gjAntall++;		// �ker antall gjenstander lagt inn
		}
		inn >> charBuffer;		// Leser inn tegn for gjenstand('T', 'S', 'E') eller slutt av gjenstandinnhenting '_'
	}
	return gjAntall;
}

/**
 * Leser steddata og gjenstander fra stedet og setter de inn i en fil
 *
 * @see Gjenstand::hentID()
 * @see Kajakk::dSele()
 * @see Kano::harTilhenger()
 * @see ElsparkeKano::hentWatt()
 **/
void Sted::skrivTilFil(ofstream &ut) {					// Skriver til fil:
	ut << IDsted << "\n";								// Stedets navn/ID
	ut << beskrivelse << "\n";							// Beskrivelse
	ut << telefonnummer << "\t" << inntjente << "\n";	// Telefon og inntjente penger
	// Itererer gjennom alle gjenstand vectorer og skriver ut deres data
	for (auto it = kajakker.begin(); it != kajakker.end(); it++) {
		ut << "\t" << "T " << (*it)->hentID() << " ";
		if ((*it)->dSele()) { ut << 1; }		// Sjekker om har drasele eller ikke
		else { ut << 0; }
		ut << "\n";
	}
	for (auto it = kanoer.begin(); it != kanoer.end(); it++) {
		ut << "\t" << "S " << (*it)->hentID() << " ";
		if ((*it)->harTilhenger()) { ut << 1; }	// sjekker om har tilhenger eller ikke
		else { ut << 0; }
		ut << "\n";
	}
	for (auto it = annet.begin(); it != annet.end(); it++) {
		ut << "\t" << "E " << (*it)->hentID() << " " << (*it)->hentWatt() << "\n";
	}
	ut << "_";

}

/**
 * legger bakerst gjenstander
 *
  **/
void Sted::settInnKajakk(Kajakk* trl) {
	kajakker.push_back(trl);
}

/**
 *  legger bakerst gjenstander
 *
  **/
void Sted::settInnKano(Kano* sykl) {
	kanoer.push_back(sykl);
}

/**
 *  legger bakerst gjenstander
 *
 **/
void Sted::settInnAnnet(Annet* els) {
	annet.push_back(els);
}

/**
 * Lager en kopi av Kajakkn bakerst i vectoren, sletter original
 * og sender tilbake kopi
 *
 * @return Kopien av Kajakk objekt
 **/
Kajakk* Sted::taKajakk() {
	Kajakk* kopi = kajakker.back();		// Kopier bakerste Kajakk
	kajakker.pop_back();                 // Fjern bakerste Kajakk
	return kopi;						// Send tilbake kopi
}

/**
 * Lager en kopi av Kanoen bakerst i vectoren, sletter original
 * og sender tilbake kopi
 *
 * @return Kopien av Kano objekt
 **/
Kano* Sted::taKano() {
	Kano* kopi = kanoer.back();		// Kopier bakerste Kano
	kanoer.pop_back();                  // Fjern bakerste Kano
	return kopi;						// Send tilbake kopi
}

/**
 * Lager en kopi av elsparkeKanoen bakerst i vectoren, sletter original
 * og sender tilbake kopi
 *
 * @return Kopien av ElsparkeKano objekt
 **/
Annet* Sted::taAnnet() {
	Annet* kopi = annet.back();	// Kopier bakerste elsparkeKano
	annet.pop_back();						// Fjern bakerste elsparkeKano
	return kopi;									// Send tilbake kopi
}

/**
 * Sender tilbake st�rrelse av Kajakkvector
 *
 * @return int med st�rrelseverdi for Kajakkr
 **/
int Sted::antKajakker() {
	return Kajakker.size();
}

/**
 * Sender tilbake st�rrelse av Kanovector
 *
 * @return int med st�rrelseverdi for Kanoer
 **/
int Sted::antKanoer() {
	return kanoer.size();
}

/**
 * Sender tilbake st�rrelse av ElsparkeKanovector
 *
 * @return int med st�rrelseverdi for Annet
 **/
int Sted::antAnnet() {
	return annet.size();
}
/**
 *  sletter en bestemt Kajakk
 *  NB dens plass i vector blir desverre ikke erstattet med en annen
 *  (Det vil heldigvis tatt en stund f�r vector sprenges da det bare er snakk om ett sted)
 *  @see  gjenstand::hentID()
 *  @param  gjenstandNr
 **/
void Sted::slettKajakk(int gjenstandNr) {
    if (!kajakker.empty()) {
        for (auto it = kajakker.begin(); it != kajakker.end(); it++) {
            if ((*it)->hentID() == gjenstandNr) { //hvis matches return true eller false
                delete *it;  // // sletter gjenstanden og dens plass i vektoren
                *it = nullptr;
                it = kajakker.erase(it);

                break;
            }
        }
    }  else cout <<"\nERROR: Ingen Kajakkr paa lager!";
}
/**
 *  sletter en bestemt Kano
 *  NB dens plass i vector blir desverre ikke erstattet med en annen
 *  (Det vil heldigvis tatt en stund f�r vector sprenges da det bare er snakk om ett sted)
 *  @see   gjenstand::hentID()
 *  @param  gjenstandNr
 */
void Sted::slettKano(int gjenstandNr) {
    if (!kanoer.empty()) {
        for (auto it = kanoer.begin(); it != kanoer.end(); it++) {
            if ((*it)->hentID() == gjenstandNr) { //hvis matches return true eller false
                delete *it;  // // sletter gjenstanden og dens plass i vektoren
                *it = nullptr;
                it = kanoer.erase(it);
                break;
            }
        }
    }   else cout <<"\nERROR: Ingen Kanoer paa lager!";
}
/**
 *  sletter en bestemt ElsparkeKano
 *  NB dens plass i vector blir desverre ikke erstattet med en annen
 *  (Det vil heldigvis tatt en stund f�r vector sprenges da det bare er snakk om ett sted)
 *  @see    gjenstand::hentID()
 *  @param  gjenstandNr
 **/
void Sted::slettAnnet(int gjenstandNr) {
    if (!Annet.empty()) {
        for (auto it = annet.begin(); it != annet.end(); it++) {
            if ((*it)->hentID() == gjenstandNr) { //hvis matches return true eller false
                delete *it;  // sletter gjenstanden og dens plass i vektoren
                *it = nullptr;
                it = annet.erase(it);
                break;
            }
        }
    }   else cout<<"\nERROR: Ingen Annet paa lager!";
}

/**
*  g�r gjennom alle tre gjenstand vectorer og returner true n�r sted med gjenstand er funnet
* @param  gjenstandNr -
* @see    gjenstand::hentID()..
* @return hvis en gjenstand matcher returner true eller false hvis det ikke matcher.
*/
bool Sted::finnGjenstand(int gjenstandNr)
{

	for (auto it = kajakker.begin(); it != kajakker.end(); it++) {
		if ((*it)->hentID() == gjenstandNr) { //hvis matches return true eller false
			return true;  // gjenstand er funnet
		}
	}


	for (auto it = kanoer.begin(); it != kanoer.end(); it++) {
		if ((*it)->hentID() == gjenstandNr) { //hvis matches return true eller false
			return true;  // gjenstand er funnet
		}
	}

	for (auto it = annet.begin(); it != annet.end(); it++) {
		if ((*it)->hentID() == gjenstandNr) { //hvis matches return true eller false
			return true;  // gjenstand er funnet
		}
	}


	return false;                    // gjenstand er ikke funnet

}

/**
*  Henter en vector av gjenstander fra sted for utl�n
*  Sjekker f�rst om det er mulig ved � teste type og antall �nskede gjenstander
*  @see    sted::antKajakk()
*  @see    sted::taKajakk()
*  @see    sted::antKano()
*  @see    sted::taKano()
*  @see    sted::antElsparkeKano()
*  @see    sted::taElsparkeKano()
*/
vector <Gjenstand*> Sted::leiGjenstand(gjenstandType typ, int ant) {
	vector <Gjenstand*> kopi;

	if (typ == Kajakk) {
		// Henter st�rrelse av eksisterende Kajakk vector for feilbehandlig
		int antallKajakker = antKajakker();

		// Passer p� at vector ikke er tom
		// og eventuelt at �nsket antall gjenstander er mindre eller lik
		// antall gjenstander i vectoren
		if (antallKajakker > 0 && antallKajakker >= ant) {
			for (int i = 0; i < ant; i++) {						// Flytter s� mange elementer som �nsket
				kopi.push_back(taKajakk());						// Kopierer pekeren til midlertidig lager
			}
		}
		else {
			cout << "\n\nIkke nok gjenstander � leie!";
		}
	}
	else if (typ == Kano) {
		// Henter st�rrelse av eksisterende Kano vector for feilbehandlig
		int antallKanoer = antKanoer();

		// Passer p� at vector ikke er tom
		// og eventuelt at �nsket antall gjenstander er mindre eller lik
		// antall gjenstander i vectoren
		if (antallKanoer > 0 && antallKanoer >= ant) {
			for (int i = 0; i < ant; i++) {						// Flytter s� mange elementer som �nsket
				kopi.push_back(taKano());						// Kopierer pekeren til midlertidig lager
			}
		}
		else {
			cout << "\n\nIkke nok gjenstander � leie!";
		}
	}
	else {
		// Henter st�rrelse av eksisterende elsparkeKano vector for feilbehandlig
		int antallAnnet = antAnnet();

		// Passer p� at vector ikke er tom
		// og eventuelt at �nsket antall gjenstander er mindre eller lik
		// antall gjenstander i vectoren
		if (antallAnnet > 0 && antallAnnet >= ant) {
			for (int i = 0; i < ant; i++) {						// Flytter s� mange elementer som �nsket
				kopi.push_back(taAnnet());				//  Kopierer pekeren til midlertidig lager
			}
		}
		else {
			cout << "\n\nIkke nok gjenstander � leie!";
		}
	}

	// Sender tilbake tom eller fylt vector med gjenstander for prossessering
	return kopi;
}

