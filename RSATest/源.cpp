#include <iostream>
#include "RSA_Test.h"
#include <gmp.h>
#include <random>

using namespace std;
void output_starter()
{
	cout << "\n输入想要的密钥长度(>1):";
}
int main(int argc, string  argv[])
{
	//_wsetlocale(LC_ALL, L"");
	unsigned int length;
	output_starter();
	while(cin>>length)
	{
		RSA_Test test1;
		test1(length);
		gmp_printf("p=0x%ZX\n\n", test1.p);
		gmp_printf("p=%Zd\n\n", test1.p);
		gmp_printf("q=0x%ZX\n\n", test1.q);
		gmp_printf("q=%Zd\n\n", test1.q);
		gmp_printf("n=0x%ZX\n\n", test1.n);
		gmp_printf("n=%Zd\n\n", test1.n);
		cout << "密钥长度：" << mpz_sizeinbase(test1.n, 2) << "位" << endl;
		gmp_printf("e=%Zd\n\n", test1.e);
		gmp_printf("d=0x%ZX\n\n", test1.d);
		gmp_printf("d=%Zd\n\n", test1.d);
		gmp_printf("φ(n)=0x%ZX\n\n", test1.z);
		gmp_printf("φ(n)=%Zd\n\n", test1.z);

		mpz_t m, c, _m;
		mpz_init(m);
		mpz_init(c);
		mpz_init(_m);
		//置随机数种子
		random_device rd;
		gmp_randstate_t seed_gmp;
		gmp_randinit_default(seed_gmp);
		gmp_randseed_ui(seed_gmp, static_cast<unsigned long>(rd()));
		//随机生成需加密原文m
		mpz_urandomm(m, seed_gmp, test1.n);//m<n
		gmp_randclear(seed_gmp);

		gmp_printf("m=0x%ZX\n\n", m);
		gmp_printf("m=%Zd\n\n", m);

		cout << "加密后..." << endl;
		test1.encrypt(c, m);
		gmp_printf("c=0x%ZX\n\n", c);
		gmp_printf("c=%Zd\n\n", c);

		cout << "解密后..." << endl;
		test1.decrypt(_m, c);
		gmp_printf("m=0x%ZX\n\n", _m);
		gmp_printf("m=%Zd\n\n", _m);

		if (mpz_cmp(m, _m) == 0)
			cout << "测试成功！" << endl;
		else
			cout << "测试失败！" << endl;

		mpz_clear(m);
		mpz_clear(c);
		mpz_clear(_m);
		output_starter();
	}
	
	//system("pause");
	return 0;

}
//33478071698956898786044169848212690817704794983713768568912431388982883793878002287614711652531743087737814467999489
//×
//36746043666799590428244633799627952632279158164343087642676032283815739666511279233373417143396810270092798736308917