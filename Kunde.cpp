#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                //  FOR  KUNNE BRUKE:  STLs  vector
#include "Kunde.h"
#include "Kunder.h"
#include "lesData3.H"
#include "Utleiesteder.h"
#include "Sted.h"
#include "conster.h"

using namespace std;

extern Utleiesteder gStedbase;

/**
*   leses inn mobilTelefon
*
**/
Kunde::Kunde(int ID, string nvn) {
    IDnummer = ID;                           // Unikt identifiserende nummer til kunde
    navn = nvn;

	// Tlf av kunde leses inn
	mobilNummer = lesInt("\t\tTelefonnummer: ", 0, 99999999);

}

/**
*   setter ID, navn, og mobil inn
*
**/
Kunde::Kunde(int ID, string nvn, int tlf) {
	IDnummer = ID;                           // Unikt identifiserende nummer til kunde
	navn = nvn;
	mobilNummer = tlf;
}

/**
*   setter ID nummer til kunder
*/
void Kunde::settID(int nr) {
    IDnummer = nr;

}

/**
* går gjennom gjenstand vector og returner true når kunde med gjenstand er funnet
* @param  gjenstandNr -
* @see    hentID()..
* @return hvis en gjenstand matcher returner true eller false hvis det ikke matcher.
*/
bool Kunde::finnGjenstand(int gjenstandNr)
{
    for (auto it = gjenstander.begin(); it != gjenstander.end(); it++) {

        if ((*it)->hentID() == gjenstandNr) {//hvis matches return true eller false
            return true; // gjenstand er funnet
        }
    }

    return false;
}

/**
 *  legger bakerst gjenstand i gjenstander vector
 *
 **/
void Kunde::settInnGjenstand(Gjenstand* gjstnd) {
	gjenstander.push_back(gjstnd);
}

/**
*   Henter IDnummer
*/
int Kunde::hentID() {

    return IDnummer;
}
/**
*   Skriver kundens data og alle gjenstander de har lånt
*   @see   gjenstand::henttType()
*   @see   Kajakk::skrivData()
*   @see   Kano::skrivData()
*   @see   elparkeKano::skrivData()
*/
void Kunde::skrivData(){
    Kajakk* kajakkPeker;
    Kano*   kanoPeker;
    Annet*  annetPeker;
    cout << "\n\tIDnummer: " << IDnummer;
    cout << "  Navn: " << navn << ", ";
    cout <<"Mobil: " << mobilNummer<<",";

    cout << " antall laante gjenstander: ";
    cout << "(totalt " << gjenstander.size() << " stk):" << "\n\n";

       for (const auto & val : gjenstander) {
        if ( val->hentType() == 't' ) { kajakkPeker = dynamic_cast <Kajakk*> (val); kajakkPeker->skrivData(); }
        else if ( val->hentType() == 's' ) { kanoPeker = dynamic_cast <Kano*> (val); kanoPeker->skrivData(); }
        else { annetPeker = dynamic_cast <Annet*> (val); annetPeker->skrivData(); }
    }

}

/**
*  @see Sted::fortjeneste()
*/

/**
*   Faktura til kunde og forretning
*   Her så vi feil i oppgaveteksten og endret til etterhvert.
*   Bruker får nå heller spørsmål i Kunde::leverAlleGjenstander() om hvor
*   han lånte gjenstandene og all fortjeneste sendes dit.
*/
int Kunde::faktura() {
    int Kajakk=0; int Kano=0;
    int el=0; int totalPris=0;

    totalPris += grunnPris;
        //Teller opp antall av hver gjenstandstype
    for (auto val : gjenstander) {
        switch (val->hentType()) {
            case 't': Kajakk++; totalPris += prisKajakk;   break;
            case 's': Kano++; totalPris += prisKano;   break;
            case 'e': el++;     totalPris += prisEl;       break;
        }
    }
    cout <<"\nFaktura: \n\n\t\tKr "<<grunnPris<<" i grunnpris når kunden forlater parken. ";
    if (Kajakk > 0) {
        cout<<Kajakk<<" Kajakkr, Kr: "<<prisKajakk<<",- per stykk\n\t"; }
    if (Kano > 0) {
        cout << Kano<<" sykler, Kr: "<<prisKano<<",- per stykk\n\t"; }
    if (el > 0) {
        cout << el<<" annet, Kr: "<<prisEl<<",- per stykk\n\t"; }
        cout << "\nTotalt kr: "<<totalPris<<",- aa betale\n";
    return totalPris;       // Sender fortjenesten til sted;
}


