#pragma once

#include "Verhalten.h"

class Weg;
class Fahrzeug;

class Fahrausnahme;
class Losfahren;
class Streckenende;


class Parken : public Verhalten
{
public:

	// Default-Konstruktor
	Parken(Weg& initWeg, double initStartzeitpunkt);

	// Destruktor
	virtual ~Parken(void);

	// Ermittelt zuruecklegbare Strecke eines Fahrzeugs innerhalb eines Zeitintervalls
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override;


protected:

	// Startzeitpunkt des Fahrzeugs
	double p_dStartzeitpunkt = 0;


};
