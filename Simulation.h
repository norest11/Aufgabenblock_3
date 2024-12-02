#pragma once

#include "Simulationsobjekt.h"
#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"


class Simulation
{

public:

	// Erzeugt aus Eingabestrom Verkehrsnetz
	void vEinlesen(istream& in, bool bMitGrafik = false);

	// Simuliert alle bekannten Kreuzungen
	void vSimulieren(double initDuration, double initInterval);

	// Map mit dem Inhalt aller Kreuzungen
	map<string, shared_ptr<Kreuzung>> Karte;


};


