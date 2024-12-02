#pragma once

#include <memory>

class Weg;
class Fahrzeug;

class Fahrausnahme;
class Losfahren;
class Streckenende;


class Verhalten
{
public:

	// Default-Konstruktor
	Verhalten(Weg& initWeg);

	// Destruktor
	virtual ~Verhalten(void);

	// Ermittelt zuruecklegbare Strecke eines Fahrzeugs innerhalb eines Zeitintervalls
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const;

	// Gibt befahrenen Weg zurueck
	virtual Weg& getWeg() const;


protected:

	// Referenz auf gespeicherten Weg
	Weg& p_rWeg;


};

