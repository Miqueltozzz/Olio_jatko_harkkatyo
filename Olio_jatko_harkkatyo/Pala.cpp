#include "Pala.h"


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

void Pala::setSijainti(unsigned int xkoord, unsigned int ykoord)
{
	_sijainti.asetaXkoordinaatti(xkoord);
	_sijainti.asetaYkoordinaatti(ykoord);
}

void Pala::setIrtopala(bool irtopala)
{
	_sijainti.asetaIrtopala(irtopala);
}

void Pala::setRotaatio(unsigned int rot)
{
	_rotaatio = rot;
}

Julkinen::PalaTyyppi Pala::haePalaTyyppi()
{
	return _pala;
}

unsigned int Pala::haeRotaatio()
{
	return _rotaatio;
}

Julkinen::Koordinaatti Pala::haeSijainti()
{
	return _sijainti;
}

Julkinen::ErikoispalaTyyppi Pala::haeErikoisPalaTyyppi()
{
	return _erikoispalaTyyppi;
}

char Pala::haeEsineMerkki()
{
	return _merkki;
}

std::string Pala::haeEsinePelaaja()
{
	return _pelaaja;
}
