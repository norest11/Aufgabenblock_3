#include "Fahrzeug.h"

#include "Weg.h"

#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;


// Bekanntmachen der Abgleichsfunktion

extern bool bGleichheit(double initWert1, double initWert2);



// Default-Konstruktor

Fahrzeug::Fahrzeug(void)
	:Simulationsobjekt()
{
#if ANALYSE_FAHRZEUG
	cout << "Konstruiertes Default-Fahrzeug:" << endl;
	cout << "ID: " << p_iID << endl << endl;
#endif
}


// Namentlicher-Konstruktor

Fahrzeug::Fahrzeug(string initName)
	:Simulationsobjekt(initName)
{
#if ANALYSE_FAHRZEUG
	cout << "Konstruiertes Namentliches-Fahrzeug:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl << endl;
#endif
}


// Geschwindigkeits-Konstruktor

Fahrzeug::Fahrzeug(string initName, double initSpeed)
	:Simulationsobjekt(initName)
	, p_dMaxGeschwindigkeit((initSpeed >= 0) ? initSpeed : -initSpeed)
{
#if ANALYSE_FAHRZEUG
	cout << "Konstruiertes Geschwindigkeits-Fahrzeug:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Geschwindigkeit: " << p_dMaxGeschwindigkeit << endl << endl;
#endif
}


// Destruktor

Fahrzeug::~Fahrzeug(void)
{
#if ANALYSE_FAHRZEUG
	cout << "Destruiertes Fahrzeug:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Geschwindigkeit: " << p_dMaxGeschwindigkeit << endl << endl;
#endif
}


// Betankt Fahrzeug

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}


// Reguliert Geschwindigkeit

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}


// Setzt fahrendes Fahrzeug auf einen neuen Weg

void Fahrzeug::vNeueStrecke(Weg& initWeg)
{
	p_pVerhalten = make_unique<Fahren>(initWeg);

	p_dAbschnittStrecke = 0.0;
}


// Setzt parkendes Fahrzeug auf einen neuen Weg

void Fahrzeug::vNeueStrecke(Weg& initWeg, double dStartzeitpunkt)
{
	p_pVerhalten = make_unique<Parken>(initWeg, dStartzeitpunkt);

	p_dAbschnittStrecke = 0.0;
}


// Simuliert Fahrzeug

void Fahrzeug::vSimulieren()
{
	if (!bGleichheit(p_dZeit, dGlobaleZeit) && p_dZeit < dGlobaleZeit)
	{
		double dVorherigeZeit = p_dZeit;

		Simulationsobjekt::vSimulieren();

		double dVergangeneZeit = p_dZeit - dVorherigeZeit;
		double dZurueckgelegteStrecke = p_pVerhalten->dStrecke(*this, dVergangeneZeit);

		p_dGesamtStrecke = p_dGesamtStrecke + dZurueckgelegteStrecke;
		p_dAbschnittStrecke = p_dAbschnittStrecke + dZurueckgelegteStrecke;
	}
}


// Gibt Gesamtstrecke zurueck

double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}


// Gibt Fahrzeugdaten aus

void Fahrzeug::vAusgeben(ostream& out) const
{
	Simulationsobjekt::vAusgeben(out);

	out.precision(3);

	out << resetiosflags(ios::left) << setiosflags(ios::right) << setw(20) << p_dMaxGeschwindigkeit << " "
		<< setw(18) << dGeschwindigkeit() << " "
		<< setw(16) << p_dGesamtStrecke << " ";
}


// Gibt Tabellenkopf aus

void Fahrzeug::vKopf()
{
	cout << resetiosflags(ios::left) << setiosflags(ios::right) << setw(4) << "ID" << " "
		<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(18) << "Name" << " "
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(20) << "MaxGeschwindigkeit" << " "
		<< setw(18) << "Geschwindigkeit" << " "
		<< setw(16) << "Gesamtstrecke" << " "
		<< setw(18) << "Gesamtverbrauch" << " "
		<< setw(14) << "Tankinhalt" << endl;

	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
}


// Liest Fahrzeugdaten ein

void Fahrzeug::vEinlesen(istream& in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dMaxGeschwindigkeit;
}


// Zeichenfunktion

void Fahrzeug::vZeichnen(const Weg& initWeg) const
{

}


// Vergleicht, ob ein Fahrzeug eine größere Strecke besitzt

bool Fahrzeug::operator < (const Fahrzeug& fahrzeug) const
{
	if (p_dGesamtStrecke < fahrzeug.p_dGesamtStrecke)
	{
		return true;
	}

	else
	{
		return false;
	}
}


// Weisst Fahrzeug Stammdaten eines anderen Fahrzeugs zu

Fahrzeug& Fahrzeug::operator = (const Fahrzeug& fahrzeug)
{
	Simulationsobjekt::operator=(fahrzeug);

	p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;
	p_dGesamtStrecke = 0.0;

	return *this;
}


