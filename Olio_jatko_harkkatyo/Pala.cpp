#include "Pala.h"


Pala::Pala()
{
}

Pala::Pala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti sijainti) :
	_pala(pala), _rotaatio(rotaatio), _sijainti(sijainti), _erikoispalaTyyppi(Julkinen::NORMAALI), _merkki('0'), _pelaaja("")
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

void Pala::setErikoisPalaTyyppi(Julkinen::ErikoispalaTyyppi erikoispalatyyppi)
{
	_erikoispalaTyyppi = erikoispalatyyppi;
}

void Pala::setErikoisPalaKohde(Julkinen::Koordinaatti erikoisPalaKohde)
{
	_erikoisPalaKohde = erikoisPalaKohde;
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

Julkinen::Koordinaatti Pala::haeErikoisPalaKohde()
{
	return _erikoisPalaKohde;
}

bool Pala::lapiKavely(Julkinen::Suunta suunta)
{
	if (_pala == Julkinen::IPALA){
		if (suunta == Julkinen::ALAS || suunta == Julkinen::YLOS){
			if (_rotaatio == 1 || _rotaatio == 3){
				return true;
			}
		}
		else if (suunta == Julkinen::OIKEALLE || suunta == Julkinen::VASEMMALLE){
			if (_rotaatio == 2 || _rotaatio == 4){
				return true;
			}
		}
	}
	else if (_pala == Julkinen::TPALA){
		if (suunta == Julkinen::ALAS || suunta == Julkinen::YLOS){
			if (_rotaatio == 2 || _rotaatio == 4){
				return true;
			}
		}
		else if (suunta == Julkinen::OIKEALLE || suunta == Julkinen::VASEMMALLE){
			if (_rotaatio == 1 || _rotaatio == 3){
				return true;
			}
		}
	}
	return false;
}

bool Pala::sisaanKavely(Julkinen::Suunta suunta)
{
	if (_pala == Julkinen::IPALA){
		if (suunta == Julkinen::ALAS || suunta == Julkinen::YLOS){
			if (_rotaatio == 1 || _rotaatio == 3){
				return true;
			}
		}
		else if (suunta == Julkinen::OIKEALLE || suunta == Julkinen::VASEMMALLE){
			if (_rotaatio == 2 || _rotaatio == 4){
				return true;
			}
		}
	}
	else if (_pala == Julkinen::TPALA){
		if (suunta == Julkinen::ALAS){
			if (_rotaatio == 2 || _rotaatio == 4 || _rotaatio == 3){
				return true;
			}
		}
		else if (suunta == Julkinen::YLOS){
			if (_rotaatio == 1 || _rotaatio == 2 || _rotaatio == 4){
				return true;
			}
		}
		else if (suunta == Julkinen::OIKEALLE){
			if (_rotaatio == 1 || _rotaatio == 3 || _rotaatio == 2){
				return true;
			}
		}
		else if (suunta == Julkinen::VASEMMALLE){
			if (_rotaatio == 1 || _rotaatio == 3 || _rotaatio == 4){
				return true;
			}
		}
	}
	else if (_pala == Julkinen::LPALA){
		if (suunta == Julkinen::ALAS){
			if (_rotaatio == 1 || _rotaatio == 4){
				return true;
			}
		}
		else if (suunta == Julkinen::YLOS){
			if (_rotaatio == 3 || _rotaatio == 2){
				return true;
			}
		}
		else if (suunta == Julkinen::OIKEALLE){
			if (_rotaatio == 4 || _rotaatio == 3){
				return true;
			}
		}
		else if (suunta == Julkinen::VASEMMALLE){
			if (_rotaatio == 1 || _rotaatio == 2){
				return true;
			}
		}
	}
	return false;
}