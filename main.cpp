#include "Simulationsobjekt.h"

#include <memory>
#include "vector"
#include <string>
#include <cmath>
#include <iostream>

#include "Kreuzung.h"
#include "Weg.h"
#include "Tempolimit.h"

#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"

#include "Fahrausnahme.h"
#include "Losfahren.h"
#include "Streckenende.h"

#include "Simulation.h"

#include "VListe.h"

#include "SimuClient.h"

using namespace std;

// Initialisierung der globalen Zeit

double dGlobaleZeit = 0.0;


// Prueft Gleichheit zweier double-Werte

bool bGleichheit(double initWert1, double initWert2)
{
	double epsilon = 0.0000001;

	double dDifferenz = initWert2 - initWert1;

	double dBetrag = fabs(dDifferenz);

	if (dBetrag <= epsilon)
	{
		return true;
	}

	else
	{
		return false;
	}
}


// Vorw�rtsdeklarationen aller vorhandenen Funktionen

void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();
void vAufgabe_7();
void vAufgabe_8();
void vAufgabe_9();
void vAufgabe_9a();



// Abfrage der zu bearbeitenden Aufgabe


int main()
{
	char cAbfrage = ' ';

	while (cAbfrage != 'X')
	{
		cout << "Aufgaben" << endl;
		cout << "--------------" << endl;
		cout << "A: Aufgabe 1" << endl;
		cout << "B: Aufgabe 1a" << endl;
		cout << "C: Aufgabe 2" << endl;
		cout << "D: Aufgabe 3" << endl;
		cout << "E: Aufgabe 4" << endl;
		cout << "F: Aufgabe 5" << endl;
		cout << "G: Aufgabe 6" << endl;
		cout << "H: Aufgabe 6a" << endl;
		cout << "I: Aufgabe 7" << endl;
		cout << "J: Aufgabe 8" << endl;
		cout << "K: Aufgabe 9" << endl;
		cout << "L: Aufgabe 9a" << endl;
		cout << "X: Beenden" << endl;
		cout << endl;
		cout << "Bitte geben Sie den Buchstaben der gewuenschten Aufgabe ein: ";
		cin >> cAbfrage;
		cout << endl << endl;


		switch (cAbfrage)
		{
		case 'A':
			vAufgabe_1();
			break;

		case 'B':
			vAufgabe_1a();
			break;

		case 'C':
			vAufgabe_2();
			break;

		case 'D':
			vAufgabe_3();
			break;

		case 'E':
			vAufgabe_4();
			break;

		case 'F':
			vAufgabe_5();
			break;

		case 'G':
			vAufgabe_6();
			break;

		case 'H':
			vAufgabe_6a();
			break;

		case 'I':
			vAufgabe_7();
			break;

		case 'J':
			vAufgabe_8();
			break;

		case 'K':
			vAufgabe_9();
			break;

		case 'L':
			vAufgabe_9a();
			break;

		case 'X':
			cout << "Das Programm wird nun beendet" << endl << endl;
			break;

		}

		dGlobaleZeit = 0;
	}

	return 0;
}



///////////////
// Aufgabe 1 //
///////////////



void vAufgabe_1()
{
	// Erzeugen von statischen Default-Fahrzeugen

	Fahrzeug LKWchen;
	Fahrzeug Fahrraedchen;


	// Erzeugen von statischen Namentlichen-Fahrzeugen

	Fahrzeug LKW("Packesel");
	Fahrzeug Fahrrad("Drahtesel");


	// Erzeugen von dynamischen Default-Fahrzeugen

	Fahrzeug* Autochen = new Fahrzeug();
	Fahrzeug* Motorraedchen = new Fahrzeug();


	// Erzeugen von dynamischen Namentlichen-Fahrzeugen

	Fahrzeug* Auto = new Fahrzeug("Brummer");
	Fahrzeug* Motorrad = new Fahrzeug("Rowdy");


	// L�schen der dynamischen Default-Fahrzeuge

	delete Autochen;
	delete Motorraedchen;


	// L�schen der dynamischen Namentlichen-Fahrzeuge

	delete Auto;
	delete Motorrad;



	// Erzeugen von Smartpointern

	auto Helmut_ptr = make_unique<Fahrzeug>("Helmut");
	auto Gertrud_ptr = make_unique<Fahrzeug>("Gertrud");

	auto Hildeguard_ptr = make_shared<Fahrzeug>("Hildeguard");
	auto Gustav_ptr = make_shared<Fahrzeug>("Gustav");


	// Erzeugen eines weiteren Sharedpointers auf Objekt von Hildeguard_ptr

	cout << "Analyse von Hildegurad_ptr:" << endl;

	cout << "Anazahl der Referenzen: " << Hildeguard_ptr.use_count() << endl;

	auto Hildeguard_PTR(Hildeguard_ptr);

	cout << "Neue Anzahl der Referenzen: " << Hildeguard_ptr.use_count() << endl << endl << endl << endl;


	// Erzeugen eines unique_ptr-Vektors

	vector<unique_ptr<Fahrzeug>> unique_ptrVektor;


	// Fahrzeuge dem unique_ptr-Vektor hinzuf�gn

	unique_ptrVektor.push_back(move(Helmut_ptr));
	unique_ptrVektor.push_back(move(Gertrud_ptr));


	// Fahrzeuge des unique_ptr-Vektors ausgeben

	cout << "In unique_ptr-Vektor gespeicherte Fahrzeuge:" << endl << endl;

	Fahrzeug::vKopf();

	for (unsigned int iIterator = 0; iIterator < unique_ptrVektor.size(); iIterator++)
	{
		cout << *unique_ptrVektor[iIterator] << endl;
	}

	cout << endl << endl << endl;


	// Loeschen des unique-ptr-Vektors

	unique_ptrVektor.clear();


	// Erzeugen eines shared_ptr-Vektors

	vector<shared_ptr<Fahrzeug>> shared_ptrVektor;


	// Anzahl der Referenzen vor Hinzufuegen

	unsigned int refHildeguard1 = Hildeguard_ptr.use_count();
	unsigned int refGustav1 = Gustav_ptr.use_count();


	// Fahrzeuge dem shared_ptr-Vektor hinzuf�gn

	shared_ptrVektor.push_back(move(Hildeguard_ptr));
	shared_ptrVektor.push_back(Gustav_ptr);


	// Anzahl der Referenzen nach Hinzufuegen

	unsigned int refHildeguard2 = Hildeguard_ptr.use_count();
	unsigned int refGustav2 = Gustav_ptr.use_count();


	// Fahrzeuge und Informationen des shared_ptr-Vektors ausgeben

	cout << "In shared_ptr-Vektor gespeicherte Fahrzeuge:" << endl << endl;

	Fahrzeug::vKopf();

	for (unsigned int iIterator = 0; iIterator < shared_ptrVektor.size(); iIterator++)
	{
		cout << *shared_ptrVektor[iIterator] << endl;
	}

	cout << endl << endl;

	cout << "Anzahl der Referenzen vor Hinzufuegen:" << endl;
	cout << "Hildeguard: " << refHildeguard1 << endl;
	cout << "Gustav: " << refGustav1 << endl << endl;

	cout << "Anzahl der Referenzen nach Hinzufuegen:" << endl;
	cout << "Hildeguard: " << refHildeguard2 << endl;
	cout << "Gustav: " << refHildeguard1 << endl << endl << endl << endl;


	// Loeschen des shared-ptr-Vektors

	shared_ptrVektor.clear();
}



////////////////
// Aufgabe 1a //
////////////////



void vAufgabe_1a()
{
	// Erzeuge Weg

	unique_ptr<Weg> pWeg = make_unique<Weg>("Weg", numeric_limits<double>::infinity(), Tempolimit::Autobahn, false);


	// Lese 3 Fahrzeuge ein

	for (unsigned int iIterator = 0; iIterator < 3; iIterator++)
	{
		string initName = "";
		double initSpeed = 0.0;

		cout << "Geben Sie den Namen des " << iIterator + 1 << ". Fahrzeugs ein: ";
		cin >> initName;

		cout << "Geben Sie die Maximalgeschwindigkeit des " << iIterator + 1 << ". Fahrzeugs ein: ";
		cin >> initSpeed;
		cout << endl;

		// Erzeuge Fahrzeug

		auto newVehicle_ptr = make_unique<Fahrzeug>(initName, initSpeed);

		// Fuege erzeugtes Fahrzeug dem Weg hinzu

		pWeg->vAnnahme(move(newVehicle_ptr));

		pWeg->vSimulieren();
	}


	// Fahrzeuge des vehicles-Vektors ausgeben

	cout << "In der Datenbank gespeicherte Fahrzeuge:" << endl << endl;

	Fahrzeug::vKopf();

	for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = pWeg->getFahrzeuge().begin(); pIterator != pWeg->getFahrzeuge().end(); pIterator++)
	{
		cout << **pIterator << endl;
	}

	cout << endl << endl;


	// Fahrzeuge simulieren und ausgeben

	while (dGlobaleZeit < (0.166666666667))
	{
		dGlobaleZeit = dGlobaleZeit + (0.016666666667);

		pWeg->vSimulieren();

		if (dGlobaleZeit < 2)
		{
			cout << "Fahrzeuge nach der " << dGlobaleZeit * 60 << ". Minute:" << endl << endl;
		}

		else
		{
			cout << "Fahrzeuge nach " << dGlobaleZeit << " Stunden:" << endl << endl;
		}

		Fahrzeug::vKopf();

		for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = pWeg->getFahrzeuge().begin(); pIterator != pWeg->getFahrzeuge().end(); pIterator++)
		{
			cout << **pIterator << endl;
		}

		cout << endl << endl;
	}
}



