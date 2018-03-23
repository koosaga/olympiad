#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

/*
 * InfInt - Arbitrary-Precision Integer Arithmetic Library
 * Copyright (C) 2013 Sercan Tutar
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *
 * USAGE:
 *   It is pretty straight forward to use the library. Just create an instance of
 *   InfInt class and start using it.
 *
 *   Useful methods:
 *      intSqrt:        integer square root operation
 *      digitAt:        returns digit at index
 *      numberOfDigits: returns number of digits
 *      size:           returns size in bytes
 *      toString:       converts it to a string
 *
 *   There are also conversion methods which allow conversion to primitive types:
 *   toInt, toLong, toLongLong, toUnsignedInt, toUnsignedLong, toUnsignedLongLong.
 *
 *   You may define INFINT_USE_EXCEPTIONS and library methods will start raising
 *   InfIntException in case of error instead of writing error messages using
 *   std::cerr.
 *
 *   See ReadMe.txt for more info.
 *
 *
 * No overflows, happy programmers!
 *
 */

#ifndef INFINT_H_
#define INFINT_H_

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

//#include <limits.h>
//#include <stdlib.h>

#define LONG_LONG_MIN LLONG_MIN
#define LONG_LONG_MAX LLONG_MAX
#define ULONG_LONG_MAX ULLONG_MAX

#ifdef INFINT_USE_EXCEPTIONS
#include <exception>
#endif

