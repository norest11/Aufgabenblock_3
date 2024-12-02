#include "Fahrrad.h"

#include "Weg.h"

#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"

#include "Simuclient.h"

// Initialisierung der globalen Zeit

extern double dGlobaleZeit;


// Bekanntmachen der Abgleichsfunktion

extern bool bGleichheit(double initWert1, double initWert2);



// Default-Konstruktor

Fahrrad::Fahrrad(void)
	:Fahrzeug()
{
#if ANALYSE_FAHRRAD
	cout << "Konstruiertes Default-Fahrrad:" << endl;
	cout << "ID: " << p_iID << endl << endl;
#endif
}


// Namentlicher-Konstruktor

Fahrrad::Fahrrad(string initName)
	:Fahrzeug(initName)
{
#if ANALYSE_FAHRRAD
	cout << "Konstruiertes Namentliches-Fahrrad:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl << endl;
#endif
}


// Geschwindigkeits-Konstruktor

Fahrrad::Fahrrad(string initName, double initSpeed)
	:Fahrzeug(initName, initSpeed)
{
#if ANALYSE_FAHRRAD
	cout << "Konstruiertes Geschwindigkeits-Fahrrad:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Geschwindigkeit: " << p_dMaxGeschwindigkeit << endl << endl;
#endif
}


// Destruktor

Fahrrad::~Fahrrad(void)
{
#if ANALYSE_FAHRRAD
	cout << "Destruiertes Fahrrad:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Geschwindigkeit: " << p_dMaxGeschwindigkeit << endl << endl;
#endif
}


// Reguliert Geschwindigkeit

double Fahrrad::dGeschwindigkeit() const
{
	unsigned int iTwenties = (int)(p_dGesamtStrecke / 20);

	double dSpeed = p_dMaxGeschwindigkeit * pow(0.9, iTwenties);

	if (dSpeed > 12)
	{
		return dSpeed;
	}

	else
	{
		return 12;
	}
}


// Liest Fahrrad-Daten ein

void Fahrrad::vEinlesen(istream& in)
{
	Fahrzeug::vEinlesen(in);
}


// Zeichenfunktion

void Fahrrad::vZeichnen(const Weg& initWeg) const
{
	bZeichneFahrrad(p_sName, initWeg.getName(), getAbschnittStrecke() / initWeg.getLaenge(), dGeschwindigkeit());
}


