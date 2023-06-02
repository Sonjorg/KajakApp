#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                //  FOR Å KUNNE BRUKE:  STLs  vector
#include "Sykkel.h"
#include "LesData3.H"

using namespace std;

/**
*  skriver ut sine data
* 
*/
void Sykkel::skrivData() {
   

    if ( tilhenger == true) {
        cout<<"\tSykkelen med tilhenger nr."<<gjenstandsNummer<<endl;}
    else {cout<<"\tSykkelen uten tilhenger nr."<<gjenstandsNummer<<endl;}
	
}

/**
* Sjekker om denne sykkelen har en tilhenger
*
* @return - true/false om sykkel har tilhenger eller ikke
*/
bool Sykkel::harTilhenger() {
	if (tilhenger) { return true; }
	return false;
}

/**
 *  constructor, som bare sender parameter til baseklassen.
 *
 *  @param   nr  - Gjenstands nummer/ID, som sendes til baseklassen
 *   @param  sykl - gjenstands type
 */
Sykkel::Sykkel(const int nr, char sykl, bool tilhngr) : Gjenstand(nr, sykl)
{
	tilhenger = tilhngr;
}