typedef int ELEM_TYPE;
typedef long long PRODUCT_TYPE;
static const ELEM_TYPE BASE = 1000000000;
static const ELEM_TYPE UPPER_BOUND = 999999999;
static const ELEM_TYPE DIGIT_COUNT = 9;
static const int powersOfTen[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

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

inline static div_t my_div(int num, int denom)
{
    div_t result;
    result.quot = num / denom;
    result.rem = num - denom * result.quot;
    return result;
}

inline static ldiv_t my_ldiv(long num, long denom)
{
    ldiv_t result;
    result.quot = num / denom;
    result.rem = num - denom * result.quot;
    return result;
}

inline static lldiv_t my_lldiv(long long num, long long denom)
{
    lldiv_t result;
    result.quot = num / denom;
    result.rem = num - denom * result.quot;
    return result;
}

class InfInt
{
    friend std::ostream& operator<<(std::ostream &s, const InfInt &n);
    friend std::istream& operator>>(std::istream &s, InfInt &val);

public:
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
    InfInt(const InfInt& l);

    /* assignment operators */
    const InfInt& operator=(const char* c);
    const InfInt& operator=(const std::string& s);
    const InfInt& operator=(int l);
    const InfInt& operator=(long l);
    const InfInt& operator=(long long l);
    const InfInt& operator=(unsigned int l);
    const InfInt& operator=(unsigned long l);
    const InfInt& operator=(unsigned long long l);
    const InfInt& operator=(const InfInt& l);

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

inline InfInt::InfInt() : pos(true)
{
    //PROFINY_SCOPE
    val.push_back((ELEM_TYPE) 0);
}

inline InfInt::InfInt(const char* c)
{
    //PROFINY_SCOPE
    fromString(c);
}

inline InfInt::InfInt(const std::string& s)
{
    //PROFINY_SCOPE
    fromString(s);
}

inline InfInt::InfInt(int l) : pos(l >= 0)
{
    //PROFINY_SCOPE
    bool subtractOne = false;
    if (l == INT_MIN)
    {
        subtractOne = true;
        ++l;
    }

    if (!pos)
    {
        l = -l;
    }
    do
    {
        div_t dt = my_div(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);

    if (subtractOne)
    {
        --*this;
    }
}

inline InfInt::InfInt(long l) : pos(l >= 0)
{
    //PROFINY_SCOPE
    bool subtractOne = false;
    if (l == LONG_MIN)
    {
        subtractOne = true;
        ++l;
    }

    if (!pos)
    {
        l = -l;
    }
    do
    {
        ldiv_t dt = my_ldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);

    if (subtractOne)
    {
        --*this;
    }
}

inline InfInt::InfInt(long long l) : pos(l >= 0)
{
    //PROFINY_SCOPE
    bool subtractOne = false;
    if (l == LONG_LONG_MIN)
    {
        subtractOne = true;
        ++l;
    }

    if (!pos)
    {
        l = -l;
    }
    do
    {
        lldiv_t dt = my_lldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);

    if (subtractOne)
    {
        --*this;
    }
}

inline InfInt::InfInt(unsigned int l) : pos(true)
{
    //PROFINY_SCOPE
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}

inline InfInt::InfInt(unsigned long l) : pos(true)
{
    //PROFINY_SCOPE
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}

inline InfInt::InfInt(unsigned long long l) : pos(true)
{
    //PROFINY_SCOPE
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}

inline InfInt::InfInt(const InfInt& l) : pos(l.pos), val(l.val)
{
    //PROFINY_SCOPE
}

inline const InfInt& InfInt::operator=(const char* c)
{
    //PROFINY_SCOPE
    fromString(c);
    return *this;
}

inline const InfInt& InfInt::operator=(const std::string& s)
{
    //PROFINY_SCOPE
    fromString(s);
    return *this;
}

inline const InfInt& InfInt::operator=(int l)
{
    //PROFINY_SCOPE
    bool subtractOne = false;
    if (l == INT_MIN)
    {
        subtractOne = true;
        ++l;
    }

    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
        div_t dt = my_div(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);

    return subtractOne ? --*this : *this;
}

inline const InfInt& InfInt::operator=(long l)
{
    //PROFINY_SCOPE
    bool subtractOne = false;
    if (l == LONG_MIN)
    {
        subtractOne = true;
        ++l;
    }

    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
        ldiv_t dt = my_ldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);

    return subtractOne ? --*this : *this;
}

inline const InfInt& InfInt::operator=(long long l)
{
    //PROFINY_SCOPE
    bool subtractOne = false;
    if (l == LONG_LONG_MIN)
    {
        subtractOne = true;
        ++l;
    }

    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
        lldiv_t dt = my_lldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);

    return subtractOne ? --*this : *this;
}

inline const InfInt& InfInt::operator=(unsigned int l)
{
    //PROFINY_SCOPE
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
    //PROFINY_SCOPE
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
    //PROFINY_SCOPE
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}

const InfInt& InfInt::operator=(const InfInt& l)
{
    //PROFINY_SCOPE
    pos = l.pos;
    val = l.val;
    return *this;
}

inline const InfInt& InfInt::operator++()
{
    //PROFINY_SCOPE
    val[0] += (pos ? 1 : -1);
    this->correct(false, true);
    return *this;
}

inline const InfInt& InfInt::operator--()
{
    //PROFINY_SCOPE
    val[0] -= (pos ? 1 : -1);
    this->correct(false, true);
    return *this;
}

inline InfInt InfInt::operator++(int)
{
    //PROFINY_SCOPE
    InfInt result = *this;
    val[0] += (pos ? 1 : -1);
    this->correct(false, true);
    return result;
}

inline InfInt InfInt::operator--(int)
{
    //PROFINY_SCOPE
    InfInt result = *this;
    val[0] -= (pos ? 1 : -1);
    this->correct(false, true);
    return result;
}

inline const InfInt& InfInt::operator+=(const InfInt& rhs)
{
    //PROFINY_SCOPE
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
    //PROFINY_SCOPE
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
    //PROFINY_SCOPE
    // TODO: optimize (do not use operator*)
    *this = *this * rhs;
    return *this;
}

inline const InfInt& InfInt::operator/=(const InfInt& rhs)
{
    //PROFINY_SCOPE
    if (rhs == 0)
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
    std::fill(val.begin(), val.end(), 0);
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        R.val.insert(R.val.begin(), N.val[i]);
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
    //PROFINY_SCOPE
    if (rhs == 0)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return *this;
#endif
    }
    InfInt D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    bool oldpos = pos;
    val.clear();
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        val.insert(val.begin(), N.val[i]);
        correct(true);
        *this -= D * dInR(*this, D);
    }
    correct();
    pos = (val.size() == 1 && val[0] == 0) ? true : oldpos;
    return *this;
}

inline const InfInt& InfInt::operator*=(ELEM_TYPE rhs)
{
    //PROFINY_SCOPE
    ELEM_TYPE factor = rhs < 0 ? -rhs : rhs;
    bool oldpos = pos;
    multiplyByDigit(factor, val);
    correct();
    pos = (val.size() == 1 && val[0] == 0) ? true : (oldpos == (rhs >= 0));
    return *this;
}

inline InfInt InfInt::operator-() const
{
    //PROFINY_SCOPE
    InfInt result = *this;
    result.pos = !pos;
    return result;
}

inline InfInt InfInt::operator+(const InfInt& rhs) const
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
    InfInt result;
    result.val.resize(val.size() + rhs.val.size(), 0);
    PRODUCT_TYPE carry = 0;
    size_t digit = 0;
    for (;; ++digit)
    {
        lldiv_t dt = my_lldiv(carry, BASE);
        carry = dt.quot;
        result.val[digit] = (ELEM_TYPE) dt.rem;

        bool found = false;
        for (size_t i = digit < rhs.val.size() ? 0 : digit - rhs.val.size() + 1; i < val.size() && i <= digit; ++i)
        {
            PRODUCT_TYPE pval = result.val[digit] + val[i] * (PRODUCT_TYPE) rhs.val[digit - i];
            if (pval >= BASE || pval <= -BASE)
            {
                lldiv_t dt = my_lldiv(pval, BASE);
                carry += dt.quot;
                pval = dt.rem;
            }
            result.val[digit] = (ELEM_TYPE) pval;
            found = true;
        }
        if (!found)
        {
            break;
        }
    }
    for (; carry > 0; ++digit)
    {
        lldiv_t dt = my_lldiv(carry, BASE);
        result.val[digit] = (ELEM_TYPE) dt.rem;
        carry = dt.quot;
    }
    result.correct();
    result.pos = (result.val.size() == 1 && result.val[0] == 0) ? true : (pos == rhs.pos);
    return result;
}

