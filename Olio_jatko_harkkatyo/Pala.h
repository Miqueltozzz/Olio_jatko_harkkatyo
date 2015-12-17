#pragma once
/*
Oma toteutus Pala-luokasta /Mikael Jokinen
T�m� sis�lt�� my�s esineen toteutuksen, ei mit��n syyt� tehd� siit� omaa luokkaansa
*/

#include "pelirajapinta.hh"
class Pala
{
public:
	//palan metodit
	Pala();
	Pala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti sijainti);
	void asetaEsine(std::string pelaaja, char merkki);	//lisää palaan esineen tiedot
	~Pala();

	Julkinen::Koordinaatti getSijainti();

	//esineen metodit

private:

	//Varsinaiset palan muuttujat
	Julkinen::PalaTyyppi _pala;
	unsigned int _rotaatio;
	Julkinen::Koordinaatti _sijainti;
	Julkinen::ErikoispalaTyyppi _erikoispalaTyyppi;

	//esineen muuttujat
	char _merkki;
	//Esineen koordinaattia ei tarvita, koska palalla on jo koordinaatti
	std::string _pelaaja;
};

