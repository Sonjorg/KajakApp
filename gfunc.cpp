#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                //  FOR Å KUNNE BRUKE:  STLs  vector
#include "Gjenstand.h"
#include "Kunde.h"
#include "gfunc.h"
#include "LesData3.H"

using namespace std;




/**
* meny valg
*/
void skrivMeny()
{
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
        << "\tM S        - Start en padletur\n"
        << "\tM N        - Registrer nytt medlem\n"
        << "\tM F        - Finn medlemsnummer til et medlem\n"
        << "\tM A        - SKRIV  UT ALLE medlemmene\n"
        << "\tM 1 <knr>  - Skriv alt om ett medlem <kundenr>((1) er et ett - tall.)\n"
        << "\tM H <knr>  - Hent en kajakk/Kano med <medlemsnummer>\n"
        << "\tM L <knr>  - Lever alle gjenstand(er) fra <medlemsnummer>\n"
        << "\tM S <knr>  - Slett et medlem <medlemsnummer>\n"
        << "\tS N        - Nytt Sted\n"
        << "\tS A        - Skriv ut Alle Stedene\n"
        << "\tS 1 <ID>   - Skriv alt om et sted <stedsID>((1) er et ett-tall.)\n"
        << "\tS T        - Skriver ut alle steders inntjente penger\n"
        << "\tS I        - Sted hvem har Igjen noe av en gitt gjenstand ((I) er en stor (i))\n"
        << "\tS O        - Overføre(flytte)gjenstander mellom steder\n"
        << "\tS S <ID>   - Slett et sted <stedsID>\n"
        << "\tG N        - Ny Gjenstand\n"
        << "\tG F <gjnr> - Finn Gjenstand <gjenstandnr>\n"
        << "\tG S <gjnr> - Slett Gjenstand <gjenstandnr>\n"
        << "\tQ          - Quit / avslutt\n";
}
