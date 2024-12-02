#include "Verhalten.h"

#include "Weg.h"
#include "Fahrzeug.h"

#include <memory>

#include "Fahrausnahme.h"
#include "Losfahren.h"
#include "Streckenende.h"


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;


// Bekanntmachen der Abgleichsfunktion

extern bool bGleichheit(double initWert1, double initWert2);



// Default-Konstruktor

Verhalten::Verhalten(Weg& initWeg)
	:p_rWeg(initWeg)
{

}


// Destruktor

Verhalten::~Verhalten(void)
{

}


// Ermittelt zuruecklegbare Strecke eines Fahrzeugs innerhalb eines Zeitintervalls

double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const
{
	return 0.0;
}


// Gibt befahrenen Weg zurueck

Weg& Verhalten::getWeg() const
{
	return p_rWeg;
}