///////////////
// Aufgabe 2 //
///////////////



void vAufgabe_2()
{
	// Variable zur Anzahl der zu erzeugenden PKWs und Fahrraeder
	unsigned int iNumberOfVehicles = 0;

	// Variable zur Simulationsdauer
	double dDuration = 0.0;

	// Variable zum Simulationsintervall
	double dInterval = 0.0;

	// Variablen zur Eingabe und Verarbeitung der Tankmenge
	string sAmount = " ";
	double dAmount = 0.0;

	// Variable zum Tankzeitpunkt
	double dRefuelingTime = 0.0;

	// Variable zum Pruefen, ob bereits getankt wurde
	bool bRefilled = false;

	// Variable zur Anzahl an PKWs
	unsigned int iNumberOfCars = 0;

	// Variable zur Anzahl an Fahrraedern
	unsigned int iNumberOfBicycles = 0;


	// Weg mit allen Fahrzeugen
	unique_ptr<Weg> pWeg = make_unique<Weg>("Weg", numeric_limits<double>::infinity(), Tempolimit::Autobahn, false);



	// Benutzereingabe

	cout << "Geben Sie die Anzahl der zu erzeugenden PKWs und Fahrraeder ein: ";
	cin >> iNumberOfVehicles;
	cout << endl;

	cout << "Geben Sie die Simulationsdauer in Stunden ein: ";
	cin >> dDuration;
	cout << endl;

	cout << "Geben Sie das Simulationsintervall in Stunden ein: ";
	cin >> dInterval;
	cout << endl;

	cout << "Geben Sie die Tankmenge an (Volltanken mit FULL): ";
	cin >> sAmount;
	cout << endl;

	cout << "Geben Sie den Tankzeitpunkt nach Stunden ein: ";
	cin >> dRefuelingTime;
	cout << endl;

	cout << endl;


	// Initialisierung der Datenbank

	for (unsigned int iIterator = 0; iIterator < iNumberOfVehicles; iIterator++)
	{
		// Datenbank abwechselnd mit PKWs und Fahrraedern fuellen
		if (iIterator % 2 == 0)
		{
			auto newVehicle_ptr = make_unique<PKW>("PKW " + to_string(iNumberOfCars + 1), 50 + (10 * iNumberOfCars), 6 + (0.5 * iNumberOfCars), 30 + (5 * iNumberOfCars));

			pWeg->vAnnahme(move(newVehicle_ptr));

			pWeg->vSimulieren();

			iNumberOfCars = iNumberOfCars + 1;
		}

		else
		{
			auto newVehicle_ptr = make_unique<Fahrrad>("Fahrrad " + to_string(iNumberOfBicycles + 1), 20 + (2 * iNumberOfBicycles));

			pWeg->vAnnahme(move(newVehicle_ptr));

			pWeg->vSimulieren();

			iNumberOfBicycles = iNumberOfBicycles + 1;
		}
	}


	// Datenbank zu Beginn ausgeben

	cout << "Fahrzeuge vor der Simulation" << endl << endl;

	Fahrzeug::vKopf();

	for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = pWeg->getFahrzeuge().begin(); pIterator != pWeg->getFahrzeuge().end(); pIterator++)
	{
		cout << **pIterator << endl;
	}

	cout << endl << endl;


	// Fahrzeuge simulieren

	while (!bGleichheit(dGlobaleZeit, dDuration) && dGlobaleZeit < dDuration)
	{
		// Zeit inkrementieren

		dGlobaleZeit = dGlobaleZeit + (dInterval);

		// Simulation ausfuehren

		pWeg->vSimulieren();

		// Nach dRefuelingTime Stunden tanken

		if (sAmount == "FULL")
		{
			dAmount = numeric_limits<double>::infinity();
		}

		else
		{
			dAmount = stod(sAmount);
		}

		// Falls Tankzeitpunkt Vielfaches des Simulationsintrvalls ist

		if (bGleichheit(dGlobaleZeit, dRefuelingTime))
		{
			cout << "Betanken der Fahrzeug nach der " << dGlobaleZeit << ". Stunde:" << endl << endl;

			for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = pWeg->getFahrzeuge().begin(); pIterator != pWeg->getFahrzeuge().end(); pIterator++)
			{
				double dFilled = (*pIterator)->dTanken(dAmount);

				if (dFilled > 0)
				{
					cout << "Fahrzeug " << (*pIterator)->getID() << " wurde mit " << dFilled << " Liter betankt" << endl;;
				}

				if (dFilled < 0)
				{
					cout << "Fahrzeug " << (*pIterator)->getID() << " wurde mit " << -dFilled << " Liter enttankt" << endl;;
				}
			}

			cout << endl;

			bRefilled = true;
		}

		// Falls Tankzeitpunkt kein Vielfaches des Simulationsintrvalls ist

		if (dGlobaleZeit > dRefuelingTime && !bRefilled)
		{
			cout << "Betanken der Fahrzeug nach der " << dGlobaleZeit << ". Stunde, auf Grund des Simulationsintervalls:" << endl << endl;

			for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = pWeg->getFahrzeuge().begin(); pIterator != pWeg->getFahrzeuge().end(); pIterator++)
			{
				double dFilled = (*pIterator)->dTanken(dAmount);

				if (dFilled > 0)
				{
					cout << "Fahrzeug " << (*pIterator)->getID() << " wurde mit " << dFilled << " Liter betankt" << endl;;
				}

				if (dFilled < 0)
				{
					cout << "Fahrzeug " << (*pIterator)->getID() << " wurde mit " << -dFilled << " Liter enttankt" << endl;;
				}
			}

			cout << endl;

			bRefilled = true;
		}

		// Daten ausgeben

		if (dGlobaleZeit < 2)
		{
			cout << "Fahrzeuge nach der " << dGlobaleZeit * 60 << ". Minute:" << endl << endl;
		}

		else
		{
			cout << "Fahrzeuge nach " << dGlobaleZeit << " Stunden:" << endl << endl;
		}

		Fahrzeug::vKopf();

		for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = pWeg->getFahrzeuge().begin(); pIterator != pWeg->getFahrzeuge().end(); pIterator++)
		{
			cout << **pIterator << endl;
		}

		cout << endl << endl;
	}
}



///////////////
// Aufgabe 3 //
///////////////



