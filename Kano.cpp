#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                //  FOR Å KUNNE BRUKE:  STLs  vector
#include "Kano.h"
#include "LesData3.H"

using namespace std;

/**
*  skriver ut sine data
*
*/
void Kano::skrivData() {


    if ( tilhenger == true) {
        cout<<"\tKanoen med tilhenger nr."<<gjenstandsNummer<<endl;}
    else {cout<<"\tKanoen uten tilhenger nr."<<gjenstandsNummer<<endl;}

}

/**
* Sjekker om denne Kanoen har en tilhenger
*
* @return - true/false om Kano har tilhenger eller ikke
*/
bool Kano::harTilhenger() {
	if (tilhenger) { return true; }
	return false;
}

/**
 *  constructor, som bare sender parameter til baseklassen.
 *
 *  @param   nr  - Gjenstands nummer/ID, som sendes til baseklassen
 *   @param  sykl - gjenstands type
 */
Kano::Kano(const int nr, char sykl, bool tilhngr) : Gjenstand(nr, sykl)
{
	tilhenger = tilhngr;
}
