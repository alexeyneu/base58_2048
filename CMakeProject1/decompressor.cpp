
#include "base58_2048.h"
#include <openssl/bn.h>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <base58.hpp>
#include <iostream>


const	std::string bin2hex(const unsigned char* p, size_t length) {
	std::stringstream f;
	f << std::hex << std::setfill('0');
	for (int i = 0; i < length; i++) f << std::setw(2) << (int)p[i];
	return f.str();
}

size_t hex2bin(unsigned char* p, const char* hexstr, const size_t length) {
	size_t wcount = 0;
	while (wcount++ < length && *hexstr && *(hexstr + 1)) {    //last condition cause np if check fails on middle one.thats coz of short-circuit evaluation
		long long b = sscanf(hexstr, "%2hhx", p++);  //7x slower than tables but doesnt metter
		if (b < 1) break;
		hexstr = hexstr + 2;
	}
	return  --wcount;     // error check here is a waste  
}






int main(int argc , char *argv[])
{
	if (argc > 3)
	{
		std::cerr << std::endl << "no go" << std::endl;
		return 0;
	}
	if (argc == 1)
	{
		std::cerr << std::endl << "where's the string" << std::endl;
		return 0;
	}
	if (argc == 3 && ((std::string(argv[1]) == "-wif24" == false) && (std::string(argv[1]) == "-hex32_24" == false)))
	{
		std::cerr << std::endl << "no go" << std::endl;
		return 0;
	}

	std::string a = argc == 3 ? argv[2] : argv[1];
	if ((argc == 2 == false) && std::string(argv[1]) == "-hex32_24")
	{
		unsigned char bc[32] = {};

		size_t zx = hex2bin(bc, a.c_str(), 32);

		if (zx == 32 == false)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -15;
		}

		unsigned char wb_final[250] = {};
		memcpy(wb_final, bc, 32);
		auto t = b58encode(std::string((char *)wb_final, 32 ));
		a = t.second;
	}

	if ((argc == 2 == false) && std::string(argv[1]) == "-wif24")
	{
		auto c = b58decode(a);
		size_t wq = c.second.size();
		if (wq == 37 == false && wq == 38 == false)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -5;
		}
		unsigned char wb_final[250] = {};
		memcpy(wb_final, &c.second[0] + 1, 32);

		auto t = b58encode(std::string((char *)wb_final, 32 ));
		a = t.second;
	}

	std::vector<std::string> farstone;

	std::pair<int, unsigned int> tyr = b58_to_2048(a, farstone);
	if (tyr.first == 0)
	{
		std::cerr << std::endl << "High-bit set on invalid digit" << std::endl;

		return (0);
	}
	if (tyr.first == -1)
	{
		std::cerr << std::endl << "Invalid base58 digit" << std::endl;

		return (0);
	}

	if (argc == 3 && farstone.size() > 24)
	{
		std::cerr << std::endl << "leading zeroes, will not work" << std::endl;

		return 0;
	}

	for (auto c:farstone)
		std::cout << std::endl << c << std::endl;
	std::cout << std::endl;

	return 0;
}