inline InfInt InfInt::operator/(const InfInt& rhs) const
{
    //PROFINY_SCOPE
    if (rhs == 0)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return 0;
#endif
    }
    InfInt Q, R, D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    Q.val.resize(N.val.size(), 0);
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        R.val.insert(R.val.begin(), N.val[i]);
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
{
    //PROFINY_SCOPE
    if (rhs == 0)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("division by zero");
#else
        std::cerr << "Division by zero!" << std::endl;
        return 0;
#endif
    }
    InfInt R, D = (rhs.pos ? rhs : -rhs), N = (pos ? *this : -*this);
    for (int i = (int) N.val.size() - 1; i >= 0; --i)
    {
        R.val.insert(R.val.begin(), N.val[i]);
        R.correct(true);
        R -= D * dInR(R, D);
    }
    R.correct();
    R.pos = (R.val.size() == 1 && R.val[0] == 0) ? true : pos;
    return R;
}

inline InfInt InfInt::operator*(ELEM_TYPE rhs) const
{
    //PROFINY_SCOPE
    InfInt result = *this;
    ELEM_TYPE factor = rhs < 0 ? -rhs : rhs;
    multiplyByDigit(factor, result.val);
    result.correct();
    result.pos = (result.val.size() == 1 && result.val[0] == 0) ? true : (pos == (rhs >= 0));
    return result;
}

inline bool InfInt::operator==(const InfInt& rhs) const
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
    InfInt hdn = 1;
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
{
    //PROFINY_SCOPE
    if (*this <= 0)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("intSqrt called for non-positive integer");
#else
        std::cerr << "intSqrt called for non-positive integer: " << *this << std::endl;
        return 0;
#endif
    }
    InfInt hi = *this / 2 + 1, lo = 0, mid, mid2;
    optimizeSqrtSearchBounds(lo, hi);
    do
    {
        mid = (hi + lo) / 2; // 8 factor
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
    } while (lo < hi - 1 && mid2 != *this);
    return lo;
}

inline char InfInt::digitAt(size_t i) const
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
    return (val.size() - 1) * DIGIT_COUNT +
        (val.back() > 99999999 ? 9 : (val.back() > 9999999 ? 8 : (val.back() > 999999 ? 7 : (val.back() > 99999 ? 6 :
        (val.back() > 9999 ? 5 : (val.back() > 999 ? 4 : (val.back() > 99 ? 3 : (val.back() > 9 ? 2 : 1))))))));
}

inline std::string InfInt::toString() const
{
    //PROFINY_SCOPE
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}

inline size_t InfInt::size() const
{
    //PROFINY_SCOPE
    return val.size() * sizeof(ELEM_TYPE) + sizeof(bool);
}

inline int InfInt::toInt() const
{
    //PROFINY_SCOPE
    if (*this > INT_MAX || *this < INT_MIN)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
        std::cerr << "Out of INT bounds: " << *this << std::endl;
#endif
    }
    int result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return pos ? result : -result;
}

inline long InfInt::toLong() const
{
    //PROFINY_SCOPE
    if (*this > LONG_MAX || *this < LONG_MIN)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
        std::cerr << "Out of LONG bounds: " << *this << std::endl;
#endif
    }
    long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return pos ? result : -result;
}

inline long long InfInt::toLongLong() const
{
    //PROFINY_SCOPE
    if (*this > LONG_LONG_MAX || *this < LONG_LONG_MIN)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
        std::cerr << "Out of LLONG bounds: " << *this << std::endl;
#endif
    }
    long long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return pos ? result : -result;
}

inline unsigned int InfInt::toUnsignedInt() const
{
    //PROFINY_SCOPE
    if (!pos || *this > UINT_MAX)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
        std::cerr << "Out of UINT bounds: " << *this << std::endl;
#endif
    }
    unsigned int result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return result;
}

inline unsigned long InfInt::toUnsignedLong() const
{
    //PROFINY_SCOPE
    if (!pos || *this > ULONG_MAX)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
        std::cerr << "Out of ULONG bounds: " << *this << std::endl;
#endif
    }
    unsigned long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return result;
}

