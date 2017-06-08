#pragma once
//gmp
#pragma warning(push) 
#pragma warning(disable:4244)
#pragma warning(disable:4146)
#include <gmp.h>
#pragma warning(pop)

class RSA_Test
{
	using uint = mpz_t;
public:
	uint p, q;//prime
	uint n;//p*q
	uint e;
	uint d;
	uint z;

	RSA_Test();
	~RSA_Test();
	void Init();
	void release();
	void operator ()(size_t bit_length);
	void encrypt(uint& c, const uint& m) const;
	void decrypt(uint& m, const uint& c) const;

	//public key:(e,n)
	//private key:(d,n)
	static void GeneratePublickey(uint& e);
	static void GeneratePrivatekey(uint& d, uint& e, uint& z);
	void gmpRandomPrime(mpz_t& prime_p, mpz_t& prime_q, size_t bit_length);
};