void vAufgabe_3()
{
	// Variable zur Definition der auszufuehrenden Operation
	unsigned int iAbfrage = 0;

	// Weg mit allen Fahrzeugen
	unique_ptr<Weg> pWeg = make_unique<Weg>("Weg", numeric_limits<double>::infinity(), Tempolimit::Autobahn, false);


	while (iAbfrage != 9)
	{
		// Benutzereingabe zur Operationsauswahl

		cout << "Operationen" << endl;
		cout << "------------------------" << endl;
		cout << "1: Fahrzeug hinzufuegen" << endl;
		cout << "2: Fahreug kopieren" << endl;
		cout << "3: Fahrzeuge simulieren" << endl;
		cout << "4: Fahrzeuge betanken" << endl;
		cout << "5: Fahrzeuge vergleichen" << endl;
		cout << "6: Datenbank ausgeben" << endl;
		cout << "9: Beenden" << endl << endl;
		cout << "Bitte geben Sie die Nummer der gewuenschten Operation ein: ";
		cin >> iAbfrage;
		cout << endl << endl;



		// Fahrzeug hinzufuegen


		if (iAbfrage == 1)
		{
			// Variable zur Typfestlegung eines neuen Fahrzeugs
			unsigned int iVehicleType = 0;


			// Benutzereingabe zur Fahrzeugtyp Auswahl

			cout << "1: PKW" << endl;
			cout << "2: Fahrrad" << endl;
			cout << "Bitte geben Sie den gewuenschten Fahrzuegtyp ein: ";
			cin >> iVehicleType;
			cout << endl << endl;


			// PKW hinzufuegen

			if (iVehicleType == 1)
			{
				// Variablen zur Initalisierung eines neuen PKWs
				string initPKWName = " ";
				double initPKWSpeed = 0.0;
				double initPKWVerbrauch = 0.0;
				double initPKWVolumen = 0.0;

				// Benutzereingabe zur Initialisierung des PKWs

				cout << "Bitte geben Sie einen Namen ein: ";
				cin >> initPKWName;

				cout << "Bitte geben Sie die Maximalgeschwindigkeit ein: ";
				cin >> initPKWSpeed;

				cout << "Bitte geben Sie den Verbrauch ein: ";
				cin >> initPKWVerbrauch;

				cout << "Bitte geben Sie das Tankvolumen ein: ";
				cin >> initPKWVolumen;
				cout << endl;

				// Erstellen des neuen PKWs

				auto newPKW_ptr = make_unique<PKW>(initPKWName, initPKWSpeed, initPKWVerbrauch, initPKWVolumen);

				// PKW dem Weg hinzufuegen

				pWeg->vAnnahme(move(newPKW_ptr));

				pWeg->vSimulieren();

				cout << "Der Datenbank wurde ein neuer PKW hinzugefuegt:" << endl;

				cout << "Name: " << initPKWName << endl;
				cout << "Geschwindigkeit: " << initPKWSpeed << endl;
				cout << "Verbrauch: " << initPKWVerbrauch << endl;
				cout << "Tankvolumen: " << initPKWVolumen << endl;

				cout << endl << endl;
			}


			// Fahrrad hinzufuegen

			else if (iVehicleType == 2)
			{
				// Variablen zur Initalisierung eines neuen Fahrrads
				string initFahrradName = " ";
				double initFahrradSpeed = 0.0;

				// Benutzereingabe zur Initialisierung des Fahrrads

				cout << "Bitte geben Sie einen Namen ein: ";
				cin >> initFahrradName;

				cout << "Bitte geben Sie die Maximalgeschwindigkeit ein: ";
				cin >> initFahrradSpeed;
				cout << endl;

				// Erzeugen des Fahrrads

				auto newFahrrad_ptr = make_unique<Fahrrad>(initFahrradName, initFahrradSpeed);

				// Fahrrad dem Weg hinzufuegen

				pWeg->vAnnahme(move(newFahrrad_ptr));

				pWeg->vSimulieren();

				cout << "Der Datenbank wurde ein neues Fahrrad hinzugefuegt:" << endl;

				cout << "Name: " << initFahrradName << endl;
				cout << "Geschwindigkeit: " << initFahrradSpeed << endl;

				cout << endl << endl;
			}


			// Ungueltige Eingabe

			else
			{
				cout << "Ihre Eingabe war ungueltig" << endl << endl << endl;
			}

		}



		// Fahrzeug kopieren


		else if (iAbfrage == 2)
		{
			// Variablen zum Kopierverfahren
			unsigned int iCopyOperation = 0;

			// Benutzereingabe zum Kopierverfahren

			cout << "1: Vorhandenes Fahrzeug mit Kopie ersetzen" << endl;
			cout << "2: Neues Fahrzeug generieren" << endl;

			cout << "Bitte geben Sie die gewuenschte Operation ein: ";
			cin >> iCopyOperation;
			cout << endl;


			// Anderes Fahrzeug mit kopierten Daten ersetzen

			if (iCopyOperation == 1)
			{
				unsigned int iCopyID = 0;
				unsigned int iPasteID = 0;

				cout << "Bitte geben Sie die ID des zu kopierenden Fahrzeugs an: ";
				cin >> iCopyID;

				cout << "Bitte geben Sie die ID des zu ersetzenden Fahrzeugs an: ";
				cin >> iPasteID;
				cout << endl << endl;


				for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator copyIterator = pWeg->getFahrzeuge().begin(); copyIterator != pWeg->getFahrzeuge().end(); copyIterator++)
				{
					if ((*copyIterator)->getID() == iCopyID)
					{
						for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pasteIterator = pWeg->getFahrzeuge().begin(); pasteIterator != pWeg->getFahrzeuge().end(); pasteIterator++)
						{
							if ((*pasteIterator)->getID() == iPasteID)
							{
								**pasteIterator = **copyIterator;
							}
						}
					}
				}

			}


			// Neues Fahrzeug mit kopierten Daten erstellen

			if (iCopyOperation == 2)
			{
				unsigned int iCopyID = 0;

				cout << "Bitte geben Sie die ID des zu kopierenden Fahrzeugs an: ";
				cin >> iCopyID;
				cout << endl << endl;


				auto newPKW_ptr = make_unique<Fahrzeug>();

				for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = pWeg->getFahrzeuge().begin(); pIterator != pWeg->getFahrzeuge().end(); pIterator++)
				{
					if ((*pIterator)->getID() == iCopyID)
					{
						(*newPKW_ptr) = (**pIterator);
					}
				}

				pWeg->vAnnahme(move(newPKW_ptr));

				pWeg->vSimulieren();

			}
		}



		// Fahrzeuge simulieren


		else if (iAbfrage == 3)
		{
			// Simulationsintervall
			double dInterval = 0.0;

			// Benutzereingabe zum Simulationsintervall

			cout << "Bitte geben Sie das gewuenschte Simulationsintervall an: ";
			cin >> dInterval;
			cout << endl << endl;

			// Gloable Zeit um Intervall erhoehen

			dGlobaleZeit = dGlobaleZeit + dInterval;

			// Weg simulieren

			pWeg->vSimulieren();

			cout << "Die Fahrzeuge wurden fuer weitere " << dInterval << " Stunden simuliert" << endl;
			cout << "Die Globale Zeit betraegt " << dGlobaleZeit << " Stunden" << endl << endl;
		}



		// Fahrzeuge betanken


		else if (iAbfrage == 4)
		{
			// Variablen zur Eingabe und Verarbeitung der Tankmenge
			string sAmount = " ";
			double dAmount = 0.0;

			// Benutzereingabe zur Tankmenge

			cout << "Geben Sie die Tankmenge an (Volltanken mit FULL): ";
			cin >> sAmount;
			cout << endl;

			// Volltanken Eingabe umwandeln

			if (sAmount == "FULL")
			{
				dAmount = numeric_limits<double>::infinity();
			}

			// Eingegebene Menge in double umwandeln

			else
			{
				dAmount = stod(sAmount);
			}

			// Tankvorgang ausfuehern

			cout << "Betanken der Fahrzeug nach der " << dGlobaleZeit << ". Stunde:" << endl << endl;

			for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = pWeg->getFahrzeuge().begin(); pIterator != pWeg->getFahrzeuge().end(); pIterator++)
			{
				double dFilled = (*pIterator)->dTanken(dAmount);

				if (dFilled > 0)
				{
					cout << "Fahrzeug " << (*pIterator)->getID() << " wurde mit " << dFilled << " Liter betankt" << endl;;
				}

				if (dFilled < 0)
				{
					cout << "Fahrzeug " << (*pIterator)->getID() << " wurde mit " << -dFilled << " Liter enttankt" << endl;;
				}
			}

			cout << endl << endl;
		}



		// Fahrzeuge vergleichen


		else if (iAbfrage == 5)
		{
			// Variablen der zu vergleichenden Fahrzeuge
			unsigned int iCompareID1 = 0;
			unsigned int iCompareID2 = 0;


			// Benutzereingabe der zu vergleichenden Fahrzeuge

			cout << "Geben Sie die ID eines ersten Fahrzeug an: ";
			cin >> iCompareID1;

			cout << "Geben Sie die ID eines zweiten Fahrzeug an: ";
			cin >> iCompareID2;
			cout << endl;


			for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator1 = pWeg->getFahrzeuge().begin(); pIterator1 != pWeg->getFahrzeuge().end(); pIterator1++)
			{
				if ((*pIterator1)->getID() == iCompareID1)
				{
					for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator2 = pWeg->getFahrzeuge().begin(); pIterator2 != pWeg->getFahrzeuge().end(); pIterator2++)
					{
						if ((*pIterator2)->getID() == iCompareID2)
						{
							if (**pIterator1 < **pIterator2)
							{
								cout << "Das als zweites angegebene Fahrzeug ist weiter gefahren" << endl << endl << endl;
							}
							else if (**pIterator2 < **pIterator1)
							{
								cout << "Das als erstes angegebene Fahrzeug ist weiter gefahren" << endl << endl << endl;
							}
							else
							{
								cout << "Die angegebenen Fahrzeuge sind gleich weit gefahren" << endl << endl << endl;
							}
						}
					}
				}
			}
		}



		// Fahrzeuge ausgeben


		else if (iAbfrage == 6)
		{
			if (dGlobaleZeit < 2)
			{
				cout << "Fahrzeuge nach der " << dGlobaleZeit * 60 << ". Minute:" << endl << endl;
			}

			else
			{
				cout << "Fahrzeuge nach " << dGlobaleZeit << " Stunden:" << endl << endl;
			}

			Fahrzeug::vKopf();

			// Weg ausgeben

			for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = pWeg->getFahrzeuge().begin(); pIterator != pWeg->getFahrzeuge().end(); pIterator++)
			{
				cout << **pIterator << endl;
			}

			cout << endl << endl;

		}



		// Programm beenden


		else if (iAbfrage == 9)
		{
			cout << "Das Programm wird nun beendet" << endl << endl << endl;
		}



		// Ungueltige Eingabe


		else
		{
			cout << "Ihre Eingabe war ungueltig" << endl << endl << endl;
		}

	}
}



