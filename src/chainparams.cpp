// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>

#include <chainparamsseeds.h>
#include <arith_uint256.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.nTime = nTime;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].SetEmpty();

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 * XSH old
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 * SHIELD & XSH new
 CBlock(hash=000001bb4d8e1100fcb24e21b20b89bbe8e4843822fcca8fd14f2f124f8a381d, ver=1, algo=0, mined_hash=000001bb4d8e1100fcb24e21b20b89bbe8e4843822fcca8fd14f2f124f8a381d, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=925f83741e769a8bb4c6e51586a5352e6ea511c4f7de5d46aa53ae88d0dd7d32, nTime=1507311620, nBits=1e0fffff, nNonce=2527094, vtx=1, vchBlockSig=)
  Coinbase(hash=925f83741e, nTime=1507311620, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(0000000000, 4294967295), coinbase 04ffff001d01044c534f63746f62657220352c20323031372c20426c6f6f6d626572672c2042616e6b206f66204d6f6e747265616c20616e6420546f726f6e746f204c65616420506565727320696e20506f74204163636f756e7473)
    CTxOut(empty)
  vMerkleTree: 925f83741e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion)
{
    const char* pszTimestamp = "October 5, 2017, Bloomberg, Bank of Montreal and Toronto Lead Peers in Pot Accounts";
    return CreateGenesisBlock(pszTimestamp, nTime, nNonce, nBits, nVersion);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000;// FIXME: Unused
        consensus.ForkHeight = 800000;
        consensus.MULTI_ALGO_SWITCH_BLOCK = 10000;
        consensus.BIP34Height = consensus.ForkHeight;
        consensus.BIP65Height = consensus.ForkHeight;
        consensus.BIP66Height = consensus.ForkHeight; 

        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000"); //CBigNum(~uint256(0) >> 20);
                                    // 8840
        consensus.nPowTargetTimespan = 45; // diff readjusting time
        consensus.nPowTargetSpacing = 45; // FIXME: document use as 225/5, and should always be latest!
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 100; // 100 out of 200 blocks
        consensus.nMinerConfirmationWindow = 200;
        
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1529247969; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1559347200; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1529247969; // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1559347200; // May 1st, 2017

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        // It is all safe :thumbsup:
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1529247969; // November 15th, 2016.
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1559347200; // November 15th, 2017.

        // The best chain should have at least this much work. 
        // KeyNote: (Kind of like a checkpoint)
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000ee64d1517d1d144ce9");

        // By default assume that the signatures in ancestors of this block are valid.
        // KeyNote: Seems like speedup, similar to a checkpoint
        consensus.defaultAssumeValid = uint256S("0x52b34c85e84cb1463f07578a5de63c731a419c2e9a52ec282d91f2869ce28164"); //670 000

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xa1; 
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0xc4;
        pchMessageStart[3] = 0xee;
        nDefaultPort = 21103;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1507311620, 2527094, 0x1e0fffff, 1);
        consensus.hashGenesisBlock = genesis.GetPoWHash(ALGO_SCRYPT);
        //printf("%s", genesis.ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x000001bb4d8e1100fcb24e21b20b89bbe8e4843822fcca8fd14f2f124f8a381d"));
        assert(genesis.hashMerkleRoot == uint256S("0x925f83741e769a8bb4c6e51586a5352e6ea511c4f7de5d46aa53ae88d0dd7d32"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.

        // Adding some nodes in case it works
        vSeeds.emplace_back("d01.nodex.sh"); // Pieter Wuille, only supports x1, x5, x9, and xd
        vSeeds.emplace_back("d02.nodex.sh"); // Matt Corallo, only supports x9
        vSeeds.emplace_back("d03.nodex.sh"); // Luke Dashjr
        vSeeds.emplace_back("d04.nodex.sh"); // Christian Decker, supports x1 - xf
        vSeeds.emplace_back("d05.nodex.sh");
        vSeeds.emplace_back("d06.nodex.sh");
        vSeeds.emplace_back("d07.nodex.sh");
        vSeeds.emplace_back("d08.nodex.sh");
        vSeeds.emplace_back("d09.nodex.sh");
        vSeeds.emplace_back("d10.nodex.sh");
        vSeeds.emplace_back("d11.nodex.sh");
        vSeeds.emplace_back("d12.nodex.sh");
        // vSeeds.emplace_back("seed.bitcoin.jonasschnelli.ch"); // Jonas Schnelli, only supports x1, x5, x9, and xd
        // vSeeds.emplace_back("seed.btc.petertodd.org"); // Peter Todd, only supports x1, x5, x9, and xd
        // vSeeds.emplace_back("seed.bitcoin.sprovoost.nl"); // Sjors Provoost

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,33);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,191);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x02, 0x2D, 0x25, 0x33};
        base58Prefixes[EXT_SECRET_KEY] = {0x02, 0x21, 0x31, 0x2B};

        bech32_hrp = "sh";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                { 5000, uint256S("0xcadcdeb695791dccd20b5a284a32abd73a364d5cb23ff31d62a35d2c97da2a52")},
                { 25000, uint256S("0x95ae6a7776b2ebdd0be13df931f497a384061557ba2747187413aaa2d5e6dad3")},
                { 50000, uint256S("0xe20c589f8e50bafda6870790f1a9bcb945018266c762384c75ca3f86d240d764")},
                {100000, uint256S("0xd0aa58f4abb1b422595a850cc32dc081e9235774d5d9517e1a469f202ddb791e")},
                {150000, uint256S("0x90ce1a2a93125950ad4df9ba9ebd86e94d372617b8700b1da3555c740edc944f")},
                {200000, uint256S("0xaac305b12967a7186f0e4cb3a781a73ceca81f98dec396178f2f901b2856d106")},
                {300000, uint256S("0x1eae4274a8642434391a611748082436143860a9d8e15d78ecb4fe728eb99f5c")},
                {380000, uint256S("0x907ffa7caeaa7d5216b8a43517e66feef3c655e1da9289eef2e2a7f0e054248e")},
                {400000, uint256S("0xef80fd22b6fa2de548a6052aeedef2183b1e2571337bd550bd3d7579ebdd9a16")},
                {500000, uint256S("0x0000000000058123fb81a96ede321be8d9b9233b4bdc9de92a7054718014755a")},
                {600000, uint256S("0xbea64501cfeab8ad75aef74b3d2bc8d3630bc613ad80c082fad19b0157afe923")},
                {635000, uint256S("0xca42c722dbd90a18ac2617435224d253cc6c258f7bd7db41a8f0574a1132534d")},
                {700000, uint256S("0x57348dd099ca2ca7120819b0b6c54687d1f9e4145bc49bd695a22cf3dfdb4577")},
                {750000, uint256S("0x52b34c85e84cb1463f07578a5de63c731a419c2e9a52ec282d91f2869ce28164")},
            }
        };

        // FIXME: need to know the amount of transactions
        chainTxData = ChainTxData{
            // Data as of block 0000000000000000002d6cca6761c99b3c2e936f9a0e304b7c7651a993f461de (height 506081).
            1507311620, // * UNIX timestamp of last known number of transactions
            2,  // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.1         // * estimated number of transactions per second after that timestamp
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = false;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        // KeyNote: we'll leave testnet as is for now
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 0;
        consensus.BIP65Height = 0; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP66Height = 0; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000"); // FIXME: change to actual genesis limit
        consensus.nPowTargetTimespan = 24 * 60 * 60; // 1 day
        consensus.nPowTargetSpacing = 45;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1456790400; // March 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800; // May 1st, 2017

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1462060800; // May 1st 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1493596800; // May 1st 2017

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000000000000000f");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0000000002e9e7b00e1f6dc5123a04aad68dd0f0968d8c7aa45f6640795c37b1"); //1135275

        pchMessageStart[0] = 0x0b;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0x09;
        pchMessageStart[3] = 0x07;
        nDefaultPort = 21104;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1507311620, 2527094, 0x1e0fffff, 1);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("%s", genesis.ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x000001bb4d8e1100fcb24e21b20b89bbe8e4843822fcca8fd14f2f124f8a381d"));
        assert(genesis.hashMerkleRoot == uint256S("0x925f83741e769a8bb4c6e51586a5352e6ea511c4f7de5d46aa53ae88d0dd7d32"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet-seed.bitcoin.jonasschnelli.ch");
        vSeeds.emplace_back("seed.tbtc.petertodd.org");
        vSeeds.emplace_back("seed.testnet.bitcoin.sprovoost.nl");
        vSeeds.emplace_back("testnet-seed.bluematt.me"); // Just a static list of stable node(s), only supports x9

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tb";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = {
            {
                {546, uint256S("000000002a936ca763904c3c35fce2f3556c559c0214345d31b1bcebf76acb70")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 000000000000033cfa3c975eb83ecf2bb4aaedf68e6d279f6ed2b427c64caff9 (height 1260526)
            1516903490,
            17082348,
            0.09
        };

        /* enable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 18444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1507311620, 2527094, 0x1e0fffff, 1);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000001bb4d8e1100fcb24e21b20b89bbe8e4843822fcca8fd14f2f124f8a381d"));
        assert(genesis.hashMerkleRoot == uint256S("0x925f83741e769a8bb4c6e51586a5352e6ea511c4f7de5d46aa53ae88d0dd7d32"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {
                {0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "bcrt";

        /* enable fallback fee on regtest */
        m_fallback_fee_enabled = true;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
