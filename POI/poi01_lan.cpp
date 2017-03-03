#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
/*
 * InfInt - Arbitrary-Precision Integer Arithmetic Library
 * Copyright (C) 2013 Sercan Tutar
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
 
#define INFINT_H_
 
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
 
#include <limits.h>
#include <stdlib.h>
 
#ifdef INFINT_USE_EXCEPTIONS
#include <exception>
#endif
 
#ifdef INFINT_USE_SHORT_BASE // uses 10^4 (short) as the base
typedef short ELEM_TYPE;
typedef int PRODUCT_TYPE;
static const ELEM_TYPE BASE = 10000;
static const ELEM_TYPE UPPER_BOUND = 9999;
static const ELEM_TYPE DIGIT_COUNT = 4;
static const int powersOfTen[] = { 1, 10, 100, 1000};
#else // uses 10^9 (int) as the base
typedef int ELEM_TYPE;
typedef long long PRODUCT_TYPE;
static const ELEM_TYPE BASE = 1000000000;
static const ELEM_TYPE UPPER_BOUND = 999999999;
static const ELEM_TYPE DIGIT_COUNT = 9;
static const int powersOfTen[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };
#endif
 
#ifdef INFINT_USE_EXCEPTIONS
class InfIntException: public std::exception
{
public:
    InfIntException(const std::string& txt) throw ();
    ~InfIntException() throw ();
    const char* what() const throw ();
private:
    std::string txt;
};
 
InfIntException::InfIntException(const std::string& txt) throw () :
std::exception(), txt(txt)
{
}
 
InfIntException::~InfIntException() throw ()
{
}
 
const char* InfIntException::what() const throw ()
{
    return txt.c_str();
}
#endif
 
class InfInt
{
    friend std::ostream& operator<<(std::ostream &s, const InfInt &n);
    friend std::istream& operator>>(std::istream &s, InfInt &val);
     
public:
    /* some constants */
    static const InfInt zero;
    static const InfInt one;
    static const InfInt two;
     
    /* constructors */
    InfInt();
    InfInt(const char* c);
    InfInt(const std::string& s);
    InfInt(int l);
    InfInt(long l);
    InfInt(long long l);
    InfInt(unsigned int l);
    InfInt(unsigned long l);
    InfInt(unsigned long long l);
     
    /* assignment operators */
    const InfInt& operator=(const char* c);
    const InfInt& operator=(const std::string& s);
    const InfInt& operator=(int l);
    const InfInt& operator=(long l);
    const InfInt& operator=(long long l);
    const InfInt& operator=(unsigned int l);
    const InfInt& operator=(unsigned long l);
    const InfInt& operator=(unsigned long long l);
     
    /* unary increment/decrement operators */
    const InfInt& operator++();
    const InfInt& operator--();
    InfInt operator++(int);
    InfInt operator--(int);
     
    /* operational assignments */
    const InfInt& operator+=(const InfInt& rhs);
    const InfInt& operator-=(const InfInt& rhs);
    const InfInt& operator*=(const InfInt& rhs);
    const InfInt& operator/=(const InfInt& rhs); // throw
    const InfInt& operator%=(const InfInt& rhs); // throw
    const InfInt& operator*=(ELEM_TYPE rhs);
     
    /* operations */
    InfInt operator-() const;
    InfInt operator+(const InfInt& rhs) const;
    InfInt operator-(const InfInt& rhs) const;
    InfInt operator*(const InfInt& rhs) const;
    InfInt operator/(const InfInt& rhs) const; // throw
    InfInt operator%(const InfInt& rhs) const; // throw
    InfInt operator*(ELEM_TYPE rhs) const;
     
    /* relational operations */
    bool operator==(const InfInt& rhs) const;
    bool operator!=(const InfInt& rhs) const;
    bool operator<(const InfInt& rhs) const;
    bool operator<=(const InfInt& rhs) const;
    bool operator>(const InfInt& rhs) const;
    bool operator>=(const InfInt& rhs) const;
     
    /* integer square root */
    InfInt intSqrt() const; // throw
     
    /* digit operations */
    char digitAt(size_t i) const; // throw
    size_t numberOfDigits() const;
     
    /* size in bytes */
    size_t size() const;
     
    /* string conversion */
    std::string toString() const;
     
    /* conversion to primitive types */
    int toInt() const; // throw
    long toLong() const; // throw
    long long toLongLong() const; // throw
    unsigned int toUnsignedInt() const; // throw
    unsigned long toUnsignedLong() const; // throw
    unsigned long long toUnsignedLongLong() const; // throw
     
