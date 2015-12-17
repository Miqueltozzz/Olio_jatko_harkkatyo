#include "Peli.h"


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
	_naytto->komentoAloitaRakennus();
	JALKIEHTO(_naytto != 0);

}

void Peli::alustusLopeta()
{
	ESIEHTO(onkoAlustustilassa());
	_alustusTila = false;
	_peliTila = true;
	_naytto->komentoLopetaRakennus();
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
	// ei toimi-> irtopalan koordinaatteja ei saa kysyï¿½ DEBUG_OUTPUT("LisaaPala, tyyppi: " << pala << "sijainti: " << sijainti.haeXkoordinaatti() << "," << sijainti.haeYkoordinaatti()<<" irtopala: "<<sijainti.onkoIrtopala() << std::endl);
	
	if (sijainti.onkoIrtopala() != 1)
	{
		DEBUG_OUTPUT("LisaaPala, tyyppi: " << pala << "sijainti: " << sijainti.haeXkoordinaatti() << "," << sijainti.haeYkoordinaatti() << std::endl);
	}
	else
	{
		DEBUG_OUTPUT("LisaaPala (irtopala), tyyppi: " << pala << std::endl);
	}
	_palat.push_back(Pala(pala, rotaatio, sijainti));
	_naytto->palaLaudalle(pala, Julkinen::NORMAALI, rotaatio, sijainti, Julkinen::Koordinaatti()); //tulostuksen testausta -> tï¿½mï¿½ poistetaan kun tulostus on kunnossa
}

void Peli::lisaaEsine(char merkki, Julkinen::Koordinaatti const& sijainti, std::string const& pelaaja) {
	for (unsigned int a = 0; a < _palat.size(); a++)
	{
		if (_palat[a].getSijainti() == sijainti)
		{
			DEBUG_OUTPUT("LisaaEsine, merkki: " << merkki << " pelaaja: " << pelaaja << std::endl);
			_palat[a].asetaEsine(pelaaja, merkki);
		}
	}
	
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
	if (_tyonnetty){
		throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAA_ON_JO_TYONNETTY);
		return;
	}
	if (reuna == Julkinen::EIOLE){
		throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_TUNNISTAMATON_KOMENTO);
		return;
	}
	if (paikka < 1 || paikka > (unsigned int) _alueenKoko){
		throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_OLEMATON_PAIKKA);
		return;
	}
	if (rotaatio < 1 || rotaatio > 4){
		throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_VIRHEELLINEN_ROTAATIO);
		return;
	}

	//Irtopala talteen
	Pala apupala(_palat[_alueenKoko * _alueenKoko]);
	apupala.setRotaatio(rotaatio);

	//Siirrä palat
	if (reuna == Julkinen::ALA){

		//Uusi irtopala
		_palat[_alueenKoko * _alueenKoko] = _palat[paikka - 1];
		_palat[_alueenKoko * _alueenKoko].setIrtopala(true);
		for (unsigned int i = 0; i < (unsigned int) _alueenKoko - 1; i++){
			_palat[(paikka - 1) + (_alueenKoko * i)] = _palat[(paikka - 1) + (_alueenKoko * (i + 1))];
			_palat[(paikka - 1) + (_alueenKoko * i)].setSijainti(paikka, i + 1);
		}
		apupala.setIrtopala(false);
		apupala.setSijainti(paikka, _alueenKoko);
		_palat[(paikka - 1) + (_alueenKoko * (_alueenKoko - 1))] = apupala;
	}
	if (reuna == Julkinen::YLA){
		//Uusi irtopala
		_palat[_alueenKoko * _alueenKoko] = _palat[(paikka - 1) + (_alueenKoko * (_alueenKoko - 1))];
		_palat[_alueenKoko * _alueenKoko].setIrtopala(true);
		for (unsigned int i = _alueenKoko - 2; i >= 0; i--){
			_palat[(paikka - 1) + (_alueenKoko * (i + 1))] = _palat[(paikka - 1) + (_alueenKoko * i)];
			_palat[(paikka - 1) + (_alueenKoko * (i + 1))].setSijainti(paikka, i + 2);
		}
		apupala.setIrtopala(false);
		apupala.setSijainti(paikka, 1);
		_palat[(paikka - 1)] = apupala;
	}
	if (reuna == Julkinen::VASEN){
		//Uusi irtopala
		_palat[_alueenKoko * _alueenKoko] = _palat[_alueenKoko - 1 + ((paikka - 1) * _alueenKoko)];
		_palat[_alueenKoko * _alueenKoko].setIrtopala(true);
		for (unsigned int i = ((paikka - 1) * _alueenKoko) + 4; i > (paikka - 1) * _alueenKoko; i--){
			_palat[i] = _palat[i - 1];
			_palat[i].setSijainti((i % 5) + 1, paikka);
		}
		apupala.setIrtopala(false);
		apupala.setSijainti(1, paikka);
		_palat[(paikka - 1) * _alueenKoko] = apupala;
	}
	if (reuna == Julkinen::OIKEA){
		//Uusi irtopala
		_palat[_alueenKoko * _alueenKoko] = _palat[(paikka - 1) * _alueenKoko];
		_palat[_alueenKoko * _alueenKoko].setIrtopala(true);
		for (unsigned int i = (paikka - 1) * _alueenKoko; i < ((paikka - 1) * _alueenKoko) + 4; i++){
			_palat[i] = _palat[i + 1];
			_palat[i].setSijainti((i % 5) + 1, paikka);
		}
		apupala.setIrtopala(false);
		apupala.setSijainti(_alueenKoko, paikka);
		_palat[((paikka - 1) * _alueenKoko) + _alueenKoko - 1] = apupala;
	}
	_tyonnetty = true;

}

void Peli::komentoLiiku(Julkinen::Suunta suunta, unsigned int maara) {

}

bool Peli::vaihdaVuoro() {
	//palauttaa 0 jos peli loppuu
	if (_vuorossa == _pelaajat.size()-1)
	{
		_vuorossa = 0;
	}
	else
	{
		_vuorossa++;
	}
	return 1;
}

Julkinen::PelaajaTyyppi Peli::haeVuorossa() {
	//return Julkinen::IHMINEN;
	return _pelaajat[_vuorossa].haePelaajaTyyppi();
}