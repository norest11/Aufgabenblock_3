#pragma once

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "VListe.h"

class Kreuzung;
class Fahrzeug;
class Fahrausnahme;

using namespace std;

class Weg : public Simulationsobjekt
{
public:

	// Default-Konstruktor
	Weg(void);

	// Namentlicher-Konstruktor
	Weg(string initName);

	// Laengen-Konstruktor
	Weg(string initName, double initLaenge);

	// Tempolimit-Konstruktor
	Weg(string initName, double initLaenge, Tempolimit initTempolimit);

	// Ueberholverbot-Konstruktor
	Weg(string initName, double initLaenge, Tempolimit initTempolimit, bool initUeberholverbot);

	// Zielkreuzungs-Konstruktor
	Weg(string initName, double initLaenge, Tempolimit initTempolimit, bool initUeberholverbot, shared_ptr<Kreuzung> initZielkreuzung);

	// Copy-Konstruktor
	Weg(const Weg& weg) = delete;

	// Destruktor
	virtual ~Weg(void);

	// Nimmt ein fahrendes Fahrzeug auf dem Weg auf
	virtual void vAnnahme(unique_ptr<Fahrzeug> fahrzeug_ptr);

	// Nimmt ein parkendes Fahrzeug auf dem Weg auf
	virtual void vAnnahme(unique_ptr<Fahrzeug> farzeug_ptr, double dStartzeitpunkt);

	// Gibt ein Fahrzeug von dem Weg ab
	virtual unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& rFahrzeug);

	// Setzt Schranke des vorrausfahrenden Fahrzeugs
	virtual void setSchranke(double initSchranke);

	// Setzt Rueckweg des Weges
	virtual void setRueckweg(shared_ptr<Weg> initRueckweg);

	// Konvertierungsfunktion des Tempolimits
	virtual double getTempolimit() const;

	// Gibt Weglaenge zurueck
	virtual double getLaenge() const;

	// Gibt Fahrzeuge zurueck
	virtual vertagt::VListe<unique_ptr<Fahrzeug>>& getFahrzeuge();

	// Gibt Schranke des vorrausfahrenden Fahrzeugs zurueck
	virtual double getSchranke() const;

	// Gibt Zielkreuzung zurueck
	virtual shared_ptr<Kreuzung> getZielkreuzung() const;

	// Gibt Rueckweg zurueck
	virtual shared_ptr<Weg> getRueckweg() const;

	// Simuliert Weg
	virtual void vSimulieren() override;

	// Gibt Wegdaten aus
	void vAusgeben(ostream& out) const override;

	// Gibt Tabellenkopf aus
	static void vKopf();


protected:

	// Laenge des Weges in km
	double p_dLaenge = 0.0;

	// Liste der auf dem Weg befindlichen Fahrzeuge
	vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;

	// Tempolimit des Weges
	Tempolimit p_eTempolimit = Tempolimit::Autobahn;

	// Ueberholverbot des Weges
	bool p_bUeberholverbot = true;

	// Schranke des vorrausfahrenden Fahrzeugs
	double p_dSchranke = 0.0;

	// Zielkreuzung des Weges
	const weak_ptr<Kreuzung> p_pZielkreuzung;

	// Rueckweg des Weges
	weak_ptr<Weg> p_pRueckweg;


};