private:
    static ELEM_TYPE dInR(const InfInt& R, const InfInt& D);
    static void multiplyByDigit(ELEM_TYPE factor, std::vector<ELEM_TYPE>& val);
     
    void correct(bool justCheckLeadingZeros = false, bool hasValidSign = false);
    void fromString(const std::string& s);
    void optimizeSqrtSearchBounds(InfInt& lo, InfInt& hi) const;
    void truncateToBase();
    bool equalizeSigns();
    void removeLeadingZeros();
     
    std::vector<ELEM_TYPE> val; // number with base FACTOR
    bool pos; // true if number is positive
};
 
const InfInt InfInt::zero = 0;
const InfInt InfInt::one = 1;
const InfInt InfInt::two = 2;
 
inline InfInt::InfInt() : pos(true)
{
    val.push_back((ELEM_TYPE) 0);
}
 
inline InfInt::InfInt(const char* c)
{
    fromString(c);
}
 
inline InfInt::InfInt(const std::string& s)
{
    fromString(s);
}
 
inline InfInt::InfInt(int l) : pos(l >= 0)
{
    if (!pos)
    {
        l = -l;
    }
    do
    {
        div_t dt = div(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
}
 
inline InfInt::InfInt(long l) : pos(l >= 0)
{
    if (!pos)
    {
        l = -l;
    }
    do
    {
        ldiv_t dt = ldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
}
 
inline InfInt::InfInt(long long l) : pos(l >= 0)
{
    if (!pos)
    {
        l = -l;
    }
    do
    {
#ifndef _WIN32
        lldiv_t dt = lldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
#else
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
#endif
    } while (l > 0);
}
 
inline InfInt::InfInt(unsigned int l) : pos(true)
{
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}
 
inline InfInt::InfInt(unsigned long l) : pos(true)
{
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}
 
inline InfInt::InfInt(unsigned long long l) : pos(true)
{
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}
 
inline const InfInt& InfInt::operator=(const char* c)
{
    fromString(c);
    return *this;
}
 
inline const InfInt& InfInt::operator=(const std::string& s)
{
    fromString(s);
    return *this;
}
 
inline const InfInt& InfInt::operator=(int l)
{
    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
        div_t dt = div(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
    return *this;
}
 
inline const InfInt& InfInt::operator=(long l)
{
    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
        ldiv_t dt = ldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
    return *this;
}
 
inline const InfInt& InfInt::operator=(long long l)
{
    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
#ifndef _WIN32
        lldiv_t dt = lldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
#else
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
#endif
    } while (l > 0);
    return *this;
}
 
inline const InfInt& InfInt::operator=(unsigned int l)
{
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}
 
inline const InfInt& InfInt::operator=(unsigned long l)
{
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}
 
inline const InfInt& InfInt::operator=(unsigned long long l)
{
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}
 
inline const InfInt& InfInt::operator++()
{
    val[0] += (pos ? 1 : -1);
    this->correct(false, true);
    return *this;
}
 
inline const InfInt& InfInt::operator--()
{
    val[0] -= (pos ? 1 : -1);
    this->correct(false, true);
    return *this;
}
 
inline InfInt InfInt::operator++(int)
{
    InfInt result = *this;
    val[0] += (pos ? 1 : -1);
    this->correct(false, true);
    return result;
}
 
inline InfInt InfInt::operator--(int)
{
    InfInt result = *this;
    val[0] -= (pos ? 1 : -1);
    this->correct(false, true);
    return result;
}
 
inline const InfInt& InfInt::operator+=(const InfInt& rhs)
{
    if (rhs.val.size() > val.size())
    {
        val.resize(rhs.val.size(), 0);
    }
    for (size_t i = 0; i < val.size(); ++i)
    {
        val[i] = (pos ? val[i] : -val[i]) + (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
    }
    correct();
    return *this;
}
 
inline const InfInt& InfInt::operator-=(const InfInt& rhs)
{
    if (rhs.val.size() > val.size())
    {
        val.resize(rhs.val.size(), 0);
    }
    for (size_t i = 0; i < val.size(); ++i)
    {
        val[i] = (pos ? val[i] : -val[i]) - (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
    }
    correct();
    return *this;
}
 
inline const InfInt& InfInt::operator*=(const InfInt& rhs)
{
    // TODO: optimize (do not use operator*)
    *this = *this * rhs;
    return *this;
}
 
inline const InfInt& InfInt::operator/=(const InfInt& rhs)
{
    if (rhs == zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return *this;
#endif
    }
    InfInt R, D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    bool oldpos = pos;
    val.clear();
    val.resize(N.val.size(), 0);
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        R.val.insert(R.val.begin(), (ELEM_TYPE) 0);
        R.val[0] = N.val[i];
        R.correct(true);
        ELEM_TYPE cnt = dInR(R, D);
        R -= D * cnt;
        val[i] += cnt;
    }
    correct();
    pos = (val.size() == 1 && val[0] == 0) ? true : (oldpos == rhs.pos);
    return *this;
}
 
inline const InfInt& InfInt::operator%=(const InfInt& rhs)
{
    if (rhs == zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return zero;
#endif
    }
    InfInt D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    bool oldpos = pos;
    val.clear();
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        val.insert(val.begin(), (ELEM_TYPE) 0);
        val[0] = N.val[i];
        correct(true);
        *this -= D * dInR(*this, D);
    }
    correct();
    pos = (val.size() == 1 && val[0] == 0) ? true : oldpos;
    return *this;
}
 
inline const InfInt& InfInt::operator*=(ELEM_TYPE rhs)
{
    ELEM_TYPE factor = rhs < 0 ? -rhs : rhs;
    bool oldpos = pos;
    multiplyByDigit(factor, val);
    correct();
    pos = (val.size() == 1 && val[0] == 0) ? true : (oldpos == (rhs >= 0));
    return *this;
}
 
inline InfInt InfInt::operator-() const
{//PROFILED_SCOPE
    InfInt result = *this;
    result.pos = !pos;
    return result;
}
 
inline InfInt InfInt::operator+(const InfInt& rhs) const
{//PROFILED_SCOPE
    InfInt result;
    result.val.resize(val.size() > rhs.val.size() ? val.size() : rhs.val.size(), 0);
    for (size_t i = 0; i < val.size() || i < rhs.val.size(); ++i)
    {
        result.val[i] = (i < val.size() ? (pos ? val[i] : -val[i]) : 0) + (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
    }
    result.correct();
    return result;
}
 
inline InfInt InfInt::operator-(const InfInt& rhs) const
{//PROFILED_SCOPE
    InfInt result;
    result.val.resize(val.size() > rhs.val.size() ? val.size() : rhs.val.size(), 0);
    for (size_t i = 0; i < val.size() || i < rhs.val.size(); ++i)
    {
        result.val[i] = (i < val.size() ? (pos ? val[i] : -val[i]) : 0) - (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
    }
    result.correct();
    return result;
}
 
inline InfInt InfInt::operator*(const InfInt& rhs) const
{//PROFILED_SCOPE
    InfInt result;
    result.val.resize(val.size() + rhs.val.size(), 0);
    PRODUCT_TYPE carry = 0;
    size_t digit = 0;
    for (;; ++digit)
    {//PROFILED_SCOPE
        //result.val[digit] = (ELEM_TYPE) (carry % BASE);
        //carry /= BASE;
         
        PRODUCT_TYPE oldcarry = carry;
        carry /= BASE;
        result.val[digit] = (ELEM_TYPE) (oldcarry - carry * BASE);
         
        bool found = false;
        for (size_t i = digit < rhs.val.size() ? 0 : digit - rhs.val.size() + 1; i < val.size() && i <= digit; ++i)
        {//PROFILED_SCOPE
            PRODUCT_TYPE pval = result.val[digit] + val[i] * (PRODUCT_TYPE) rhs.val[digit - i];
            if (pval >= BASE || pval <= -BASE)
            {//PROFILED_SCOPE
                //carry += pval / BASE;
                //pval %= BASE;
                 
                PRODUCT_TYPE quot = pval / BASE;
                carry += quot;
                pval -= quot * BASE;
            }
            result.val[digit] = (ELEM_TYPE) pval;
            found = true;
        }
        if (!found)
        {//PROFILED_SCOPE
            break;
        }
    }
    for (; carry > 0; ++digit)
    {//PROFILED_SCOPE
        result.val[digit] = (ELEM_TYPE) (carry % BASE);
        carry /= BASE;
    }
    result.correct();
    result.pos = (result.val.size() == 1 && result.val[0] == 0) ? true : (pos == rhs.pos);
    return result;
}
 
inline InfInt InfInt::operator/(const InfInt& rhs) const
{//PROFILED_SCOPE
    if (rhs == zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return zero;
#endif
    }
    InfInt Q, R, D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    Q.val.resize(N.val.size(), 0);
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {//PROFILED_SCOPE
        R.val.insert(R.val.begin(), (ELEM_TYPE) 0);
        R.val[0] = N.val[i];
        R.correct(true);
        ELEM_TYPE cnt = dInR(R, D);
        R -= D * cnt;
        Q.val[i] += cnt;
    }
    Q.correct();
    Q.pos = (Q.val.size() == 1 && Q.val[0] == 0) ? true : (pos == rhs.pos);
    return Q;
}
 
inline InfInt InfInt::operator%(const InfInt& rhs) const
{//PROFILED_SCOPE
    if (rhs == zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return zero;
#endif
    }
    InfInt R, D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        R.val.insert(R.val.begin(), (ELEM_TYPE) 0);
        R.val[0] = N.val[i];
        R.correct(true);
        R -= D * dInR(R, D);
    }
    R.correct();
    R.pos = (R.val.size() == 1 && R.val[0] == 0) ? true : pos;
    return R;
}
 
inline InfInt InfInt::operator*(ELEM_TYPE rhs) const
{//PROFILED_SCOPE
    InfInt result = *this;
    ELEM_TYPE factor = rhs < 0 ? -rhs : rhs;
    multiplyByDigit(factor, result.val);
    result.correct();
    result.pos = (result.val.size() == 1 && result.val[0] == 0) ? true : (pos == (rhs >= 0));
    return result;
}
 
inline bool InfInt::operator==(const InfInt& rhs) const
{//PROFILED_SCOPE
    if (pos != rhs.pos || val.size() != rhs.val.size())
    {
        return false;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] != rhs.val[i])
        {
            return false;
        }
    }
    return true;
}
 
inline bool InfInt::operator!=(const InfInt& rhs) const
{//PROFILED_SCOPE
    if (pos != rhs.pos || val.size() != rhs.val.size())
    {
        return true;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] != rhs.val[i])
        {
            return true;
        }
    }
    return false;
}
 
