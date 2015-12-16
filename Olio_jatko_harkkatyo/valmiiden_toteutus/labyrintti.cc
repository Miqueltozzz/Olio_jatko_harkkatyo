/**
 *	\version $Id: labyrintti.cc 1802 2011-02-07 09:17:58Z salone58 $
 *  \file labyrintti.cc
 *  \brief Labyrintti pelin pääohjelma ($Revision: 1802 $)
 *  \author ©2011 Eero Salonen <eero.j.salonen@tut.fi>
 */

#include "./include/include.hh"

const unsigned int MAX_PARAMETREJA = 4;
std::string lueArgumentit(std::deque<std::string> parametrit);

/**
 * \brief Globaali debug-lippu
 *
 * Pääohjelma asettaa tämän lipun, jos ohjelma on käynnistetty debug-optiolla
 */
bool debug_output = false;

bool debug_naytto = false;

/**
 *	\brief Labyrintti-pelin pääohjelma.
 *
 *	Käyttöjärjestelmä kutsuu tätä funktiota ja käynnistää labyrintti-pelin.
 *
 *	\param argc komentorivi argumenttien määrä.
 *	\param argv komentorivi argumentit.
 *
 *	\return Tiedon onnistuiko ohjelman suoritus vai epäonnistuiko se.
 */
int main(int argc, char** argv)
{
	std::string tiedosto = "";
	std::deque<std::string> parametrit(argv, argv + argc);



   //Luetaan parametrit
	try
	{
		
		tiedosto = lueArgumentit(parametrit);
	}
	catch(Julkinen::Alustusvirhe virhe)
	{
		//Jos debug tilassa heitetään virhe eteenpäin
		if(debug_output)
		{ 
			DEBUG_OUTPUT(virhe);
			throw;
		}
		else
		{	std::cerr << virhe << std::endl;
			return EXIT_FAILURE;
		}
	}
	catch(...)
	{
		//Jos debug tilassa heitetään virhe eteenpäin
		if(debug_output)
		{ 
			DEBUG_OUTPUT("VIRHE: Parametrien lukeminen ep�onnistui");
			throw;
		}
		else
		{
			std::cerr
				<< "VIRHE: Parametrien lukeminen ep�onnistui"
				<< std::endl;
			return EXIT_FAILURE;
		}
	}

	try
	{
		Julkinen::Koordinaatti koko(5,5);
		//Luodaan osoitin n�ytt��nn.
		std::shared_ptr<Naytto> naytto(
			new Naytto(koko , 25, 20, debug_naytto));
		//Luodaan osoitin peliin
		
           std::shared_ptr<Julkinen::Pelirajapinta> peli(Julkinen::luoPeli());
		
		peli->lisaaNaytto(naytto.get());
		//Luodaan osoitin rakentajaan

           Rakentaja rakentaja(peli, koko,
                             tiedosto, naytto);
           
		//Alustetaan peli
		try
		{
	
			rakentaja.lueTiedosto();
	
			rakentaja.lisaaPalat();
	
			rakentaja.lisaaIrtopala();
	
			rakentaja.lisaaPelaajat();
	
			rakentaja.lisaaEsineet();
			peli->alustusLopeta();
        

		}
		catch(Julkinen::Virhe virhe)
		{
			//Jos debug tilassa heitetään virhe eteenpäin
			if(debug_output)
			{ 
				DEBUG_OUTPUT(  virhe );
				throw;
			}
			else
			{
				std::cerr << virhe << std::endl;
				return EXIT_FAILURE;
			}
		}
		catch(...)
		{
			//Jos debug tilassa heitetään virhe eteenpäin
			if(debug_output)
			{ 
				DEBUG_OUTPUT(  "VIRHE: Alustus epaonnistui" );
				throw;
			}
			else
			{
				std::cerr << "VIRHE: Alustus epaonnistui" << std::endl;
				return EXIT_FAILURE;
			}
		}
		
		try
		{
			//Luodaan komentotulkki osoitin
			std::shared_ptr<Komentotulkki> komentotulkki(
				Komentotulkki::uusiKomentotulkki(naytto));
			//Käynnistetään komentotulkki
			komentotulkki->kaynnistaKomentotulkki(peli);

		}
		catch(Julkinen::Virhe virhe)
		{
			//Jos debug tilassa heitetään virhe eteenpäin
			if(debug_output)
			{ 
				DEBUG_OUTPUT(  virhe );
				throw;
			}
			else
			{
				std::cerr << virhe << std::endl;
				return EXIT_FAILURE;
			}
		}
		catch(...)
		{
			//Jos debug tilassa heitetään virhe eteenpäin
			if(debug_output)
			{ 
				DEBUG_OUTPUT(  "VIRHE: Kaynnistys epaonnistui" );
				throw;
			}
			else
			{
				std::cerr << "VIRHE: Kaynnistys epaonnistui" << std::endl;
				return EXIT_FAILURE;
			}
		}

	}
	catch(Julkinen::Virhe virhe)
	{
		//Jos debug tilassa heitetään virhe eteenpäin
		if(debug_output)
		{ 
			DEBUG_OUTPUT(  virhe );
			throw;
		}
		else
		{
			std::cerr << virhe << std::endl;
			return EXIT_FAILURE;
		}
	}
	
	catch(...)
	{
		//Jos debug tilassa heitetään virhe eteenpäin
		if(debug_output)
		{ 
			DEBUG_OUTPUT(  "VIRHE: Tuntematon virhe" );
			throw;
		}
		else
		{
			std::cerr << "VIRHE: Tuntematon virhe" << std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;

}

std::string lueArgumentit(std::deque<std::string> parametrit)
{
   //Apumuuttuja alustustiedoston nime� varten
   std::string palaute;
   //K�yd��nn parametrit l�pi
   for(unsigned int i = 1; i < parametrit.size(); i++)
   {
      //Jos parametrina -d laitetaan ohjelma debug tilaan.
      if(parametrit[i] == "-d")
      {
         debug_output = true;
		 DEBUG_OUTPUT("Debug output enabled\n");
      }
      else if ( parametrit[i] == "-n" )
      {
         debug_naytto = true;
		 DEBUG_OUTPUT("Debug naytto enabled\n");
      }
                 
      else
      {
         palaute = parametrit[i];
      }
   }
   
   // Jos liikaa parametreja niin heitet��n poikkeus.
   if(parametrit.size() > MAX_PARAMETREJA)
   {
      throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHE_LIIKAA_PARAMETREJA);
   }
   
   return palaute;
}
