#include "Pala.h"
//T�m� tiedosto ei mene githubiin?


Pala::Pala()
{
}

Pala::Pala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti sijainti):
	_pala(pala),_rotaatio(rotaatio),_sijainti(sijainti)
{
}
void Pala::asetaEsine(std::string pelaaja, char merkki)
{
	_pelaaja = pelaaja;
	_merkki = merkki;
}
;


Pala::~Pala()
{
}

Julkinen::Koordinaatti Pala::getSijainti()
{
	return _sijainti;
}
