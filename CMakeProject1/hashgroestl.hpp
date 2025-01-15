// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The DigiByte developers
// Copyright (c) 2025 Alex Neudatchin

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef HASH_GROESTL
#define HASH_GROESTL
#include "sph_groestl.h"
#include <vector>

template<typename T1>
inline std::string Groestl512(const T1 p)
{
    sph_groestl512_context ctx_groestl;

    std::string hash1(64, ' ');

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512(&ctx_groestl, static_cast<const void*>(&p[0]), p.size());
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash1[0]));

    return hash1;
}


#endif
