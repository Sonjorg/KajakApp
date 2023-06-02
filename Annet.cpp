#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                //  FOR Å KUNNE BRUKE:  STLs  vector
#include "Annet.h"
#include "Gjenstand.h"
#include "LesData3.H"


using namespace std;


/**
*  Leser inn egne datamedlemmer fra brukeren
*
*/
void Annet::lesData() {
	antallWatt = lesInt("Antall watt på sykkelen?", 50, 100);
}


/**
*
* skriver ut alle sine data
*
*/
void Annet::skrivData() {

	cout <<"\tAnnet nr."<<gjenstandsNummer <<" Antall Watt: "
		                                        << antallWatt << endl;
}

/**
* Sender tilbake antall watt i denne Anneten
*
* @return - Int med antall watt
*/
int Annet::hentWatt() {
	return antallWatt;
}

/**
*   constructor, som bare sender parameter til baseklassen.
*
*  @param   nr  - Gjenstands nummer/ID, som sendes til baseklassen
*  @param   els - gjenstands type
*  @param   w   - antall watt
*/
Annet::Annet(const int nr, char els, int w) : Gjenstand(nr, els)
{
	antallWatt = w;
}


