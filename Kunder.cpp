#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                //  FOR Å KUNNE BRUKE:  STLs  vector
#include <list>
#include "Kunder.h"
#include "lesData3.H"
#include "gfunc.h"
#include "Kunde.h"
#include <algorithm>
#include "Utleiesteder.h"

using namespace std;

extern Kunder gKundebase;
extern Utleiesteder gStedbase;


/**
*   Kundebase "main"
**/
void Kunder::handling(char valg){
	if (valg == 'M') {
		switch (lesInt("Tast inn funksjonsvalg for 'medlem'", 1, 15)) {		// Leser funksjonsvalg i rute 'kunde'
		case 1:	  padletur(); 		break;    //oppretter en ny kunde
		case 2:	avsluttPadletur();	break;
		case 3:	 nyKunde();			break;
		case 4:	 dataOmAlle();      break;    //skriver alle kundene ut
		case 5:	SkrivData1();       break;    //skriver alt om en gitt kunde ut
		case 6:	 finnKundeNr();  	break;    //henter gjenstander til kunder
		case 7:  hentGjenstand();   break;    //leverer gjenstander til steder
		case 8:	leverGjenstander(); break;    //sletter en kunde
		case 9:	slettKunde();		break;
		case 10: finnPadler();		break;

		default:	skrivMeny();		break;
		}
	}

}

void Kunder::padletur() {
	int mNr;
	char k;
	string navn;
	cout << "Du har valgt aa starte en padletur.\n\n";
	k = lesChar("Trykk 'A' for aa taste inn ditt medlemsnummer, 'B' for ditt brukernavn, 'C' for aa gaa tilbake");
	switch (k) {
	case 'A': mNr = lesInt("medlemsnummer:", 0, kundeListe.size()); 
				finnKunde(mNr)->startPadletur();					break;
	case 'B': do {
				do { cout << "Brukernavn: "; getline(cin, navn); cout << "Du tastet inn '" << navn << "' Er dette riktig? ('J'a/'N'ei)"; 
				   } while (lesChar("") == 'N');
					if (!finnKunde3(navn)) { cout << "Fant ikke medlem med dette brukernavn/navn. "; }
				} while (!finnKunde3(navn) && lesChar("Soke igjen? 'J'a/'N'ei") == 'J');
			finnKunde2(navn)->startPadletur(); break;
	case 'C': break;
	default: cout << "Trykk 'A' for å taste inn ditt brukernavn, 'B' for ditt medlemsnummer, 'C' for aa gaa tilbake";
	}
	
} 
void Kunder::finnPadler() {
	int mNr;
	char k;
	string navn;
	k = lesChar("Trykk 'A' for aa taste inn padlerens medlemsnummer, 'B' for han/hennes brukernavn, 'C' for aa gaa tilbake");
	switch (k) {
	case 'A': mNr = lesInt("medlemsnummer:", 0, kundeListe.size()); finnKunde(mNr)->visTur();	break;
	case 'B': do {
					do {
						cout << "Brukernavn: "; getline(cin, navn); cout << "Du tastet inn '" << navn << "' Er dette riktig? ('J'a/'N'ei)";
					} while (lesChar("") == 'N');
					if (!finnKunde3(navn)) { cout << "Fant ikke medlem med dette brukernavn/navn. "; }
			  } while (!finnKunde3(navn) && lesChar("Soke igjen? 'J'a/'N'ei") == 'J');
			  finnKunde2(navn)->visTur();				break;
	case 'C': break;
	default: cout << "Trykk 'A' for aa taste inn padlerens medlemsnummer, 'B' for han/hennes brukernavn, 'C' for aa gaa tilbake";
	}


}
void Kunder::avsluttPadletur() {
	int mNr;
	char k;
	string navn;
	cout << "\nRegistrer/avslutt padletur: \n";
	k = lesChar("Trykk 'A' for aa taste inn ditt medlemsnummer, 'B' for ditt brukernavn, 'C' for aa gaa tilbake");
	switch (k) {
	case 'A': mNr = lesInt("medlemsnummer:", 0, kundeListe.size());
		finnKunde(mNr)->avsluttPadletur();					break;
	case 'B': do {
		do {
			cout << "Brukernavn: "; getline(cin, navn); cout << "Du tastet inn '" << navn << "' Er dette riktig? ('J'a/'N'ei)";
		} while (lesChar("") == 'N');
		if (!finnKunde3(navn)) { cout << "Fant ikke medlem med dette brukernavn/navn. "; }
	} while (!finnKunde3(navn) && lesChar("Soke igjen? 'J'a/'N'ei") == 'J');
	finnKunde2(navn)->avsluttPadletur(); break;
	case 'C': break;
	default: cout << "Trykk 'A' for å taste inn ditt brukernavn, 'B' for ditt medlemsnummer, 'C' for aa gaa tilbake";
	}
	

}

