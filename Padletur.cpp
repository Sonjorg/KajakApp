#define _CRT_SECURE_NO_WARNINGS
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
#include "Padletur.h"
#include <stdio.h>
#include <time.h>
#include <sstream>


using namespace std;

Padletur::Padletur() {
    //stringstream tid;
    string tid, aa, m, d, time, min;
	cout << "\nBeskrivelse av turen (for eksempel hvor du skal padle og hvilken kajakk som skal brukes): ";
	getline(cin, beskrivelse);
	cout << "\n\nNy padletur startet ";

    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    cout << "dato (aar-maaned-dag): "<< (now->tm_year + 1900) << '-'
        << (now->tm_mon + 1) << '-'
        << now->tm_mday
        << "\tKlokken: "
        << now->tm_hour << ":"
        << now->tm_min << ":"
        << now->tm_sec;
 
    cout << "\n\n God tur! =)";
  aa = to_string((now->tm_year + 1900)); m = to_string((now->tm_mon + 1)); d = to_string(now->tm_mday);
  time = to_string(now->tm_hour);  min = to_string(now->tm_min);
  tidspunkt = "dato (aar-maaned-dag): " + aa + "-" + m + "-" + d + " klokken " + time + ":" + min;
    //cout << tidspunkt;
}

void Padletur::skrivData() {
    cout << "Tidspunkt: " << tidspunkt << "\nBeksrivelse: " << beskrivelse;
}