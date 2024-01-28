#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>				   //  FOR Å KUNNE BRUKE:  STLs  vector
#include <fstream>
#include <map>
#include <list>
#include "LesData3.h"			   // Verdi innlesningsverktøy
#include "Utleiesteder.h"
#include "conster.h"
#include "Kunde.h"
#include "Kunder.h"
#include "Sted.h"
using namespace std;

// Global variabel definert i MAIN.CPP
extern Utleiesteder gStedbase;
extern Kunder gKundebase;


/**
 * Constructor
 **/
Utleiesteder::Utleiesteder() {
	sisteNr = 0;	// Starter opptelling av steder
}

/**
 * Tom destructor
 **/
Utleiesteder::~Utleiesteder() {}

/**
 * Funksjonen behandler funksjonsvalg for 'Sted' og 'Gjenstand' rutene i programmet
 *
 * @param valg - parameter tilført funksjonen for valg av rute Sted ('S') eller Gjenstand ('G')
 **/
void Utleiesteder::handling(char valg) {
	// Velger rute
	if (valg == 'S') {
		switch (lesChar("Tast inn funksjonsvalg for (S)ted")) {		// Leser funksjonsvalg i rute 'Sted'
		case 'N':	nyttSted();				break;    // Oppretter nytt sted
		case 'A':	skrivAlleSteder();		break;    // Skriver ut alle steder
		case '1':	skrivAltOmEtSted();		break;    // Skriver ut alt om ett sted
		case 'T':	skrivInntjent();		break;    // Skriver ut alle steders inntjente penger
		case 'I':	skrivGjenstandAntall();	break;    // Skriver ut alle steder som har en spesifik gjenstand på lager
		case 'O':	flyttGjenstand();		break;    // Overfører et antall gjenstander fra et sted til et annet

		case 'S':	slettSted();			break;    // Sletter et sted (Overfører stedets gjenstander til annet sted)
		default:							break;
		}
	}
	else if (valg == 'G') {            // Leser funksjonsvalg i rute 'Gjenstand'
		switch (lesChar("Tast inn funksjonsvalg for (G)jenstand-'N'-'F'-'S':")) {
		case 'N':	nyGjenstand();		break;  //oppretter en ny gjenstand
		case 'F':	gjenstandSok(); 	break;      //finner en gjenstand

		case 'S':	slettGjenstand();	break;  //sletter en gjenstand
		default:						break;
		}
	}
}

/**
 * Leser inn et stedsnavn og oppretter et nytt 'Sted' med navnet hvis det er unikt
 *
 * @see Sted::Sted(...)
 **/
void Utleiesteder::nyttSted() {
	string navn = "";	// Tomt navn
	cout << "\nNavn: ";
	getline(cin, navn); // Leser inn navn fra bruker

	// Søker etter om navnet finnes allerede
	auto it = Steder.find(navn);

	if (it == Steder.end()) { // Oppretter nytt sted hvis navn er unikt
		// Fører inn nytt Sted i map med navn som key
		Steder.insert(pair<string, Sted*>(navn, new Sted(navn)));
		//Melding til brukeren om at sonen ble opprettet.
		cout << "\nNytt sted '" << navn << "' er Opprettet!";
	}
	else {					  // Melding om navnet ikke er unikt
		cout << "\nDette stedet finnes allerede!";
	}
}

/**
 * Skriver ut generell info om alle steder registrert
 *
 * @see Sted::skrivGenerellData()
 **/
void Utleiesteder::skrivAlleSteder() const {
	if (!Steder.empty()) {
		for (auto const& it : Steder)	// Går gjennom alle steder
		{
			it.second->skrivGenerellData(); // Sted skriver sin egen data
		}
	}
	else
		cout << "\n\tIngen steder er registrert!\n";
}

/**
 * Leser inn et stedsnavn og skriver ut alt info om stedet hvis det finnes
 *
 * @see Sted::skrivData()
 **/
