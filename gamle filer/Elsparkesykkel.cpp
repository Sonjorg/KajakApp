#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                //  FOR Å KUNNE BRUKE:  STLs  vector
#include "Elsparkesykkel.h"
#include "Gjenstand.h"
#include "LesData3.H"


using namespace std;


/**
*  Leser inn egne datamedlemmer fra brukeren
*  
*/
void Elsparkesykkel::lesData() {
	antallWatt = lesInt("Antall watt på sykkelen?", 50, 100);
}


/**
*
* skriver ut alle sine data
*
*/
void Elsparkesykkel::skrivData() {

	cout <<"\tElsparkesykkel nr."<<gjenstandsNummer <<" Antall Watt: "
		                                        << antallWatt << endl;
}

/**
* Sender tilbake antall watt i denne elsparkesykkelen
*
* @return - Int med antall watt
*/
int Elsparkesykkel::hentWatt() {
	return antallWatt;
}

/**
*   constructor, som bare sender parameter til baseklassen.
*
*  @param   nr  - Gjenstands nummer/ID, som sendes til baseklassen
*  @param   els - gjenstands type
*  @param   w   - antall watt
*/
Elsparkesykkel::Elsparkesykkel(const int nr, char els, int w) : Gjenstand(nr, els)
{
	antallWatt = w;
}


