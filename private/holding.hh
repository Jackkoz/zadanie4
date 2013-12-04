#ifndef HOLDING_HH
#define HOLDING_HH

#include <stddef.h>
#include <iostream>

constexpr inline unsigned int subtract(unsigned int A, unsigned int B)
{
    return (A > B) ? A - B : 0;
}

constexpr inline unsigned int divide(unsigned int A, unsigned int B)
{
    return (B > 0) ? A / B : 0;
}

template <unsigned int A, unsigned int H, unsigned int E>
class Company
{
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
    typedef Company<subtract(C1::accNumber, C2::accNumber),
                    subtract(C1::hunNumber, C2::hunNumber),
                    subtract(C1::excNumber, C2::excNumber)> type;

};

/*
 * Typ reprezentujący firmę powstałą z firmy C przez powiększenie n razy liczby
 * poszczególnych przedsiębiorstw. Struktura powinna zawierać publiczną
 * definicję type, opisującą nową firmę.
 */
template<class C, unsigned int n>
struct multiply_comp
{
    typedef Company<C::accNumber * n, C::hunNumber * n, C::excNumber * n> type;

};

/*
 * Potrzebny jest również typ, który ułatwi podział firmy na n mniejszych. Ten
 * typ reprezentuje firmę powstałą z firmy C przez pomniejszenie n razy liczby
 * poszczególnych przedsiębiorstw. Struktura powinna zawierać publiczną
 * definicję type, opisującą nową firmę.
 */
template<class C, unsigned int n>
struct split_comp
{
    typedef Company<divide(C::accNumber, n),
                    divide(C::hunNumber, n),
                    divide(C::excNumber, n)> type;

};

/*
 * Bardzo przydatną operacją jest zwiększenie o jeden liczby wszystkich
 * przedsiębiorstw wchodzących w skład firmy. Napisz typ opisujący efekt takiej
 * operacji.
 */
template<class C>
struct additive_expand_comp
{
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
    typedef Company<subtract(C::accNumber, 1),
                    subtract(C::hunNumber, 1),
                    subtract(C::excNumber, 1)> type;
};


template<class C>
class Group
{
private:
    static const unsigned int DEFAULT_ACC_VAL = 15;
    static const unsigned int DEFAULT_HUN_VAL = 150;
    static const unsigned int DEFAULT_EXC_VAL = 50;

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
     * Konstruktor wywołany z jednym parametrem tworzy grupę składającą się
     * dokładnie z k firm o identycznej strukturze.
     */
    Group(unsigned int k = 1) :
        size(k),
        accValue(DEFAULT_ACC_VAL),
        hunValue(DEFAULT_HUN_VAL),
        excValue(DEFAULT_EXC_VAL)
    {
    }

    /*
     * Konstruktor tworzący nową grupę, która jest identyczna z tą podaną jako
     * argument.
     */
    template<class Company>
    Group(Group<Company> const &group) :
        size(group.get_size()),
        accValue(group.get_acc_val()),
        hunValue(group.get_hs_val()),
        excValue(group.get_exo_val())
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
        return (accValue * company.accNumber +
                hunValue * company.hunNumber +
                excValue * company.excNumber) * size;
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
     *      liczba kantorów w g2 * wartość kantoru w g2) /
     *      liczba kantorów w g0
     */
    Group<C>& operator+= (const Group<C>& rhs)
    {
        unsigned int new_size = size + rhs.size;
        accValue = (size * accValue + rhs.size * rhs.accValue) / new_size;
        hunValue = (size * hunValue + rhs.size * rhs.hunValue) / new_size;
        excValue = (size * excValue + rhs.size * rhs.excValue) / new_size;
        size = new_size;

        return *this;
    }

    Group<C>& operator-= (const Group<C>& rhs)
    {
        unsigned int new_size = size > rhs.size ? size - rhs.size : 0;
        if (new_size == 0) {
            accValue = 0;
            hunValue = 0;
            excValue = 0;
        } else {
            unsigned int lhs_acc_worth = size * accValue;
            unsigned int rhs_acc_worth = rhs.size * rhs.accValue;
            accValue = lhs_acc_worth > rhs_acc_worth ?
                      (lhs_acc_worth - rhs_acc_worth) / new_size : 0;

            unsigned int lhs_hun_worth = size * hunValue;
            unsigned int rhs_hun_worth = rhs.size * rhs.hunValue;
            hunValue = lhs_hun_worth > rhs_hun_worth ?
                      (lhs_hun_worth - rhs_hun_worth) / new_size : 0;

            unsigned int lhs_exc_worth = size * excValue;
            unsigned int rhs_exc_worth = rhs.size * rhs.excValue;
            excValue = lhs_exc_worth > rhs_exc_worth ?
                      (lhs_exc_worth - rhs_exc_worth) / new_size : 0;
        }
        size = new_size;

        return *this;
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

    /*
     * Operatory porównywania grup firm: ==, !=, <, >, <=, >=. Pamiętaj, że w
     * krytycznych sytuacjach nie jest istotne, ile mamy biur rachunkowych. Liczy się
     * tylko liczba kantorów (czyli kasa) oraz sklepów myśliwskich (broń). Posiadanie
     * większej liczby przedsiębiorstw tych dwóch typów czyni nas silniejszymi od
     * przeciwnika. Porządek na grupach nie jest liniowy.
     */

};

