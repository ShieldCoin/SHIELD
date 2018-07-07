// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2018-2018 The SHIELD Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SHIELD_WALLET_TEST_WALLET_TEST_FIXTURE_H
#define SHIELD_WALLET_TEST_WALLET_TEST_FIXTURE_H

#include <test/test_shield.h>

#include <wallet/wallet.h>

#include <memory>

/** Testing setup and teardown for wallet.
 */
struct WalletTestingSetup: public TestingSetup {
    explicit WalletTestingSetup(const std::string& chainName = CBaseChainParams::MAIN);
    ~WalletTestingSetup();

    CWallet m_wallet;
};

#endif // SHIELD_WALLET_TEST_WALLET_TEST_FIXTURE_H