void Utleiesteder::skrivAltOmEtSted() const {
	string navn = "";	// Tomt navn

	if (!Steder.empty()) { // sjekker om det finnes steder først
		cout << "\nNavn: ";
		getline(cin, navn); // Leser inn navn fra bruker

		// Søker etter om navnet finnes allerede
		auto it = Steder.find(navn);

		if (it != Steder.end()) { // Skriver ut data om stedsnavnet er funnet
			// Kaller for stedet å skrive sin egen data
			it->second->skrivData();
		}
		else {					  // Melding om navnet ikke er funnet
			cout << "\nDette stedet finnes ikke i registeret!";
		}
	}
	else
		cout << "\n\tIngen steder er registrert!\n";
}


/**
*  ser etter navn på steder
*  @param     string nvn
*  @return    returnere navn om det finnes
*/
Sted* Utleiesteder::finnSted2(string nvn) {
    //string navn;
	//navn = nvn;


	// Søker etter om navnet finnes allerede
	auto it = Steder.find(nvn);

	if (it != Steder.end()) {
		return (*it).second;
	}
	else {					  // Melding om navnet ikke er funnet
		cout << "\nDette stedet finnes ikke i registeret!";
		return nullptr;
	}
}

/**
 * Itererer gjennom Steder og returnerer true om parameter
 * for stednavn samsvarer med sted som finnes
 *
 * @return Om sted finnes eller ikke
 **/
bool Utleiesteder::finnSted(string nvn) {
	// Søker etter om navnet finnes allerede
	auto it = Steder.find(nvn);

	if (it != Steder.end()) { // Return true om stedet er funnet
		return true;
	}
	else {					  // Return false stedet ikke er funnet
		return false;

	}
}

/**
 * Skriver ut inntjente penger og navn om alle steder registrert
 *
 * @see Sted::skrivTjent()
 **/
void Utleiesteder::skrivInntjent() const {

	if (!Steder.empty()) { //sjekker om det finnes steder først
		for (auto const& it : Steder)	// Går gjennom alle steder
		{
			it.second->skrivTjent(); // Sted skriver sin egen data
		}
	}
	else
		cout << "\n\tIngen steder er registrert!\n";
}

/**
 * Øker sisteNr for gjenstander med sendt inn parameter
 *
 **/
void Utleiesteder::oppdaterSisteNr(int ant) {
	sisteNr += ant;
}

/**
 * Spør om et steds navn og sletter stedet etter bekreftelse fra bruker
 *
 * @see Sted::antKajakkr()
 * @see Sted::antSykler()
 * @see Sted::antElsparkesykler()
 * @see Sted::taKajakk()
 * @see Sted::taKano()
 * @see Sted::taElsparkeKano()
 * @see Sted::settInnKajakk()
 * @see Sted::settInnKano()
 * @see Sted::settInnElsparkeKano()
 **/
void Utleiesteder::slettSted() {
	string navn = "";		// Tomt navn

	if (!Steder.empty()) { //sjekker om det finnes steder først
		cout << "\nNavn: ";
		getline(cin, navn);		// Leser inn navn fra bruker
		bool flyttet = false;	// Sjekker om gjenstander er flyttet
		char valg;				// Sjekker om bruker bekrefter at de vil slette

		// Sjekker om valgt sted finnes
		auto it = Steder.find(navn);

		if (it != Steder.end()) { // Spør bruker om bekreftelse hvis funnet

			valg = lesChar("\nEr du sikker på at du vil slette dette stedet? (J/n)");	// Spør om bekreftelse
			if (toupper(valg) == 'J') {
				// Går gjennom alle gjenstander til valgt sted og flytter de til nyeste registrerte sted
				// Hvis stedet er det eneste som finnes, så slettes det uten å flytte gjenstander
				if (Steder.size() != 1) {
					// Flytter alle gjenstander til første mulige sted
					for (auto it2 = Steder.begin(); it2 != Steder.end(); it2++)
					{
						// Sjekker at vi ikke flytter gjenstander til stedet som skal slettes
						// og at gjenstander ikke allerede er flytta
						if (it2->first != it->first && !flyttet) {

							// Henter størrelse av eksisterende gjenstand vectorer fra
							// sted som skal slettes
							int antKajakkr = it->second->antKajakkr();
							int antSykler = it->second->antSykler();
							int antElsparkesykler = it->second->antElsparkesykler();

							// Flytter Kajakkr
							for (int i = 0; i < antKajakkr; i++) {						// Flytter så mange elementer som ønsket
								it2->second->settInnKajakk(it->second->taKajakk());	//  Kopierer pekeren til nytt sted
							}
							// Flytter sykler
							for (int i = 0; i < antSykler; i++) {
								it2->second->settInnKano(it->second->taKano());
							}
							// Flytter elsparkesykler
							for (int i = 0; i < antElsparkesykler; i++) {
								it2->second->settInnElsparkeKano(it->second->taElsparkeKano());
							}

							cout << "\n\nGjenstander flyttet til: " << it2->first;
							flyttet = true;
						}
					}
				}

				delete it->second;	// Sletter objektet
				Steder.erase(it);	// Sletter key paret fra map

				cout << "\nStedet har blitt slettet!";
			}
			else {
				cout << "\nStedet har ikke blitt slettet!";
			}
		}
		else {					  // Melding om navnet ikke er funnet
			cout << "\nDette stedet finnes ikke i registeret!";
		}
	}
	else
		cout << "\n\tIngen steder er registrert!\n";
}

