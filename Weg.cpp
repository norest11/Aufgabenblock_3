#include "Weg.h"

#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;


// Bekanntmachen der Abgleichsfunktion

extern bool bGleichheit(double initWert1, double initWert2);



// Default-Konstruktor

Weg::Weg(void)
	:Simulationsobjekt()
{
#if ANALYSE_WEG
	cout << "Konstruierter Default-Weg:" << endl;
	cout << "ID: " << p_iID << endl << endl;
#endif
}


// Namentlicher-Konstruktor

Weg::Weg(string initName)
	:Simulationsobjekt(initName)
{
#if ANALYSE_WEG
	cout << "Konstruierter Namentlicher-Weg:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl << endl;
#endif
}


// Laengen-Konstruktor

Weg::Weg(string initName, double initLaenge)
	:Simulationsobjekt(initName)
	, p_dLaenge(initLaenge)
{
#if ANALYSE_WEG
	cout << "Konstruierter Laengen-Weg:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Laenge: " << p_dLaenge << endl << endl;
#endif
}


// Tempolimit-Konstruktor

Weg::Weg(string initName, double initLaenge, Tempolimit initTempolimit)
	:Simulationsobjekt(initName)
	, p_dLaenge(initLaenge)
	, p_eTempolimit(initTempolimit)
{
#if ANALYSE_WEG
	cout << "Konstruierter Tempolimit-Weg:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Laenge: " << p_dLaenge << endl;
	cout << "Tempolimit: " << (double)p_eTempolimit << endl << endl;
#endif
}


// Ueberholverbot-Konstruktor

Weg::Weg(string initName, double initLaenge, Tempolimit initTempolimit, bool initUeberholverbot)
	:Simulationsobjekt(initName)
	, p_dLaenge(initLaenge)
	, p_eTempolimit(initTempolimit)
	, p_bUeberholverbot(initUeberholverbot)
{
#if ANALYSE_WEG
	cout << "Konstruierter Ueberholverbot-Weg:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Laenge: " << p_dLaenge << endl;
	cout << "Tempolimit: " << (double)p_eTempolimit << endl;
	cout << "Ueberholverbot: " << p_bUeberholverbot << endl << endl;
#endif
}


// Zielkreuzungs-Konstruktor

Weg::Weg(string initName, double initLaenge, Tempolimit initTempolimit, bool initUeberholverbot, shared_ptr<Kreuzung> initZielkreuzung)
	:Simulationsobjekt(initName)
	, p_dLaenge(initLaenge)
	, p_eTempolimit(initTempolimit)
	, p_bUeberholverbot(initUeberholverbot)
	,p_pZielkreuzung(initZielkreuzung)
{
#if ANALYSE_WEG
	cout << "Konstruierter Zielkreuzungs-Weg:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Laenge: " << p_dLaenge << endl;
	cout << "Tempolimit: " << (double)p_eTempolimit << endl;
	cout << "Ueberholverbot: " << p_bUeberholverbot << endl;
	cout << "Zielkreuzung: " << p_pZielkreuzung.lock()->getName() << endl << endl;
#endif
}


// Destruktor

Weg::~Weg(void)
{
#if ANALYSE_WEG
	cout << "Destruierter Weg:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Laenge: " << p_dLaenge << endl;
	cout << "Tempolimit: " << (double)p_eTempolimit << endl;
	cout << "Ueberholverbot: " << p_bUeberholverbot << endl << endl;
#endif
}


// Nimmt ein fahrendes Fahrzeug auf dem Weg auf

void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug_ptr)
{
	fahrzeug_ptr->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(move(fahrzeug_ptr));
}


// Nimmt ein parkendes Fahrzeug auf dem Weg auf

void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug_ptr, double dStartzeitpunkt)
{
	fahrzeug_ptr->vNeueStrecke(*this, dStartzeitpunkt);
	p_pFahrzeuge.push_front(move(fahrzeug_ptr));
}


