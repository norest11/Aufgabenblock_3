#pragma once

#include <exception>

class Kreuzung;
class Weg;
class Fahrzeug;


class Fahrausnahme : std::exception
{
public:

	// Konstruktor
	Fahrausnahme(Fahrzeug& initFahrzeug, Weg& initWeg);

	// Destruktor
	virtual ~Fahrausnahme(void);

	// Bearbeitungsfunktion
	virtual void vBearbeiten() = 0;


protected:

	// Referenz auf Fahrzeug
	Fahrzeug& p_rFahrzeug;

	// Referenz auf Weg;
	Weg& p_rWeg;


};