/**
 * Leser steddata fra fil og setter de inn i Steder vector
 *
 * @see Sted::lesFraFil()
 **/
void Utleiesteder::lesFraFil() {
	string ID, beskr;
	int tlf, tjent;
	ifstream innfil("STEDER.DTA");

	if (innfil) {
		int gjenstandAntall = 0;

		while (!innfil.eof()) {
			// Henter inn ID for sted
			getline(innfil, ID);
			getline(innfil, beskr);
			innfil >> tlf;
			innfil >> tjent;

			Sted* sted = new Sted(ID, beskr, tlf, tjent);	// Initierer sted objekt med navn
			// Leser inn gjenstander for sted og teller antall gjenstander totalt fra
			// Alle steder er lest fra filen.
			gjenstandAntall += sted->lesFraFil(innfil);
			innfil.ignore();	// ignorer tomt rom mellom '_' og nytt ID
			// Setter inn sted og sine gjenstander inne i map Steder
			Steder.insert(pair<string, Sted*>(ID, sted));
		}

		// Oppdaterer antall gjenstander hos sisteNr
		sisteNr += gjenstandAntall;
	}
	else {
		cout << "\nKUNNE IKKE LESE .DTA FOR STEDER\n";
	}
}

/**
 * Leser steddata fra Steder og setter de inn i en fil
 *
 * @see Sted::skrivTilFil()
 **/
void Utleiesteder::skrivTilFil() {
	ofstream utfil("STEDER.DTA");
	// Itererer gjennom hvert eneste sted i Steder vector
	// Og skriver ut stedets data og gjenstander
	for (auto it = Steder.begin(); it != Steder.end(); it++)
	{
		it->second->skrivTilFil(utfil);
		if (next(it) != Steder.end()) {		// std::next() sjekker at verdien til it i neste omgang av løkke
			utfil << "\n";					// ikke er slutten av løkken og passer på ingen ekstra tomt rom etter siste "_"b
		}
	}
}

/**
 * Skriver gjenværende antall gjenstander av en type for alle steder som har den
 *
 * @see Sted::skrivGjenstand(gjenstandType type)
 **/
void Utleiesteder::skrivGjenstandAntall() const {

	gjenstandType type;		// Gjenstandstype valg

	if (!Steder.empty()) { // sjekker om det finnes steder først
		cout << "\n Kajakk(0), Kano(1), ElsparkeKano(2)";
		switch (lesInt("\nTast inn type gjenstand", 0, 2)) { // Leser gjenstandsvalg og setter ønsket enum verdi
		case 0:	type = Kajakk;			break;
		case 1:	type = Kano;			break;
		case 2:	type = elsparkeKano;	break;
		default:						break;
		}

		// Sikrer at bruker velger en type gjenstand
		if (type == Kajakk || type == Kano || type == elsparkeKano) {
			for (auto const& it : Steder)	// Går gjennom alle steder
			{
				it.second->skrivGjenstand(type); // Sted skriver sin egen data
			}
		}
	}
	else
		cout << "\n\tIngen steder er registrert!\n";

}


