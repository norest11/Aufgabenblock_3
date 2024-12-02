#pragma once

#include "Simulationsobjekt.h"
#include "Tempolimit.h"

#include <memory>

class Weg;
class Fahrzeug;

class Kreuzung : public Simulationsobjekt
{
public:

	// Default-Konstruktor
	Kreuzung(void);

	// Namentlicher-Konstruktor
	Kreuzung(string initName);

	// Tankstellen-Konstruktor
	Kreuzung(string initName, double initTankstelle);

	// Copy-Konstruktor
	Kreuzung(const Kreuzung& kreuzung) = delete;

	// Destruktor
	virtual ~Kreuzung(void);

	// Verbindet zwei Kreuzungen miteinander
	static void vVerbinde(string initHinwegName, string initRueckwegName, double initLaenge, shared_ptr<Kreuzung> initStartKreuzung, shared_ptr<Kreuzung> initZielKreuzung, Tempolimit initTempolimit, bool initUeberholverbot);

	// Betankt vorbeifahrende Fahrzeuge
	void vTanken(Fahrzeug& initFahrzeug);

	// Nimmt Fahrzeuge auf Kreuzung auf
	void vAnnahme(unique_ptr<Fahrzeug> initFahrzeug, double initZeit);

	// Waehlt zufaelligen Weg aus
	Weg& pZufaelligerWeg(Weg& initWeg);

	// Gibt Inhalt der Tankstelle zurueck
	double getTankstelle() const;

	// Gibt Wege der Kreuzung aus
	void printWege() const;

	// Simuliert Kreuzung
	virtual void vSimulieren() override;

	// Gibt Kreuzungsdaten aus
	void vAusgeben(ostream& out) const override;

	// Gibt Tabellenkopf aus
	static void vKopf();

	// Liest Kreuzungsdaten ein
	virtual void vEinlesen(istream& in) override;


protected:

	// Wegfuehrende Wege
	list<shared_ptr<Weg>> p_pWege;

	// Tankvolumen
	double p_dTankstelle = 0.0;

};

