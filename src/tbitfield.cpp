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
        MemLen = len / (sizeof(TELEM) * 8) + 1;

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
    
    return (BitLen - n) / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen) {
        throw std::exception("index out of the bounds");

        return TELEM();
    }

    return (1 << ((BitLen - n) - GetMemIndex(n) * sizeof(TELEM)));
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
        for (int i = 0; i < BitLen; i++)
            if (GetBit(i) != bf.GetBit(i)) return 0;

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
    int resultBitLen = std::max(BitLen, bf.BitLen);
    int beforeLastEl = std::min(MemLen, bf.MemLen) - 1;
    int a, b;

    TBitField result(0);

    if (MemLen > bf.MemLen) result = *this;
    else result = bf;
    

    for (int i = 0; i < beforeLastEl; i++)
        result.pMem[resultBitLen - i - 1] = pMem[BitLen - i - 1] | bf.pMem[bf.BitLen - i - 1];

    for (int i = beforeLastEl * sizeof(TELEM); i < std::min(BitLen, bf.BitLen); i++) {
        a = GetBit(i); b = bf.GetBit(i);
        if (GetBit(i) || bf.GetBit(i))
            result.SetBit(i);
    }
    std::cout << result << std::endl;
    

    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField result(BitLen);

    for (int i = 0; i < MemLen; i++)
        result.pMem[i] = pMem[i] & bf.pMem[i];

    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);

    TELEM res;

    for (int i = 0; i < MemLen; i++) {
        res = pMem[i];
        res = (~pMem[i]);
        result.pMem[i] = res;
    }

    return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    TELEM bit;

    for (int i = 0; i < bf.BitLen; i++) {
        istr >> bit;
        bf.SetBit(bit);
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i);
    }

    return ostr;
}
