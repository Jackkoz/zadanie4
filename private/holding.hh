#ifndef HOLDING_HH
#define HOLDING_HH

#include <stddef.h>
#include <iostream>

template <int A, int H, int E>
class Company
{
	static_assert(A >= 0, "Negative accountancy number.");
	static_assert(H >= 0, "Negative hunting shops number.");
	static_assert(E >= 0, "Negative exchange offices number.");

public:
	constexpr static unsigned int accNumber = A;
	constexpr static unsigned int hunNumber = H;
	constexpr static unsigned int excNumber = E;
};

typedef Company<1, 0, 0> Accountancy;
typedef Company<0, 1, 0> Hunting_shop;
typedef Company<0, 0, 1> Exchange_office;

/*
 * Typ reprezentujący firmę powstałą z połączenia firm C1 i C2. Struktura
 * powinna zawierać publiczną definicję type, opisującą nową firmę.
 */
template<class C1, class C2>
struct add_comp
{
public:
	//TODO zakres (MAX_UINT) ??
	typedef Company<C1::accNumber + C2::accNumber,
					C1::hunNumber + C2::hunNumber,
					C1::excNumber + C2::excNumber> type;
};

/*
 * Typ reprezentujący firmę C1 pomniejszoną o firmę C2. Struktura powinna
 * zawierać publiczną definicję type, opisującą nową firmę.
 */
template<class C1, class C2>
struct remove_comp
{
public:
	typedef Company<(C1::accNumber - C2::accNumber >= 1 ? C1::accNumber - C2::accNumber : 0),
					(C1::hunNumber - C2::hunNumber >= 1 ? C1::hunNumber - C2::hunNumber : 0),
					(C1::excNumber - C2::excNumber >= 1 ? C1::excNumber - C2::excNumber : 0)> type;

};

/*
 * Typ reprezentujący firmę powstałą z firmy C przez powiększenie n razy liczby
 * poszczególnych przedsiębiorstw. Struktura powinna zawierać publiczną
 * definicję type, opisującą nową firmę.
 */
template<class C, unsigned int n>
struct multiply_comp
{
public:
	//TODO zakres (MAX_UINT) ??
	typedef Company<C::accNumber * n, C::hunNumber * n, C::excNumber * n> type;

};

/*
 * Potrzebny jest również typ, który ułatwi podział firmy na n mniejszych. Ten
 * typ reprezentuje firmę powstałą z firmy C przez pomniejszenie n razy liczby
 * poszczególnych przedsiębiorstw. Struktura powinna zawierać publiczną
 * definicję type, opisującą nową firmę.
 * TODO Dzielimy całkowicie, czy sprawdzamy podzielność przez asercję?
 * - dzielenie jest zawsze całkowitoliczbowe, resztę odrzucamy;
 * - jeśli dzielnik ma wartość zero, to wynikiem dzielenia ma być zero;
 */
template<class C, unsigned int n>
struct split_comp
{
public:
	typedef Company<n >= 1 ? C::accNumber / n : 0, n >= 1 ? C::hunNumber / n : 0, n >= 1 ? C::excNumber / n : 0> type;

};

/*
 * Bardzo przydatną operacją jest zwiększenie o jeden liczby wszystkich
 * przedsiębiorstw wchodzących w skład firmy. Napisz typ opisujący efekt takiej
 * operacji.
 */
template<class C>
struct additive_expand_comp
{
public:
	typedef Company<C::accNumber + 1, C::hunNumber + 1, C::excNumber + 1> type;
};

/*
 * Czasami zdarza się, że musimy zamknąć po jednym przedsiębiorstwie każdego
 * typu, dlatego przygotuj strukturę, która będzie opisywać efekt takiej
 * operacji.
 */
