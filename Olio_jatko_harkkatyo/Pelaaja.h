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
	Julkinen::Koordinaatti haeSijainti();
	std::string haeNimi();
	char haeLyhenne();

	std::string haeKeratutEsineet();
	std::string haeKerattavatEsineet();
	std::string haeEdellinenToiminto();

	char haeTamanHetkinenEsine(void);

	void asetaKeratutEsineet(std::string keratutesineet);
	void asetaKerattavatEsineet(std::string kerattavatesineet);
	void asetaEdellinenToiminto(std::string edellinentoiminto);

	void lisaaKerattavaEsine(char lisattavaEsine);

	void keraaTamanHetkinenEsine(void);

	~Pelaaja();
private:
	std::string _nimi;
	Julkinen::Koordinaatti _sijainti;
	Julkinen::PelaajaTyyppi _tyyppi;
	char _lyhenne;
	std::string _keratytesineet;
	std::string _kerattavatesineet;
	std::string _edellinentoiminto;
};
