#include "BigInteger.h"
BigInteger::BigInteger()
{
	mpz_init(val);
}
BigInteger::BigInteger(int i)
{
	mpz_init_set_si(val, i);
}
BigInteger::~BigInteger()
{
	mpz_clear(val);
}
BigIntConverter::BigIntConverter()
{
	mpz_init(largest);
	mpz_init(totalRange);
	mpq_init(tempQuotient0);
	mpq_init(tempQuotient1);
}
BigIntConverter::~BigIntConverter()
{
	mpz_clear(largest);
	mpz_clear(totalRange);
	mpq_clear(tempQuotient0);
	mpq_clear(tempQuotient1);
}
BigIntConverter::BigIntConverter(BigInteger& modulus, size_t _fracPartLen)
{
	fracPartLen = _fracPartLen;
	mpz_init(largest);
	mpz_init(totalRange);
	mpq_init(tempQuotient0);
	mpq_init(tempQuotient1);

	mpz_set(totalRange, modulus.val);
	// Since we have to represent negative numbers, one bit should be the sign
	mpz_cdiv_q_ui(largest, totalRange, (unsigned int)2);
}
void BigIntConverter::GetBigInt(float val, BigInteger& bigInt)
{
	mpq_set_d(tempQuotient0, (double)val);
	mpq_mul_2exp(tempQuotient1, tempQuotient0, (unsigned int)fracPartLen);
	mpz_set_q(bigInt.val, tempQuotient1);
	mpz_mod(bigInt.val, bigInt.val, totalRange);
	return;
}
float BigIntConverter::GetFloat(BigInteger& bigInt)
{
	// Notice mpz_cmp returns a int, not bool variables.
	if (mpz_cmp(bigInt.val, largest) > 0)
	{
		mpz_sub(bigInt.val, bigInt.val, largest);
		mpz_sub(bigInt.val, bigInt.val, largest);
	}
	mpq_set_z(tempQuotient0, bigInt.val);
	mpq_div_2exp(tempQuotient1, tempQuotient0, fracPartLen);
	return (float)mpq_get_d(tempQuotient1);
}

BigIntException::BigIntException(const char* _msg, BigInteger* _bigInt)
{
	msg = _msg;
	bigInt = _bigInt;
}

const char* BigIntException::what()
{
	return msg;
}