inline bool InfInt::operator<(const InfInt& rhs) const
{//PROFILED_SCOPE
    if (pos && !rhs.pos)
    {
        return false;
    }
    if (!pos && rhs.pos)
    {
        return true;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? false : true;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? true : false;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? true : false;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? false : true;
        }
    }
    return false;
}
 
inline bool InfInt::operator<=(const InfInt& rhs) const
{//PROFILED_SCOPE
    if (pos && !rhs.pos)
    {
        return false;
    }
    if (!pos && rhs.pos)
    {
        return true;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? false : true;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? true : false;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? true : false;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? false : true;
        }
    }
    return true;
}
 
inline bool InfInt::operator>(const InfInt& rhs) const
{//PROFILED_SCOPE
    if (pos && !rhs.pos)
    {
        return true;
    }
    if (!pos && rhs.pos)
    {
        return false;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? true : false;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? false : true;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? false : true;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? true : false;
        }
    }
    return false;
}
 
inline bool InfInt::operator>=(const InfInt& rhs) const
{//PROFILED_SCOPE
    if (pos && !rhs.pos)
    {
        return true;
    }
    if (!pos && rhs.pos)
    {
        return false;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? true : false;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? false : true;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? false : true;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? true : false;
        }
    }
    return true;
}
 
inline void InfInt::optimizeSqrtSearchBounds(InfInt& lo, InfInt& hi) const
{//PROFILED_SCOPE
    InfInt hdn = one;
    for (int i = (int) this->numberOfDigits() / 2; i >= 2; --i)
    {
        hdn *= 10;
    }
    if (lo < hdn)
    {
        lo = hdn;
    }
    hdn *= 100;
    if (hi > hdn)
    {
        hi = hdn;
    }
}
 
