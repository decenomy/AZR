// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

#define DISABLED 0x7FFFFFFE;

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "U.S. News & World Report Dec 20 2019 With His Absence, Trump signs $1.4 trillion bill to avoid government shutdown, raise minimum age for tobacco";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
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
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256S("00000c76e5393b390e03a0c0ecd6e773a99bb906d30aa8bc2a1108146bc78561"))
    (17577, uint256S("8cf666f6a29ff2d31d1e5556fb4fd78d3b9437fe4e67d7bf21172c8623e6530b"))
    (35155, uint256S("ac4835bc60e8ef9d857542600c662c8a7adf6bff9c94d5f16599fb641851ac6f"))
    (52733, uint256S("4f1e4faf9365d9e535304ac94a27e36549c7b68c14ef2d2cd5c5acfd56cd6f7a"))
    (70311, uint256S("96ccc7e46918942cbf1129b107a79c6174e89e33b3374d420ae87e48972ce6ad"))
    (87889, uint256S("f6f021b5d1a658e389d36de5ab5403d9c95f5a73c4ff2f24ce25238ffed555c9"))
    (105467, uint256S("bc91ea2cb14540b4977f9fc6d22d7b98cb22e8c52e81fcd1920fb2101cf01823"))
    (123045, uint256S("3879da9a238488fac5f241e14b02d59fc8edeef7cad13518d7eb62de881c39b5"))
    (140623, uint256S("478dff5eff8879c7a1839f6eba261b16620700fe3a6aebc010774d78e2545766"))
    (158201, uint256S("246628339bc52e1fd3dfdbe29a32d7fd7bd13a797fa05de44c3cfdc7cd9febe0"))
    (175779, uint256S("c3cb8189a6ccb17a1cb0bfb0f264ef35633af701980c4da3af614dbd14d72cc5"))
    (193357, uint256S("38e6f822b0c2f8b4be075d406fc8eda41ae2393228b341e408066abf45ead62d"))
    (210935, uint256S("862a193cb76c91e8999cdc6ada0b935ebb1e33c1a36b43b8a7fce9ad2f3d851e"))
    (228513, uint256S("bc5f95d2e0b8d890b8795447aa20ccc10680c71a37e44e2b9c86332679bd9624"))
    (246091, uint256S("f2bfe2fc70f2cf922056773d51cd2da994a37c5d96ceb8d81c486444e5324b28"))
    (263669, uint256S("a51b20b000325b0ae7556a3d28ed6456a6cc0c1055246040c072b1a2b61a951b"))
    (281247, uint256S("5fe3b294edbfd05ec35810193b64e0abf13dee225c96b3a5e2647da1825bf22d"))
    (298825, uint256S("72c8c9ec06c0ba4f62318fc2dd24701b8dd982028b558ef9d2ef164aa9a24906"))
    (316403, uint256S("5a69b7096ab0d83203f22a3b1ac3c3b295c900da24247d1618ed58b34d44b9be"))
    (333981, uint256S("7a6961aaa10ec43eef2799715b2fd531ef09be650fb3031d12d5d1c80b36db58"))
    (351559, uint256S("a69d1ca812f4322bf49802b2012677f3a1fc67c496f4ec817eb74e16dd50eaf4"))
    (369137, uint256S("d8e96f1d92813828504d0b1cf1ceae8eb4855e08608c6b9d449b02617ac55209"))
    (386715, uint256S("072ea58d24b8f6e29e0dd4a181c886f1449f0302218aeb84572da44449c5138c"))
    (404293, uint256S("70d83ecedb526b9e7c25577bf8380455ca2203af1667554e224e5fdeaa7dc436"))
    (421871, uint256S("af351ca1f57809bfc14c4cadadddd84c9c895def1bcd61092700a6c084409bb3"))
    (439449, uint256S("7b2b1bef713ed60edf35de3e79e0ce56fa4a277679cab88df7ebc7df19641071"))
    (457027, uint256S("7b3adb613f87b6385bb78093a1774f58f7fe1a03da6e6ebaf538576e8cde1745"))
    (474605, uint256S("29fa85dee03e5ad1d14d6110be2b22301f57b34bf7d1b8125a5efc9f07ef8172"))
    (492183, uint256S("880685d968e9f31e3992a2bf25a34dbc0a651a100d787b3d4af0ff7432fcfe1c"))
    (509761, uint256S("2258c170c484ac294d99cc4f9f2e3f5a653cf33e39736fd6de3c9f196ec61f85"))
    (527339, uint256S("3f12f161f3b38f25dbffe2074e7f052bb22391abde8321f947632df88470df67"))
    (544917, uint256S("83d9729fe7bbc84841c87c79f67135ec0990879ca1cb28fa43e98aae6f727e21"))
    (562495, uint256S("db9197574c5420444263a224689cb39047d4129e2e8b1377b39ce79748e3b0de"))
    (580073, uint256S("c6f2e991a20f574761fdd1ebb6a1a46385e6ef162c8b6e9936f89e438d3060a3"))
    (597651, uint256S("c681abc11fdf3a2120297b14930628d36fbdcbf34875c0aa5d26100945bd1451"))
    (615229, uint256S("39515edb60a715c5cdf9f68e14755e946757e49f6b924c71fba9bc81c1bbfaa2"))
    (632807, uint256S("4342c23d03363fe89599c01961d964b9ce1cff63990094f20a381a59d66c042f"))
    (650385, uint256S("f5d78c3ede9bf11264541a657b85ea9a42c809e6896329cd761556899592fe21"))
    (667963, uint256S("eaa750522214c6ea386d490007f1058dba30241e61a6d85caf2dac6a475ae660"))
    (685541, uint256S("56ce137184966ba6da9451172abcc28d2a0714dfb23e05f89969f45686343c0d"))
    (703119, uint256S("6ddd6c74a2325f34a124ebc587517445e5e6a26abb5eeea8877c6537e6018312"))
    (720697, uint256S("7b69052de0eb05a0d315b6c80f0d568f7c96871df94fb2ce1455f243d7169303"))
    (738275, uint256S("f34763d72c39da5a8de7671705e21cdfc75b037880a4764ee3feb29758ff4ea6"))
    (755853, uint256S("ade8ea98925dd95f4ed5901235bd251e1c057b5f20880868636508e7bb281a9c"))
    (773431, uint256S("18411867e12422f721d8bdafce327940c66fe502616faeb68c1fea1a45e8aa65"))
    (791009, uint256S("8454e8ac31396753a3daa289d42db283efdbd8d9928081a8de2e871a691247bd"))
    (808587, uint256S("2910bc03d69f4ea0df82a16fb8ce14e74d224c9e3f1c89f2a0826548aee91824"))
    (826165, uint256S("e442e696e28f56068a2a2650adb3eac9f8720aa45db814fc752c5a916babb413"))
    (843743, uint256S("474bb018a1a31b89970967b10ccc1718929a3eff818c903be7f54e7fab0f4e88"))
    (861321, uint256S("a04d95c84925fbd1f8a71ed236ca50178e33ea94a61b108f2b40cab7f615a910"))
    (878899, uint256S("1977ebdd04ffa389beb6ceb7cb06a0ddb638e461f2eedb5ca45ef5c487c387a5"))
    (896477, uint256S("0dda03d5ff939a3a031e217ee36c00b25754058b6950da1e2dbc02417444dae8"))
    (914055, uint256S("448a66b1c5a503576fca28c60662fd1a573d9846d0d450a2639129f598a65189"))
    (931633, uint256S("7edd4d45e02d27d0d7f06d7fcdf7129f1acd83bab91ab337ec3c31d1c1b426d0"))
    (949211, uint256S("b06fae733166f48b1ffd5b52412af79d27d221b8bc6c615cc82edc491f9e2b24"))
    (966789, uint256S("63d97148d68b204392e1dbd11815f62771127b6bd349eacf3d6147293feff93d"))
    (984367, uint256S("6c0d72a3272e587c3185bd692b8dd074ae3fd7f49434909ba9cef528195b22d2"))
    (1001945, uint256S("a739e72269d0631167b81cb9b2df7e3cf452a2019492acbcafa68845b7966f09"))
    (1019523, uint256S("fc4f7db5bd45b72b446ef52d78277eb3cb758e184eedc58da2f0cb695d0751a1"))
    (1037101, uint256S("c503fa59fa07681b960f298c61f24680b59c0af277739a0d4930c27778331b3f"))
    (1054679, uint256S("5077ec1d2db1f5904c355251d7ac4cb1f30ddb282218e5516a704f0e4381585d"))
    (1072257, uint256S("6e964bec5dd651f253c37b38cfaee91298e6fff08ff3a1c8201394e542d9e096"))
    (1089835, uint256S("402857849cee5e2712e1e99ba41d11fae92932491c146f5bd66958fa6f70c99d"))
    (1107413, uint256S("7641db153cd2a228c754054c798d95edf3866e369cde137191320e57742348e7"))
    (1124991, uint256S("38f0cac0b1388019d9351493c90f611edffa127249b765bedfd558fb23a7f872"))
    (1142569, uint256S("39a5149cb6035361eafcc0cb209ae4a83453f6201f89d8c279000817cb97ea2c"))
    (1160147, uint256S("94a555ab1497521c09dee4a503ee120da11300b588e1dcea274443168689ad44"))
    (1177725, uint256S("6b9508da7adab0ea36cdb2033b4ee19cd12b0b21f1213a190a04d6fb77584895"))
    (1195303, uint256S("df44fae39b06dbd6b9587dba2bbf49fd9436a38238da6b9392278a621dfdcbc3"))
    (1212881, uint256S("7890f5da5dbc1d3510e0d44a548d48d3b4ef354b7989f46569fbc69205ebf684"))
    (1230459, uint256S("86ef2eb0baf2d76e26fc02d4a46d03d67be5d259ef05fd6599463bcae1e182e1"))
    (1248037, uint256S("b82e40d873c288d14b98d60c746ee86f6d331e79bfe3e30608fc7a0ec6189a82"))
    (1265615, uint256S("52383b8c4d78dd8ccf26f0404a6c9a6e757d476476cdce0b687c696bc7147834"))
    (1283193, uint256S("c3b1f08afab26b2893b57ddc694a747775aead7fca27c3b669b212ba499b5be7"))
    (1300771, uint256S("d53c426f16ee9496c752f7200fc607f91e2beb6ef24d78fe4906a1bd555546fa"))
    (1318349, uint256S("900fed01c2cbd035311f58840d071aa2c615c96da2ec3d406df6e16d232182be"))
    (1335927, uint256S("24cd2892257f960e7981275e307e58f9491206c64676d1e1f50f762096956967"))
    (1353505, uint256S("732e4d1e70ba41afcefd332d1e6eb68cdac0ec469f4789ac01c7f1511c69fa5f"))
    (1371083, uint256S("dd17dca1f96bc916958368b316fc28be50a6bcec1e79732762b7249a75237f04"))
    (1388661, uint256S("5790fe4c0ddbb52ee1927ecd0554e921f3a99810bd87b35186cd23141d1982a7"))
    (1406239, uint256S("1fc61ccbfea158e988fc3458cbb31de9fa10385cc90218aff7dfc229d562b642"))
    (1423817, uint256S("a99f3203e4fe7301c52f7d85c975adedae0ef59e91c4860ac337232191f8a453"))
    (1441395, uint256S("847cd534b05e96db90f6b2975fda37246f8419784e131586935eb16ae1bec835"))
    (1458973, uint256S("e62d8c32ba365302bb7c8ec202f7bbdf12cb25bc65d5e1fa76b8f7355a81563a"))
    (1476551, uint256S("3a805e1534d9e1f255ce82ab85c9b2d6c786b97596cad205991cd86549ffe616"))
    (1494129, uint256S("f061692ec43ba59eb29664980e8a3d818f469324403b439ba4cc580e593b56b9"))
    (1511707, uint256S("786cf00b3ef4daa7392a61d119e0bd43d36d784285cc628acb5ed653862605ee"))
    (1529285, uint256S("cb5e4a829e6065e08b420287afe769577ea67aeea16d94cd7c0fba5338cfd9e0"))
    (1546863, uint256S("49893519a3aafa4a4693676d00fd1af0f0a8a6d109a8ede8677032815d10ae70"))
    (1564441, uint256S("d17626828e8538bc527a63bbc4dc453ef610d9c089a24be56ba3df707b99adad"))
    (1582019, uint256S("8339bc3741af1713defa735efde04d4884b418697f18c4bab3cef94ec86f8568"))
    (1599597, uint256S("6eed157f878c3984c4559f20e902015c1062eb2530aacb49aeda47c2bd7e098b"))
    (1617175, uint256S("e369b3306afd04422e90ed86f0104ee1f1da58e7690d46f3c9829dedf1b93ddc"))
    (1634753, uint256S("3bc3886a7c23890670aecf9eefa6f9f0201ea2db3bcb5b41b32651208080c93d"))
    (1652331, uint256S("fc14bba01415f0725a30bd4e63e42edf60900333eaee8517aeef8cd93d32f65a"))
    (1669909, uint256S("b1de5218e8e456be146cb5a73263242041ae76739b4a1f1bfe17248eda670bef"))
    (1687487, uint256S("286bd2524161bb1bd8d5912e180c36c9c7ff8bbc2d6c8a6979432f661a9dda57"))
    (1705065, uint256S("acba69b6d643a60f2bb3769a46de9f97996646849738daa6bbead2dcdd41df57"))
    (1722643, uint256S("0cf9c5a8c861b80d4e59217e940b5fa93c459442fe8571107fa9feb95ff16a21"))
    (1740221, uint256S("509351f48ddac1efe5bb3b39995b29b4ee99f6ce2eabc3c67568b8c477a01934"))
    (1757799, uint256S("c8d88d87af414ddd0cb61c8987c92152e134e67a9149cbca687bebea3ff38c6c"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1686444120, // * UNIX timestamp of last checkpoint block
    4191586,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2834        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1618037081,
    2501682,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1618038166,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1576918337, 2012178, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c76e5393b390e03a0c0ecd6e773a99bb906d30aa8bc2a1108146bc78561"));
        assert(genesis.hashMerkleRoot == uint256S("0x6df2c144da90964516839ed9d56ab2742cfaa8956824c16cfd0c4ad482f0e1dd"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 160;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nAZZRCoinSupplyMintHeight = 800001;
        consensus.nAZZRCoinSupply = 38000000 * COIN;
        consensus.sAZZRCoinSupplyMintAddress = "AJ9U4dLkwuxw4bLayZN6BMrVyHRsKfXJ55";

        // spork keys
        consensus.strSporkPubKey = "023a979aefef58890e1cae7934c5bed09a8dc8f70da29d884d84bf083eaac6d566";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "AbURNXXXXXXXXXXXXXXXXXXXXXXXTPBUBf", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 320;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 330;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 320;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 350;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 800001;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 800001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight        = 800001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("84ce0f65f4261b1d1e951c9a10f283c1c31d9915bc6e07eac170dc8803341d3e");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("de10b92f53b0ee686ce9393dbe0a175bfec8e3a1ec9b0a12d15dacdffa614217");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("134cf44ffbe2b8abfddad62e42fbe1ac48e00cec282cd620aebd80c0eb2cb001");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("de10b92f53b0ee686ce9393dbe0a175bfec8e3a1ec9b0a12d15dacdffa614217");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("6d41821d7438c430d602d96fee51807e7a3fb8412a456a8e34082541ab10b2a0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("64c3ba555ff22fc6a4bddb646a0a38a406a36adf7e896ea97971917c0914cf99");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("64c3ba555ff22fc6a4bddb646a0a38a406a36adf7e896ea97971917c0914cf99");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock      = uint256S("64c3ba555ff22fc6a4bddb646a0a38a406a36adf7e896ea97971917c0914cf99");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x06;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0x12;
        pchMessageStart[3] = 0x19;
        nDefaultPort = 14725;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1",  "seed1.azzurecoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2",  "seed2.azzurecoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3",  "seed3.azzurecoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4",  "seed4.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5",  "seed5.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6",  "seed6.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7",  "seed7.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8",  "seed8.azzurecoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 24);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 198);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x43).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main)); // added
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v1)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1618037081; //

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1e0ffff0, 1, 50 * COIN);
        //     //genesis.hashPrevBlock = TempHashHolding;
        //     consensus.hashGenesisBlock = genesis.GetHash();

        //     arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
        //     if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
        //         BestBlockHash = consensus.hashGenesisBlock;
        //         std::cout << BestBlockHash.GetHex() << " Nonce: " << i << "\n";
        //         std::cout << "   PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
        //     }

        //     TempHashHolding = consensus.hashGenesisBlock;

        //     if (BestBlockHashArith < test) {
        //         genesisNonce = i - 1;
        //         break;
        //     }
        //     //std::cout << consensus.hashGenesisBlock.GetHex() << "\n";
        // }
        // std::cout << "\n";
        // std::cout << "\n";
        // std::cout << "\n";

        // std::cout << "hashGenesisBlock to 0x" << BestBlockHash.GetHex() << std::endl;
        // std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        // std::cout << "Genesis Merkle 0x" << genesis.hashMerkleRoot.GetHex() << std::endl;

        // exit(0);

        // /////////////////////////////////////////////////////////////////

        genesis = CreateGenesisBlock(1618037081, 3673827, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000bc103d39f3620750bbf80d5cfdcffeeab5d97cbdac6b9f8ba3da04d8718"));
        assert(genesis.hashMerkleRoot == uint256S("0x6df2c144da90964516839ed9d56ab2742cfaa8956824c16cfd0c4ad482f0e1dd"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 12;   // azzure starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 200;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
        consensus.strSporkPubKeyOld = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        consensus.nTime_EnforceNewSporkKey = 1566860400;    //!> August 26, 2019 11:00:00 PM GMT
        consensus.nTime_RejectOldSporkKey = 1569538800;     //!> September 26, 2019 11:00:00 PM GMT

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 301;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 401;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x57;
        pchMessageStart[1] = 0x21;
        pchMessageStart[2] = 0x33;
        pchMessageStart[3] = 0xff;
        nDefaultPort = 14726;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("testnet1", "testnet1.4444.tools"));
        vSeeds.push_back(CDNSSeedData("testnet2", "testnet2.4444.tools"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet azzure addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet azzure script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet azzure BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet azzure BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet azzure BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1618038166; //

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1fffffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1fffffff, 1, 50 * COIN);
        //     //genesis.hashPrevBlock = TempHashHolding;
        //     consensus.hashGenesisBlock = genesis.GetHash();

        //     arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
        //     if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
        //         BestBlockHash = consensus.hashGenesisBlock;
        //         std::cout << BestBlockHash.GetHex() << " Nonce: " << i << "\n";
        //         std::cout << "   PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
        //     }

        //     TempHashHolding = consensus.hashGenesisBlock;

        //     if (BestBlockHashArith < test) {
        //         genesisNonce = i - 1;
        //         break;
        //     }
        //     //std::cout << consensus.hashGenesisBlock.GetHex() << "\n";
        // }
        // std::cout << "\n";
        // std::cout << "\n";
        // std::cout << "\n";

        // std::cout << "hashGenesisBlock to 0x" << BestBlockHash.GetHex() << std::endl;
        // std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        // std::cout << "Genesis Merkle 0x" << genesis.hashMerkleRoot.GetHex() << std::endl;

        // exit(0);

        // /////////////////////////////////////////////////////////////////

        genesis = CreateGenesisBlock(1618038166, 302, 0x1fffffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x006656221e2e3eed8679ea44b0ad48121ceb26b38408aec372ac8bca1fa6f8cf"));
        assert(genesis.hashMerkleRoot == uint256S("0x6df2c144da90964516839ed9d56ab2742cfaa8956824c16cfd0c4ad482f0e1dd"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 2;   // azzure starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 5;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 300;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x21;
        pchMessageStart[3] = 0x57;
        nDefaultPort = 14728;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
