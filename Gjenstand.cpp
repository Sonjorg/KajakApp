#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                //  FOR Å KUNNE BRUKE:  STLs  vector
#include "Gjenstand.h"
#include "LesData3.H"
#include "Elsparkesykkel.h"
#include "enumer.h"

using namespace std;


/**
* skriver gjenstands nummer ut
*
*/
void Gjenstand::skrivData() {
    cout << "\tGjenstands-nummer: "<<gjenstandsNummer<<"\n";
}


/**
*   henter gjenstandens type
*
*/
char Gjenstand::hentType() {
    if (type == Kajakk) { return 't';}
    else if (type == Kano) { return 's';}
    else { return 'e';}
}


/**
*
* henter gjenstands nummer
*/
int Gjenstand::hentID() const
{
	return gjenstandsNummer;

}


/**
 *  Setter eget nummer/ID (ut fra parameters verdi).
 *
 *  @param   nr  - Gjenstands eget nummer/ID
 * @param   valg  - Gjenstands type
 */
Gjenstand::Gjenstand(const int nr, char valg)
{
	switch (valg) { //  Konverterer bokstav til enum
	case 'T': type = Kajakk;			break;
	case 'S': type = Kano;			    break;
	case 'E': type = Annet;	            break;
	}

	gjenstandsNummer = nr;
}

/*
* tomt konstrukt
*/
Gjenstand::~Gjenstand() { }   //tom deconstruct



