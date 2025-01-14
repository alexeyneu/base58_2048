

#include "base58_2048.h"
#include "hashgroestl.h"
#include <sodium.h>
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
	if (argc == 3 && ((std::string(argv[1]) == "-wif24" == false) && (std::string(argv[1]) == "-hex32_24" == false)) && std::string(argv[1]) == "-secretkey" == false)
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
		if (  c.second.size() == 32 == false)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -5;
		}

		std::string wb_final_compressed;

		wb_final_compressed.insert(wb_final_compressed.cbegin(), (char)0x80);
		wb_final_compressed.insert(1, c.second);
		wb_final_compressed.insert(wb_final_compressed.cend(), (char)0x01);

		std::string h_compressed_groestl  = Groestl512(wb_final_compressed);
		std::string hf_compressed_groestl  =Groestl512 (h_compressed_groestl);
		auto hf_compressed_f(hf_compressed_groestl);
		hf_compressed_f.resize(4);
		std::string wb_final_compressed_groestl = wb_final_compressed;

		wb_final_compressed_groestl.insert(wb_final_compressed.size(), hf_compressed_f);
		auto t_compressed_groestl = b58encode(wb_final_compressed_groestl);

		unsigned char h_compressed[250] = {};
		unsigned char hf_compressed[250] = {};
		SHA256((unsigned char*)wb_final_compressed.c_str(), wb_final_compressed.size(), h_compressed);
		SHA256(h_compressed, 32, hf_compressed);

		wb_final_compressed.insert(wb_final_compressed.size(), std::string((char*)hf_compressed, 4));

		auto t_compressed = b58encode(wb_final_compressed);

		std::string wb_final;
		wb_final.insert(wb_final.cbegin(), (char)0x80);
		wb_final.insert(1, c.second);

		std::string h_groestl  = Groestl512(wb_final);
		std::string hf_groestl  =Groestl512 (h_groestl);
		auto hf_f(h_groestl);
		hf_f.resize(4);
		std::string wb_final_groestl = wb_final;

		wb_final_groestl.insert(wb_final.size(), hf_f);
		auto t_groestl = b58encode(wb_final_groestl);

		unsigned char h[250] = {};
		unsigned char hf[250] = {};
		SHA256((unsigned char *)wb_final.c_str(), wb_final.size(), h);
		SHA256(h, 32, hf);
		wb_final.insert(wb_final.size(), std::string((char *)hf, 4));

		auto t = b58encode(wb_final);
		std::string whydah = t.second;
		std::cout << std::endl << whydah << std::endl;
		std::string mill = t_compressed.second;
		std::cout << std::endl << mill << std::endl;
		std::cout << std::endl << "Groestl:" << std::endl;

		std::string whydah_groestl = t_groestl.second;
		std::cout << std::endl << whydah_groestl << std::endl;
		std::string mill_groestl = t_compressed_groestl.second;
		std::cout << std::endl << mill_groestl << std::endl;

	}
	if ((argc == 2 == false) && std::string(argv[1]) == "-hex32_24")
	{
		if (b.size() > 24)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -5;
		}

		auto c = b58decode(harbour);
		if (c.second.size() == 32 == false)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -5;
		}

		std::string draw = bin2hex((unsigned char *)c.second.c_str(), 32);
		std::cout << std::endl << draw << std::endl;

	}
	if ((argc == 2 == false) && std::string(argv[1]) == "-secretkey")
	{
		if (b.size() > 24)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			return -5;

		}

		auto c = b58decode(harbour);
		if (c.second.size() == 32 == false)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;

			return -1;

		}

		unsigned char bc[32];
		unsigned char f[64];

		crypto_sign_seed_keypair(bc, f, (unsigned char*)c.second.c_str());
		auto t = b58encode(std::string((char*)f, 64));
		std::cout << std::endl << t.second << std::endl;

	}
	return 0;
}