/**
*   skriver data om alle kunder(kort data og ikke alt)
*   NB: Denne skriver ikke om kundes gjenstander har drasele osv.
*   Det gjør bare skrivData om en kunde.
*   @see void Kunder::dataOmAlle()
*/
void Kunde::skrivDataALL() const
{   //int DS;
    int Kajakk = 0;
    int Kano = 0;
    int el = 0;
    //Teller opp antall av hver gjenstandstype
    for (auto val : gjenstander) {
        switch (val->hentType()) {
            case 't': Kajakk += 1;    break;
            case 's': Kano += 1;    break;
            case 'e': el += 1;        break;
        }
    }

    cout << "\n\tIDnummer: " << IDnummer;
    cout << "  Navn: " << navn << ", ";
    cout << "Mobil: "<<mobilNummer<<", ";
    cout << " antall laante gjenstander: ";
    cout << "(totalt " << gjenstander.size() << " stk)\n" << endl;
        //Skriver antall av hver type gjenstand:
    cout << "\t\t"<< Kajakk <<" Kajakker,\t"<<Kano<<" kanoer,\t"<<el<<" annet.";
}



/**
*  Leverer alle gjenstander fra kunder til steder
*
*   @see  utleiesteder::finnSted2(sted)
*   @see  utleiesteder::finnSted(sted)
*   @see  gjenstand::hentType()
*   @see  sted::settInnElsparkeKano(elPeker)
*   @see  sted::settInnSekkel(KanoPeker)
*   @see  sted::settInnKajakk(KajakkPeker)
*   @see  Kunde::faktura()
*/
void Kunde::leverAlleGjenstander() {
    string sted, sted2;
    Sted* s;
    Sted* s2;
    int gjNr;
    bool kKlubben;
    Kajakk* KajakkPeker;
    Kano* KanoPeker;
    Annet* annet;

    // Spør bruker hvilket sted kunden befinner seg på
    // hvis stedet ikke finnes blir de spurt igjen.

    do {
    cout << "Hvilket sted befinner kunden seg paa? ";
    getline(cin, sted);
        s = gStedbase.finnSted2(sted);                     // Denne henter peker til sted
            if (gStedbase.finnSted(sted) == false ) {     // Denne returnerer om stedet finnes
                cout <<"\n\nBeklager, stedet finnes ikke eller er stavet feil\n\n";
            }
    } while (gStedbase.finnSted(sted) != true );

    do {
    cout << "Hvilket sted lånte kunden gjenstandene sine fra? ";

    getline(cin, sted2);
        s2 = gStedbase.finnSted2(sted2);                     // Denne henter peker til sted
            if (gStedbase.finnSted(sted2) == false ) {     // Denne returnerer om stedet finnes
                cout <<"\n\nBeklager, stedet finnes ikke eller er stavet feil\n\n";
            }
    } while (gStedbase.finnSted(sted2) != true );
    cout <<"kunden har "<< gjenstander.size() <<" Gjenstander:\n\n";
    for (const auto & val : gjenstander) {

        if ( val->hentType() == 't' ) { KajakkPeker = dynamic_cast <Kajakk*> (val); s->settInnKajakk(kajakkPeker); }
        else if ( val->hentType() == 's' ) { KanoPeker = dynamic_cast <Kano*> (val); s->settInnKano(kanoPeker); }
        else { annet = dynamic_cast <Annet*> (val); s->settInnAnnet(elPeker); }
    }
    s2->fortjeneste(faktura());          //Sender fortjenesten til stedet og skriver ut faktura
    gjenstander.clear();


}

/**
 * Leser kundedata fra fil
 * og setter de inn i gjenstand vector.
 * Teller også opp antall gjenstander for oppdatering av 'sisteNr' i Utleiested objekt
 * gjID for gjenstander
 *
 * @param inn - fil parameter for innlesning av gjenstander
 * @return siste gjenstandsnummer telt
 **/
