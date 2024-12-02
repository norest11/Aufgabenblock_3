#pragma once

#include "Fahrzeug.h"

class Weg;

class Verhalten;
class Fahren;
class Parken;


class Fahrrad : public Fahrzeug
{
public:

	// Default-Kostruktor
	Fahrrad(void);

	// Namentlicher-Konstruktor
	Fahrrad(string initName);

	// Geschwindigkeits-Konstruktor
	Fahrrad(string initName, double initSpeed);

	// Destruktor
	virtual ~Fahrrad(void);

	// Reguliert Geschwindigkeit
	virtual double dGeschwindigkeit() const override;

	// Liest Fahrrad-Daten ein
	virtual void vEinlesen(istream& in) override;

	// Zeichenfunktion
	virtual void vZeichnen(const Weg& initWeg) const override;


};

