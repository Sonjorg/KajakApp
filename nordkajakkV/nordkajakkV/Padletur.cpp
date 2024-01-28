#include <iostream>                //  cout, cin
#include <iomanip>                 //  setw
#include <string>                  //  STRING-KLASSEN
#include <vector>
#include <fstream>                 //  FOR � KUNNE BRUKE:  STLs  vector
#include "Sted.h"
#include "LesData3.h"			   // Verdi innlesningsverkt�y
#include "Gjenstand.h"
#include <algorithm>
#include "conster.h"

using namespace std;

Padletur::Padletur() {
	cout << "\nBeskrivelse av turen (hvor du skal padle, hvilken kajakk som skal brukes og n�r du ansl�r � v�re tilbake):"
	getline(cin, beskrivelse);
	cout <<"\n\nNy padletur startet klokken " << std::chrono::system_clock::now();
}