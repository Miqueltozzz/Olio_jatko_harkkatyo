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
	paivitaNaytto();
	_naytto->komentoLopetaRakennus();
	_naytto->ilmoitusVuorossa(_pelaajat[_vuorossa].haeNimi());
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
	DEBUG_OUTPUT("LisaaPelaaja, nimi: " << nimi << std::endl);

	_pelaajat.push_back(Pelaaja(tyyppi, nimi, lyhenne, sijainti));
}

void Peli::lisaaPala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti const& sijainti) {
	// ei toimi-> irtopalan koordinaatteja ei saa kysy� DEBUG_OUTPUT("LisaaPala, tyyppi: " << pala << "sijainti: " << sijainti.haeXkoordinaatti() << "," << sijainti.haeYkoordinaatti()<<" irtopala: "<<sijainti.onkoIrtopala() << std::endl);

	if (sijainti.onkoIrtopala() != 1)
	{
		DEBUG_OUTPUT("LisaaPala, tyyppi: " << pala << "sijainti: " << sijainti.haeXkoordinaatti() << "," << sijainti.haeYkoordinaatti() << std::endl);
	}
	else
	{
		DEBUG_OUTPUT("LisaaPala (irtopala), tyyppi: " << pala << std::endl);
	}
	_palat.push_back(Pala(pala, rotaatio, sijainti));
	//_naytto->palaLaudalle(pala, Julkinen::NORMAALI, rotaatio, sijainti, Julkinen::Koordinaatti()); //tulostuksen testausta -> t�m� poistetaan kun tulostus on kunnossa
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
	for (unsigned int a = 0; a < _pelaajat.size(); a++)
	{
		if (_pelaajat[a].haeNimi() == pelaaja)
		{
			_pelaajat[a].lisaaKerattavaEsine(merkki);
		}
	}

}

