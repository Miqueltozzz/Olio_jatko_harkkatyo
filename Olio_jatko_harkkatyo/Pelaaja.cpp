#include "Pelaaja.h"

Pelaaja::Pelaaja()
{
	_nimi = "";
}

Pelaaja::Pelaaja(Julkinen::PelaajaTyyppi tyyppi, std::string nimi, char lyhenne, Julkinen::Koordinaatti sijainti):
	_tyyppi(tyyppi),_nimi(nimi),_lyhenne(lyhenne),_sijainti(sijainti)
	//Parametrinen rakentaja /Mikael Jokinen
{
};

Pelaaja::~Pelaaja()
{
	;
}
