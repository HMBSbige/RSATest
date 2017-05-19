#include <iostream>
#include "RSA_Test.h"

using namespace std;

int main(int argc, string  argv[])
{
	setlocale(LC_ALL, "");
	mpz_t p,q;
	mpz_init(p);
	mpz_init(q);
	mpz_set_str(p,"33478071698956898786044169848212690817704794983713768568912431388982883793878002287614711652531743087737814467999489",10);
	mpz_set_str(q, "36746043666799590428244633799627952632279158164343087642676032283815739666511279233373417143396810270092798736308917", 10);
	//mpz_nextprime(p, p);
	//mpz_nextprime(q, q);

	RSA_Test Test1;
	Test1(p, q);
	gmp_printf("p=0x%ZX\n", Test1.p);
	gmp_printf("q=0x%ZX\n", Test1.q);
	gmp_printf("n=0x%ZX\n",Test1.n);
	gmp_printf("e=%Zd\n", Test1.e);
	gmp_printf("d=0x%ZX\n", Test1.d);
	gmp_printf("φ(n)=%Zd\n", Test1.z);
	mpz_t m,c;
	mpz_init_set_str(m,"26595",10);//m<n
	mpz_init(c);
	gmp_printf("m=0x%ZX\n", m);

	cout << "加密后..." << endl;
	Test1.encrypt(c, m);
	gmp_printf("c=0x%ZX\n", c);

	cout << "解密后..." << endl;
	Test1.decrypt(m, c);
	gmp_printf("m=0x%ZX\n", m);

	mpz_clear(m);
	mpz_clear(c);
	mpz_clear(p);
	mpz_clear(q);
	system("pause");
	return 0;
}
//33478071698956898786044169848212690817704794983713768568912431388982883793878002287614711652531743087737814467999489
//×
//36746043666799590428244633799627952632279158164343087642676032283815739666511279233373417143396810270092798736308917