#pragma once

#include "Fahrausnahme.h"

class Kreuzung;
class Weg;
class Fahrzeug;


class Losfahren : public Fahrausnahme
{
public:

	// Konstruktor
	Losfahren(Fahrzeug& initFahrzeug, Weg& initWeg);

	// Destruktor
	virtual ~Losfahren(void);

	// Bearbeitungsfunktion
	virtual void vBearbeiten() override;


};