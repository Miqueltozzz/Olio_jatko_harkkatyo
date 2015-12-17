#include "Pelaaja.h"

Pelaaja::Pelaaja()
{
	_nimi = "";
}

Pelaaja::Pelaaja(Julkinen::PelaajaTyyppi tyyppi, std::string nimi, char lyhenne, Julkinen::Koordinaatti sijainti):
	_tyyppi(tyyppi),_nimi(nimi),_lyhenne(lyhenne),_sijainti(sijainti)
	//Parametrinen rakentaja /Mikael Jokinen
{
}
Julkinen::PelaajaTyyppi Pelaaja::haePelaajaTyyppi()
{
	return _tyyppi;
}
Julkinen::Koordinaatti Pelaaja::haeSijainti()
{
	return _sijainti;
}
;

Pelaaja::~Pelaaja()
{
	;
}
