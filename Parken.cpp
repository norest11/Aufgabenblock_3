#include "Parken.h"

#include "Weg.h"
#include "Fahrzeug.h"

#include "Fahrausnahme.h"
#include "Losfahren.h"
#include "Streckenende.h"


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;


// Bekanntmachen der Abgleichsfunktion

extern bool bGleichheit(double initWert1, double initWert2);



// Default-Konstruktor

Parken::Parken(Weg& initWeg, double initStartzeitpunkt)
	:Verhalten(initWeg)
	,p_dStartzeitpunkt(initStartzeitpunkt)
{

}


// Destruktor

Parken::~Parken(void)
{

}


// Ermittelt zuruecklegbare Strecke eines Fahrzeugs innerhalb eines Zeitintervalls

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const
{
	if (bGleichheit(dGlobaleZeit, p_dStartzeitpunkt) || dGlobaleZeit > p_dStartzeitpunkt)
	{
		throw Losfahren(aFzg, p_rWeg);
	}
	
	else
	{
		return 0.0;
	}
}

