// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2018-2018 The SHIELD Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SHIELD_CRYPTO_POW_HASHBLAKE_H
#define SHIELD_CRYPTO_POW_HASHBLAKE_H

#include <uint256.h>
#include <serialize.h>
#include <crypto/pow/blake2.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <vector>
#include <string>

template<typename T1>
inline uint256 HashBlake(const T1 pbegin, const T1 pend)
{
    static unsigned char pblank[1];
    uint256 hash1;
    blake2s_state S[1];
    blake2s_init( S, BLAKE2S_OUTBYTES );
    blake2s_update( S, (pbegin == pend ? pblank : (unsigned char*)&pbegin[0]), (pend - pbegin) * sizeof(pbegin[0]) );
    blake2s_final( S, (unsigned char*)&hash1, BLAKE2S_OUTBYTES );
    return hash1;
}




#endif