template<class C>
struct additive_rollup_comp
{
	static_assert(C::accNumber > 0, "Negative accountancy number.");
	static_assert(C::hunNumber > 0, "Negative hunting shops number.");
	static_assert(C::excNumber > 0, "Negative exchange offices number.");

public:
	typedef Company<C::accNumber >= 1 ? C::accNumber - 1 : 0,
					C::hunNumber >= 1 ? C::hunNumber - 1 : 0,
					C::excNumber >= 1 ? C::excNumber - 1 : 0> type;
};


template<class C>
class Group
{
private:
	unsigned int size;

	unsigned int accValue;
	unsigned int hunValue;
	unsigned int excValue;

public:
	/*
	 * Wszystkie błędy, które niefortunnie mogłyby się znaleźć w przygotowanym
	 * przez Ciebie programie mogłyby kosztować nas bardzo dużo pieniędzy,
	 * dlatego w celu ułatwienia testowania klasa Group<Company> powinna
	 * zawierać publiczną definicję typu reprezentującego strukturę pojedynczej
	 * firmy o nazwie company_type oraz zmienną statyczną company typu
	 * company_type.
	 */
	typedef C company_type;
	static const company_type company;


	/*
	 * Konstruktor wywołany bez parametrów tworzy grupę składającą się tylko z
	 * jednej firmy.
	 */
	Group() :
		Group(1)
	{
	}

	/*
	 * Konstruktor wywołany z jednym parametrem tworzy grupę składającą się
	 * dokładnie z k firm o identycznej strukturze.
	 */
	Group(unsigned int k) :
		size(k),
		accValue(15),
		hunValue(150),
		excValue(50)
	{
	}

	/*
	 * Konstruktor tworzący nową grupę, która jest identyczna z tą podaną jako
	 * argument.
	 */
	Group(Group<C> const &group) :
		size(group.size),
		accValue(group.accValue),
		hunValue(group.hunValue),
		excValue(group.excValue)
	{
	}

	/*
	 * Zwraca liczbę firm wchodzących w skład grupy.
	 */
	unsigned int get_size() const
	{
		return size;
	}

	/*
	 * Metody pozwalające ustalać nową wartość biura rachunkowego,
	 * sklepu myśliwskiego oraz kantoru. Początkowa wartość pojedynczego kantoru
	 * to 50, sklepu myśliwskiego to 150, a biura rachunkowego to 15.
	 */
	void set_acc_val(unsigned int i)
	{
		accValue = i;
	}
	void set_hs_val(unsigned int i)
	{
		hunValue = i;
	}
	void set_exo_val(unsigned int i)
	{
		excValue = i;
	}

	/*
	 * Metody pozwalające odczytać wartość biura rachunkowego, sklepu
	 * myśliwskiego oraz kantoru.
	 */
	unsigned int get_acc_val() const
	{
		return accValue;
	}
	unsigned int get_hs_val() const
	{
		return hunValue;
	}
	unsigned int get_exo_val() const
	{
		return excValue;
	}

	/*
	 * Metoda zwracające wartość danej grupy, czyli sumę wartośći wszystkich
	 * przedsiębiorstw wchodzących w skład tej grupy.
	 */
	unsigned int get_value() const
	{
		return (accValue * company.accNumber
				+ hunValue * company.hunNumber
				+ excValue * company.excNumber) * size;
	}

	/*
	 * Oczekujemy również, że zaimplementujesz następujące operatory.
	 * Operatory dodawania i odejmowania na grupach firm: +, -, +=, -=. Dodawane i
	 * odejmowane mogą być tylko grupy równoważnych firm. W wyniku takich działań
	 * liczba firm w grupie wynikowej zachowuje się zgodnie z naturalnymi regułami tych
	 * działań. Wartość pojedynczego przedsiębiorstwa w nowej grupie liczymy jako
	 * średnią ważoną wartości firm z sumowanych grup, czyli przykładowo dla operacji
	 * g0 = g1 - g2 wartość kantoru wyznacza się formułą:
	 *
	 * wartość kantoru w g0 := (liczba kantorów w g1 * wartość kantoru w g1 -
	 *		liczba kantorów w g2 * wartość kantoru w g2) /
	 *		liczba kantorów w g0
	 */
	Group<C>& operator+= (const Group<C>& rhs)
	{
		unsigned int new_size = size + rhs.get_size();
		accValue = (size * accValue + rhs.get_size() * rhs.accValue) / new_size;
		hunValue = (size * hunValue + rhs.get_size() * rhs.hunValue) / new_size;
		excValue = (size * excValue + rhs.get_size() * rhs.excValue) / new_size;
		size = new_size;

		return *this;
	}