/**
* oppretter en ny gjenstand på et gitt sted(kommand K N)
* @see   sted::settinnKajakk()
* @see   sted::settinnKano()
* @see   sted::settinnElparkeKano()
*
*/
void Utleiesteder::nyGjenstand()
{
	Kajakk* nyKajakk = nullptr;
	Kano* nyKano = nullptr;
	ElsparkeKano* nyEl = nullptr;
	char type, valg;
	string stedNavn;
	int antall, watt;
	bool dSele, tilhenger;

	if (!Steder.empty()) {
		cout << "\tNy gjenstand til utleiestedet(Stedsnavn):";
		getline(cin, stedNavn); //leser inn sted av brukeren

		auto it = Steder.find(stedNavn);// for å finne et stedNavn

		if (it != Steder.end()) { //hvis stedet finnes
			antall = lesInt("\tAntall nye gjenstander:", 0, MAXANTALL);

			do {                //leser inn type gjenstand og spesifikasjon/tilbehør
				type = lesChar("\t(T)ralle, (S)ykkel, eller (E)lsparkeKano");
				if (type == 'T') {
					valg = lesChar("Har Kajakkne drasele?(j/N)");
					if (toupper(valg) == 'J') { dSele = true; }
					else { dSele = false; }
				}
				else if (type == 'S') {
					valg = lesChar("Har syklene tilhenger?(j/N)");
					if (toupper(valg) == 'J') { tilhenger = true; }
					else { tilhenger = false; }
				}
				else if (type == 'E') {
					watt = lesInt("Watt på elsparkesyklene: ", MINWATT, MAXWATT);
				}
			} while (type != 'T' && type != 'S' && type != 'E');

			for (int i = 0; i < antall; i++) {
				switch (type)
				{
				case 'T':
				{
					nyKajakk = new Kajakk(sisteNr++, type, dSele);
					it->second->settInnKajakk(nyKajakk);
					cout << "\tNy Kajakk legges inn med nr." << sisteNr - 1 << endl;
				}
				break;
				case 'S':
				{
					nyKano = new Kano(sisteNr++, type, tilhenger);
					it->second->settInnKano(nyKano);
					cout << "\tNy Kano legges inn med nr." << sisteNr - 1 << endl;
				}
				break;
				case 'E':
				{
					nyEl = new ElsparkeKano(sisteNr++, type, watt);
					it->second->settInnElsparkeKano(nyEl);
					cout << "\tNy elsparkeKano legges inn med nr." << sisteNr - 1 << endl;
				}
				break;
				default:
					break;
				}
			}
		}
		else {
			cout << "\tUlovelig, Dette stedet finnes ikke!\n";
		}

	}
	else
		cout << "\n\tIngen steder er registrert!\n";
}

/**
* Søker etter en gitt gjenstand inne I gKundebase og gStedBase
* @see  utleiesteder::finnGjenstand()..
* @see  kunder::finnGjenstand(nr)
*/
void Utleiesteder::gjenstandSok()	 {

	if (sisteNr>0) { //sjekker om det finnes gjenstander først
		int nr = lesInt("\tGjenstandNr:", 0, sisteNr - 1);	//leser ønsket gjenstand nummer

		// Søker etter gjenstand hos kunder hvis ikke funnet på steder
		if (!finnGjenstand(nr)) {
			gKundebase.finnGjenstand(nr);
		}
	}
	else
		cout << "\n\tIngen gjenstander er registrert!\n";
}


/**
* finner en gjenstand på et sted eller hos en kunde
* @see  sted::finnGjenstand()..
* @param    int nr
* @return    returnere sted om det finnes eller ikke
*
*/
bool Utleiesteder::finnGjenstand(int nr)
{
	if (!Steder.empty()) { //steder er ikke tomme
		if (nr>=0) {
			for (auto it : Steder) {//går gjennom alle steder

				if (it.second->finnGjenstand(nr) == true) {
					cout << "\tGjenstanden er på utleiestedet " << it.first << endl;
					return true;
				}

			}

		}
		else
		{
			cout << "\tGjenstanden finnes ikke på steder" << endl;
		}

	}
	else {
		cout << "\tSteder er tomme\n";
	}
	return false;
}