inline InfInt InfInt::intSqrt() const
{//PROFILED_SCOPE
    if (*this <= zero)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("intSqrt called for non-positive integer");
#else
        std::cerr << "intSqrt called for non-positive integer: " << *this << std::endl;
        return zero;
#endif
    }
    InfInt hi = *this / two + one, lo = zero, mid, mid2;
    optimizeSqrtSearchBounds(lo, hi);
    do
    {
        mid = (hi + lo) / two; // 8 factor
        mid2 = mid * mid; // 1 factor
        if (mid2 == *this)
        {
            lo = mid;
            break;
        }
        else if (mid2 < *this)
        {
            lo = mid;
        }
        else
        {
            hi = mid;
        }
    } while (lo < hi - one && mid2 != *this);
    return lo;
}
 
inline char InfInt::digitAt(size_t i) const
{//PROFILED_SCOPE
    if (numberOfDigits() <= i)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("invalid digit index");
#else
        std::cerr << "Invalid digit index: " << i << std::endl;
        return -1;
#endif
    }
    return (val[i / DIGIT_COUNT] / powersOfTen[i % DIGIT_COUNT]) % 10;
}
 
inline size_t InfInt::numberOfDigits() const
{//PROFILED_SCOPE
    return (val.size() - 1) * DIGIT_COUNT
#ifdef INFINT_USE_SHORT_BASE
    + (val.back() > 999 ? 4 : (val.back() > 99 ? 3 : (val.back() > 9 ? 2 : 1)));
#else
    + (val.back() > 99999999 ? 9 : (val.back() > 9999999 ? 8 : (val.back() > 999999 ? 7 : (val.back() > 99999 ? 6 :
                                                                                           (val.back() > 9999 ? 5 : (val.back() > 999 ? 4 : (val.back() > 99 ? 3 : (val.back() > 9 ? 2 : 1))))))));
#endif
}
 
