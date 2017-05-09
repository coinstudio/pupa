// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xee;
        pchMessageStart[1] = 0x17;
        pchMessageStart[2] = 0xea;
        pchMessageStart[3] = 0xcb;
        nDefaultPort = 6811;
        nRPCPort = 6812;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 24);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
		//CBlock(hash=00000b3ff49c17395182bb3536efef383639184ece830b96fa7eccc1b6202a46, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, 
		// hashMerkleRoot=6177cec160c779139193ddbc002ccd65ec2bfd964053c714c9e42cb7e5f67aa4, nTime=1494310753, nBits=1e0fffff, nNonce=274470, vtx=1, vchBlockSig=)
		// Coinbase(hash=6177cec160c779139193ddbc002ccd65ec2bfd964053c714c9e42cb7e5f67aa4, nTime=1494310753, ver=1, vin.size=1, vout.size=1, nLockTime=0)
		// CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a1550757061436f696e20323031372120626f726e6564)
		// CTxOut(empty)
		//  vMerkleTree:  6177cec160c779139193ddbc002ccd65ec2bfd964053c714c9e42cb7e5f67aa4

        const char* pszTimestamp = "PupaCoin 2017! borned";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1494310753, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1494310753;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1125450;

		
        //// debug print
	//	 hashGenesisBlock == uint256("0x01");
        if (false && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "mainnet.genesis : \n" << genesis.ToString() << endl;
            cout << "mainnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "mainnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "mainnet.genesis.nTime: " << genesis.nTime << endl;
            cout << "mainnet.genesis.nNonce: " << genesis.nNonce << endl;
        }

          hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000000a01796cef1da05d174e940dec37717e6b52b7def2b3d0eae513875dfb8"));
        assert(genesis.hashMerkleRoot == uint256("0x6177cec160c779139193ddbc002ccd65ec2bfd964053c714c9e42cb7e5f67aa4"));

        vSeeds.push_back(CDNSSeedData("PupaCoin", "213.169.33.11"));


        base58Prefixes[PUBKEY_ADDRESS] = list_of(55);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(183);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x81)(0xDA)(0xAE);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x82)(0xA1)(0xA4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa7;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0xae;
        pchMessageStart[3] = 0x7c;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        nDefaultPort = 16811;
        nRPCPort = 16812;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1494310000;
        genesis.nNonce = 77;
	
//	hashGenesisBlock == uint256("0x01");
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00834aa9bcaceb1412c106f3fcebc6e460a23bee4a7ea5dbfc722de5ceaa6616"));
        if (false && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "testnet.genesis : \n" << genesis.ToString() << endl;
            cout << "testnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "testnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "testnet.genesis.nTime: " << genesis.nTime << endl;
            cout << "testnet.genesis.nNonce: " << genesis.nNonce << endl;
        }
        vFixedSeeds.clear();
        vSeeds.push_back(CDNSSeedData("PupaCoin.pw", "test1.PupaCoin.pw"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;




static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;

        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);



    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
