#include <random>
#include "PaillierEncryptor.h"
namespace Random
{
	std::default_random_engine random_generator;
	std::uniform_int_distribution<short>distribution(0, 255);
	char NextRandomChar() 
	{
		return distribution(random_generator);
	}
}
namespace ran = Random;
/*
	Write random bytes to buffer with length len
*/
void WriteRandomBuffer(void* buf, int len)
{
	for (size_t i = 0; i < (size_t)len; i++)
	{
		((char*)buf)[i] = ran::NextRandomChar();
	}
}
PaillierEncryptor::PaillierEncryptor(): hasKey(false) 
{
	privKey = new paillier_prvkey_t();
	pubKey = new paillier_pubkey_t();
	mpz_init(plainText.m);
	mpz_init(cipherText.c);
}
/* 
	Since pubKey and privKey is initialized by functions in paillier.c
	I have to give it back to free
	Notice malloc and free must be in a pair
	Do not use free before malloc
	Do not use free with new
	Otherwise, the program will exit with error like Critical error detected c0000374
*/
PaillierEncryptor::~PaillierEncryptor()
{
	mpz_clear(pubKey->n);
	mpz_clear(pubKey->n_squared);
	mpz_clear(pubKey->n_plusone);
	delete pubKey;
	mpz_clear(privKey->lambda);
	mpz_clear(privKey->x);
	delete privKey;
}

bool PaillierEncryptor::KeyGen(size_t keyBytesLength)
{
	paillier_keygen(keyBytesLength * 8
		, &pubKey, &privKey, WriteRandomBuffer);
	mpz_init(modulus.val);
	mpz_set(modulus.val, pubKey->n);
	return true;
}

void PaillierEncryptor::Encrypt(BigInteger& encryptedInt, BigInteger& plainInt)
{
	mpz_set(plainText.m, plainInt.val);
	paillier_enc(&cipherText, pubKey, &plainText, WriteRandomBuffer);
	mpz_set(encryptedInt.val, cipherText.c);
}
void PaillierEncryptor::Decrypt(BigInteger& plainInt, BigInteger& encryptedInt)
{
	mpz_set(cipherText.c, encryptedInt.val);
	paillier_dec(&plainText, pubKey, privKey, &cipherText);
	mpz_set(plainInt.val, plainText.m);
}

BigInteger& PaillierEncryptor::N()
{
	return modulus;
	// TODO: 在此处插入 return 语句
}

PaillierEncryptorException::PaillierEncryptorException(const char* _msg, PaillierEncryptor* _encryptor)
{
	msg = _msg;
	encryptor = _encryptor;
}
