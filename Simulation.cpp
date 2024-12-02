#include "Simulation.h"


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;


// Bekanntmachen der Abgleichsfunktion

extern bool bGleichheit(double initWert1, double initWert2);



// Erzeugt aus Eingabestrom Verkehrsnetz

void Simulation::vEinlesen(istream& in, bool bMitGrafik)
{
	in.exceptions(ios_base::eofbit | ios_base::failbit | ios_base::badbit);

	unsigned int iLine = 0;

	try
	{
		while(!in.eof())
		{
			string vehicleType = "";
			in >> vehicleType;

			iLine++;


			if(vehicleType == "KREUZUNG")
			{
				shared_ptr<Kreuzung> Kreuzung_ptr = make_shared<Kreuzung>();

				in >> *Kreuzung_ptr;

				Karte[Kreuzung_ptr->getName()] = Kreuzung_ptr;


				if (bMitGrafik)
				{
					int xCoordiante = 0;
					int yCoordiante = 0;

					in >> xCoordiante >> yCoordiante;

					bZeichneKreuzung(xCoordiante, yCoordiante);
				}
			}


			else if (vehicleType == "STRASSE")
			{
				string NameQ = "";
				string NameZ = "";
				string NameW1 = "";
				string NameW2 = "";
				double Laenge = 0.0;
				unsigned int inTempolimit = 0;
				unsigned int inUeberholverbot = 0;

				in >> NameQ >> NameZ >> NameW1 >> NameW2 >> Laenge >> inTempolimit >> inUeberholverbot;


				shared_ptr<Kreuzung> Quellkreuzung_ptr = Karte[NameQ];

				if (Quellkreuzung_ptr == nullptr)
				{
					throw runtime_error("Die Quellkreuzung wurde nicht korrekt definiert");
				}

				shared_ptr<Kreuzung> Zielkreuzung_ptr = Karte[NameZ];

				if (Zielkreuzung_ptr == nullptr)
				{
					throw runtime_error("Die Zielkreuzung wurde nicht korrekt definiert");
				}


				double reLaenge = (double)Laenge;

				if (reLaenge <= 0)
				{
					throw runtime_error("Die Weglaenge wurde nicht korrekt definiert");
				}


				Tempolimit reTempolimit = Tempolimit::Autobahn;

				switch (inTempolimit)
				{
					case 1: reTempolimit = Tempolimit::Innerorts; break;
					case 2: reTempolimit = Tempolimit::Landstrasse; break;
					case 3: reTempolimit = Tempolimit::Autobahn; break;
					default: throw runtime_error("Das Tempolimit wurde nicht korrekt definiert"); break;
				}


				bool reUeberholverbot = true;

				switch (inUeberholverbot)
				{
					case 0: reUeberholverbot = false; break;
					case 1: reUeberholverbot = true; break;
					default: throw runtime_error("Das Ueberholverbot wurde nicht korrekt definiert"); break;
				}


				if (Quellkreuzung_ptr != nullptr && Zielkreuzung_ptr != nullptr)
				{
					Quellkreuzung_ptr->vVerbinde(NameW1, NameW2, reLaenge, Quellkreuzung_ptr, Zielkreuzung_ptr, reTempolimit, reUeberholverbot);
				}



				if (bMitGrafik)
				{
					unsigned int iCoordinatePairs = 0;

					in >> iCoordinatePairs;

					int iCoordinates[12];

					for (unsigned int iPairIterator = 0; iPairIterator < iCoordinatePairs; iPairIterator++)
					{
						in >> iCoordinates[2 * iPairIterator] >> iCoordinates[2 * iPairIterator + 1];
					}

					bZeichneStrasse(NameW1, NameW2, (int)Laenge, iCoordinatePairs, iCoordinates);
				}
			}


			else if (vehicleType == "PKW")
			{
				unique_ptr<PKW> PKW_ptr = make_unique<PKW>();
				string NameS = "";
				double StartZeitpunkt = 0.0;

				in >> *PKW_ptr >> NameS >> StartZeitpunkt;


				shared_ptr<Kreuzung> Startkreuzung_ptr = Karte[NameS];

				if (Startkreuzung_ptr == nullptr)
				{
					throw runtime_error("Die Startkreuzung wurde nicht korrekt definiert");
				}

				else
				{
					Karte[Startkreuzung_ptr->getName()]->vAnnahme(move(PKW_ptr), StartZeitpunkt);
				}
			}


			else if (vehicleType == "FAHRRAD")
			{
				unique_ptr<Fahrrad> Fahrrad_ptr = make_unique<Fahrrad>();
				string NameS = "";
				double StartZeitpunkt = 0.0;

				in >> *Fahrrad_ptr >> NameS >> StartZeitpunkt;


				shared_ptr<Kreuzung> Startkreuzung_ptr = Karte[NameS];

				if (Startkreuzung_ptr == nullptr)
				{
					throw runtime_error("Die Startkreuzung wurde nicht korrekt definiert");
				}

				else
				{
					Karte[Startkreuzung_ptr->getName()]->vAnnahme(move(Fahrrad_ptr), StartZeitpunkt);
				}
			}


			else
			{
				throw runtime_error("Der Objekttyp wurde nicht korrekt definiert");
			}
		}
	}

	catch (runtime_error errorMessage)
	{
		if (in.bad())
		{
			cout << "Die Datei konnte nicht geoeffnet werden" << endl << endl;

			return;
		}

		if (in.fail())
		{
			cout << "Formatierungsfehler in Zeile " << iLine << endl << endl;

			return;
		}

		if (in.eof())
		{
			cout << "Das Dateiende wurde erreicht" << endl << endl;

			cout << "Kreuzungen" << endl;
			cout << "----------" << endl << endl;

			for (map<string, shared_ptr<Kreuzung>>::iterator pIterator = Karte.begin(); pIterator != Karte.end(); pIterator++)
			{
				cout << *pIterator->second << endl;
			}

			cout << endl << endl;

			return;
		}


		cout << errorMessage.what() << endl;
		cout << "Fehler in Zeile: " << iLine << endl << endl;

		return;
	}
}

// Simuliert alle bekannten Kreuzungen

void Simulation::vSimulieren(double initDuration, double initInterval)
{
	while (!bGleichheit(dGlobaleZeit, initDuration) && dGlobaleZeit < initDuration)
	{
		dGlobaleZeit = dGlobaleZeit + initInterval;

		for (map<string, shared_ptr<Kreuzung>>::iterator pIterator = Karte.begin(); pIterator != Karte.end(); pIterator++)
		{
			pIterator->second->vSimulieren();
		}


		vSetzeZeit(dGlobaleZeit);

		cout << "Wege nach " << dGlobaleZeit << " Stunden" << endl;
		cout << "---------------------" << endl << endl;

		Weg::vKopf();

		for (map<string, shared_ptr<Kreuzung>>::iterator pIterator = Karte.begin(); pIterator != Karte.end(); pIterator++)
		{
			cout << "KREUZUNG " << pIterator->second->getName() << ":" << endl;

			pIterator->second->printWege();
		}

		cout << endl << endl;
	}
}

