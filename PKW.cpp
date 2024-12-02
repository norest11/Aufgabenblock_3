#include "PKW.h"

#include "Weg.h"

#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"

#include "SimuClient.h"


// Initialisierung der globalen Zeit

extern double dGlobaleZeit;


// Bekanntmachen der Abgleichsfunktion

extern bool bGleichheit(double initWert1, double initWert2);



// Default-Konstruktor

PKW::PKW(void)
	:Fahrzeug()
{
#if ANALYSE_PKW
	cout << "Konstruierter Default-PKW:" << endl;
	cout << "ID: " << p_iID << endl << endl;
#endif
}


// Namentlicher-Konstruktor

PKW::PKW(string initName)
	:Fahrzeug(initName)
{
#if ANALYSE_PKW
	cout << "Konstruierter Namentlicher-PKW:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl << endl;
#endif
}


// Geschwindigkeits-Konstruktor

PKW::PKW(string initName, double initSpeed)
	:Fahrzeug(initName, initSpeed)
{
#if ANALYSE_PKW
	cout << "Konstruierter Geschwindigkeits-PKW:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Geschwindigkeit: " << p_dMaxGeschwindigkeit << endl << endl;
#endif
}


// Verbrauch-Konstruktor

PKW::PKW(string initName, double initSpeed, double initVerbrauch)
	:Fahrzeug(initName, initSpeed)
	, p_dVerbrauch(initVerbrauch)
	, p_dTankvolumen(60)
	, p_dTankinhalt(p_dTankvolumen / 2.0)
{
#if ANALYSE_PKW
	cout << "Konstruierter Verbrauch-PKW:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Geschwindigkeit: " << p_dMaxGeschwindigkeit << endl;
	cout << "Verbrauch: " << p_dVerbrauch << endl << endl;
#endif
}


// Tank-Konstruktor

PKW::PKW(string initName, double initSpeed, double initVerbrauch, double initTankvolumen)
	:Fahrzeug(initName, initSpeed)
	, p_dVerbrauch(initVerbrauch)
	, p_dTankvolumen(initTankvolumen)
	, p_dTankinhalt(p_dTankvolumen / 2)
{
#if ANALYSE_PKW
	cout << "Konstruierter Tank-PKW:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Geschwindigkeit: " << p_dMaxGeschwindigkeit << endl;
	cout << "Verbrauch: " << p_dVerbrauch << endl;
	cout << "Tankvolumen: " << p_dTankvolumen << endl;
	cout << "Tankinhalt: " << p_dTankinhalt << endl << endl;
#endif
}


// Destruktor

PKW::~PKW(void)
{
#if ANALYSE_PKW
	cout << "Destruierter PKW:" << endl;
	cout << "ID: " << p_iID << endl;
	cout << "Name: " << p_sName << endl;
	cout << "Geschwindigkeit: " << p_dMaxGeschwindigkeit << endl;
	cout << "Verbrauch: " << p_dVerbrauch << endl;
	cout << "Tankvolumen: " << p_dTankvolumen << endl;
	cout << "Tankinhalt: " << p_dTankinhalt << endl << endl;
#endif
}


// Reguliert Geschwindigkeit

double PKW::dGeschwindigkeit() const
{
	if (p_pVerhalten == nullptr)
	{
		return p_dMaxGeschwindigkeit;
	}

	else
	{
		if (p_dMaxGeschwindigkeit > p_pVerhalten->getWeg().getTempolimit())
		{
			return p_pVerhalten->getWeg().getTempolimit();
		}

		else
		{
			return p_dMaxGeschwindigkeit;
		}
	}
}


// Betankt PKW

double PKW::dTanken(double dMenge)
{
	// Volltanken
	if (dMenge == numeric_limits<double>::infinity())
	{
		double dBenzinstand = p_dTankinhalt;

		p_dTankinhalt = p_dTankvolumen;

		return (p_dTankvolumen - dBenzinstand);
	}

	// Menge tanken
	else if (dMenge > 0.0)
	{
		if (dMenge > (p_dTankvolumen - p_dTankinhalt))
		{
			double dBenzinstand = p_dTankinhalt;

			p_dTankinhalt = p_dTankvolumen;

			return (p_dTankvolumen - dBenzinstand);
		}

		else
		{
			p_dTankinhalt = p_dTankinhalt + dMenge;

			return dMenge;
		}
	}

	// Negative Menge
	else
	{
		if (-dMenge > p_dTankinhalt)
		{
			double dBenzinstand = p_dTankinhalt;

			p_dTankinhalt = 0.0;

			return -dBenzinstand;
		}

		else
		{
			p_dTankinhalt = p_dTankinhalt + dMenge;

			return dMenge;
		}
	}
}


// Simuliert PKW

void PKW::vSimulieren()
{
	if (!bGleichheit(p_dZeit, dGlobaleZeit) && p_dZeit < dGlobaleZeit)
	{
		if (p_dTankinhalt > 0.0)
		{
			double dKilometerstand = p_dGesamtStrecke;

			Fahrzeug::vSimulieren();

			double dAktuellerVerbrauch = (p_dGesamtStrecke - dKilometerstand) * (p_dVerbrauch / 100.0);

			if (dAktuellerVerbrauch > p_dTankinhalt)
			{
				p_dTankinhalt = 0.0;
			}

			else
			{
				p_dTankinhalt = p_dTankinhalt - dAktuellerVerbrauch;
			}

			p_dGesamtVerbrauch = p_dGesamtStrecke * (p_dVerbrauch / 100.0);
		}

		else
		{
			p_dZeit = dGlobaleZeit;
		}
	}
}


// Gibt PKW-Daten aus

void PKW::vAusgeben(ostream& out) const
{
	Fahrzeug::vAusgeben(out);

	out << setw(18) << p_dGesamtVerbrauch << " "
		<< setw(14) << p_dTankinhalt << " ";
}


// Liest PKW-Daten ein
void PKW::vEinlesen(istream& in)
{
	Fahrzeug::vEinlesen(in);

	in >> p_dVerbrauch >> p_dTankvolumen;

	p_dTankinhalt = p_dTankvolumen / 2;
}


// Zeichenfunktion

void PKW::vZeichnen(const Weg& initWeg) const
{
	bZeichnePKW(p_sName, initWeg.getName(), getAbschnittStrecke() / (initWeg.getLaenge()), dGeschwindigkeit(), p_dTankinhalt);
}


// Weisst PKW Stammdaten eines anderen PKWs zu

PKW& PKW::operator = (const PKW& pkw)
{
	Fahrzeug::operator=(pkw);

	p_dVerbrauch = pkw.p_dVerbrauch;
	p_dGesamtVerbrauch = 0.0;

	p_dTankvolumen = pkw.p_dTankvolumen;
	p_dTankinhalt = p_dTankvolumen / 2.0;

	return *this;
}

