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
void RSA_Test::operator ()(size_t bit_length){
	GeneratePublickey(e);
	gmpRandomPrime(p, q, bit_length);
	mpz_mul(n, p, q);//n = p*q;
	GeneratePrivatekey(d, e, z);
}
void RSA_Test::encrypt(uint& c, const uint& m) const
{
	//solve m**e ≡ c (mod n) => c=m**e%n
	mpz_powm(c, m, e, n);
}
void RSA_Test::decrypt(uint& m, const uint& c) const
{
	//solve c**d ≡ m (mod n) => m=c**d%n
	mpz_powm(m, c, d, n);
}
void RSA_Test::GeneratePublickey(uint& e)
{
	unsigned long a[] = { 3, 5, 17, 257, 65537 };
	RandomINT R_size_t;
	mpz_set_ui(e, a[R_size_t.GetRandomInteger<unsigned long>(0, 4)]);//通常选65537
}
void RSA_Test::GeneratePrivatekey(uint& d, uint& e, uint& z)
{
	//ed ≡ 1 (mod φ(n)) => solve ex + φ(n)y = 1 d=x|y &&d>0
	mpz_invert(d, e, z);
}
void RSA_Test::gmpRandomPrime(mpz_t& prime_p, mpz_t& prime_q,size_t bit_length)
{
	uint gcd_mpz;
	uint p1, q1;
	mpz_init(p1);
	mpz_init(q1);
	mpz_init(gcd_mpz);
	//置随机数种子
	std::random_device rd;
	gmp_randstate_t seed_gmp;
	gmp_randinit_default(seed_gmp);
	gmp_randseed_ui(seed_gmp, static_cast<unsigned long>(rd()));
	do{
		//生成bit_length/2位的质数
		size_t Psize = bit_length>>1;
		do
		{
			mpz_urandomb(prime_p, seed_gmp, Psize);//prime_p=random in [0,2**(bit_length/2)-1]
		}while (mpz_sizeinbase(prime_p, 2) != Psize);
		mpz_nextprime(prime_p, prime_p);
		//生成bit_length - bit_length/2位的质数
		size_t Qsize = bit_length -(bit_length >> 1);
		do
		{
			mpz_urandomb(prime_q, seed_gmp, Qsize);
		} while (mpz_sizeinbase(prime_q, 2) != Qsize);
		mpz_nextprime(prime_q, prime_q);
		//判断质数对是否符合条件
		///φ(n)=(p-1)*(q-1)
		mpz_sub_ui(p1, prime_p, 1);
		mpz_sub_ui(q1, prime_q, 1);
		mpz_mul(z, p1, q1);
		///1< e < φ(n) && coprime(e,φ(n))
		mpz_gcd(gcd_mpz, e, z);
	} while (mpz_cmp_ui(gcd_mpz, 1) != 0);//isCoprime(e,φ(n))
	mpz_clear(p1);
	mpz_clear(q1);
	mpz_clear(gcd_mpz);
	gmp_randclear(seed_gmp);
}
