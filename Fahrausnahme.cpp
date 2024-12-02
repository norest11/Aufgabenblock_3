#include "Fahrausnahme.h"

#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;



// Konstruktor

Fahrausnahme::Fahrausnahme(Fahrzeug& initFahrzeug, Weg& initWeg)
	:p_rFahrzeug(initFahrzeug)
	,p_rWeg(initWeg)
{

}


// Destruktor

Fahrausnahme::~Fahrausnahme(void)
{

}


