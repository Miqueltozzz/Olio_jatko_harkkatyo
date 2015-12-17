#include "Peli.h"

//*Testikommentti testipushausta varten* -Tuomas Hakala

Peli::Peli() {
	_alustusTila = true;
	_peliTila = false;

}

bool Peli::onkoAlustustilassa() const
{
	return _alustusTila;
}

void Peli::lisaaNaytto(Julkinen::Nayttorajapinta* naytto)
{
	ESIEHTO(onkoAlustustilassa());
	_naytto = naytto;
	JALKIEHTO(_naytto != 0);

}

void Peli::alustusLopeta()
{
	ESIEHTO(onkoAlustustilassa());
	_alustusTila = false;
	_peliTila = true;

	JALKIEHTO(onkoPelitilassa());
}

bool Peli::onkoPelitilassa() const
{
	return _peliTila;
}

void Peli::maaritaPelialueenKoko(Julkinen::Koordinaatti const& koko) {

	_alueenKoko = koko.haeXkoordinaatti();

}

void Peli::lisaaPelaaja(Julkinen::PelaajaTyyppi tyyppi, std::string const& nimi, char lyhenne, Julkinen::Koordinaatti const& sijainti) {
	DEBUG_OUTPUT("LisaaPelaaja, nimi: "<<nimi<<std::endl);

	_pelaajat.push_back(Pelaaja(tyyppi, nimi, lyhenne, sijainti));
}

void Peli::lisaaPala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti const& sijainti) {
	DEBUG_OUTPUT("LisaaPala, tyyppi: " << pala << std::endl);
	_palat.push_back(Pala(pala, rotaatio, sijainti));
}

void Peli::lisaaEsine(char merkki, Julkinen::Koordinaatti const& sijainti, std::string const& pelaaja) {

	DEBUG_OUTPUT("LisaaEsine, merkki: " << merkki <<" pelaaja: "<<pelaaja<< std::endl);
}

void Peli::asetaPalanTyyppi(Julkinen::ErikoispalaTyyppi tyyppi, Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde) {
	for (unsigned int a = 0; a < _palat.size(); a++)
	{
		if (_palat[a].getSijainti() == kohde)
		{
			DEBUG_OUTPUT("asetaPalanTyyppi, tyyppi: " << tyyppi << std::endl);
		}
	}
}

void Peli::komentoTyonna(Julkinen::Reuna reuna, unsigned int paikka, unsigned int rotaatio) {

}

void Peli::komentoLiiku(Julkinen::Suunta suunta, unsigned int maara) {

}

bool Peli::vaihdaVuoro() {
	return 0;
}

Julkinen::PelaajaTyyppi Peli::haeVuorossa() {
	return Julkinen::IHMINEN;
}