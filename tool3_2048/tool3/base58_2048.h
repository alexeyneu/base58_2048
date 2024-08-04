// CMakeProject1.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <string>
#include <vector>

std::pair<int, unsigned int> b58_to_2048(std::string a, std::vector<std::string>& b);

std::pair<int, unsigned int> transfer2048_to_b58(std::vector<std::string> tw, std::string& bt);

// TODO: Reference additional headers your program requires here.