///////////////
// Aufgabe 4 //
///////////////



void vAufgabe_4()
{
	// Variable zur Definition der auszufuehrenden Operation
	unsigned int iAbfrage = 0;


	// ways-Vektor zum Speichern von Wegen
	vector<unique_ptr<Weg>> ways;


	while (iAbfrage != 9)
	{
		// Benutzereingabe zur Operationsauswahl

		cout << "Operationen" << endl;
		cout << "------------------------" << endl;
		cout << "1: Weg erstellen" << endl;
		cout << "2: Wege vergleichen" << endl;
		cout << "3: Wege ausgeben" << endl;
		cout << "4: Weg ausgeben" << endl;
		cout << "9: Beenden" << endl << endl;
		cout << "Bitte geben Sie die Nummer der gewuenschten Operation ein: ";
		cin >> iAbfrage;
		cout << endl << endl;



		// Weg erstellen


		if (iAbfrage == 1)
		{
			// Variablen zur Initalisierung eines neuen Weges
			string initWegName = " ";
			double initWegLaenge = 0.0;
			string userWegTempolimit = " ";
			Tempolimit initWegTempolimit;

			// Benutzereingabe zur Initialisierung des PKWs

			cout << "Bitte geben Sie einen Namen ein: ";
			cin >> initWegName;

			cout << "Bitte geben Sie eine Laenge ein: ";
			cin >> initWegLaenge;

			cout << "Bitte geben Sie den Strassentyp ein: ";
			cin >> userWegTempolimit;
			cout << endl;

			if (userWegTempolimit == "Innerorts")
			{
				initWegTempolimit = Tempolimit::Innerorts;
			}

			if (userWegTempolimit == "Landstrasse")
			{
				initWegTempolimit = Tempolimit::Landstrasse;
			}

			if (userWegTempolimit == "Autobahn")
			{
				initWegTempolimit = Tempolimit::Autobahn;
			}

			// Erstellen des neuen Wegs

			auto newWeg_ptr = make_unique<Weg>(initWegName, initWegLaenge, initWegTempolimit);

			// Weg dem ways-Vektor hinzufuegen

			ways.push_back(move(newWeg_ptr));

			cout << "Der Datenbank wurde ein neuer Weg hinzugefuegt:" << endl;

			cout << "Name: " << initWegName << endl;
			cout << "Laenge: " << initWegLaenge << endl;

			cout << endl << endl;
		}



		// Weg vergleichen


		else if (iAbfrage == 2)
		{
			// Variablen der zu vergleichenden Wege
			unsigned int iCompareID1 = 0;
			unsigned int iCompareID2 = 0;


			// Benutzereingabe der zu vergleichenden Wege

			cout << "Geben Sie die ID eines ersten Weg an: ";
			cin >> iCompareID1;

			cout << "Geben Sie die ID eines zweiten Weg an: ";
			cin >> iCompareID2;
			cout << endl;


			for (unsigned int iIterator1 = 0; iIterator1 < ways.size(); iIterator1++)
			{
				if (ways[iIterator1]->getID() == iCompareID1)
				{
					for (unsigned int iIterator2 = 0; iIterator2 < ways.size(); iIterator2++)
					{
						if (ways[iIterator2]->getID() == iCompareID2)
						{
							if (*ways[iIterator1] == *ways[iIterator2])
							{
								cout << "Die angegebenen Wege sind identisch" << endl << endl << endl;
							}

							else
							{
								cout << "Die angegebenen Wege sind verschieden" << endl << endl << endl;
							}
						}
					}
				}
			}
		}



		// Wege ausgeben


		else if (iAbfrage == 3)
		{
			if (dGlobaleZeit < 2)
			{
				cout << "Wege nach der " << dGlobaleZeit * 60 << ". Minute:" << endl << endl;
			}

			else
			{
				cout << "Wege nach " << dGlobaleZeit << " Stunden:" << endl << endl;
			}

			Weg::vKopf();

			for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
			{
				cout << *ways[iIterator] << endl;
			}

			cout << endl << endl;
		}



		// Weg ausgeben


		else if (iAbfrage == 4)
		{
			// Variable des auszugebenden Weges

			unsigned int iWayID = 0;


			// Benutzereingabe des auszugebenden Weges

			cout << "Geben Sie die ID des auszugebenden Weges an: ";
			cin >> iWayID;
			cout << endl;


			if (dGlobaleZeit < 2)
			{
				cout << "Weg " << iWayID << " nach der " << dGlobaleZeit * 60 << ". Minute:" << endl << endl;
			}

			else
			{
				cout << "Weg " << iWayID << " nach " << dGlobaleZeit << " Stunden:" << endl << endl;
			}


			for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
			{
				if (ways[iIterator]->getID() == iWayID)
				{
					Fahrzeug::vKopf();

					for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = ways[iIterator]->getFahrzeuge().begin(); pIterator != ways[iIterator]->getFahrzeuge().end(); pIterator++)
					{
						cout << **pIterator << endl;
					}

					cout << endl << endl;
				}
			}
		}



		// Programm beenden


		else if (iAbfrage == 9)
		{
			cout << "Das Programm wird nun beendet" << endl << endl << endl;
		}
	}
}



///////////////
// Aufgabe 5 //
///////////////