	Group<C>& operator-= (const Group<C>& rhs)
	{
		unsigned int new_size = max(size - rhs.get_size(), 0);
		if (new_size == 0) {
			accValue = 0;
			hunValue = 0;
			excValue = 0;
		} else {
			accValue = max((size * accValue - rhs.get_size() * rhs.accValue) / new_size, 0);
			hunValue = max((size * hunValue - rhs.get_size() * rhs.hunValue) / new_size, 0);
			excValue = max((size * excValue - rhs.get_size() * rhs.excValue) / new_size, 0);
		}
		size = new_size;

		return *this;
	}

	Group<C> operator+ (const Group<C>& rhs) const
	{
		Group<C> new_group(this);
		new_group += rhs;
		return new_group;
	}

	Group<C> operator- (const Group<C>& rhs) const
	{
		Group<C> new_group(this);
		new_group -= rhs;
		return new_group;
	}

	/*
	 * Operatory mnożenia i dzielenia grupy firm przez nieujemną liczbę całkowitą: *,
	 * /, *=, /=. Operacje te modyfikują liczność grupy zgodnie z ich naturalnymi
	 * regułami. Przy mnożeniu grupy przez n wartość pojedynczego przedsiębiorstwa
	 * ulega zmniejszeniu n razy, a przy dzieleniu grupy przez n zwiększa się n razy.
	 * Zawsze dzielimy całkowitoliczbowo i odrzucamy ewentualną resztę.
	 */
 	Group<C>& operator*= (const int n)
	{
		size *= n;

		if (n == 0)
		{
			accValue = 0;
			hunValue = 0;
			excValue = 0;
		} else
		{
	 		accValue /= n;
			hunValue /= n;
			excValue /= n;
		}

		return *this;
	}

	Group<C>& operator/= (const int n)
	{
		if (n == 0)
		{
			size = 0;
			accValue = 0;
			hunValue = 0;
			excValue = 0;
		} else
		{
	 		size /= n;
			accValue *= n;
			hunValue *= n;
			excValue *= n;
		}

		return *this;
	}

	Group<C> operator* (const int n)
	{
		Group<C> new_group(this);
		new_group *= n;
		return new_group;
	}

	Group<C> operator/ (const int n)
	{
		Group<C> new_group(this);
		new_group /= n;
		return new_group;
	}

	/*
	 * Operatory porównywania grup firm: ==, !=, <, >, <=, >=. Pamiętaj, że w
	 * krytycznych sytuacjach nie jest istotne, ile mamy biur rachunkowych. Liczy się
	 * tylko liczba kantorów (czyli kasa) oraz sklepów myśliwskich (broń). Posiadanie
	 * większej liczby przedsiębiorstw tych dwóch typów czyni nas silniejszymi od
	 * przeciwnika. Porządek na grupach nie jest liniowy.
	 */



};

/*
 * Operator << wypisujący na strumień opis grupy.
 */
template<class C>
std::ostream& operator<< (std::ostream& os, const Group<C>& rhs)
{
	os << "Company:" << std::endl;
	os << "Size: " << rhs.get_size() << " Value: " << rhs.get_value() << std::endl;
	os << "Accountancies: " << C::company.accNumber << " Value: " << rhs.get_acc_val() << std::endl;
	os << "Hunting shops: " << C::company.hunNumber << " Value: " << rhs.get_hs_val() << std::endl;
	os << "Exchange offices: " << C::excNumber << " Value: " << rhs.get_exo_val() << std::endl;

	return os;
}

#endif