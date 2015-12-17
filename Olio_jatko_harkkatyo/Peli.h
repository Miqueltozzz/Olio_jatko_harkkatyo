#pragma once
/*
Oma toteutus peli-luokasta /Mikael Jokinen
*/

#include <iostream>
#include <algorithm>
#include <vector>

#include "luettelotyypit.hh"
#include "vaittama.hh"
#include "pelirajapinta.hh"
#include "komentovirhe.hh"
#include "koordinaatti.hh"
#include "toimintovirhe.hh"
#include "alustusvirhe.hh"
#include "valmiiden_toteutus/include/naytto.hh"
#include "toteuttamaton_virhe.hh"
#include "nayttorajapinta.hh"
#include "debug.hh"

//omien toteutusten includet:
#include "Pelaaja.h"
#include "Pala.h"

class Peli:
	public Julkinen::Pelirajapinta
{
public:

	// Pelirajapinnasta perityt funktiot
	Peli();
	bool onkoAlustustilassa() const;
	void lisaaNaytto(Julkinen::Nayttorajapinta* naytto);
	void alustusLopeta();
	bool onkoPelitilassa() const;

	void maaritaPelialueenKoko(Julkinen::Koordinaatti const& koko);
	void lisaaPelaaja(Julkinen::PelaajaTyyppi tyyppi, std::string const& nimi, char lyhenne, Julkinen::Koordinaatti const& sijainti);
	void lisaaPala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti const& sijainti);
	void lisaaEsine(char merkki, Julkinen::Koordinaatti const& sijainti, std::string const& pelaaja);
	void asetaPalanTyyppi(Julkinen::ErikoispalaTyyppi tyyppi, Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde = Julkinen::Koordinaatti());

	void komentoTyonna(Julkinen::Reuna reuna, unsigned int paikka, unsigned int rotaatio);
	void komentoLiiku(Julkinen::Suunta suunta, unsigned int maara = 0);
	bool vaihdaVuoro();
	void paivitaNaytto();//nayton pitaa olla rakennustilassa ennen tätä
	Julkinen::PelaajaTyyppi haeVuorossa();

private:
	std::vector<Pelaaja> _pelaajat; //
	std::vector<Pala> _palat;
	bool _alustusTila; // ollaanko alustustilassa
	bool _peliTila;// ollaanko pelitilassa
	bool _pelaajaLiikkunut;
	Julkinen::Nayttorajapinta * _naytto;
	int _alueenKoko;

	unsigned int _vuorossa;// indeksi vektorin pelaajaan
	bool _voitto; // onko joku voittanut pelin
	bool _tyonnetty; // palaa ty�nnetty
};