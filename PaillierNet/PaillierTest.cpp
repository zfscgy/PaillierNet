// PaillierTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#pragma warning(disable:4146)
#include <iostream>
// #include "libs/include/mpir.h"
#include "PaillierEncryptor.h"
int main()
{
	// Test whether mpir library can be used
	mpz_t n;
	mpz_init(n);
	mpz_init_set_si(n, 100);
	unsigned long a = 100;
	mpz_add_ui(n, n, a);
	gmp_printf("%Zd\n", n);
	
	// Test BigInteger Converter
	BigInteger bigInt1, bigInt2;
	BigInteger modulus(100000);
	BigIntConverter biConverter(modulus, 8);
	biConverter.GetBigInt(3.1415926, bigInt1);
	biConverter.GetBigInt(-3.1415926, bigInt2);
	float pi1 = biConverter.GetFloat(bigInt1);
	float pi2 = biConverter.GetFloat(bigInt2);
	std::cout << "pi:" <<pi1 << " -pi:" << pi2 << std::endl;
	
	BigInteger c1, c2, m1, m2;
	PaillierEncryptor encryptor;
	encryptor.KeyGen(16);
	BigIntConverter encConverter(encryptor.N(), 32);
	BigInteger intPi1, intPi2;
	encConverter.GetBigInt(3.1415926, intPi1);
	encConverter.GetBigInt(-3.1415926, intPi2);
	encryptor.Encrypt(c1, intPi1);
	encryptor.Decrypt(m1, c1);
	float pi1_recovered = encConverter.GetFloat(m1);
	encryptor.Encrypt(c2, intPi2);
	encryptor.Decrypt(m2, c2);
	float pi2_recovered = encConverter.GetFloat(m2);
	std::cout << "pi recovered:" << pi1_recovered << " -pi recovered:" << pi2_recovered << std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
