#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <cmath>
#include <random>
#include <map>

#include "SimuClient.h"


// Aktiviert Analysefunktionenen

#define ANALYSE_SIMULATIONSOBJEKT false
#define ANALYSE_KREUZUNG false
#define ANALYSE_WEG false
#define ANALYSE_FAHRZEUG false
#define ANALYSE_PKW false
#define ANALYSE_FAHRRAD false


using namespace std;



class Simulationsobjekt
{
public:

	// Default-Konstruktor
	Simulationsobjekt(void);

	// Namentlicher-Konstruktor
	Simulationsobjekt(string initName);

	// Copy-Konstruktor
	Simulationsobjekt(const Simulationsobjekt& simulationsobjekt) = delete;

	// Destruktor
	virtual ~Simulationsobjekt(void);

	// Simuliert Simulationsobjekt
	virtual void vSimulieren() = 0;

	// Gibt Objekt-ID zurueck
	virtual unsigned int getID() const;

	// Gibt Objekt-Name zurueck
	virtual string getName() const;

	// Gibt Objektdaten aus
	virtual void vAusgeben(ostream& out) const;

	// Liest Objektdaten ein
	virtual void vEinlesen(istream& in);

	// Vergleicht, ob zwei Simulationsobjekte die gleiche ID besitzen
	virtual bool operator == (const Simulationsobjekt& simulationsobjekt) const;

	// Weisst Fahrzeug Stammdaten eines anderen Fahrzeugs zu
	virtual Simulationsobjekt& operator = (const Simulationsobjekt& simulationsobjekt);


private:

	// Aktuell zu vergebende ID
	static unsigned int p_iMaxID;


protected:

	// ID des Objekts
	const unsigned int p_iID = 0;

	// Name des Objekts
	string p_sName = "";

	// Letzte Simulationszeit des Objekts
	double p_dZeit = 0.0;

	// Gesamte Simulationszeit des Objekts
	double p_dGesamtZeit = 0.0;


};


//Überladung des Ausgabeoperators

ostream& operator << (ostream& out, const Simulationsobjekt& simulationsobjekt);


//Überladung des Eingabeoperators

istream& operator >> (istream& in, Simulationsobjekt& simulationsobjekt);


