#include "Pala.h"


Pala::Pala()
{
}

Pala::Pala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti sijainti):
	_pala(pala),_rotaatio(rotaatio),_sijainti(sijainti)
{
};


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