#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                 //  FOR Å KUNNE BRUKE:  STLs  vector
#include "Sted.h"
#include "LesData3.h"			   // Verdi innlesningsverktøy
#include "Gjenstand.h"
#include <algorithm>
#include "conster.h"

using namespace std;

Padletur::Padletur() {
	cout << "\nBeskrivelse av turen (hvor du skal padle, hvilken kajakk som skal brukes og når du anslår å være tilbake):"
	getline(cin, beskrivelse);
	cout <<"\n\nNy padletur startet klokken " << std::chrono::system_clock::now();
}