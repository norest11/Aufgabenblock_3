#pragma once

#include "Simulationsobjekt.h"
#include <memory>
#include <string>
#include <iostream>
#include <iomanip>
#include <ostream>

class Weg;

class Verhalten;
class Fahren;
class Parken;

using namespace std;

class Fahrzeug : public Simulationsobjekt
{
public:

	// Default-Konstruktor
	Fahrzeug(void);

	// Namentlicher-Konstruktor
	Fahrzeug(string initName);

	// Geschwindigkeits-Konstruktor
	Fahrzeug(string initName, double initSpeed);

	// Copy-Konstruktor
	Fahrzeug(const Fahrzeug& fahrzeug) = delete;

	// Destruktor
	virtual ~Fahrzeug(void);

	// Betankt Fahrzeug
	virtual double dTanken(double dMenge = 0.0);

	// Reguliert Geschwindigkeit
	virtual double dGeschwindigkeit() const;

	// Setzt fahrendes Fahrzeug auf einen neuen Weg
	virtual void vNeueStrecke(Weg& initWeg);

	// Setzt parkendes Fahrzeug auf einen neuen Weg
	virtual void vNeueStrecke(Weg& initWeg, double dStartzeitpunkt);

	// Simuliert Fahrzeug
	virtual void vSimulieren() override;

	// Gibt Abschnittstrecke zurueck
	virtual double getAbschnittStrecke() const;

	// Gibt Fahrzeugdaten aus
	virtual void vAusgeben(ostream& out) const override;

	// Gibt Tabellenkopf aus
	static void vKopf();

	// Liest Fahrzeugdaten ein
	virtual void vEinlesen(istream& in) override;

	// Zeichenfunktion
	virtual void vZeichnen(const Weg& initWeg) const;

	// Vergleicht, ob ein Fahrzeug eine gr��ere Strecke besitzt
	virtual bool operator < (const Fahrzeug& fahrzeug) const;

	// Kopiert Name und MaxGeschwindigkeit eines Fahrzeug auf ein anderes Fahrzeug
	virtual Fahrzeug& operator = (const Fahrzeug& fahrzeug);


protected:

	// Maximalgeschwindigkeit des Fahrzeugs
	double p_dMaxGeschwindigkeit = 0.0;

	// Gesamtstrecke des Fahrzeugs
	double p_dGesamtStrecke = 0.0;

	// Strecke auf dem aktuellen Weg des Fahrzeugs
	double p_dAbschnittStrecke = 0.0;

	// Verhalten des Fahrzeugs
	unique_ptr<Verhalten> p_pVerhalten;


};

