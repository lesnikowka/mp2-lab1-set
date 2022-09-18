// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (BitField.GetBit(Elem)) return 1;

    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;

    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower) {
        for (int i = 0; i < MaxPower; i++)
            if (BitField.GetBit(i) != s.BitField.GetBit(i))
                return 0;
    }
    else return 0;

    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !operator==(s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet result(std::max(MaxPower, s.MaxPower));
    result = BitField | s.BitField;

    return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::exception("Element not in universe");
        return 0;
    }

    TSet result(*this);
    if (Elem < MaxPower) result.InsElem(Elem);

    return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::exception("Element not in universe");
        return 0;
    }

    TSet result(*this);
    if (Elem < MaxPower) result.DelElem(Elem);

    return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet result(std::max(MaxPower, s.MaxPower));
    result = BitField & s.BitField;

    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet result(MaxPower);
    result.BitField = (~BitField);

    return result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{

    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++) 
        if (s.BitField.GetBit(i)) ostr << i;

    return ostr;
}
