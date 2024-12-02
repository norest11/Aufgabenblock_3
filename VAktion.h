#pragma once

#include <list>


namespace vertagt
{
	////////////////////////
	// Oberklasse VAktion //
	////////////////////////

	template <class T>

	class VAktion
	{
	protected:

		// Zeiger auf Liste der Objekte
		std::list<T>& p_pListe;


	public:

		// Konstruktor
		VAktion(std::list<T>& ptListe) : p_pListe(ptListe) {}

		// Destruktor
		virtual ~VAktion() = default;

		// Ausfuehren der Aktion
		virtual void vAusfuehren() = 0;


	};

	//////////////
	// PushBack //
	//////////////

	template <class T>

	class VPushBack : public VAktion<T>
	{
	private:

		// Betrachtetes Objekt
		T p_objekt;


	public:

		// Konstruktor
		VPushBack(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj)) {}

		// Destruktor
		virtual ~VPushBack() = default;

		// Ausfuehren der Aktion
		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.push_back(std::move(p_objekt));
		}
	};


	///////////////
	// PushFront //
	///////////////

	template <class T>

	class VPushFront : public VAktion<T>
	{
	private:

		// Betrachtetes Objekt
		T p_objekt;


	public:

		// Konstruktor
		VPushFront(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj)) {}

		// Destruktor
		virtual ~VPushFront() = default;

		// Ausfuehren der Aktion
		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.push_front(std::move(p_objekt));
		}
	};


	///////////
	// Erase //
	///////////

	template <class T>

	class VErase : public VAktion<T>
	{
	public:

		// Durchlaufender Iterator
		using iterator = typename std::list<T>::iterator;


	private:

		// Speichern des Iterators bei erase
		iterator p_it;

	public:

		VErase(std::list<T>& liste, iterator& it) : VAktion<T>(liste), p_it(it) {}

		// Destruktor
		virtual ~VErase() = default;

		// Ausfuehen der Aktion
		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.erase(p_it);
		}

	};
}  // namespace vertagt
