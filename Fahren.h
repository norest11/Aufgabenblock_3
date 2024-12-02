#pragma once

#include "Verhalten.h"

class Weg;
class Fahrzeug;

class Fahrausnahme;
class Losfahren;
class Streckenende;


class Fahren : public Verhalten
{
public:

	// Default-Konstruktor
	Fahren(Weg& initWeg);

	// Destruktor
	virtual ~Fahren(void);

	// Ermittelt zuruecklegbare Strecke eines Fahrzeugs innerhalb eines Zeitintervalls
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override;


};