// Gibt ein Fahrzeug von dem Weg ab

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& rFahrzeug)
{
	unique_ptr<Fahrzeug> deletedVehicle_ptr = nullptr;

	for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = p_pFahrzeuge.begin(); pIterator != p_pFahrzeuge.end(); pIterator++)
	{
		if ((*pIterator) != nullptr)
		{
			if ((**pIterator) == rFahrzeug)
			{
				deletedVehicle_ptr = move(*pIterator);

				p_pFahrzeuge.erase(pIterator);

				break;
			}
		}
	}

	return move(deletedVehicle_ptr);
}


// Setzt Schranke des vorrausfahrenden Fahrzeugs

void Weg::setSchranke(double initSchranke)
{
	p_dSchranke = initSchranke;
}


// Setzt Rueckweg des Weges

void Weg::setRueckweg(shared_ptr<Weg> initRueckweg)
{
	p_pRueckweg = initRueckweg;
}


// Konvertierungsfunktion des Tempolimits

double Weg::getTempolimit() const
{
	if (p_eTempolimit == Tempolimit::Innerorts)
	{
		return (double)Tempolimit::Innerorts;
	}

	else if (p_eTempolimit == Tempolimit::Landstrasse)
	{
		return (double)Tempolimit::Landstrasse;
	}

	else if (p_eTempolimit == Tempolimit::Autobahn)
	{
		return (double)Tempolimit::Autobahn;
	}

	else
	{
		return 0.0;
	}
}


// Gibt Weglaenge zurueck

double Weg::getLaenge() const
{
	return p_dLaenge;
}


// Gibt Fahrzeuge zurueck

vertagt::VListe<unique_ptr<Fahrzeug>>& Weg::getFahrzeuge()
{
	return p_pFahrzeuge;
}


// Gibt Schranke des vorrausfahrenden Fahrzeugs zurueck

double Weg::getSchranke() const
{
	if (p_bUeberholverbot == true)
	{
		return p_dSchranke;
	}

	else
	{
		return p_dLaenge;
	}
}


// Gibt Zielkreuzung zurueck

shared_ptr<Kreuzung> Weg::getZielkreuzung() const
{
	return p_pZielkreuzung.lock();
}


// Gibt Rueckweg zurueck

shared_ptr<Weg> Weg::getRueckweg() const
{
	return p_pRueckweg.lock();
}


// Simuliert Weg

void Weg::vSimulieren()
{
	p_dSchranke = p_dLaenge;

	for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = p_pFahrzeuge.begin(); pIterator != p_pFahrzeuge.end(); pIterator++)
	{
		try
		{
			(*pIterator)->vSimulieren();
			(*pIterator)->vZeichnen(*this);
		}

		catch (Fahrausnahme& rAusnahme)
		{
			rAusnahme.vBearbeiten();
		}
	}

	p_pFahrzeuge.vAktualisieren();

	Simulationsobjekt::vSimulieren();
}


// Gibt Wegdaten aus

void Weg::vAusgeben(ostream& out) const
{
	Simulationsobjekt::vAusgeben(out);

	string sWayMembers = "( ";

	for (vertagt::VListe<unique_ptr<Fahrzeug>>::const_iterator pIterator = p_pFahrzeuge.begin(); pIterator != p_pFahrzeuge.end(); pIterator++)
	{
		sWayMembers = sWayMembers + ((*pIterator)->getName() + " ");
	}

	sWayMembers = sWayMembers + ")";


	out.precision(3);

	out << resetiosflags(ios::left) << setiosflags(ios::right) << setw(8) << p_dLaenge << " "
		<< setw(32) << sWayMembers << " ";
}


// Gibt Tabellenkopf aus

void Weg::vKopf()
{
	cout << resetiosflags(ios::left) << setiosflags(ios::right) << setw(4) << "ID" << " "
		<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(18) << "Name" << " "
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(8) << "Laenge" << " "
		<< setw(32) << "Fahrzeuge" << endl;

	cout << "----------------------------------------------------------------" << endl;
}