int Kunde::lesFraFil(ifstream &inn) {
	char charBuffer = '.';	// tegnbuffer for innlesning fra fil init med '.' for ingen endring i sted
	int intBuffer;			// tallbuffer for innlesning fra fil
	int gjAntall = 0;		// Antall gjenstander talt opp for dette stedet
	int gjID;				// gjenstandsID hentet fra fil
	int watt;				// Antall watt på elsparkeKano
	bool dSele, tilhenger;	// Tilbehør for Kajakk eller Kano


	while (charBuffer != '_') {	// Ikke slutt av gjenstandinnhenting
		switch (charBuffer) {
		case 'T':
		{
			inn >> intBuffer; gjID = intBuffer;		 // leser inn gjenstandsID
			inn >> intBuffer; dSele = intBuffer;	 // leser inn tilbehør/spec
			gjenstander.push_back(new Kajakk(gjID, charBuffer, dSele));	// Setter inn Kajakk
		}
		break;
		case 'S':
		{
			inn >> intBuffer; gjID = intBuffer;		 // leser inn gjenstandsID
			inn >> intBuffer; tilhenger = intBuffer; // leser inn tilbehør/spec
			gjenstander.push_back(new Kano(gjID, charBuffer, tilhenger));	// Setter inn Kano
		}
		break;
		case 'E':
		{
			inn >> intBuffer; gjID = intBuffer;		 // leser inn gjenstandsID
			inn >> intBuffer; watt = intBuffer;		 // leser inn tilbehør/spec
			gjenstander.push_back(new ElsparkeKano(gjID, charBuffer, watt)); // Setter inn elsparkeKano
		}
		break;

		default:
			break;
		}
		if (charBuffer == 'T' || charBuffer == 'S' || charBuffer == 'E') {	// Sjekker at en gjenstand er lagt inn
			gjAntall++;		// øker antall gjenstander lagt inn
		}
		inn >> charBuffer;		// Leser inn tegn for gjenstand('T', 'S', 'E') eller slutt av gjenstandinnhenting '_'
	}
	return gjAntall;					// legger til 1 kunde i totalt antall kunder hentet
}

/**
 * Leser kundedata og gjenstander fra kunden og setter de inn i en fil
 *
 * @see Gjenstand::hentID()
 * @see Kajakk::dSele()
 * @see Kano::harTilhenger()
 * @see ElsparkeKano::hentWatt()
 **/
void Kunde::skrivTilFil(ofstream &ut) {					// Skriver til fil:
	ut << IDnummer << "\n";								// Stedets navn/ID
	ut << navn << "\n";							// Beskrivelse
	ut << mobilNummer << "\n";	// Telefon og inntjente penger

	// Itererer gjennom alle gjenstander og skriver ut deres data
	for (auto it = gjenstander.begin(); it != gjenstander.end(); it++) {
		char type = (*it)->hentType();

		if (type == 't') {
			// Dynamic cast konverterer en klasse opp og ned i klasse hierarkien for tilgang til spesialiserte funksjoner
			Kajakk* KajakkPeker = dynamic_cast <Kajakk*> (*it);
			ut << "\t" << "T " << (*it)->hentID() << " ";
			if (KajakkPeker->dSele()) { ut << 1; }		// Sjekker om har drasele eller ikke
			else { ut << 0; }
			ut << "\n";
		}
		else if (type == 's') {
			Kano* KanoPeker = dynamic_cast <Kano*> (*it);
			ut << "\t" << "S " << (*it)->hentID() << " ";
			if (KanoPeker->harTilhenger()) { ut << 1; }	// sjekker om har tilhenger eller ikke
			else { ut << 0; }
			ut << "\n";
		}
		else if (type == 'e') {
			ElsparkeKano* elspykkelPeker = dynamic_cast <ElsparkeKano*> (*it);
			ut << "\t" << "E " << elspykkelPeker->hentID() << " " << elspykkelPeker->hentWatt() << "\n";
		}

	}
	ut << "_";
}