bool Kunder::finnKunde3(string n) {

		auto it2 = find_if(kundeListe.begin(), kundeListe.end(),
			[n](const auto& val) { return(val->hentNvn() == n); });
		if (it2 != kundeListe.end()) {
			return true;
		}
		else {
			return false;
		}
}

Kunde* Kunder::finnKunde2(string n) {
bool funnet = false;
char ny;
do {
	auto it2 = find_if(kundeListe.begin(), kundeListe.end(),
		[n](const auto& val) { return(val->hentNvn() == n); });
	if (it2 != kundeListe.end()) {
		funnet = true;
		return *it2;                //  Retunerer peker til 'kunde'.
	}
	else funnet = false;  ny = lesChar("\nFant ikke dette medlemmet. Husk aa skille mellom stor og smaa bokstav, vil du soke igjen? (J)a/(N)ei");
} while (funnet == false && ny == 'J');
}

void Kunder::finnKundeNr() {
    string navn;
    bool funnet = false;
    char ny;
    do {
    cout <<  "\nBrukernavn eller navn: ";
    getline(cin, navn);
   // for (auto it = kundeListe.begin(); it != kundeListe.end(); it++) {
   // if ((*it)->hentNvn == navn) { //hvis matches, return true eller false
   // auto it = kundeListe.find(it->hentNvn());       // Gir brukeren meny over gjenstander på valgt sted
    //if (it != kundeListe.end()) {
        for (auto val : kundeListe) {
            if (navn == val->hentNvn()) {
                cout << "\nMedlemsnummeret til "<< navn << " er " << val->hentID();
                funnet = true;
            }
        } if (funnet == false) {
            ny = lesChar("\nFant ikke dette medlemmet. Husk aa skille mellom stor og smaa bokstav, vil du soke igjen? (J)a/(N)ei");
           }
    } while (funnet == false && ny == 'J');
}

/**
*   Spør kunde om kundeNr og lever dennes gjenstander
*  @see  Kunde::leverAlleGjenstander()
*  @see  kunder::finnKunde(nr)
*/
void Kunder::leverGjenstander() {

	if (!kundeListe.empty()) {
		int nr = lesInt("Kundenr: ", 0, kundeListe.size() - 1);
		finnKunde(nr)->leverAlleGjenstander();
		cout << "Kunde med nr: " << nr << " har nå levert fra seg alle gjenstandene sine.";
	}
	else
	{
		cout << "\n\tIngen kunder er registrert!\n";
	}
}

/**
* returnere størrelse til alle kunder
* @return  kundeListe.size();
*/
int Kunder::kundeStorrelse() {

    return kundeListe.size();
}

/**
*   Oppretter en ny kunde
*   @See: Kunde::Kunde
*   @see  kunde::hentID()
**/
void Kunder::nyKunde() {
    int ID;
    Kunde* kundeNy;
	string navn = "";	// Tomt navn
	bool eksisterer = false;
	char ny;

	ID = lesInt("Nytt medlems medlemsnummer: ", 0, 999999999999);     // Den nye kundens ID nummer blir en høyere enn den forrige
	sisteNr++;
	cout << "\n\tKundens IDnummer er " << ID;
    do {
        eksisterer = false;
         // Leser inn navn fra bruker
        cout << "\n\t\tNavn eller valgfritt brukernavn: "; getline(cin, navn);
        for (auto val : kundeListe) {
            if (navn == val->hentNvn()) {
                eksisterer = true;
            }
        }
        if (eksisterer == true) {
           ny = lesChar("\nDette navnet/brukernavnet eksisterer allerede, (J) for a prove et annet");
        }
    } while (eksisterer == true && ny == 'J');

    if (eksisterer == false) {
        kundeNy = new Kunde(ID, navn);          // opretter ny kunde med navn og ID
            kundeListe.push_back(kundeNy);      // legger inn i listen
                                          // sorterer listen
            kundeListe.sort([](Kunde* venstre, Kunde* hoyre)
                {return venstre->hentID() < hoyre->hentID(); });

            //Melding til brukeren om at kunden ble opprettet.
        cout << "\n\t\tNy kunde '" << navn << "' er Opprettet! Vennligst husk/noter ditt ID-nummer og/eller brukernavn.\n";
    }
}