inline std::string InfInt::toString() const
{//PROFILED_SCOPE
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}
 
inline size_t InfInt::size() const
{//PROFILED_SCOPE
    return val.size() * sizeof(ELEM_TYPE) + sizeof(bool);
}
 
inline int InfInt::toInt() const
{//PROFILED_SCOPE
    if (*this > INT_MAX || *this < INT_MIN)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of INT bounds: " << *this << std::endl;
#endif
    int result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return pos ? result : -result;
}
 
inline long InfInt::toLong() const
{//PROFILED_SCOPE
    if (*this > LONG_MAX || *this < LONG_MIN)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of LONG bounds: " << *this << std::endl;
#endif
    long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return pos ? result : -result;
}
 
inline long long InfInt::toLongLong() const
{//PROFILED_SCOPE
    long long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return pos ? result : -result;
}
 
inline unsigned int InfInt::toUnsignedInt() const
{//PROFILED_SCOPE
    if (!pos || *this > UINT_MAX)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of UINT bounds: " << *this << std::endl;
#endif
    unsigned int result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return result;
}
 
inline unsigned long InfInt::toUnsignedLong() const
{//PROFILED_SCOPE
    if (!pos || *this > ULONG_MAX)
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
    std::cerr << "Out of ULONG bounds: " << *this << std::endl;
#endif
    unsigned long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return result;
}
 