/**
* leter etter en gjenstand på et sted og sletter den
* @see Sted::slettKajakk(int gjenstandNr);
* @see Sted::slettSykler(int gjenstandNr);
* @see Sted::slettElsparkesykler(int gjenstandNr);
* @see utleiesteder::finnSted()
* @see sted::skrivData()
* @see utleiesteder::finnGjenstand()
* @see utleiesteder::finnSted2()
*/
void Utleiesteder::slettGjenstand() {
    int gjNr;
    string sted;
    char typ;
    char sikker;
    if (sisteNr > 0) {                  // Hvis gjenstander er registrert
        cout<<"Hvilket sted befinner gjenstanden seg paa?: "; getline(cin, sted);
        if ( finnSted(sted) ) {                         // sted funnet
            cout<<"\n\nDette stedet har følgende gjenstander: \n";
                auto it = Steder.find(sted);       // Gir brukeren meny over gjenstander på valgt sted
                    if (it != Steder.end()) { // Skriver ut data om stedsnavnet er funnet
                        // Kaller for stedet å skrive sin egen data
                        it->second->skrivData();
                    }
                            typ = lesChar("Hva slags type gjenstand vil du slette? (T)ralle, (S)ykkel, (E)lsparkeKano: ");
                            gjNr = lesInt("\nNummer på gjenstand du vil slette?\n", 0, sisteNr-1);
                            if ( finnGjenstand(gjNr) ) {
                       // } while ( finnGjenstand(gjNr) != true);
                            sikker = lesChar("Er du sikker paa at du vil slette denne gjenstanden?(J/N)");
                                if (sikker == 'J') {
                                    switch (typ) {
                                        case 'T':  finnSted2(sted)->slettKajakk(gjNr);          break;
                                        case 'S':  finnSted2(sted)->slettKano(gjNr);          break;
                                        case 'E':  finnSted2(sted)->slettAnnet(gjNr);  break;
                                        default: cout << "Gjenstanden ble ikke slettet.";       break;
                                    }    cout<<"\n\nGjenstand nummer " << gjNr << " Er nå slettet.\n";
                                }   else {cout << "Ok gjenstanden ble ikke slettet\n"; }
                            }  else {cout << "Gjenstanden ble ikke funnet eller er eventuelt slettet allerede!"; }
        } else { cout << "Stedet finnes ikke."; }
    } else { cout<<"\n\tIngen gjenstander registrert!\n"; }
}

/**
 * Overfører/flytter et gitt antall av en ønsket gjenstand fra ett sted til et annet.
 *
 * @see Sted::antKajakkr()
 * @see Sted::antSykler()
 * @see Sted::antElsparkesykler()
 * @see Sted::taKajakk()
 * @see Sted::taKano()
 * @see Sted::taElsparkeKano()
 * @see Sted::settInnKajakk()
 * @see Sted::settInnKano()
 * @see Sted::settInnElsparkeKano()
 * @see Sted::skrivGenerellData()
 *
 **/