void vAufgabe_5()
{
	// Variable zur Definition der auszufuehrenden Operation
	unsigned int iAbfrage = 0;


	// ways-Vektor zum Speichern von Wegen
	vector<unique_ptr<Weg>> ways;


	while (iAbfrage != 9)
	{
		// Benutzereingabe zur Operationsauswahl

		cout << "Operationen" << endl;
		cout << "------------------------" << endl;
		cout << "1: Weg erstellen" << endl;
		cout << "2: Fahrendes Fahrzeug einem Weg hinzufuegen" << endl;
		cout << "3: Parkendes Fahrzeug einem Weg hinzufuegen" << endl;
		cout << "4: Wege simulieren" << endl;
		cout << "5: Wege vergleichen" << endl;
		cout << "6: Wege ausgeben" << endl;
		cout << "7: Weg ausgeben" << endl;
		cout << "9: Beenden" << endl << endl;
		cout << "Bitte geben Sie die Nummer der gewuenschten Operation ein: ";
		cin >> iAbfrage;
		cout << endl << endl;



		// Weg erstellen


		if (iAbfrage == 1)
		{
			// Variablen zur Initalisierung eines neuen Weges
			string initWegName = " ";
			double initWegLaenge = 0.0;
			string userWegTempolimit = " ";
			Tempolimit initWegTempolimit;

			// Benutzereingabe zur Initialisierung des PKWs

			cout << "Bitte geben Sie einen Namen ein: ";
			cin >> initWegName;

			cout << "Bitte geben Sie eine Laenge ein: ";
			cin >> initWegLaenge;

			cout << "Bitte geben Sie den Strassentyp ein: ";
			cin >> userWegTempolimit;
			cout << endl;

			if (userWegTempolimit == "Innerorts")
			{
				initWegTempolimit = Tempolimit::Innerorts;
			}

			if (userWegTempolimit == "Landstrasse")
			{
				initWegTempolimit = Tempolimit::Landstrasse;
			}

			if (userWegTempolimit == "Autobahn")
			{
				initWegTempolimit = Tempolimit::Autobahn;
			}

			// Erstellen des neuen Wegs

			auto newWeg_ptr = make_unique<Weg>(initWegName, initWegLaenge, initWegTempolimit);

			// Weg dem ways-Vektor hinzufuegen

			ways.push_back(move(newWeg_ptr));

			cout << "Der Datenbank wurde ein neuer Weg hinzugefuegt:" << endl;

			cout << "Name: " << initWegName << endl;
			cout << "Laenge: " << initWegLaenge << endl;

			cout << endl << endl;
		}



		// Fahrendes Fahrzeug einem Weg hinzufuegen


		else if (iAbfrage == 2)
		{
			// Variable des zu bearbeitendem Weges
			unsigned int iWayID = 0;


			// Benutzereingabe des zu bearbeitendem Weges

			cout << "Geben Sie die ID des zu bearbeitendem Weges an: ";
			cin >> iWayID;
			cout << endl;


			for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
			{
				if (ways[iIterator]->getID() == iWayID)
				{
					// Variable zur Typfestlegung eines neuen Fahrzeugs
					unsigned int iVehicleType = 0;


					// Benutzereingabe zur Fahrzeugtyp Auswahl

					cout << "1: PKW" << endl;
					cout << "2: Fahrrad" << endl;
					cout << "Bitte geben Sie den gewuenschten Fahrzuegtyp ein: ";
					cin >> iVehicleType;
					cout << endl << endl;


					// PKW hinzufuegen

					if (iVehicleType == 1)
					{
						// Variablen zur Initalisierung eines neuen PKWs
						string initPKWName = " ";
						double initPKWSpeed = 0.0;
						double initPKWVerbrauch = 0.0;
						double initPKWVolumen = 0.0;

						// Benutzereingabe zur Initialisierung des PKWs

						cout << "Bitte geben Sie einen Namen ein: ";
						cin >> initPKWName;

						cout << "Bitte geben Sie die Maximalgeschwindigkeit ein: ";
						cin >> initPKWSpeed;

						cout << "Bitte geben Sie den Verbrauch ein: ";
						cin >> initPKWVerbrauch;

						cout << "Bitte geben Sie das Tankvolumen ein: ";
						cin >> initPKWVolumen;
						cout << endl;

						// Erstellen des neuen PKWs

						auto newPKW_ptr = make_unique<PKW>(initPKWName, initPKWSpeed, initPKWVerbrauch, initPKWVolumen);

						// PKW hinzufuegen

						ways[iIterator]->vAnnahme(move(newPKW_ptr));

						ways[iIterator]->vSimulieren();

						cout << "Der Datenbank wurde ein neuer PKW hinzugefuegt:" << endl;

						cout << "Name: " << initPKWName << endl;
						cout << "Geschwindigkeit: " << initPKWSpeed << endl;
						cout << "Verbrauch: " << initPKWVerbrauch << endl;
						cout << "Tankvolumen: " << initPKWVolumen << endl;

						cout << endl << endl;
					}


					// Fahrrad hinzufuegen

					else if (iVehicleType == 2)
					{
						// Variablen zur Initalisierung eines neuen Fahrrads
						string initFahrradName = " ";
						double initFahrradSpeed = 0.0;

						// Benutzereingabe zur Initialisierung des Fahrrads

						cout << "Bitte geben Sie einen Namen ein: ";
						cin >> initFahrradName;

						cout << "Bitte geben Sie die Maximalgeschwindigkeit ein: ";
						cin >> initFahrradSpeed;
						cout << endl;

						// Erzeugen des Fahrrads

						auto newFahrrad_ptr = make_unique<Fahrrad>(initFahrradName, initFahrradSpeed);

						// Fahrrad hinzufuegen

						ways[iIterator]->vAnnahme(move(newFahrrad_ptr));

						ways[iIterator]->vSimulieren();

						cout << "Der Datenbank wurde ein neues Fahrrad hinzugefuegt:" << endl;

						cout << "Name: " << initFahrradName << endl;
						cout << "Geschwindigkeit: " << initFahrradSpeed << endl;

						cout << endl << endl;
					}


					// Ungueltige Eingabe

					else
					{
						cout << "Ihre Eingabe war ungueltig" << endl << endl << endl;
					}

				}
			}
		}



		// Parkendes Fahrzeug einem Weg hinzufuegen


		else if (iAbfrage == 3)
		{
			// Variable des zu bearbeitendem Weges
			unsigned int iWayID = 0;


			// Benutzereingabe des zu bearbeitendem Weges

			cout << "Geben Sie die ID des zu bearbeitendem Weges an: ";
			cin >> iWayID;
			cout << endl;


			for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
			{
				if (ways[iIterator]->getID() == iWayID)
				{
					// Variable zur Typfestlegung eines neuen Fahrzeugs
					unsigned int iVehicleType = 0;


					// Benutzereingabe zur Fahrzeugtyp Auswahl

					cout << "1: PKW" << endl;
					cout << "2: Fahrrad" << endl;
					cout << "Bitte geben Sie den gewuenschten Fahrzuegtyp ein: ";
					cin >> iVehicleType;
					cout << endl << endl;


					// PKW hinzufuegen

					if (iVehicleType == 1)
					{
						// Variablen zur Initalisierung eines neuen PKWs
						string initPKWName = " ";
						double initPKWSpeed = 0.0;
						double initPKWVerbrauch = 0.0;
						double initPKWVolumen = 0.0;

						// Benutzereingabe zur Initialisierung des PKWs

						cout << "Bitte geben Sie einen Namen ein: ";
						cin >> initPKWName;

						cout << "Bitte geben Sie die Maximalgeschwindigkeit ein: ";
						cin >> initPKWSpeed;

						cout << "Bitte geben Sie den Verbrauch ein: ";
						cin >> initPKWVerbrauch;

						cout << "Bitte geben Sie das Tankvolumen ein: ";
						cin >> initPKWVolumen;
						cout << endl;

						// Erstellen des neuen PKWs

						auto newPKW_ptr = make_unique<PKW>(initPKWName, initPKWSpeed, initPKWVerbrauch, initPKWVolumen);


						// Variable des Startzeitpunktes
						double dStartzeitpunkt = 0.0;


						// Benutzereingabe zum Starteitpunkt
						cout << "Bitte geben Sie den Startzeitpunkt ein: ";
						cin >> dStartzeitpunkt;
						cout << endl << endl;


						// PKW hinzufuegen

						ways[iIterator]->vAnnahme(move(newPKW_ptr), dStartzeitpunkt);

						ways[iIterator]->vSimulieren();

						cout << "Der Datenbank wurde ein neuer PKW hinzugefuegt:" << endl;

						cout << "Name: " << initPKWName << endl;
						cout << "Geschwindigkeit: " << initPKWSpeed << endl;
						cout << "Verbrauch: " << initPKWVerbrauch << endl;
						cout << "Tankvolumen: " << initPKWVolumen << endl;

						cout << endl << endl;
					}


					// Fahrrad hinzufuegen

					else if (iVehicleType == 2)
					{
						// Variablen zur Initalisierung eines neuen Fahrrads
						string initFahrradName = " ";
						double initFahrradSpeed = 0.0;

						// Benutzereingabe zur Initialisierung des Fahrrads

						cout << "Bitte geben Sie einen Namen ein: ";
						cin >> initFahrradName;

						cout << "Bitte geben Sie die Maximalgeschwindigkeit ein: ";
						cin >> initFahrradSpeed;
						cout << endl;

						// Erzeugen des Fahrrads

						auto newFahrrad_ptr = make_unique<Fahrrad>(initFahrradName, initFahrradSpeed);


						// Variable des Startzeitpunktes
						double dStartzeitpunkt = 0.0;


						// Benutzereingabe zum Starteitpunkt
						cout << "Bitte geben Sie den Startzeitpunkt ein: ";
						cin >> dStartzeitpunkt;
						cout << endl << endl;


						// Fahrrad hinzufuegen

						ways[iIterator]->vAnnahme(move(newFahrrad_ptr), dStartzeitpunkt);

						ways[iIterator]->vSimulieren();

						cout << "Der Datenbank wurde ein neues Fahrrad hinzugefuegt:" << endl;

						cout << "Name: " << initFahrradName << endl;
						cout << "Geschwindigkeit: " << initFahrradSpeed << endl;

						cout << endl << endl;
					}


					// Ungueltige Eingabe

					else
					{
						cout << "Ihre Eingabe war ungueltig" << endl << endl << endl;
					}

				}
			}
		}



		// Wege simulieren


		else if (iAbfrage == 4)
		{
			// Simulationsintervall
			double dInterval = 0.0;

			// Benutzereingabe zum Simulationsintervall

			cout << "Bitte geben Sie das gewuenschte Simulationsintervall an: ";
			cin >> dInterval;
			cout << endl << endl;

			// Gloable Zeit um Intervall erhoehen

			dGlobaleZeit = dGlobaleZeit + dInterval;

			// ways-Vektor simulieren

			for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
			{
				ways[iIterator]->vSimulieren();
			}

			cout << "Die Wege wurden fuer weitere " << dInterval << " Stunden simuliert" << endl;
			cout << "Die Globale Zeit betraegt " << dGlobaleZeit << " Stunden" << endl << endl;

		}



		// Wege vergleichen


		else if (iAbfrage == 5)
		{
			// Variablen der zu vergleichenden Wege
			unsigned int iCompareID1 = 0;
			unsigned int iCompareID2 = 0;


			// Benutzereingabe der zu vergleichenden Wege

			cout << "Geben Sie die ID eines ersten Weg an: ";
			cin >> iCompareID1;

			cout << "Geben Sie die ID eines zweiten Weg an: ";
			cin >> iCompareID2;
			cout << endl;


			for (unsigned int iIterator1 = 0; iIterator1 < ways.size(); iIterator1++)
			{
				if (ways[iIterator1]->getID() == iCompareID1)
				{
					for (unsigned int iIterator2 = 0; iIterator2 < ways.size(); iIterator2++)
					{
						if (ways[iIterator2]->getID() == iCompareID2)
						{
							if (*ways[iIterator1] == *ways[iIterator2])
							{
								cout << "Die angegebenen Wege sind identisch" << endl << endl << endl;
							}

							else
							{
								cout << "Die angegebenen Wege sind verschieden" << endl << endl << endl;
							}
						}
					}
				}
			}
		}



		// Wege ausgeben


		else if (iAbfrage == 6)
		{
			if (dGlobaleZeit < 2)
			{
				cout << "Wege nach der " << dGlobaleZeit * 60 << ". Minute:" << endl << endl;
			}

			else
			{
				cout << "Wege nach " << dGlobaleZeit << " Stunden:" << endl << endl;
			}

			Weg::vKopf();

			for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
			{
				cout << *ways[iIterator] << endl;
			}

			cout << endl << endl;
		}



		// Weg ausgeben


		else if (iAbfrage == 7)
		{
			// Variable des auszugebenden Weges

			unsigned int iWayID = 0;


			// Benutzereingabe des auszugebenden Weges

			cout << "Geben Sie die ID des auszugebenden Weges an: ";
			cin >> iWayID;
			cout << endl;


			if (dGlobaleZeit < 2)
			{
				cout << "Weg " << iWayID << " nach der " << dGlobaleZeit * 60 << ". Minute:" << endl << endl;
			}

			else
			{
				cout << "Weg " << iWayID << " nach " << dGlobaleZeit << " Stunden:" << endl << endl;
			}


			for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
			{
				if (ways[iIterator]->getID() == iWayID)
				{
					Fahrzeug::vKopf();

					for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = ways[iIterator]->getFahrzeuge().begin(); pIterator != ways[iIterator]->getFahrzeuge().end(); pIterator++)
					{
						cout << **pIterator << endl;
					}

					cout << endl << endl;
				}
			}
		}



		// Programm beenden


		else if (iAbfrage == 9)
		{
			cout << "Das Programm wird nun beendet" << endl << endl << endl;
		}
	}
}



