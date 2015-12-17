#pragma once
#include "pelirajapinta.hh"
/* 
Oma toteutus pelaaja-luokasta /Mikael Jokinen
*/

class Pelaaja
{
public:
	Pelaaja();
	Pelaaja(Julkinen::PelaajaTyyppi tyyppi, std::string nimi, char lyhenne, Julkinen::Koordinaatti sijainti);
	Julkinen::PelaajaTyyppi haePelaajaTyyppi();
	~Pelaaja();
private:
	std::string _nimi;
	Julkinen::Koordinaatti _sijainti;
	Julkinen::PelaajaTyyppi _tyyppi;
	char _lyhenne;
};