inline unsigned long long InfInt::toUnsignedLongLong() const
{
    //PROFINY_SCOPE
    if (!pos || *this > ULONG_LONG_MAX)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("out of bounds");
#else
        std::cerr << "Out of ULLONG bounds: " << *this << std::endl;
#endif
    }
    unsigned long long result = 0;
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        result = result * BASE + val[i];
    }
    return result;
}

inline void InfInt::truncateToBase()
{
    //PROFINY_SCOPE
    for (size_t i = 0; i < val.size(); ++i) // truncate each
    {
        if (val[i] >= BASE || val[i] <= -BASE)
        {
            div_t dt = my_div(val[i], BASE);
            val[i] = dt.rem;
            if (i + 1 >= val.size())
            {
                val.push_back(dt.quot);
            }
            else
            {
                val[i + 1] += dt.quot;
            }
        }
    }
}

inline bool InfInt::equalizeSigns()
{
    //PROFINY_SCOPE
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
                for (; (size_t)(index) < val.size() && val[index] == 0; ++k, ++index); // count adjacent zeros on left
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
                for (; (size_t)(index) < val.size() && val[index] == 0; ++k, ++index); // count adjacent zeros on right
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
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
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
{
    //PROFINY_SCOPE
    pos = true;
    val.clear();
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
{
    //PROFINY_SCOPE
    ELEM_TYPE min = 0, max = UPPER_BOUND;
    while (max > min)
    {
        ELEM_TYPE avg = max + min;
        div_t dt = my_div(avg, 2);
        avg = dt.rem ? (dt.quot + 1) : dt.quot;
        InfInt prod = D * avg;
        if (R == prod)
        {
            return avg;
        }
        else if (R > prod)
        {
            min = avg;
        }
        else
        {
            max = avg - 1;
        }
    }
    return min;
}

inline void InfInt::multiplyByDigit(ELEM_TYPE factor, std::vector<ELEM_TYPE>& val)
{
    //PROFINY_SCOPE
    ELEM_TYPE carry = 0;
    for (size_t i = 0; i < val.size(); ++i)
    {
        PRODUCT_TYPE pval = val[i] * (PRODUCT_TYPE) factor + carry;
        if (pval >= BASE || pval <= -BASE)
        {
            lldiv_t dt = my_lldiv(pval, BASE);
            carry = (ELEM_TYPE) dt.quot;
            pval = dt.rem;
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
{
    //PROFINY_SCOPE
    std::string str;
    s >> str;
    n.fromString(str);
    return s;
}

inline std::ostream& operator<<(std::ostream &s, const InfInt &n)
{
    //PROFINY_SCOPE
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

#endif

InfInt dp[205];
int n;
string s;

InfInt fib[205];
string wd[205];

string tracel(int x, int l){
	if(fib[x] >= l) return wd[x].substr(fib[x].toInt() - l, l);
	if(fib[x-2] >= l) return tracel(x-2, l);
	return tracel(x-1, l-fib[x-2].toInt()) + wd[x-2];
}

string tracer(int x, int l){
	if(fib[x] >= l) return wd[x].substr(0, l);
	if(fib[x-1] >= l) return tracer(x-1, l);
	return wd[x-1] + tracer(x-2, l-fib[x-1].toInt());
}

int fail[100005];

InfInt overlap(int a, int b){
	int ls = s.size()-1;
	int rs = s.size()-1;
	ls = min(ls, fib[min(a, 26 + a%2)].toInt());
	rs = min(rs, fib[min(b, 26)].toInt());
	string str = tracel(min(a, 26+a%2), ls) + tracer(min(b, 26), rs);
	int p = 0;
	InfInt ret = 0;
	for(int i=0; i<str.size(); i++){
		while(p && str[i] != s[p]) p = fail[p];
		if(s[p] == str[i]) p++;
		if(p == s.size()){
			ret++;
			p = fail[p];
		}
	}
	return ret;
}

int main(){
	cin >> s >> n;
	n--;
	for(auto &i : s){
		if(i == 'b') i = '0';
		else i = '1';
	}

	fib[0] = fib[1] = 1;
	wd[0] = "0";
	wd[1] = "1";
	for(int i=2; i<=n+2;i++){
		fib[i] = fib[i-1] + fib[i-2];
		if(i <= 27) wd[i] = wd[i-1] + wd[i-2];
	}
	int p = 0;
	for(int i=1; i<s.size(); i++){
		while(p && s[p] != s[i]) p = fail[p];
		if(s[p] == s[i]) p++;
		fail[i+1] = p;
	}
	dp[0] = (s.size() == 1 && s[0] == '0');
	dp[1] = (s.size() == 1 && s[0] == '1');
	for(int i=2; i<=n; i++) dp[i] = dp[i-1] + dp[i-2] + overlap(i-1, i-2);
	cout << dp[n] << endl;
}