///////////////
// Aufgabe 6 //
///////////////



void vAufgabe_6()
{
	unsigned int iAbfrage = 0;

	cout << "Menue:" << endl;
	cout << "----------------" << endl;
	cout << "1: Wege testen" << endl;
	cout << "2: Grafik testen" << endl;
	cout << "3. Umsortierung testen" << endl;
	cout << "4: Ueberholverbot testen" << endl;
	cout << endl;
	cout << "Bitte geben Sie die Nummer des gewuenschten Programms ein: ";
	cin >> iAbfrage;
	cout << endl;


	// Wege testen

	if (iAbfrage == 1)
	{
		// ways-Vektor zum Speichern von Wegen

		vector<unique_ptr<Weg>> ways;


		// Wege generieren

		auto A4_ptr = make_unique<Weg>("A4", 150.0, Tempolimit::Autobahn);
		auto B264_ptr = make_unique<Weg>("B264", 65.0, Tempolimit::Landstrasse);
		auto Templergraben_ptr = make_unique<Weg>("Templergraben", 0.85, Tempolimit::Innerorts);

		ways.push_back(move(A4_ptr));
		ways.push_back(move(B264_ptr));
		ways.push_back(move(Templergraben_ptr));

		cout << "Der Datenbank wurden neue Wege hinzugefuegt:" << endl << endl;

		Weg::vKopf();

		for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
		{
			cout << *ways[iIterator] << endl;
		}

		cout << endl << endl;


		// Fahrzeuge generieren

		auto Christian_ptr = make_unique<PKW>("Christian", 180.0, 7.0, 75.0);
		auto Sabine_ptr = make_unique<Fahrrad>("Sabine", 22.0);
		auto Lina_ptr = make_unique<PKW>("Lina", 120.0, 6.0, 65.0);


		// Variable des zu bearbeitendem Weges

		unsigned int iWayID = 0;


		// Benutzereingabe des zu bearbeitendem Weges

		cout << "Geben Sie die ID des zu bearbeitendem Weges an: ";
		cin >> iWayID;
		cout << endl;


		// Weg in der Liste suchen

		for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
		{
			if (ways[iIterator]->getID() == iWayID)
			{
				// Fahrzeuge dem Weg hinzufuegen

				ways[iIterator]->vAnnahme(move(Christian_ptr));
				ways[iIterator]->vAnnahme(move(Sabine_ptr));
				ways[iIterator]->vAnnahme(move(Lina_ptr), 0.5);


				// Fahrzeuge aktualisieren

				ways[iIterator]->vSimulieren();


				// Weg ausgeben

				cout << "Weg " << ways[iIterator]->getName() << " zu Beginn:" << endl << endl;

				Fahrzeug::vKopf();

				for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = ways[iIterator]->getFahrzeuge().begin(); pIterator != ways[iIterator]->getFahrzeuge().end(); pIterator++)
				{
					cout << **pIterator << endl;
				}

				cout << endl << endl;


				// Simulationvariablen
				double dDuration = 0.0;
				double dInterval = 0.0;

				// Benutzereingabe zur Simulation
				cout << "Bitte geben Sie die gewuenschte Simulationsdauer an: ";
				cin >> dDuration;
				cout << endl;

				cout << "Bitte geben Sie das gewuenschte Simulationsintervall an: ";
				cin >> dInterval;
				cout << endl << endl;

				double dEndzeit = dGlobaleZeit + dDuration;


				// Simulieren bis Simulationsdauer durchlaufen ist

				while (!bGleichheit(dGlobaleZeit, dEndzeit) && dGlobaleZeit < dEndzeit)
				{
					// Gloable Zeit um Intervall erhoehen

					dGlobaleZeit = dGlobaleZeit + dInterval;

					cout << "Simulaionsschritt auf " << dGlobaleZeit << " Stunden" << endl << endl;


					// ways-Vektor simulieren

					for (unsigned int iWayIterator = 0; iWayIterator < ways.size(); iWayIterator++)
					{
						ways[iWayIterator]->vSimulieren();
					}


					// Weg ausgeben

					cout << "Weg " << ways[iIterator]->getName() << " nach " << dGlobaleZeit << " Stunden" << endl << endl;

					Fahrzeug::vKopf();

					for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = ways[iIterator]->getFahrzeuge().begin(); pIterator != ways[iIterator]->getFahrzeuge().end(); pIterator++)
					{
						cout << **pIterator << endl;
					}

					cout << endl << endl;
				}
			}
		}
	}


	// Grafik testen

	else if (iAbfrage == 2)
	{
		// Simulationvariablen

		double dDuration = 0.0;
		double dInterval = 0.0;

		// Benutzereingabe zur Simulation

		cout << "Bitte geben Sie die gewuenschte Simulationsdauer an: ";
		cin >> dDuration;
		cout << endl;

		cout << "Bitte geben Sie das gewuenschte Simulationsintervall an: ";
		cin >> dInterval;
		cout << endl << endl;


		// Grafik initialisieren

		bInitialisiereGrafik(800, 500);


		// ways-Vektor zum Speichern von Wegen

		vector<unique_ptr<Weg>> ways;


		// Wege generieren

		auto B1p_ptr = make_unique<Weg>("B1p", 500.0, Tempolimit::Landstrasse);
		auto B1n_ptr = make_unique<Weg>("B1n", 500.0, Tempolimit::Landstrasse);


		// Wege hinzufuegen

		ways.push_back(move(B1p_ptr));
		ways.push_back(move(B1n_ptr));


		// Stra�e zeichnen

		int iKoordinaten[] = { 700, 250, 100, 250 };
		bZeichneStrasse(ways[0]->getName(), ways[1]->getName(), 500, 2, iKoordinaten);



		// Fahrzeuge generieren

		auto Christian_ptr = make_unique<PKW>("Christian", 120.0, 7.0, 75.0);
		auto Sabine_ptr = make_unique<Fahrrad>("Sabine", 22.0);
		auto Lina_ptr = make_unique<PKW>("Lina", 80.0, 6.0, 65.0);


		// Fahrzeuge der Stra�e hinzufuegen

		ways[0]->vAnnahme(move(Christian_ptr));
		ways[1]->vAnnahme(move(Sabine_ptr));
		ways[1]->vAnnahme(move(Lina_ptr), 3);


		// Fahrzeuge aktualisieren und zeichnen

		for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
		{
			ways[iIterator]->vSimulieren();
		}


		// Simulieren bis Simulationsdauer durchlaufen ist

		double dEndzeit = dGlobaleZeit + dDuration;


		while (!bGleichheit(dGlobaleZeit, dEndzeit) && dGlobaleZeit < dEndzeit)
		{
			//	Gloable Zeit um Intervall erhoehen

			dGlobaleZeit = dGlobaleZeit + dInterval;


			// GlobaleZeit im Fenster setzen

			vSetzeZeit(dGlobaleZeit);


			// ways-Vektor simulieren

			for (unsigned int iIterator = 0; iIterator < ways.size(); iIterator++)
			{
				ways[iIterator]->vSimulieren();
			}


			// Kurz warten

			vSleep(200);
		}

		vBeendeGrafik();
	}


	// Umsortierung testen

	else if (iAbfrage == 3)
	{
		// Simulationvariablen

		double dDuration = 12;
		double dInterval = 0.5;


		// ways-Vektor zum Speichern von Wegen

		vector<unique_ptr<Weg>> ways;


		// Wege generieren

		auto B1p_ptr = make_unique<Weg>("B1p", 400.0, Tempolimit::Landstrasse, false);


		// Wege hinzufuegen

		ways.push_back(move(B1p_ptr));



		// Fahrzeuge generieren

		auto Christian_ptr = make_unique<PKW>("Christian", 120.0, 7.0, 75.0);
		auto Sabine_ptr = make_unique<PKW>("Sabine", 50.0, 6.5, 70.0);
		auto Lina_ptr = make_unique<PKW>("Lina", 80.0, 6.0, 65.0);


		// Fahrzeuge der Stra�e hinzufuegen

		ways[0]->vAnnahme(move(Christian_ptr), 6);
		ways[0]->vAnnahme(move(Sabine_ptr));
		ways[0]->vAnnahme(move(Lina_ptr), 2);


		// Fahrzeuge aktualisieren und ausgeben

		for (unsigned int iWayIterator = 0; iWayIterator < ways.size(); iWayIterator++)
		{
			ways[iWayIterator]->vSimulieren();

			cout << "Weg " << ways[iWayIterator]->getName() << " zu Beginn:" << endl << endl;

			Fahrzeug::vKopf();

			for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = ways[iWayIterator]->getFahrzeuge().begin(); pIterator != ways[iWayIterator]->getFahrzeuge().end(); pIterator++)
			{
				cout << **pIterator << endl;
			}

			cout << endl << endl;
		}


		// Simulieren und Ausgeben bis Simulationsdauer durchlaufen ist

		double dEndzeit = dGlobaleZeit + dDuration;


		while (!bGleichheit(dGlobaleZeit, dEndzeit) && dGlobaleZeit < dEndzeit)
		{
			// Gloable Zeit um Intervall erhoehen

			dGlobaleZeit = dGlobaleZeit + dInterval;

			cout << "Simulaionsschritt auf " << dGlobaleZeit << " Stunden" << endl << endl;


			// ways-Vektor simulieren und ausgeben

			for (unsigned int iWayIterator = 0; iWayIterator < ways.size(); iWayIterator++)
			{
				ways[iWayIterator]->vSimulieren();

				cout << "Weg " << ways[iWayIterator]->getName() << " nach " << dGlobaleZeit << " Stunden" << endl << endl;

				Fahrzeug::vKopf();

				for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = ways[iWayIterator]->getFahrzeuge().begin(); pIterator != ways[iWayIterator]->getFahrzeuge().end(); pIterator++)
				{
					cout << **pIterator << endl;
				}

				cout << endl << endl;
			}
		}
	}


	// Ueberholverbot testen

	else if (iAbfrage == 4)
	{
		// Simulationvariablen

		double dDuration = 12;
		double dInterval = 0.5;


		// ways-Vektor zum Speichern von Wegen

		vector<unique_ptr<Weg>> ways;


		// Wege generieren

		auto B1p_ptr = make_unique<Weg>("B1p", 400.0, Tempolimit::Landstrasse, true);


		// Wege hinzufuegen

		ways.push_back(move(B1p_ptr));



		// Fahrzeuge generieren

		auto Christian_ptr = make_unique<PKW>("Christian", 120.0, 7.0, 75.0);
		auto Sabine_ptr = make_unique<PKW>("Sabine", 50.0, 6.0, 65.0);
		auto Julian_ptr = make_unique<PKW>("Julian", 70, 6.2, 10.0);
		auto Lina_ptr = make_unique<PKW>("Lina", 80.0, 6.5, 70.0);


		// Fahrzeuge der Stra�e hinzufuegen

		ways[0]->vAnnahme(move(Christian_ptr), 6);
		ways[0]->vAnnahme(move(Sabine_ptr));
		ways[0]->vAnnahme(move(Julian_ptr), 1);
		ways[0]->vAnnahme(move(Lina_ptr), 2);


		// Fahrzeuge aktualisieren und ausgeben

		for (unsigned int iWayIterator = 0; iWayIterator < ways.size(); iWayIterator++)
		{
			ways[iWayIterator]->vSimulieren();

			cout << "Weg " << ways[iWayIterator]->getName() << " zu Beginn:" << endl << endl;

			Fahrzeug::vKopf();

			for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = ways[iWayIterator]->getFahrzeuge().begin(); pIterator != ways[iWayIterator]->getFahrzeuge().end(); pIterator++)
			{
				cout << **pIterator << endl;
			}

			cout << endl << endl;
		}


		// Simulieren und Ausgeben bis Simulationsdauer durchlaufen ist

		double dEndzeit = dGlobaleZeit + dDuration;


		while (!bGleichheit(dGlobaleZeit, dEndzeit) && dGlobaleZeit < dEndzeit)
		{
			// Gloable Zeit um Intervall erhoehen

			dGlobaleZeit = dGlobaleZeit + dInterval;

			cout << "Simulaionsschritt auf " << dGlobaleZeit << " Stunden" << endl << endl;


			// ways-Vektor simulieren und ausgeben

			for (unsigned int iWayIterator = 0; iWayIterator < ways.size(); iWayIterator++)
			{
				ways[iWayIterator]->vSimulieren();

				cout << "Weg " << ways[iWayIterator]->getName() << " nach " << dGlobaleZeit << " Stunden" << endl << endl;

				Fahrzeug::vKopf();

				for (vertagt::VListe<unique_ptr<Fahrzeug>>::iterator pIterator = ways[iWayIterator]->getFahrzeuge().begin(); pIterator != ways[iWayIterator]->getFahrzeuge().end(); pIterator++)
				{
					cout << **pIterator << endl;
				}

				cout << endl << endl;
			}
		}
	}


	// Ungueltige Eingabe

	else
	{

	}
}



