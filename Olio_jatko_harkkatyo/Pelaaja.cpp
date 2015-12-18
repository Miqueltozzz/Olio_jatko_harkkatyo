#include "Pelaaja.h"

Pelaaja::Pelaaja()
{
	_nimi = "";
}

Pelaaja::Pelaaja(Julkinen::PelaajaTyyppi tyyppi, std::string nimi, char lyhenne, Julkinen::Koordinaatti sijainti):
	_tyyppi(tyyppi),_nimi(nimi),_lyhenne(lyhenne),_sijainti(sijainti),_kerattavatesineet(""),_keratytesineet(""),_edellinentoiminto("")
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
std::string Pelaaja::haeKeratutEsineet()
{
	return _keratytesineet;
}
std::string Pelaaja::haeKerattavatEsineet()
{
	return _kerattavatesineet;
}
std::string Pelaaja::haeEdellinenToiminto()
{
	return _edellinentoiminto;
}
char Pelaaja::haeTamanHetkinenEsine(void)
{
	return (char)_kerattavatesineet[0];
}
void Pelaaja::asetaKeratutEsineet(std::string keratutesineet)
{
	_keratytesineet = keratutesineet;
}
void Pelaaja::asetaKerattavatEsineet(std::string kerattavatesineet)
{
	_kerattavatesineet = kerattavatesineet;
}
void Pelaaja::asetaEdellinenToiminto(std::string edellinentoiminto)
{
	_edellinentoiminto = edellinentoiminto;
}
void Pelaaja::lisaaKerattavaEsine(char lisattavaEsine)
{
	_kerattavatesineet += lisattavaEsine;
}

void Pelaaja::keraaTamanHetkinenEsine(void)
{
	_keratytesineet += _kerattavatesineet[0];
	_kerattavatesineet.erase(0);
}


Pelaaja::~Pelaaja()
{
	;
}
