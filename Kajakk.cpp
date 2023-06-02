#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                //  FOR Å KUNNE BRUKE:  STLs  vector
#include "Kajakk.h"
#include "Gjenstand.h"
#include "LesData3.H"
using namespace std;


/**
*   Leser data om Kajakkn
*
*/
void Kajakk::lesData() {
    char dSele;

    dSele = lesChar("Har Kajakkn drasele?");
    if (dSele=='J') { draSele = true;}
    else { draSele = false; }
}

/**
*  skriver ut sine data
*
*/
void Kajakk::skrivData()
{

    if (draSele == true) {
        cout << "\tKajakk med drasele nr." << gjenstandsNummer << endl;
    }
    else { cout << "\tKajakk uten drasele nr." << gjenstandsNummer << endl; }

}

/**
 *   constructor, som bare sender parameter til baseklassen.
 *
 *  @param   nr  - Gjenstands nummer/ID, som sendes til baseklassen
 *   @param  trl - gjenstands type
 */
Kajakk::Kajakk(const int nr, char trl, bool dSele) : Gjenstand(nr, trl)
{
	draSele = dSele;
}

/**
* Sjekker om denne Kajakkn har en drasele
*
* @return - true/false om Kajakk har drasele eller ikke
*/
bool Kajakk::dSele() {
    if (draSele){return true;}
    return false;
}
