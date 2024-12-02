#include "Simulationsobjekt.h"


// Initialisierung der hochzaehlenden ID Variable

unsigned int Simulationsobjekt::p_iMaxID = 1;


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;


// Bekanntmachen der Abgleichsfunktion

extern bool bGleichheit(double initWert1, double initWert2);



// Default-Konstruktor

Simulationsobjekt::Simulationsobjekt(void)
	:p_iID(p_iMaxID++)
{
#if ANALYSE_SIMULATIONSOBJEKT
	cout << "Konstruiertes Default-Objekt:" << endl;
	cout << "ID: " << p_iID << endl << endl;
#endif
}


// Namentlicher-Konstruktor

Simulationsobjekt::Simulationsobjekt(string initName)
	:p_sName(initName)
	, p_iID(p_iMaxID++)
{
#if ANALYSE_SIMULATIONSOBJEKT
	cout << "Konstruiertes Namentliches-Objekt:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl << endl;
#endif
}


// Destruktor

Simulationsobjekt::~Simulationsobjekt(void)
{
#if ANALYSE_SIMULATIONSOBJEKT
	cout << "Destruiertes Objekt:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
#endif
}


// Simuliert Simulationsobjekt

void Simulationsobjekt::vSimulieren()
{
	if (!bGleichheit(p_dZeit, dGlobaleZeit) && p_dZeit < dGlobaleZeit)
	{
		double dVergangeneZeit = dGlobaleZeit - p_dZeit;

		p_dGesamtZeit = p_dGesamtZeit + dVergangeneZeit;
		p_dZeit = dGlobaleZeit;
	}
}


// Gibt Objekt-ID zurueck

unsigned int Simulationsobjekt::getID() const
{
	return p_iID;
}


// Gibt Objekt-Name zurueck

string Simulationsobjekt::getName() const
{
	return p_sName;
}


// Gibt Objektdaten aus

void Simulationsobjekt::vAusgeben(ostream& out) const
{
	out << resetiosflags(ios::left) << setiosflags(ios::right) << setw(4) << p_iID << " "
		<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(18) << p_sName << " ";
}


// Liest Objektdaten ein

void Simulationsobjekt::vEinlesen(istream& in)
{
	if (p_sName == "")
	{
		in >> p_sName;
	}

	else
	{
		string errorMessage = "Der Name des Objekts wurde bereits mit " + p_sName + " definiert";

		throw runtime_error(errorMessage);
	}
}


// Vergleicht, ob zwei Simulationsobjekte die gleiche ID besitzen

bool Simulationsobjekt::operator == (const Simulationsobjekt& simulationsobjekt) const
{
	if (p_iID == simulationsobjekt.p_iID)
	{
		return true;
	}

	else
	{
		return false;
	}
}


// Weisst Fahrzeug Stammdaten eines anderen Fahrzeugs zu

Simulationsobjekt& Simulationsobjekt::operator = (const Simulationsobjekt& simulationsobjekt)
{
	p_sName = "New " + simulationsobjekt.p_sName;
	p_dZeit = simulationsobjekt.p_dZeit;
	p_dGesamtZeit = 0.0;

	return *this;
}


//Überladung des Ausgabeoperators

ostream& operator << (ostream& out, const Simulationsobjekt& simulationsobjekt)
{
	simulationsobjekt.vAusgeben(out);

	return out;
}


//Überladung des Eingabeoperators

istream& operator >> (istream& in, Simulationsobjekt& simulationsobjekt)
{
	simulationsobjekt.vEinlesen(in);

	return in;
}

