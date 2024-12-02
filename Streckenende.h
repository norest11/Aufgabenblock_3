#pragma once

#include "Fahrausnahme.h"

class Kreuzung;
class Weg;
class Fahrzeug;


class Streckenende : public Fahrausnahme
{
public:

	// Konstruktor
	Streckenende(Fahrzeug& initFahrzeug, Weg& initWeg);

	// Destruktor
	virtual ~Streckenende(void);

	// Bearbeitungsfunktion
	virtual void vBearbeiten() override;


};