//***Non-member function overloads***

template<class C>
Group<C> operator+ (const Group<C>& lhs, const Group<C>& rhs)
{
    Group<C> new_group(lhs);
    new_group += rhs;
    return new_group;
}

template<class C>
Group<C> operator- (const Group<C>& lhs, const Group<C>& rhs)
{
    Group<C> new_group(lhs);
    new_group -= rhs;
    return new_group;
}

template<class C>
Group<C> operator* (const Group<C>& lhs, const int n)
{
    Group<C> new_group(lhs);
    new_group *= n;
    return new_group;
}

template<class C>
Group<C> operator/ (const Group<C>& lhs, const int n)
{
    Group<C> new_group(lhs);
    new_group /= n;
    return new_group;
}

template<class C, class D>
bool operator==(const Group<C>& lhs, const Group<D>& rhs)
{
    return lhs.get_size() * C::hunNumber == rhs.get_size() * D::hunNumber &&
           lhs.get_size() * C::excNumber == rhs.get_size() * D::excNumber;
}

template<class C, class D>
bool operator!=(const Group<C>& lhs, const Group<D>& rhs)
{
    return !(lhs == rhs);
}

template<class C, class D>
bool operator<=(const Group<C>& lhs, const Group<D>& rhs)
{
    return lhs.get_size() * C::hunNumber <= rhs.get_size() * D::hunNumber &&
           lhs.get_size() * C::excNumber <= rhs.get_size() * D::excNumber;
}

template<class C, class D>
bool operator>=(const Group<C>& lhs, const Group<D>& rhs)
{
    return lhs.get_size() * C::hunNumber >= rhs.get_size() * D::hunNumber &&
           lhs.get_size() * C::excNumber >= rhs.get_size() * D::excNumber;
}

template<class C, class D>
bool operator<(const Group<C>& lhs, const Group<D>& rhs)
{
    return lhs <= rhs && lhs != rhs;
}

template<class C, class D>
bool operator>(const Group<C>& lhs, const Group<D>& rhs)
{
    return lhs >= rhs && lhs != rhs;
}

template<class C>
std::ostream& operator<< (std::ostream& os, const Group<C>& rhs)
{
    os << "Company:" << std::endl;
    os << "Size: " << rhs.get_size() << " Value: " << rhs.get_value() << std::endl;
    os << "Accountancies: " << C::accNumber << " Value: " << rhs.get_acc_val() << std::endl;
    os << "Hunting shops: " << C::hunNumber << " Value: " << rhs.get_hs_val() << std::endl;
    os << "Exchange offices: " << C::excNumber << " Value: " << rhs.get_exo_val() << std::endl;

    return os;
}

// Bardzo liczymy również na to, że napiszesz następujące funkcje globalne.

template<class C>
Group<typename additive_expand_comp<C>::type> const
additive_expand_group(Group<C> const &s1)
{
    return Group<typename additive_expand_comp<C>::type>(s1);
}
// Zwiększa o jeden liczbę przedsiębiorstw (wszystkich typów) wchodzących w skład
// każdej firmy należącej do grupy s1, nie zmieniając wartości pojedynczego
// przedsiębiorstwa.

template<class C>
Group<typename multiply_comp<C, 10>::type> const
multiplicative_expand_group(Group<C> const &s1)
{
    return Group<typename multiply_comp<C, 10>::type>(s1);
}
// Zwiększa dziesięciokrotnie liczbę przedsiębiorstw (wszystkich typów) wchodzących
// w skład każdej firmy należącej do grupy s1, nie zmieniając wartości pojedynczego
// przedsiębiorstwa.

template<class C>
Group<typename additive_rollup_comp<C>::type> const
additive_rollup_group(Group<C> const &s1)
{
    return Group<typename additive_rollup_comp<C>::type>(s1);
}
// Zmniejsza o jeden liczbę przedsiębiorstw (wszystkich typów) wchodzących w skład
// każdej firmy należącej do grupy s1, nie zmieniając wartości pojedynczego
// przedsiębiorstwa.

template<class C>
Group<typename split_comp<C, 10>::type> const
multiplicative_rollup_group(Group<C> const &s1)
{
    return Group<typename split_comp<C, 10>::type>(s1);
}
// Zmniejsza dziesięciokrotnie liczbę przedsiębiorstw (wszystkich typów)
// wchodzących w skład każdej firmy należącej do grupy s1, nie zmieniając wartości
// pojedynczego przedsiębiorstwa.

template<class C1, class C2, class C3>
bool
solve_auction(Group<C1> const &g1, Group<C2> const &g2, Group<C3> const &g3)
{
    return (g1 > g2 && g1 > g3) || (g2 > g1 && g2 > g3) || (g3 > g1 && g3 > g2);
}
// Funkcja, która pomoże nam określać, czy możliwe jest wyłonienie zwycięzcy
// przetargu (nie zawsze jest to możliwe) w przypadku, gdy startują w nim grupy g1,
// g2 oraz g3. Zwycięzcą zostaje grupa, która jest największa w sensie porządku
// zdefiniowanego na grupach.

#endif