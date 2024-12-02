#pragma once

#include "Fahrzeug.h"

class Weg;

class Verhalten;
class Fahren;
class Parken;


class PKW : public Fahrzeug
{
public:

	// Default-Kostruktor
	PKW(void);

	// Namentlicher-Konstruktor
	PKW(string initName);

	// Geschwindigkeits-Konstruktor
	PKW(string initName, double initSpeed);

	// Verbrauch-Konstruktor
	PKW(string initName, double initSpeed, double initVerbrauch);

	// Tank-Konstruktor
	PKW(string initName, double initSpeed, double initVerbrauch, double initTankvolumen);

	// Destruktor
	virtual ~PKW(void);

	// Reguliert Geschwindigkeit
	virtual double dGeschwindigkeit() const override;

	// Betankt PKW
	virtual double dTanken(double dMenge = numeric_limits<double>::infinity()) override;

	// Simuliert PKW
	virtual void vSimulieren() override;

	// Gibt PKW-Daten aus
	virtual void vAusgeben(ostream& out) const override;

	// Liest PKW-Daten ein
	virtual void vEinlesen(istream& in) override;

	// Zeichenfunktion
	virtual void vZeichnen(const Weg& initWeg) const override;

	// Weisst PKW Stammdaten eines anderen PKWs zu
	virtual PKW& operator=(const PKW& p);


private:

	// Benzin-Verbrauch des PKWs auf 100 km
	double p_dVerbrauch = 0.0;

	// Gesamter Benzin-Verbrauch des PKWs
	double p_dGesamtVerbrauch = 0.0;

	// Tankvolumen des PKWs
	double p_dTankvolumen = 0.0;

	// Tankinhalt des PKWs
	double p_dTankinhalt = 0.0;


};