inline unsigned long long InfInt::toUnsignedLongLong() const
{//PROFILED_SCOPE
    unsigned long long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return result;
}
 
inline void InfInt::truncateToBase()
{//PROFILED_SCOPE
    for (size_t i = 0; i < val.size(); ++i) // truncate each
    {
        if (val[i] >= BASE || val[i] <= -BASE)
        {//PROFILED_SCOPE
            div_t dt = div(val[i], BASE);
            val[i] = dt.rem;
            if (i + 1 >= val.size())
            {//PROFILED_SCOPE
                val.push_back(dt.quot);
            }
            else
            {//PROFILED_SCOPE
                val[i + 1] += dt.quot;
            }
        }
    }
}
 
inline bool InfInt::equalizeSigns()
{//PROFILED_SCOPE
    bool isPositive = true;
    int i = (int) ((val.size())) - 1;
    for (; i >= 0; --i)
    {
        if (val[i] != 0)
        {
            isPositive = val[i--] > 0;
            break;
        }
    }
     
    if (isPositive)
    {
        for (; i >= 0; --i)
        {
            if (val[i] < 0)
            {
                int k = 0, index = i + 1;
                for (; (size_t)(index) < val.size() && val[index] == 0; ++k, ++index)
                ; // count adjacent zeros on left
                //if ((size_t)(index) < val.size() && val[index] > 0)
                { // number on the left is positive
                    val[index] -= 1;
                    val[i] += BASE;
                    for (; k > 0; --k)
                    {
                        val[i + k] = UPPER_BOUND;
                    }
                }
            }
        }
    }
    else
    {
        for (; i >= 0; --i)
        {
            if (val[i] > 0)
            {
                int k = 0, index = i + 1;
                for (; (size_t)(index) < val.size() && val[index] == 0; ++k, ++index)
                ; // count adjacent zeros on right
                //if ((size_t)(index) < val.size() && val[index] < 0)
                { // number on the left is negative
                    val[index] += 1;
                    val[i] -= BASE;
                    for (; k > 0; --k)
                    {
                        val[i + k] = -UPPER_BOUND;
                    }
                }
            }
        }
    }
     
    return isPositive;
}
 
inline void InfInt::removeLeadingZeros()
{//PROFILED_SCOPE
    for (int i = (int) (val.size()) - 1; i > 0; --i) // remove leading 0's
    {
        if (val[i] != 0)
        {
            return;
        }
        else
        {
            val.erase(val.begin() + i);
        }
    }
}
 
inline void InfInt::correct(bool justCheckLeadingZeros, bool hasValidSign)
{//PROFILED_SCOPE
    if (!justCheckLeadingZeros)
    {
        truncateToBase();
         
        if (equalizeSigns())
        {
            pos = ((val.size() == 1 && val[0] == 0) || !hasValidSign) ? true : pos;
        }
        else
        {
            pos = hasValidSign ? !pos : false;
            for (size_t i = 0; i < val.size(); ++i)
            {
                val[i] = abs(val[i]);
            }
        }
    }
     
    removeLeadingZeros();
}
 
