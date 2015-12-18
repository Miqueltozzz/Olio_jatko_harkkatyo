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

void Pelaaja::asetaXkoord(unsigned int xkoord){
	_sijainti.asetaXkoordinaatti(xkoord);
}

void Pelaaja::asetaYkoord(unsigned int ykoord){
	_sijainti.asetaYkoordinaatti(ykoord);
}

std::string Pelaaja::haeNimi()
{
	return _nimi;
}
char Pelaaja::haeLyhenne()
{
	return _lyhenne;
}
;

Pelaaja::~Pelaaja()
{
	;
}
