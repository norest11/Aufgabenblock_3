#include "Fahren.h"

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

Fahren::Fahren(Weg& initWeg)
	:Verhalten(initWeg)
{

}


// Destruktor

Fahren::~Fahren(void)
{

}


// Ermittelt zuruecklegbare Strecke eines Fahrzeugs innerhalb eines Zeitintervalls

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const
{
	double dPossibleDistance = dZeitIntervall * aFzg.dGeschwindigkeit();
	double dTravelledDistance = aFzg.getAbschnittStrecke();
	double dPathBarrier = p_rWeg.getSchranke();

	if (bGleichheit(dTravelledDistance, dPathBarrier))
	{
		p_rWeg.setSchranke(dPathBarrier);

		throw Streckenende(aFzg, p_rWeg);
	}

	else
	{
		if (bGleichheit((dTravelledDistance + dPossibleDistance), dPathBarrier)
			|| (dTravelledDistance + dPossibleDistance) > dPathBarrier)
		{
			p_rWeg.setSchranke(dPathBarrier);

			return (dPathBarrier - dTravelledDistance);
		}

		else
		{
			p_rWeg.setSchranke(dTravelledDistance + dPossibleDistance);

			return (dPossibleDistance);
		}
	}
}

