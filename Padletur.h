#include <vector>
#include <string>
#include "enumer.h"
//#include "KAJAKK.H"
//#include "KANO.H"
//#include "ANNET.H"
//#include "Gjenstand.h"

class Padletur {
private:
	std::string beskrivelse;
	std::string tidspunkt;
	//std::vector <Gjenstand*> gjenstander;
	//std::vector <Kajakk*> kajakker;
	//std::vector <Kano*> kanoer;
	//std::vector <Annet*> andre;


public:
	Padletur();
	void skrivData();

};