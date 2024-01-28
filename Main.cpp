/**
*   Et program som holder orden på utleie av ulike gjenstander (dvs. Kajakk, sykkel eller elsparkesykkel)
*   i en stor fornøyelsespark.
*   Parken har flere steder/kontorer der man kan leie/hente ut og levere inn slike gjenstander.
*
*   @file       main.cpp
*   @date       01.04.2021
*   @author     Abdulhadi Al-Sayed, Ibrahim Said, Sondre Jørgensen
*/

#include <iostream>
#include "kunder.h"
#include "utleiesteder.h"
#include "gfunc.h"
#include "LesData3.h"
using namespace std;


Kunder gKundebase;
Utleiesteder gStedbase;


int main()  {
  char valg;

  gKundebase.lesFraFil();
  gStedbase.lesFraFil();

  skrivMeny();
  valg = lesChar("\nKommando (A for alternativer)");

  while (valg != 'Q')  {
    switch(valg)  {
      case 'M':  gKundebase.handling(valg);      break;
      case 'S':  case 'G':
                 gStedbase.handling(valg);   break;
      default:   skrivMeny();                break;
    }
    valg = lesChar("\nKommando");
  }

  gKundebase.skrivTilFil();
  gStedbase.skrivTilFil();

  cout << "\n\n";
  return 0;
}
