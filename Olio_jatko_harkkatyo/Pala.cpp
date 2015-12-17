#include "Pala.h"
//T�m� tiedosto ei mene githubiin?


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
