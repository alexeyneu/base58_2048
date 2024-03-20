// CMakeProject1.cpp : Defines the entry point for the application.
//

#include "CMakeProject1.h"
#include <openssl\bn.h>
#include <vector>
#include <string>
#include <algorithm>
#include "libbase58.h"




static const int8_t b58digits_map[128] = {
	-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
	-1, 0, 1, 2, 3, 4, 5, 6,  7, 8,-1,-1,-1,-1,-1,-1,
	-1, 9,10,11,12,13,14,15, 16,-1,17,18,19,20,21,-1,
	22,23,24,25,26,27,28,29, 30,31,32,-1,-1,-1,-1,-1,
	-1,33,34,35,36,37,38,39, 40,41,42,43,-1,44,45,46,
	47,48,49,50,51,52,53,54, 55,56,57,-1,-1,-1,-1,-1,
};


int main()
{
	char* t = new char[1000]();
	size_t c = 1000;
	const unsigned char b[19] = "uiyiuiuyijiojijjio";  /* last byte is '\0' coz of b[] dealt with by compiler.
(size_t)sizeof(b) - 1 as last arg removes it from source binary block. */
	b58enc(t, &c, (void*)b, (size_t)sizeof(b));

	std::cout << t << std::endl;
	unsigned char bc[250] = {};
	size_t wq = 250;
	bool c5 = b58tobin((void*)bc, &wq, t, strlen(t));
	c5 = b58tobin((void*)bc, &wq, t, strlen(t));

	std::cout << bc << std::endl << std::endl << wq;
	std::cout << std::endl << 2048/58 << std::endl << 2048%58;


	char a[30] = "NVhHMCyXNHYRYg5mXw2nSnkLBh";
	BIGNUM* balance_eth_ex = BN_new();
	BIGNUM* balance_eth_exm = BN_new();
	BIGNUM* balance_eth_remmi = BN_new();
	BIGNUM* balance_eth_h = BN_new();
	unsigned char fx = 58;
	BIGNUM* balance_eth_f = BN_lebin2bn(&fx, 1, NULL);
	unsigned short ft = 256;
	BIGNUM* balance_eth_ft = BN_lebin2bn((unsigned char *)&ft, 2, NULL);

    BN_CTX *bz = BN_CTX_new();
	BN_zero(balance_eth_ex);

	for (int k = 0; k < 26; k++)
	{
		unsigned char pi = b58digits_map[a[k]];

		BIGNUM*  balance_eth_exmk = BN_lebin2bn(&pi, 1, NULL);

        BN_mul(balance_eth_exm, balance_eth_ex, balance_eth_f, bz);

		BN_add(balance_eth_ex, balance_eth_exm, balance_eth_exmk);
		BN_free(balance_eth_exmk);
	}
	std::string tc;
	bool w = false;
	unsigned char tr = 0;
	while (w == false)
	{
		BN_div(balance_eth_ex, balance_eth_remmi, balance_eth_ex, balance_eth_ft, bz);
		BN_bn2bin(balance_eth_remmi, &tr);
		tc = tc + (char)tr;

		w = BN_is_zero(balance_eth_ex);
	}
	std::reverse((unsigned char *)&tc[0], (unsigned char*)&tc[0] + 19);
	std::cout << std::endl << tc << std::endl << 2048 % 58;




	BIGNUM* balance_eth_ex_e = BN_new();
	BIGNUM* balance_eth_exm_e = BN_new();
	BIGNUM* balance_eth_remmi_e = BN_new();
	BIGNUM* balance_eth_h_e = BN_new();

	BN_zero(balance_eth_ex_e);
	BN_one(balance_eth_h_e);
	for (int kwe = 18; kwe + 1> 0; kwe--)
	{
		unsigned char pi = b[kwe];

		BIGNUM* balance_eth_exmk_e = BN_lebin2bn(&pi, 1, NULL);
		BN_mul(balance_eth_exm_e, balance_eth_h_e, balance_eth_exmk_e, bz);
		BN_add(balance_eth_ex_e, balance_eth_ex_e, balance_eth_exm_e);
		BN_mul(balance_eth_h_e, balance_eth_h_e, balance_eth_ft, bz);
		BN_free(balance_eth_exmk_e);
	}
	unsigned char bt[50] = {};
	w = false;
	int cw = 0;
	unsigned char tr_e = 0;

	static const char b58digits_ordered[59] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	std::string tc_e;

	while (w == false)
	{
		BN_div(balance_eth_ex_e, balance_eth_remmi_e, balance_eth_ex_e, balance_eth_f, bz);
		BN_bn2bin(balance_eth_remmi_e, &tr_e);
		tc_e = tc_e + b58digits_ordered[tr_e];

		w = BN_is_zero(balance_eth_ex_e);
	}
	std::reverse((unsigned char*)&tc_e[0], (unsigned char*)&tc_e[0] + tc_e.size());
	std::cout << std::endl << tc_e << std::endl;

	return 0;
}