////////////////
// Aufgabe 6a //
////////////////



void vAufgabe_6a()
{
	// Liste fuer Zufallszahlen erzeuegen

	vertagt::VListe<unsigned int> Zufallszahlen;


	// 10 Zufallszahlen erzeugen und der Liste hinzufuegen

	for (unsigned int iIterator = 0; iIterator < 10; iIterator++)
	{
		// Zufallszahl erzeuegen

		static std::mt19937 device(0);
		std::uniform_int_distribution <unsigned int> dist(1, 10);
		unsigned int zuf = dist(device);

		// Zufallszahl hinzufuegen

		Zufallszahlen.push_back(zuf);

		// Liste aktualisieren

		Zufallszahlen.vAktualisieren();
	}


	// Komplette Liste ausgeben

	cout << "Es wurde eine Liste mit 10 Zufallszahlen erstellt: " << endl << endl;

	for (list<unsigned int>::iterator pIterator = Zufallszahlen.begin(); pIterator != Zufallszahlen.end(); pIterator++)
	{
		std::cout << *pIterator << " ";
	}

	cout << endl << endl << endl;


	// Alle Elemente > 5 entfernen

	for (list<unsigned int>::iterator pIterator = Zufallszahlen.begin(); pIterator != Zufallszahlen.end(); pIterator++)
	{
		if (*pIterator > 5)
		{
			Zufallszahlen.erase(pIterator);
		}
	}



	// Liste vor und nach dem Aktualisieren ausgeben

	cout << "Es wurden alle Elemente > 5 aus der Liste entfernt" << endl << endl;

	cout << "Liste vor dem Aktualisieren: " << endl << endl;

	for (list<unsigned int>::iterator pIterator = Zufallszahlen.begin(); pIterator != Zufallszahlen.end(); pIterator++)
	{
		std::cout << *pIterator << " ";
	}

	cout << endl << endl;


	// Liste aktualisieren

	Zufallszahlen.vAktualisieren();


	cout << "Liste nach dem Aktualisieren: " << endl << endl;

	for (list<unsigned int>::iterator pIterator = Zufallszahlen.begin(); pIterator != Zufallszahlen.end(); pIterator++)
	{
		std::cout << *pIterator << " ";
	}

	cout << endl << endl << endl;


	// Zwei beliebige Zahlen am Anfang und Ende der Liste einfuegen

	Zufallszahlen.push_front(1);
	Zufallszahlen.push_back(9);


	// Liste vor und nach dem Aktualisieren ausgeben

	cout << "Es wurden zwei beliebige Zahlen am Anfang und Ende der Liste eingefuegt" << endl << endl;

	cout << "Liste vor dem Aktualisieren: " << endl << endl;

	for (list<unsigned int>::iterator pIterator = Zufallszahlen.begin(); pIterator != Zufallszahlen.end(); pIterator++)
	{
		std::cout << *pIterator << " ";
	}

	cout << endl << endl;


	// Liste aktualisieren

	Zufallszahlen.vAktualisieren();


	cout << "Liste nach dem Aktualisieren: " << endl << endl;

	for (list<unsigned int>::iterator pIterator = Zufallszahlen.begin(); pIterator != Zufallszahlen.end(); pIterator++)
	{
		std::cout << *pIterator << " ";
	}

	cout << endl << endl << endl;
}



