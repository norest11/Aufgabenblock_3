#include "Streckenende.h"

#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;



// Konstruktor

Streckenende::Streckenende(Fahrzeug& initFahrzeug, Weg& initWeg)
	:Fahrausnahme(initFahrzeug, initWeg)
{

}


// Destruktor

Streckenende::~Streckenende(void)
{

}


// Bearbeitungsfunktion

void Streckenende::vBearbeiten()
{
	unique_ptr<Fahrzeug> movingVehicle_ptr = p_rWeg.pAbgabe(p_rFahrzeug);
	shared_ptr<Kreuzung> pKreuzung = p_rWeg.getZielkreuzung();

	if (pKreuzung != nullptr)
	{
		Weg& rWeiterfahrt = pKreuzung->pZufaelligerWeg(p_rWeg);

		pKreuzung->vTanken(*movingVehicle_ptr);

		cout << resetiosflags(ios::right) << setiosflags(ios::left);
		cout << "KREUZUNG UEBERQUERT" << endl;
		cout << "-------------------" << endl;
		cout << setw(10) << "ZEIT: " << dGlobaleZeit << endl;
		cout << setw(10) << "KREUZUNG: " << pKreuzung->getName() << ", " << pKreuzung->getTankstelle() << " Liter" << endl;
		cout << setw(10) << "WECHSEL: " << p_rWeg.getName() << " -> " << rWeiterfahrt.getName() << endl;
		cout << setw(10) << "FAHRZEUG: " << movingVehicle_ptr->getName() << ", " << movingVehicle_ptr->dGeschwindigkeit() << " km/h" << endl << endl;
		
		rWeiterfahrt.vAnnahme(move(movingVehicle_ptr));
	}

	else
	{
		cout << "Fahrzeug " << p_rFahrzeug.getName() << " steht ab dem Simulationsintervall auf " << dGlobaleZeit << " Stunden am Ende des Weges " << p_rWeg.getName() << endl << endl;
	}
}

