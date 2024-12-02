#include "Losfahren.h"
#include <memory>
#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;



// Konstruktor

Losfahren::Losfahren(Fahrzeug& initFahrzeug, Weg& initWeg)
	:Fahrausnahme(initFahrzeug, initWeg)
{

}


// Destruktor

Losfahren::~Losfahren(void)
{

}


// Bearbeitungsfunktion

void Losfahren::vBearbeiten()
{
	unique_ptr<Fahrzeug> startedVehicle_ptr = p_rWeg.pAbgabe(p_rFahrzeug);
	shared_ptr<Kreuzung> pKreuzung = nullptr;

	if (p_rWeg.getRueckweg() != nullptr)
	{
		pKreuzung = p_rWeg.getRueckweg()->getZielkreuzung();
	}


	if (pKreuzung != nullptr)
	{
		cout << resetiosflags(ios::right) << setiosflags(ios::left);
		cout << "FAHRZEUG GESTARTET" << endl;
		cout << "------------------" << endl;
		cout << setw(10) << "ZEIT: " << dGlobaleZeit << endl;
		cout << setw(10) << "KREUZUNG: " << pKreuzung->getName() << ", " << pKreuzung->getTankstelle() << " Liter" << endl;
		cout << setw(10) << "WECHSEL: " << p_rWeg.getName() << endl;
		cout << setw(10) << "FAHRZEUG: " << startedVehicle_ptr->getName() << ", " << startedVehicle_ptr->dGeschwindigkeit() << " km/h" << endl << endl;
	}

	else
	{
		cout << "Fahrzeug " << p_rFahrzeug.getName() << " startet ab dem Simulationsintervall auf " << dGlobaleZeit << " Stunden am Anfang des Weges " << p_rWeg.getName() << endl << endl;
	}

	p_rWeg.vAnnahme(move(startedVehicle_ptr));
}