///////////////
// Aufgabe 7 //
///////////////



void vAufgabe_7()
{
	vector<shared_ptr<Kreuzung>> Kreuzungen;

	double dDuration = 0.0;
	double dInterval = 0.05;

	cout << "Bitte geben Sie die Simulationsdauer ein: ";
	cin >> dDuration;
	cout << endl;


	// Kreuzungen erstellen, verbinden und hinzufuegen

	shared_ptr<Kreuzung> Kr1_ptr = make_shared<Kreuzung>("Kr1");
	shared_ptr<Kreuzung> Kr2_ptr = make_shared<Kreuzung>("Kr2", 1000.0);
	shared_ptr<Kreuzung> Kr3_ptr = make_shared<Kreuzung>("Kr3");
	shared_ptr<Kreuzung> Kr4_ptr = make_shared<Kreuzung>("Kr4");

	Kr1_ptr->vVerbinde("W12", "W21", 40.0, Kr1_ptr, Kr2_ptr, Tempolimit::Innerorts, true);
	Kr2_ptr->vVerbinde("W23a", "W32a", 115.0, Kr2_ptr, Kr3_ptr, Tempolimit::Autobahn, false);
	Kr2_ptr->vVerbinde("W23b", "W32b", 40.0, Kr2_ptr, Kr3_ptr, Tempolimit::Innerorts, true);
	Kr2_ptr->vVerbinde("W24", "W42", 55.0, Kr2_ptr, Kr4_ptr, Tempolimit::Innerorts, true);
	Kr3_ptr->vVerbinde("W34", "W43", 85.0, Kr3_ptr, Kr4_ptr, Tempolimit::Autobahn, false);
	Kr4_ptr->vVerbinde("W44a", "W44b", 130.0, Kr4_ptr, Kr4_ptr, Tempolimit::Landstrasse, false);

	Kreuzungen.push_back(Kr1_ptr);
	Kreuzungen.push_back(Kr2_ptr);
	Kreuzungen.push_back(Kr3_ptr);
	Kreuzungen.push_back(Kr4_ptr);


	// Fahrzeuge erstellen und annehmen

	unique_ptr<PKW> PKW1_ptr = make_unique<PKW>("PKW1", 120.0, 6.0, 65.0);
	unique_ptr<PKW> PKW2_ptr = make_unique<PKW>("PKW2", 160.0, 7.0, 75.0);
	unique_ptr<PKW> PKW3_ptr = make_unique<PKW>("PKW3", 180.0, 7.5, 80.0);

	unique_ptr<Fahrrad> Fahrrad1_ptr = make_unique<Fahrrad>("Fahrrad1", 20.0);
	unique_ptr<Fahrrad> Fahrrad2_ptr = make_unique<Fahrrad>("Fahrrad2", 22.0);
	unique_ptr<Fahrrad> Fahrrad3_ptr = make_unique<Fahrrad>("Fahrrad3", 26.0);

	Kr1_ptr->vAnnahme(move(PKW1_ptr), 0.15);
	Kr1_ptr->vAnnahme(move(PKW2_ptr), 0.5);
	Kr1_ptr->vAnnahme(move(PKW3_ptr), 0.7);
	Kr1_ptr->vAnnahme(move(Fahrrad1_ptr), 0.25);
	Kr1_ptr->vAnnahme(move(Fahrrad2_ptr), 0.55);
	Kr1_ptr->vAnnahme(move(Fahrrad3_ptr), 0.95);


	// Grafik initialisieren und zeichnen

	bInitialisiereGrafik(1200, 800);

	int iKoordinaten1[] = { 680,  40, 680, 300 };
	int iKoordinaten2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
	int iKoordinaten3[] = { 680, 300, 680, 570 };
	int iKoordinaten4[] = { 680, 300, 320, 300 };
	int iKoordinaten5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	int iKoordinaten6[] = { 320, 300, 320, 150, 200,  60,  80,  90,  70, 250, 170, 300, 320, 300 };

	bZeichneStrasse("W12", "W21", 40, 2, iKoordinaten1);
	bZeichneStrasse("W23a", "W32a", 115, 6, iKoordinaten2);
	bZeichneStrasse("W23b", "W32b", 40, 2, iKoordinaten3);
	bZeichneStrasse("W24", "W42", 55, 2, iKoordinaten4);
	bZeichneStrasse("W34", "W43", 85, 5, iKoordinaten5);
	bZeichneStrasse("W44a", "W44b", 130, 7, iKoordinaten6);

	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);


	// Simulation

	for (unsigned int iIterator = 0; iIterator < Kreuzungen.size(); iIterator++)
	{
		Kreuzungen[iIterator]->vSimulieren();
	}

	while (!bGleichheit(dGlobaleZeit, dDuration) && dGlobaleZeit < dDuration)
	{
		dGlobaleZeit = dGlobaleZeit + dInterval;

		for (unsigned int iIterator = 0; iIterator < Kreuzungen.size(); iIterator++)
		{
			Kreuzungen[iIterator]->vSimulieren();
		}
	}

	vBeendeGrafik();

}



///////////////
// Aufgabe 8 //
///////////////



void vAufgabe_8()
{
	ifstream infile("VO.dat");
	infile.exceptions(ios_base::eofbit | ios_base::failbit | ios_base::badbit);

	unique_ptr<PKW> PKW_ptr = make_unique<PKW>();
	unique_ptr<Fahrrad> Fahrrad_ptr = make_unique<Fahrrad>();
	shared_ptr<Kreuzung> Kreuzung_ptr = make_shared<Kreuzung>();

	try
	{
		infile >> *PKW_ptr >> *Fahrrad_ptr >> *Kreuzung_ptr;
	}

	catch (runtime_error errorMessage)
	{
		cout << errorMessage.what() << endl << endl << endl;

		return;
	}

	Fahrzeug::vKopf();
	cout << *PKW_ptr << endl;
	cout << *Fahrrad_ptr << endl << endl;

	Kreuzung::vKopf();
	cout << *Kreuzung_ptr << endl << endl;


}



///////////////
// Aufgabe 9 //
///////////////



void vAufgabe_9()
{
	ifstream infile("Simu_korrigiert.dat");
	infile.exceptions(ios_base::eofbit | ios_base::failbit | ios_base::badbit);

	Simulation Simulationsdatei;

	cout << "Die Datei wird eingelesen..." << endl << endl;

	Simulationsdatei.vEinlesen(infile);


	double dDuration = 0.0;
	double dInterval = 0.25;

	cout << "Bitte geben Sie die Simulationsdauer ein: ";
	cin >> dDuration;
	cout << endl;

	Simulationsdatei.vSimulieren(dDuration, dInterval);
}



////////////////
// Aufgabe 9a //
////////////////



void vAufgabe_9a()
{
	double dDuration = 0.0;
	double dInterval = 0.05;

	cout << "Bitte geben Sie die Simulationsdauer ein: ";
	cin >> dDuration;
	cout << endl;


	ifstream infile("SimuDisplay.dat");
	infile.exceptions(ios_base::eofbit | ios_base::failbit | ios_base::badbit);

	Simulation Simulationsdatei;

	bInitialisiereGrafik(1400, 900);

	cout << "Die Datei wird eingelesen..." << endl << endl;

	Simulationsdatei.vEinlesen(infile, true);


	Simulationsdatei.vSimulieren(dDuration, dInterval);


	vBeendeGrafik();
}