/**
* Finner en gjenstand på et sted eller hos en kunde
* @see   kunde::finnGjenstand(nr)..
* @see   kunde::hentID()
*
*/
void Kunder::finnGjenstand(int nr)
{
	if (!kundeListe.empty()) { //kunder er ikke tomme
		if (nr>=0) {
			for (auto it = kundeListe.begin(); it != kundeListe.end(); it++) {
				if ((*it)->finnGjenstand(nr) == true) { //hvis matches, return true eller false
					cout << "\tGjenstanden er hos kunde nr: " << (*it)->hentID() << endl;
				}
			}
		}
		else
		{
			cout << "\tGjenstanden finnes ikke hos kunder" << endl;
		}

	}
	else { cout << "\n\tIngen kunder er registrert (eller gjenstanden finnes ikke)!\n"; }   // Det i parantes ble nødvendig i forhold til hvordan programmet ble.
}

/**
*   Finner og returnerer kundeobjekt med et bestemt IDnummer.
*
*   @return  peker til kunde
**/
Kunde* Kunder::finnKunde(const int nr) {

    auto it2 = find_if(kundeListe.begin(), kundeListe.end(),
                   [nr] (const auto & val) { return(val->hentID() == nr); } );
    if (it2 != kundeListe.end()) {

        return *it2;                //  Retunerer peker til 'kunde'.
    }                               //
                                    //
                                    //  Ikke funnet:
    return nullptr;
}
/**
*   Skriver data om alle kunder
*   @see kunde::skrivDataAll()
**/
void Kunder::dataOmAlle() {

	if (!kundeListe.empty()) {

		cout << "\n\tAlle kundene i registrert (totalt " << kundeListe.size() << " stk):\n";

		for (const auto& val : kundeListe) {

			val->skrivDataALL();
		}
	}
	else
		cout << "\n\tKundelisten er tom!\n";
}

/**
*
*   Sletter en kunde
*   @see  kunder::finnKunde(nr)
*   @see  kunde::skrivData()
*   @see  leverAlleGjenstander()
*   @see  Kunde::faktura()
**/
void Kunder::slettKunde() {
    //Kunde* k;
    char svar;
    int nr;

	if (!kundeListe.empty()) { //sjekker om det finnes kunder først
		nr = lesInt("Kundenummer på kunden du vil slette?: ", 0, sisteNr - 1);
		cout << "Du har valgt kunde: \n\n";
		finnKunde(nr)->skrivData();
		svar = lesChar("\nEr du sikker på at du vil slette denne kunden? (J)/(N)");
		if (svar == 'J') {
			finnKunde(nr)->leverAlleGjenstander();
			cout << "Kunde med nr: " << nr << " har nå levert fra seg alle gjenstandene sine.";
			kundeListe.remove(finnKunde(nr));
			cout << "\nKunde med IDnummer " << nr << " er nå slettet!\n";
		}
		else { cout << "Ok, kunden ble ikke slettet.\n\n"; }

	}
	else
		cout << "\n\tKundelisten er tom!\n";
}

