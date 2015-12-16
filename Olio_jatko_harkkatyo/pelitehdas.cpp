#include "pelitehdas.hh"

namespace Julkinen {
	/**
	*  \brief Luo instanssi pelirajapinnasta.
	*
	*  P��ohjelma kutsuu t�t� funktiota saadakseen itselleen instanssin
	*  oliosta, joka toteuttaa pelirajapinnan.
	*  Funktion toteutus on teht�v� omaan koodiin.
	*
	*  \post Luodun peli-instanssin tuhoamisvastuu siirtyi p��ohjelmalle.
	*      Luotu olio on alustustilassa.
	*  \return Dynaamisesti luotu instanssi luokasta, joka toteuttaa
	*      Labyrintti-pelin.
	*/
	std::unique_ptr<Julkinen::Pelirajapinta> Julkinen::luoPeli() {
		return std::unique_ptr<Julkinen::Pelirajapinta>(new Peli);/*jotain*/;
	}
}