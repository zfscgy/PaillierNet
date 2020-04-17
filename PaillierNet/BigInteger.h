#pragma once
#include "libs/include/mpir.h"
class BigInteger
{
public:
	mpz_t val;
	BigInteger();
	BigInteger(int i);
	~BigInteger();

};
class BigIntConverter
{
public:
	size_t fracPartLen;
	mpz_t largest;
	mpz_t totalRange;
	mpq_t tempQuotient0;
	mpq_t tempQuotient1;
	BigIntConverter();
	~BigIntConverter();
	BigIntConverter(BigInteger& modulus, size_t _fracPartLen);
	void GetBigInt(float val, BigInteger& bigInt);
	float GetFloat(BigInteger& bigInt);
};
class BigIntException
{
public:
	const char* msg;
	BigInteger* bigInt;
	BigIntException(const char* _msg, BigInteger *_bigInt);
	const char* what();
};