inline void InfInt::fromString(const std::string& s)
{//PROFILED_SCOPE
    pos = true;
    val.clear();
    // TODO use resize
    val.reserve(s.size() / DIGIT_COUNT + 1);
    int i = (int) s.size() - DIGIT_COUNT;
    for (; i >= 0; i -= DIGIT_COUNT)
    {
        val.push_back(atoi(s.substr(i, DIGIT_COUNT).c_str()));
    }
    if (i > -DIGIT_COUNT)
    {
        std::string ss = s.substr(0, i + DIGIT_COUNT);
        if (ss.size() == 1 && ss[0] == '-')
        {
            pos = false;
        }
        else
        {
            val.push_back(atoi(ss.c_str()));
        }
    }
    if (val.back() < 0)
    {
        val.back() = -val.back();
        pos = false;
    }
    correct(true);
}
 
inline ELEM_TYPE InfInt::dInR(const InfInt& R, const InfInt& D)
{//PROFILED_SCOPE
    ELEM_TYPE min = 0, max = UPPER_BOUND;
    while (max - min > 0)
    {
        ELEM_TYPE avg = max + min;
        //div_t dt = div(avg, 2);
        //avg = dt.rem ? (dt.quot + 1) : dt.quot;
        ELEM_TYPE havg = avg / 2;
        avg = (avg - havg * 2) ? (havg + 1) : havg;
        InfInt prod = D * avg;
        if (R == prod)
        {//PROFILED_SCOPE
            return avg;
        }
        else if (R > prod)
        {//PROFILED_SCOPE
            min = avg;
        }
        else
        {//PROFILED_SCOPE
            max = avg - 1;
        }
    }
    return min;
}
 
inline void InfInt::multiplyByDigit(ELEM_TYPE factor, std::vector<ELEM_TYPE>& val)
{//PROFILED_SCOPE
    ELEM_TYPE carry = 0;
    for (size_t i = 0; i < val.size(); ++i)
    {
        PRODUCT_TYPE pval = val[i] * (PRODUCT_TYPE) factor + carry;
        if (pval >= BASE || pval <= -BASE)
        {
            //carry = (ELEM_TYPE) (pval / BASE);
            //pval %= BASE;
             
            carry = (ELEM_TYPE) (pval / BASE);
            pval -= carry * BASE;
        }
        else
        {
            carry = 0;
        }
        val[i] = (ELEM_TYPE) pval;
    }
    if (carry > 0)
    {
        val.push_back(carry);
    }
}
 
/**************************************************************/
/******************** NON-MEMBER OPERATORS ********************/
/**************************************************************/
 
inline std::istream& operator>>(std::istream &s, InfInt &n)
{//PROFILED_SCOPE
    std::string str;
    s >> str;
    n.fromString(str);
    return s;
}
 
inline std::ostream& operator<<(std::ostream &s, const InfInt &n)
{//PROFILED_SCOPE
    if (!n.pos)
    {
        s << '-';
    }
    bool first = true;
    for (int i = (int) n.val.size() - 1; i >= 0; --i)
    {
        if (first)
        {
            s << n.val[i];
            first = false;
        }
        else
        {
            s << std::setfill('0') << std::setw(DIGIT_COUNT) << n.val[i];
        }
    }
    return s;
}

int n, a[1005];

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i];
	}
	for(int i=n-1; i>0; i--){
		if(a[i]) a[i-1] ^= 1;
	}
	InfInt ans = 0, piv = 1;
	for(int i=0; i<n; i++){
		if(a[i]) ans += piv;
		piv *= 2;
	}
	cout << ans;
}