void Utleiesteder::flyttGjenstand() {
	gjenstandType type;		// Gjenstandstype valg
	string navnFra = "";	// Stedsnavn for å flytte gjenstand fra
	string navnTil = "";	// Stedsnavn for å flytte gjenstand til
	int antall = 0;			// Antall gjenstander

	cout << "\nFra(Sted): ";
	getline(cin, navnFra); // Leser inn stedsnavn for å flytte fra

	// Søker etter om navnet finnes allerede
	auto fra = Steder.find(navnFra);

	if (fra != Steder.end()) { // Sjekker om stedsnavn finnes
		Sted* fraSted = fra->second;	// Forkorte stednavn

		// Skriver antall gjenstander for ønsket navn som referanse
		fraSted->skrivGenerellData();

		// Spør om ønsket gjenstandstype for å flytte
		cout << "\n Kajakk(0), Kano(1), ElsparkeKano(2)";
		switch (lesInt("\nTast inn type gjenstand", 0, 2)) { // Leser gjenstandsvalg og setter ønsket enum verdi
			case 0:	type = Kajakk;			break;
			case 1:	type = Kano;			break;
			case 2:	type = elsparkeKano;	break;
			default:						break;
		}

		// Les inn antall gjenstander ønsket for flytting
		antall = lesInt("\nTast inn antall som skall flyttes", 1, 1000);

		cout << "\nTil(Sted): ";
		getline(cin, navnTil); // Leser inn stedsnavn for å flytte til

		// Søker etter om navnet finnes allerede
		auto til = Steder.find(navnTil);

		if (til != Steder.end()) { // Sjekker om stedsnavn finnes
			Sted* tilSted = til->second;	// Forkorte stednavn

			// Skriver antall gjenstander for ønsket navn som referanse
			tilSted->skrivGenerellData();

			if (type == Kajakk) {
				// Henter størrelse av eksisterende Kajakk vector for feilbehandlig
				int antKajakkr = fraSted->antKajakkr();

				// Passer på at kopiert vector ikke er tom
				// og eventuelt at ønsket antall gjenstander er mindre eller lik
				// antall gjenstander i vectoren
				if (antKajakkr > 0 && antKajakkr >= antall) {
					for (int i = 0; i < antall; i++) {						// Flytter så mange elementer som ønsket
						tilSted->settInnKajakk(fraSted->taKajakk());	//  Kopierer pekeren til nytt sted
					}
				}
				else {
					cout << "\n\nIkke nok gjenstander å flytte!";
				}
			}
			else if(type == Kano) {
				// Henter størrelse av eksisterende Kano vector for feilbehandlig
				int antSykler = fraSted->antSykler();

				// Passer på at kopiert vector ikke er tom
				// og eventuelt at ønsket antall gjenstander er mindre eller lik
				// antall gjenstander i vectoren
				if (antSykler > 0 && antSykler >= antall) {
					for (int i = 0; i < antall; i++) {						// Flytter så mange elementer som ønsket
						tilSted->settInnKano(fraSted->taKano());	//  Kopierer pekeren til nytt sted
					}
				}
				else {
					cout << "\n\nIkke nok gjenstander å flytte!";
				}
			}
			else {
				// Henter størrelse av eksisterende elsparkeKano vector for feilbehandlig
				int antElsparkesykler = fraSted->antElsparkesykler();

				// Passer på at kopiert vector ikke er tom
				// og eventuelt at ønsket antall gjenstander er mindre eller lik
				// antall gjenstander i vectoren
				if (antElsparkesykler > 0 && antElsparkesykler >= antall) {
					for (int i = 0; i < antall; i++) {						// Flytter så mange elementer som ønsket
						tilSted->settInnElsparkeKano(fraSted->taElsparkeKano());	//  Kopierer pekeren til nytt sted
					}
				}
				else {
					cout << "\n\nIkke nok gjenstander å flytte!";
				}
			}

			// Skriver antall gjenstander for ønsket navn som referanse
			// for å se oppdaterte gjenstandsantall
			fraSted->skrivGenerellData();
			tilSted->skrivGenerellData();
		}
		else {					  // Melding om navnet ikke er funnet
			cout << "\nDette stedet finnes ikke i registeret!";
		}
	}
	else {					  // Melding om navnet ikke er funnet
		cout << "\nDette stedet finnes ikke i registeret!";
	}
}

/**
 * Henter en vector med gjenstander fra et sted
 * Vector er en kopi av ønskede gjenstander
 *
 * @see   Sted::leiGjenstand(typ, ant)
 * @return Vector med ønsket antall type av gjenstander
 **/
vector <Gjenstand*> Utleiesteder::hentGjenstandTilKunde(string nvn, gjenstandType typ, int ant) {

	// Velger ønsket sted
	auto it = Steder.find(nvn);

	// Henter ønskede gjenstander fra sted for utleie
	return (*it).second->leiGjenstand(typ, ant);
}
