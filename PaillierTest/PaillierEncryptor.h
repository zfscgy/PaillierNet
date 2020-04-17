#pragma once

#include "BigInteger.h"
// Since the header is written in C, must use extern, otherwise will produce link errors.
extern "C"
{
	#include "paillier/paillier.h"
}


class PaillierEncryptor 
{
private:
	bool hasKey;
	paillier_prvkey_t *privKey;
	paillier_pubkey_t *pubKey;
	paillier_plaintext_t plainText;
	paillier_ciphertext_t cipherText;
	BigInteger modulus;
public:
	PaillierEncryptor();
	~PaillierEncryptor();
	bool KeyGen(size_t keyBytesLength);
	void Encrypt(BigInteger& encryptedInt, BigInteger& plainInt);
	void Decrypt(BigInteger& plainInt, BigInteger& encryptedInt);
	BigInteger& N();
};
class PaillierEncryptorException :std::exception
{
public:
	const char* msg;
	PaillierEncryptor* encryptor;
	PaillierEncryptorException(const char* _msg, PaillierEncryptor* _encryptor);
	const char* what();
};