/**
*	Henter gjenstand fra et sted til kunde
*
*   @see   kunder::finnKunde(nr)
*   @see   kunde::hentID()
*   @see   utleiesteder::finnSted(navn)
*   @see   kunde::settInnGjenstand(gjenstand)
*   @see   utleiesteder::hentGjenstandTilKunde(navn, type, antall)
**/
void Kunder::hentGjenstand() {


	if (!kundeListe.empty()) {

	int nr = lesInt("\tKundens ID:", 0, sisteNr - 1);	//leser ønsket kunde nummer

		Kunde* kunde = finnKunde(nr);

		if (kunde->hentID() >= 0) {				// Hvis ønsket kunde er funnet

			string navn = "";	// Tomt navn
			cout << "\nNavn(Sted): ";
			getline(cin, navn); // Leser inn stednavn fra bruker

			//if (gStedbase.finnSted(navn)) {
				gjenstandType type;		// Gjenstandstype valg

				cout << "\n Kajakk(0), Kano(1), Annet(2)";
				switch (lesInt("\nTast inn type gjenstand for innhenting", 0, 2)) { // Leser gjenstandsvalg og setter ønsket enum verdi
				case 0:	type = kajakk;			break;
				case 1:	type = kano;			break;
				case 2:	type = annet;	        break;
				default:						break;
				}

				// Les inn antall gjenstander ønsket for flytting
				int antall = lesInt("\nTast inn antall som skal hentes", 1, 1000);

				// Henter en liten vector inneholdene ønskede gjenstander fra sted
				vector <Gjenstand*> gjenstandKopi = gStedbase.hentGjenstandTilKunde(navn, type, antall);

				// Sjekker om at ønskede gjenstander er hentet
				if (!gjenstandKopi.empty()) {
					int antallGjenstander = gjenstandKopi.size();	// Henter antall gjenstander
					for (int i = 0; i < antallGjenstander; i++) {
						Gjenstand* gj = gjenstandKopi.back();		// Velger gjenstand
						gjenstandKopi.pop_back();					// Fjerner gjenstand peker fra kopi
						kunde->settInnGjenstand(gj);				// Pusher inn gjenstand
					}

					cout << "\nGjenstander er nå hos medlem!";
				}
			//}
			//else {
			//	cout << "\nDette stedet finnes ikke i registeret!";
			}
		}

	else {
		cout << "\n\tIngen kunder er registrert!\n";
	}
}

/**
*   Skriver data om valgt kunde i kundeListen
*   @see   kunder::finnKunde(nr)
*   @see   kunde::skrivData()
**/
void Kunder::SkrivData1() {
    Kunde* kundeValg;
    int kundeNr;
	if (!kundeListe.empty()) { // sjekker om det finnes kunder først
		kundeNr = lesInt("\n\tKundenummer det skal skrives om: ", 0, kundeListe.size() - 1);
		kundeValg = finnKunde(kundeNr);
		kundeValg->skrivData();
	}
	else
		cout << "\n\tKundelisten er tom!\n";
}

/**
 * Leser steddata fra fil og setter de inn i Kunder vector
 *
 * @see Kunde::lesFraFil()
 **/
void Kunder::lesFraFil() {
	string navn;
	int tlf, ID;
	ifstream innfil("KUNDER.DTA");

	if (innfil) {
		int kundeAntall = 0;	    // Init antall kunder (telling starter på 0)
		int gjenstandAntall = 0;	// Antall gjenstander

		while (!innfil.eof()) {
			innfil >> ID;				// Henter inn ID for kunde
			innfil >> navn;				// Navn
			innfil >> tlf;				// Mobilnummer

			Kunde* kunde = new Kunde(ID, navn, tlf);	// Initierer sted objekt med navn
			// Leser inn gjenstander for sted og teller antall gjenstander totalt fra
			// Alle steder er lest fra filen.
			gjenstandAntall += kunde->lesFraFil(innfil);
			innfil.ignore();	// ignorer tomt rom mellom '_' og nytt ID
			// Setter inn sted og sine gjenstander inne i map Steder
			kundeListe.push_back(kunde);      // legger inn i listen
			kundeAntall++;					  // Øker antall kunder
		}
		// Oppdaterer antall kunder hos kundes sisteNr
		sisteNr += kundeAntall;
		// Oppdaterer antall gjenstander hos utleiesteds sisteNr
		gStedbase.oppdaterSisteNr(gjenstandAntall);
	}
	else {
		cout << "\nKUNNE IKKE LESE .DTA FOR KUNDER\n";
	}
}

/**
 * Leser kundedata fra kundeListe og setter de inn i en fil
 *
 * @see Kunde::skrivTilFil()
 **/
void Kunder::skrivTilFil() {
	ofstream utfil("KUNDER.DTA");
	// Itererer gjennom hvert eneste sted i Steder vector
	// Og skriver ut stedets data og gjenstander
	for (auto const &it : kundeListe)
	{
		it->skrivTilFil(utfil);
		if (it != kundeListe.back()) {		// sjekker at verdien til it ikke er siste i listen
			utfil << "\n";					// hvis ikke er slutten av løkken, så passer på ingen ekstra tomt rom etter siste "_"
		}
	}
}
