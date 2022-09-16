// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 1) { 
        throw std::exception("Size can not be less than 1");
    }
    else {
        BitLen = len;
        MemLen = len / (sizeof(TELEM) * 8) + 1;

        pMem = new TELEM[MemLen];
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0) {
        throw std::exception("Index can not be less than 0");
    }
    else {
        return pMem[GetMemIndex(n)];
    }

    return TELEM();
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    int memIndex = GetMemIndex(n);
    TELEM mask = 1;

    mask << n - memIndex;
    
    pMem[memIndex] = pMem[memIndex] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return TBitField(0);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
    return TBitField(0);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
