// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) { 
        throw std::exception("Size can not be less than 0");
    }
    else {
        BitLen = len;
        MemLen = len % (sizeof(TELEM)*8) ? len / (sizeof(TELEM) * 8) + 1 : len / (sizeof(TELEM) * 8);

        pMem = new TELEM[MemLen];

        for (int i = 0; i < MemLen; i++)
            pMem[i] = 0;
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
    if (n < 0 || n >= BitLen) {
        throw std::exception("index out of the bounds");

        return 0;
    }
    
    return (n) / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen) {
        throw std::exception("index out of the bounds");

        return TELEM();
    }

    return (1 << ((n) - GetMemIndex(n) * sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen) {
        throw std::exception("index out of the bounds");
    }
    else {
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
    }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen) {
        throw std::exception("index out of the bounds");
    }
    else {
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen) {
        throw std::exception("index out of the bounds");

        return 0;
    }

    if ((~GetMemMask(n)) == ((~GetMemMask(n)) | pMem[GetMemIndex(n)]))
        return 0;
    else
        return 1;

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (MemLen != bf.MemLen) {
        delete[] pMem;
        pMem = new TELEM[bf.MemLen];
    }
    
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen) {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i]) return 0;

        return 1;
    }

    return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !operator==(bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField result(0);

    if (BitLen > bf.BitLen) result = *this;
    else result = bf;

    for (int i = 0; i < std::min(MemLen, bf.MemLen); i++) 
        result.pMem[i] = pMem[i] | bf.pMem[i];
    
    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция  "и"
{
    TBitField result(std::max(BitLen, bf.BitLen));

    for (int i = 0; i < std::min(MemLen, bf.MemLen); i++) 
        result.pMem[i] = pMem[i] & bf.pMem[i];

    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);

    for (int i = 0; i < MemLen - 1; i++) 
        result.pMem[i] = (~pMem[i]);

    for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++) 
        if (!GetBit(i))
            result.SetBit(i);
    
    return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int bit;

    for (int i = 0; i < bf.BitLen; i++) {
        istr >> bit;
        bf.SetBit(bit);
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) 
        ostr << bf.GetBit(i);

    return ostr;
}
