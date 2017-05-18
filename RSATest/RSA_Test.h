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
	RSA_Test();
	~RSA_Test();
	void Init();
	void release();
	void operator ()(uint _p, uint _q);
	void encrypt(uint& c, uint m) const;
	void decrypt(uint& m, uint c) const;
//private:
	uint p, q;//prime
	uint n;//p*q
	uint e;
	uint d;
	uint z;

	//public key:(e,n)
	//private key:(d,n)
	void GeneratePublickey(uint& e, uint& p, uint& q);
	static void GeneratePrivatekey(uint& d, uint& e, uint& z);
};