void Peli::asetaPalanTyyppi(Julkinen::ErikoispalaTyyppi tyyppi, Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde) {
	for (unsigned int a = 0; a < _palat.size(); a++)
	{
		if (_palat[a].getSijainti() == kohde)
		{
			if (_palat[a].getSijainti().onkoIrtopala() != 1)
			{
				DEBUG_OUTPUT("asetaPalanTyyppi, tyyppi: " << tyyppi << "sijainti: " << _palat[a].haeSijainti().haeXkoordinaatti() << "." << _palat[a].haeSijainti().haeYkoordinaatti() << std::endl);
			}
			else
			{
				DEBUG_OUTPUT("asetaPalanTyyppi, tyyppi: " << tyyppi << "sijainti: irtopala" << std::endl);
			}
			_palat[a].setErikoisPalaTyyppi(tyyppi);
			_palat[a].setErikoisPalaKohde(kohde);
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
	if (paikka < 1 || paikka >(unsigned int) _alueenKoko){
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

	//Siirr� palat
	if (reuna == Julkinen::ALA){

		//Uusi irtopala
		_palat[_alueenKoko * _alueenKoko] = _palat[paikka - 1];
		_palat[_alueenKoko * _alueenKoko].setIrtopala(true);
		for (unsigned int i = 0; i < (unsigned int)_alueenKoko - 1; i++){
			_palat[(paikka - 1) + (_alueenKoko * i)] = _palat[(paikka - 1) + (_alueenKoko * (i + 1))];
			_palat[(paikka - 1) + (_alueenKoko * i)].setSijainti(paikka, i + 1);
		}
		apupala.setIrtopala(false);
		apupala.setSijainti(paikka, _alueenKoko);
		_palat[(paikka - 1) + (_alueenKoko * (_alueenKoko - 1))] = apupala;

		//siirrä pelaajat
		for (int i = 0; i < _pelaajat.size(); i++){
			Julkinen::Koordinaatti koordinaatit = _pelaajat[i].haeSijainti();
			if (koordinaatit.haeXkoordinaatti() == paikka){
				if ((int)koordinaatit.haeYkoordinaatti() - 1 > 0){
					_pelaajat[i].asetaYkoord(koordinaatit.haeYkoordinaatti() - 1);
	}
				else{
					_pelaajat[i].asetaYkoord(_alueenKoko);
				}
			}
		}
	}
	else if (reuna == Julkinen::YLA){
		//Uusi irtopala
		_palat[_alueenKoko * _alueenKoko] = _palat[(paikka - 1) + (_alueenKoko * (_alueenKoko - 1))];
		_palat[_alueenKoko * _alueenKoko].setIrtopala(true);
		for (int i = _alueenKoko - 2; i >= 0; i--){
			_palat[(paikka - 1) + (_alueenKoko * (i + 1))] = _palat[(paikka - 1) + (_alueenKoko * i)];
			_palat[(paikka - 1) + (_alueenKoko * (i + 1))].setSijainti(paikka, i + 2);
		}
		apupala.setIrtopala(false);
		apupala.setSijainti(paikka, 1);
		_palat[(paikka - 1)] = apupala;

		//siirrä pelaajat
		for (int i = 0; i < _pelaajat.size(); i++){
			Julkinen::Koordinaatti koordinaatit = _pelaajat[i].haeSijainti();
			if (koordinaatit.haeXkoordinaatti() == paikka){
				if ((int) koordinaatit.haeYkoordinaatti() + 1 <= _alueenKoko){
					_pelaajat[i].asetaYkoord(koordinaatit.haeYkoordinaatti() + 1);
				}
				else{
					_pelaajat[i].asetaYkoord(1);
				}
			}
		}
	}
	else if (reuna == Julkinen::VASEN){
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

		//siirrä pelaajat
		for (int i = 0; i < _pelaajat.size(); i++){
			Julkinen::Koordinaatti koordinaatit = _pelaajat[i].haeSijainti();
			if (koordinaatit.haeYkoordinaatti() == paikka){
				if ((int) koordinaatit.haeXkoordinaatti() + 1 <= _alueenKoko){
					_pelaajat[i].asetaXkoord(koordinaatit.haeXkoordinaatti() + 1);
	}
				else{
					_pelaajat[i].asetaXkoord(1);
				}
			}
		}
	}
	else if (reuna == Julkinen::OIKEA){
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

		//siirrä pelaajat
		for (int i = 0; i < _pelaajat.size(); i++){
			Julkinen::Koordinaatti koordinaatit = _pelaajat[i].haeSijainti();
			if (koordinaatit.haeYkoordinaatti() == paikka){
				if ((int) koordinaatit.haeXkoordinaatti() - 1 > 0){
					_pelaajat[i].asetaXkoord(koordinaatit.haeXkoordinaatti() - 1);
				}
				else{
					_pelaajat[i].asetaXkoord(_alueenKoko);
				}
			}

	}
	}
	_tyonnetty = true;
	_naytto->komentoAloitaRakennus();
	paivitaNaytto();
	_naytto->komentoLopetaRakennus();
	_naytto->ilmoitusVuorossa(_pelaajat[_vuorossa].haeNimi());
	
}

void Peli::komentoLiiku(Julkinen::Suunta suunta, unsigned int maara) {
	
	if (_pelaajaLiikkunut){
		throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_TUNNISTAMATON);
		return;
	}
	if (!_tyonnetty  && suunta != Julkinen::AUTOMAATTI){
		throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAA_EI_OLE_TYONNETTY);
		return;
	}
	if (maara < 0){
		throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_TUNNISTAMATON_PARAMETRI);
	}
	if (maara == 0 && (suunta != Julkinen::PAIKALLAAN && suunta != Julkinen::AUTOMAATTI)){
		throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_TUNNISTAMATON_KOMENTO);
	}

	Pelaaja pelaaja(_pelaajat[_vuorossa]);
	char esine = 0;
	int xkoord = (int)pelaaja.haeSijainti().haeXkoordinaatti();
	int ykoord = (int)pelaaja.haeSijainti().haeYkoordinaatti();

	if (suunta == Julkinen::ALAS){
		//Tarkista ettei menn� laudan reunan yli
		if (ykoord + (int)maara > _alueenKoko){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
		//Tarkista ettei kukaan pelaajista ole ruudussa
		for (unsigned int i = 0; i < _pelaajat.size(); i++){
			Julkinen::Koordinaatti sij = _pelaajat[i].haeSijainti();
			if (sij.haeXkoordinaatti() == xkoord && sij.haeYkoordinaatti() == ykoord + (int)maara){
				throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
			}
		}
		//Tarkista ettei reitill� ole seini�
		if (maara > 1){
			for (unsigned int i = 0; i < maara - 1; i++){
				if (!_palat[xkoord - 1 + ((ykoord + i) * _alueenKoko)].lapiKavely(suunta)){
					throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
				}
			}
		}
		if (!_palat[xkoord - 1 + ((ykoord + maara - 1) * _alueenKoko)].sisaanKavely(suunta)){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
		//Tarkista onko reitill� ker�tt�vi� esineit�
		if (maara > 1){
			for (unsigned int i = 0; i < maara - 1; i++){
				esine = _palat[xkoord - 1 + ((ykoord + maara - 1) * _alueenKoko)].haeEsineMerkki();
				if (_pelaajat[i].haeTamanHetkinenEsine() == esine){
					_pelaajat[i].keraaTamanHetkinenEsine();
					_naytto->ilmoitusEsinePoimittu(esine, pelaaja.haeNimi());
				}
			}
		}
		//Liiku alas
		_pelaajat[_vuorossa].asetaYkoord(ykoord + maara);
		esine = _palat[(xkoord - 1) + (ykoord + maara - 1) * _alueenKoko].haeEsineMerkki();
		if (_pelaajat[_vuorossa].haeTamanHetkinenEsine() == esine){
			_pelaajat[_vuorossa].keraaTamanHetkinenEsine();
			_naytto->ilmoitusEsinePoimittu(esine, pelaaja.haeNimi());
		}
	}
	else if (suunta == Julkinen::YLOS){
		//Tarkista ettei mennä laudan reunan yli
		if (ykoord - (int)maara < 1){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
		//Tarkista ettei kukaan pelaajista ole ruudussa
		for (unsigned int i = 0; i < _pelaajat.size(); i++){
			Julkinen::Koordinaatti sij = _pelaajat[i].haeSijainti();
			if (sij.haeXkoordinaatti() == xkoord && sij.haeYkoordinaatti() == ykoord - (int)maara){
				throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
			}
		}
		//Tarkista ettei reitill� ole seini�
		if (maara > 1){
			for (unsigned int i = 2; i <= maara; i++){
				if (!_palat[xkoord - 1 + ((ykoord - i) * _alueenKoko)].lapiKavely(suunta)){
					throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
				}
			}
		}
		if (!_palat[xkoord - 1 + ((ykoord - maara - 1) * _alueenKoko)].sisaanKavely(suunta)){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
		//Tarkista onko reitill� ker�tt�vi� esineit�
		if (maara > 1){
			for (unsigned int i = 2; i <= maara; i++){
				esine = _palat[xkoord - 1 + ((ykoord - i) * _alueenKoko)].haeEsineMerkki();
				if (_pelaajat[i].haeTamanHetkinenEsine() == esine){
					_pelaajat[i].keraaTamanHetkinenEsine();
					_naytto->ilmoitusEsinePoimittu(esine, pelaaja.haeNimi());
				}
			}
		}
		//Liiku ylos
		_pelaajat[_vuorossa].asetaYkoord(ykoord - maara);
		esine = _palat[(xkoord - 1) + (ykoord - maara - 1) * _alueenKoko].haeEsineMerkki();
		if (_pelaajat[_vuorossa].haeTamanHetkinenEsine() == esine){
			_pelaajat[_vuorossa].keraaTamanHetkinenEsine();
			_naytto->ilmoitusEsinePoimittu(esine, pelaaja.haeNimi());
		}
	}
	else if (suunta == Julkinen::OIKEALLE){
		//Tarkista ettei mennä laudan reunan yli
		if (xkoord + (int)maara > _alueenKoko){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
		//Tarkista ettei kukaan pelaajista ole ruudussa
		for (unsigned int i = 0; i < _pelaajat.size(); i++){
			Julkinen::Koordinaatti sij = _pelaajat[i].haeSijainti();
			if (sij.haeXkoordinaatti() == xkoord + (int)maara && sij.haeYkoordinaatti() == ykoord){
				throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
			}
		}
		//Tarkista ettei reitill� ole seini�
		if (maara > 1){
			for (unsigned int i = 0; i < maara - 1; i++){
				if (!_palat[xkoord + i + ((ykoord - 1) * _alueenKoko)].lapiKavely(suunta)){
					throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
				}
			}
		}
		if (!_palat[xkoord + maara - 1 + ((ykoord - 1) * _alueenKoko)].sisaanKavely(suunta)){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
		//Tarkista onko reitill� ker�tt�vi� esineit�
		if (maara > 1){
			for (unsigned int i = 0; i < maara - 1; i++){
				esine = _palat[xkoord + i + ((ykoord - 1) * _alueenKoko)].haeEsineMerkki();
				if (_pelaajat[i].haeTamanHetkinenEsine() == esine){
					_pelaajat[i].keraaTamanHetkinenEsine();
					_naytto->ilmoitusEsinePoimittu(esine, pelaaja.haeNimi());
				}
			}
		}
		//Liiku oikealle
		_pelaajat[_vuorossa].asetaXkoord(xkoord + maara);
		esine = _palat[(xkoord + maara - 1) + (ykoord - 1) * _alueenKoko].haeEsineMerkki();
		if (_pelaajat[_vuorossa].haeTamanHetkinenEsine() == esine){
			_pelaajat[_vuorossa].keraaTamanHetkinenEsine();
			_naytto->ilmoitusEsinePoimittu(esine, pelaaja.haeNimi());
		}
	}
	else if (suunta == Julkinen::VASEMMALLE){
		//Tarkista ettei mennä laudan reunan yli
		if (xkoord - (int)maara < 1){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
		//Tarkista ettei kukaan pelaajista ole ruudussa
		for (unsigned int i = 0; i < _pelaajat.size(); i++){
			Julkinen::Koordinaatti sij = _pelaajat[i].haeSijainti();
			if (sij.haeXkoordinaatti() == xkoord - (int)maara && sij.haeYkoordinaatti() == ykoord){
				throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
			}
		}
		//Tarkista ettei reitill� ole seini�
		if (maara > 1){
			for (unsigned int i = 2; i <= maara; i++){
				if (!_palat[xkoord - i + ((ykoord - 1) * _alueenKoko)].lapiKavely(suunta)){
					throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
				}
			}
		}
		if (!_palat[xkoord - maara - 1 + ((ykoord - 1) * _alueenKoko)].sisaanKavely(suunta)){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
		//Tarkista ettei reitill� ole ker�tt�vi� esineit�
		if (maara > 1){
			for (unsigned int i = 2; i <= maara; i++){
				esine = _palat[xkoord - i + ((ykoord - 1) * _alueenKoko)].haeEsineMerkki();
				if (_pelaajat[i].haeTamanHetkinenEsine() == esine){
					_pelaajat[i].keraaTamanHetkinenEsine();
					_naytto->ilmoitusEsinePoimittu(esine, pelaaja.haeNimi());
				}
			}
		}
		//Liiku vasemmalle
		_pelaajat[_vuorossa].asetaXkoord(xkoord - maara);
		esine = _palat[(xkoord - maara - 1) + (ykoord - 1) * _alueenKoko].haeEsineMerkki();
		if (_pelaajat[_vuorossa].haeTamanHetkinenEsine() == esine){
			_pelaajat[_vuorossa].keraaTamanHetkinenEsine();
			_naytto->ilmoitusEsinePoimittu(esine, pelaaja.haeNimi());
		}
	}

	_pelaajaLiikkunut = true;
	_naytto->komentoAloitaRakennus();
	paivitaNaytto();
	_naytto->komentoLopetaRakennus();
	_naytto->ilmoitusVuorossa(_pelaajat[_vuorossa].haeNimi());
	
}

bool Peli::vaihdaVuoro() {
	_pelaajaLiikkunut = false;
	_tyonnetty= false;
	//palauttaa 0 jos peli loppuu
	if (_vuorossa == _pelaajat.size() - 1)
	{
		_vuorossa = 0;
	}
	else
	{
		_vuorossa++;
	}
	return 1;
}

void Peli::paivitaNaytto()
{
	DEBUG_OUTPUT("paivitaNaytto" << std::endl);


	//lis�� palat laudalle
	for (unsigned int a = 0; a < _palat.size(); a++)
	{
		_naytto->palaLaudalle(_palat[a].haePalaTyyppi(), _palat[a].haeErikoisPalaTyyppi(), _palat[a].haeRotaatio(), _palat[a].haeSijainti(), _palat[a].haeErikoisPalaKohde());
	}

	//lis�� pelaajat laudalle
	for (unsigned int a = 0; a < _pelaajat.size(); a++)
	{
		_naytto->pelaajaLaudalle(_pelaajat[a].haeLyhenne(), _pelaajat[a].haeSijainti());
	}
	//lis�� esineet laudalle
	for (unsigned int a = 0; a < _palat.size(); a++)
	{
		if (_palat[a].haeEsineMerkki() != '0')
		{
			_naytto->esineLaudalle(_palat[a].haeEsineMerkki(), _palat[a].haeSijainti());
		}
	}
	//tulosta pelaajien nimet ja esineet
	for (unsigned int a = 0; a < _pelaajat.size(); a++)
	{
		_naytto->tulostaPelaajantiedot(_pelaajat[a].haeNimi(), _pelaajat[a].haeKeratutEsineet(), _pelaajat[a].haeKerattavatEsineet(), _pelaajat[a].haeEdellinenToiminto());
	}

}

Julkinen::PelaajaTyyppi Peli::haeVuorossa() {
	//return Julkinen::IHMINEN;
	return _pelaajat[_vuorossa].haePelaajaTyyppi();
}