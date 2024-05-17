

#include "base58_2048.h"
#include <openssl/sha.h>
#include <openssl/bn.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstring>
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
		sscanf(hexstr, "%2hhx", p++);  //7x slower than tables but doesnt metter 
		hexstr = hexstr + 2;
	}
	return  --wcount;     // error check here is a waste  
}

int main(int argc, char *argv[])
{
	
	if (argc > 3)
	{
		std::cerr << std::endl << "no go" << std::endl;
		return 0;
	}
	if (argc == 1)
	{
		std::cerr << std::endl << "where's the" << std::endl;
		return 0;
	}
	if (argc == 3 && ((std::string(argv[1]) == "-wif24" == false) && (std::string(argv[1]) == "-hex32_24" == false)))
	{
		std::cerr << std::endl << "no go" << std::endl;
		return 0;
	}
	
	std::vector<std::string> b;

	std::ifstream fw(argc == 3 ? argv[2] : argv[1]);
	if (fw.fail())
	{
		std::cerr << std::endl << "not found" << std::endl;
		return 0;
	}

	do 
	{
		std::string last;
		fw >> last;
		if (fw.fail()) break;
		b.insert(b.cend(), last);
	} while (fw.bad() == false);


	std::string harbour;
	std::pair<int, unsigned int> f = transfer2048_to_b58(b, harbour);
	if (f.first == 0) 
	{
		return (0);
	}

	if (argc == 2)
	{
		std::cout << std::endl << harbour << std::endl;
	}
	if ((argc == 2 == false) && std::string(argv[1]) == "-wif24")
	{
		if (b.size() > 24)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -5;
		}

		auto c = b58decode(harbour);
		size_t wq = c.second.size();
		if ( wq == 32 == false)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -5;
		}

		unsigned char wb_final_compressed[250] = {};

		wb_final_compressed[0] = 0x80;

		memcpy(wb_final_compressed + 1, &c.second[0], wq);
		wb_final_compressed[wq + 1] = 0x01;

		unsigned char h_compressed[250] = {};
		unsigned char hf_compressed[250] = {};
		SHA256(wb_final_compressed, wq + 2, h_compressed);
		SHA256(h_compressed, 32, hf_compressed);
		memcpy(wb_final_compressed + wq + 2, hf_compressed, 4);

		auto t_compressed = b58encode(std::string((char *)wb_final_compressed, 38));
		unsigned char wb_final[250] = {};
		wb_final[0] = 0x80;

		memcpy(wb_final + 1, c.second.c_str(), wq);
		unsigned char h[250] = {};
		unsigned char hf[250] = {};
		SHA256(wb_final, wq + 1, h);
		SHA256(h, 32, hf);
		memcpy(wb_final + wq + 1, hf, 4);

		auto t = b58encode(std::string((char *)wb_final, 1 + 32 + 4));
		std::string whydah = t.second;
		std::cout << std::endl << whydah << std::endl;
		std::string mill = t_compressed.second;
		std::cout << std::endl << mill << std::endl;

	}
	if ((argc == 2 == false) && std::string(argv[1]) == "-hex32_24")
	{
		if (b.size() > 24)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -5;
		}

		auto c = b58decode(harbour);
		size_t wq = c.second.size();
		if (wq == 32 == false)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -5;
		}

		unsigned char wb_final[250] = {};
		memcpy(wb_final, &c.second[0], wq);

		std::string draw = bin2hex(wb_final, 32);
		std::cout << std::endl << draw << std::endl;

	}
	return 0;
}


