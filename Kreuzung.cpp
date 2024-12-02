#include "Kreuzung.h"

#include "Weg.h"
#include "Fahrzeug.h"

#include <memory>


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;


// Bekanntmachen der Abgleichsfunktion

extern bool bGleichheit(double initWert1, double initWert2);



// Default-Konstruktor

Kreuzung::Kreuzung(void)
	:Simulationsobjekt()
{
#if ANALYSE_KREUZUNG
	cout << "Konstruierte Default-Kreuzung:" << endl;
	cout << "ID: " << p_iID << endl << endl;
#endif
}


// Namentlicher-Konstruktor

Kreuzung::Kreuzung(string initName)
	:Simulationsobjekt(initName)
{
#if ANALYSE_KREUZUNG
	cout << "Konstruierte Namentliche-Kreuzung:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl << endl;
#endif
}


// Tankstellen-Konstruktor

Kreuzung::Kreuzung(string initName, double initTankstelle)
	:Simulationsobjekt(initName)
	,p_dTankstelle(initTankstelle)
{
#if ANALYSE_KREUZUNG
	cout << "Konstruierte Tankstellen-Kreuzung:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Tankstelle: " << p_dTankstelle << endl << endl;
#endif
}


// Destruktor

Kreuzung::~Kreuzung(void)
{
#if ANALYSE_KREUZUNG
	cout << "Destruierte Kreuzung:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Tankstelle: " << p_dTankstelle << endl << endl;
#endif
}


// Verbindet zwei Kreuzungen miteinander

void Kreuzung::vVerbinde(string initHinwegName, string initRueckwegName, double initLaenge, shared_ptr<Kreuzung> initStartKreuzung, shared_ptr<Kreuzung> initZielKreuzung, Tempolimit initTempolimit, bool initUeberholverbot)
{
	shared_ptr<Weg> Hinweg_ptr = make_shared<Weg>(initHinwegName, initLaenge, initTempolimit, initUeberholverbot, initZielKreuzung);
	shared_ptr<Weg> Rueckweg_ptr = make_shared<Weg>(initRueckwegName, initLaenge, initTempolimit, initUeberholverbot, initStartKreuzung);

	Hinweg_ptr->setRueckweg(Rueckweg_ptr);
	initStartKreuzung->p_pWege.push_back(Hinweg_ptr);

	Rueckweg_ptr->setRueckweg(Hinweg_ptr);
	initZielKreuzung->p_pWege.push_back(Rueckweg_ptr);
}


// Betankt vorbeifahrende Fahrzeuge

void Kreuzung::vTanken(Fahrzeug& initFahrzeug)
{
	if (!bGleichheit(p_dTankstelle, 0.0))
	{
		if (p_dTankstelle < 0.0)
		{
			p_dTankstelle = 0.0;
		}

		else
		{
			double dAmount = initFahrzeug.dTanken(numeric_limits<double>::infinity());

			p_dTankstelle = p_dTankstelle - dAmount;
		}
	}
}


// Nimmt Fahrzeuge auf Kreuzung auf

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> initFahrzeug, double initZeit)
{
	vTanken(*initFahrzeug);

	(*p_pWege.begin())->vAnnahme(move(initFahrzeug), initZeit);
}


// Waehlt zufaelligen Weg aus

Weg& Kreuzung::pZufaelligerWeg(Weg& initWeg)
{
	list<shared_ptr<Weg>>::iterator pRanWay = p_pWege.begin();

	if (p_pWege.size() < 2)
	{
		*pRanWay = initWeg.getRueckweg();
	}

	else
	{
		do
		{
			pRanWay = p_pWege.begin();

			static std::mt19937 device(0);
			std::uniform_int_distribution <unsigned int> dist(0, (unsigned int)p_pWege.size() - 1);
			unsigned int iRanNum = dist(device);

			for (unsigned int iIterator = 0; iIterator != iRanNum; iIterator++)
			{
				pRanWay++;
			}
		} while (*pRanWay == initWeg.getRueckweg());
	}

	return (**pRanWay);
}


// Gibt Inhalt der Tankstelle zurueck

double Kreuzung::getTankstelle() const
{
	return p_dTankstelle;
}


// Gibt Wege der Kreuzung aus

void Kreuzung::printWege() const
{
	for (list<shared_ptr<Weg>>::const_iterator pIterator = p_pWege.begin(); pIterator != p_pWege.end(); pIterator++)
	{
		cout << **pIterator << endl;
	}

	cout << endl;
}


// Simuliert Kreuzung

void Kreuzung::vSimulieren()
{
	for (list<shared_ptr<Weg>>::iterator pIterator = p_pWege.begin(); pIterator != p_pWege.end(); pIterator++)
	{
		(*pIterator)->vSimulieren();
	}

	Simulationsobjekt::vSimulieren();
}


// Gibt Kreuzungsdaten aus

void Kreuzung::vAusgeben(ostream& out) const
{
	Simulationsobjekt::vAusgeben(out);

	string sWays = "( ";

	for (list<shared_ptr<Weg>>::const_iterator pIterator = p_pWege.begin(); pIterator != p_pWege.end(); pIterator++)
	{
		sWays = sWays + ((*pIterator)->getName() + " ");
	}

	sWays = sWays + ")";


	out.precision(3);

	out << resetiosflags(ios::left) << setiosflags(ios::right) << setw(12) << p_dTankstelle << " "
		<< setw(46) << sWays << " ";
}


// Gibt Tabellenkopf aus

void Kreuzung::vKopf()
{
	cout << resetiosflags(ios::left) << setiosflags(ios::right) << setw(4) << "ID" << " "
		<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(18) << "Name" << " "
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(12) << "Tankstelle" << " "
		<< setw(46) << "Wege" << endl;

	cout << "------------------------------------------------------------------------------------" << endl;
}


// Liest Kreuzungsdaten ein

void Kreuzung::vEinlesen(istream& in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dTankstelle;
}

