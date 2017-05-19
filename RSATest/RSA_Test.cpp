#include "RSA_Test.h"
#include "myrandom.h"

RSA_Test::RSA_Test()
{
	Init();
}
RSA_Test::~RSA_Test()
{
	release();
}
void RSA_Test::Init()
{
	mpz_init(p);
	mpz_init(q);
	mpz_init(n);
	mpz_init(e);
	mpz_init(d);
	mpz_init(z);
}
void RSA_Test::release()
{
	mpz_clear(p);
	mpz_clear(q);
	mpz_clear(n);
	mpz_clear(e);
	mpz_clear(d);
	mpz_clear(z);
}
void RSA_Test::operator ()(uint _p, uint _q) {
	mpz_set(p, _p);//p = _p;
	mpz_set(q, _q);//q = _q;
	mpz_mul(n, p, q);//n = p*q;
	GeneratePublickey(e, p, q);
	GeneratePrivatekey(d, e, z);
}
void RSA_Test::encrypt(uint& c, uint m) const
{
	//solve m**e ≡ c (mod n) => c=m**e%n
	mpz_powm(c, m, e, n);
}
void RSA_Test::decrypt(uint& m, uint c) const
{
	//solve c**d ≡ m (mod n) => m=c**d%n
	mpz_powm(m, c, d, n);
}
void RSA_Test::GeneratePublickey(uint& e, uint& p, uint& q)
{
	///φ(n)=(p-1)*(q-1)
	uint p1, q1;
	mpz_init(p1);
	mpz_init(q1);
	mpz_sub_ui(p1, p, 1);
	mpz_sub_ui(q1, q, 1);
	mpz_mul(z, p1, q1);
	mpz_clear(p1);
	mpz_clear(q1);

	///1< e < φ(n) && coprime(e,φ(n))
	unsigned long a[] = { 3, 5, 17, 257, 65537 };
	RandomINT R_size_t;
	mpz_set_ui(e, a[R_size_t.GetRandomInteger<unsigned long>(0, 4)]);
	/*uint gcd_mpz;
	mpz_init(gcd_mpz);
	//置随机数种子
	gmp_randstate_t seed_gmp;
	gmp_randinit_default(seed_gmp);
	gmp_randseed_ui(seed_gmp, static_cast<unsigned long>(time(nullptr)));
	//Generate e
	while (true)
	{
		mpz_urandomm(e, seed_gmp, z);//e=random in [0,z-1]
		mpz_gcd(gcd_mpz, e, z);
		if (mpz_cmp_ui(gcd_mpz, 1) == 0)//isCoprime(e,φ(n))
			break;
	}
	gmp_randclear(seed_gmp);
	mpz_clear(gcd_mpz);*/
}
void RSA_Test::GeneratePrivatekey(uint& d, uint& e, uint& z)
{
	//ed ≡ 1 (mod φ(n)) => solve ex + φ(n)y = 1 d=x|y &&d>0
	mpz_invert(d, e, z);
}