//
// Created by 佘崧林 on 2020/4/2.
//

#ifndef KEYMININGALGORITHM_EFFICIENTLYGCDTESTCASES_H
#define KEYMININGALGORITHM_EFFICIENTLYGCDTESTCASES_H
#include <utility>
#include <vector>
#include <string>
#include <utility>
#include <gmpxx.h>

typedef struct {
    std::string testMessage;
    std::vector<mpz_class> bigNumbersVector;
    std::vector<mpz_class> expectedRemaindersVector;
} EgcdTestCaseType;

EgcdTestCaseType __CASE1 = {
        .testMessage = "Normal test case",
        .bigNumbersVector = {15, 77, 221, 57},
        .expectedRemaindersVector = {3, 1, 1, 3}
};

EgcdTestCaseType __CASE2 = {
        .testMessage = "Case1: Amount isnot equal to 2^k",
        .bigNumbersVector = {15, 77, 221, 57, 667},
        .expectedRemaindersVector = {3, 1, 1, 3, 1}
};

EgcdTestCaseType __CASE3 = {
        .testMessage = "Case2: Amount isnot equal to 2^k",
        .bigNumbersVector = {15, 77, 221, 57, 667, 217},
        .expectedRemaindersVector = {3, 7, 1, 3, 1, 7}
};

EgcdTestCaseType __CASE4 = {
        .testMessage = "Case3: Amount isnot equal to 2^k",
        .bigNumbersVector = {221, 57, 15, 667, 217, 1763, 77,},
        .expectedRemaindersVector = {1, 3, 3, 1, 7, 1, 7,}
};

EgcdTestCaseType __CASE5 = {
        .testMessage = "Numbers contain 0",
        .bigNumbersVector = {0, 57, 15, 667, 217, 1763, 77,},
        .expectedRemaindersVector = {1, 3, 3, 1, 7, 1, 7,}};

EgcdTestCaseType __CASE6 = {
        .testMessage = "Big number with 1024bits test.",
        .bigNumbersVector = {
                mpz_class("bb2ec6b657a9db78422c9272e3824b062ff18393f466334cce69cde18bfeb17481920fb9de7a7fb82bbf18310b3262303d0c5285ea3097a107dfa55b18df8b0505b500f51e1a2bad2199e9a3711977f954e9736a554328727502fb7ee32b627fb7b835f2d20ab6650acfdee88e44d36057dd527f235ce3eb937bdbe4a1873d10b749e9b4ca13f8a295845e4365a630eadc71cad659f8819732a56d340bf1f1cda1ebca476539ab814ff6f4502cf59166d1fb882487bea29f5be1a16d205c5f54584fac535dcd36b8cab0901ece6b38d86464eed9b3957349e3535e357a9e153582ae75b7dfc65d8d1620bae16e6353a1633da3dca71e850fadf877c4715739d9", 16),
                mpz_class("9b5655304faba06b8b309d3ffc36eae0d5a0aaac7a1ce4cd27769042894df727ff27a049c76e5fa5b31b11ded8364888f942aba9a0ee1d7283c46fce032a628c31f0bde5b40596d5e3b2c090960f7b1ef83e8e13cca76a0a6da3d6988aced401db298d6fa930f9c926b30a82fe593e5a9597563388729f2a03cc4d752acb0ab5323628ea29534fbbb8e3c36260b976627a0493cb0f1c314b1f2d733014ec15239a596e7ab60011c632bb7964d996a79583810833ae1c55914ab0ee363fe5709c5f18ebf4261aabd44b8bf839d1ed4657b147bbefb5d862cefa3018e8fc60b63d62131526a9500c0cedfbe3e40f97e6e9720415fb1ff5e0db2f940cf7248f757b", 16),
                mpz_class("874473f965807cb47c48ebe1ee4298e8892f0a3a442472b7a302c66192886bc5c5348ec2d90d3d331bb2e6a70fe11faf2487dcc17d68ba0b9c0f7c45cf7b6d0036db459b3c3a90c33c3944a76d17d5514e9a232439a8c4f1de953d55f746086adeefdd42c2dd1582283f903df2e5724a0201b425c7554f0717a6d5ad97ad59fe3595d12e33151d16e7d2ed99e1f75b0ff17a4454b8ace6b5035901844af2d59893123eaa86d2598943863a0aec47da6c2b92f1a25fe977f3c777dbfe33b37defbce4dc4494ed75a1881f37f18659cefe9dd9b1cf99d5e51907771194d3566736abb5952e6440a75fa2593a52742fe62e8eb7bef16b36ae405e9c8146627b2f69", 16),
                mpz_class("dd402da0ce691bb657576481f1c93b8ebef35d7ae850e39a5e536fb60624ce2407bc7262db4fd828a49383e9002b826476e57d8d3b05f4a4d083a7eb00a10ba2cbfde468a64905f12ce195300d199e08093cd94e9eb5776cbdfe88e882cb68ea8f44559cf57f58c34c2b0735f039b7de98e6fe7fe6e467f2b05856c4d8a83b18d4fafbf64213dfb3d78ed509fae1889d576291432c9eb9b67a1d1c95f9f2e2149972247a89a5890560bd569065f2c4556a28def6e62d6f124e20fa42ec110662ead4eaf13b5bdc978b5d2a97fcb418205b08e4f74ae004d2e1a66738d40cad26c9bc5b82acd1ebf68c63075aa1a28f1431af5d91973159204948ffcd712ddf85", 16),
        },
        .expectedRemaindersVector = {
                mpz_class("de8d8894af94df6b6950c8cc544a3a9ffb5d8a7b5e3da2dfd0f10d556fd8ccb5f3842793b438b20f8aa7d51296b8fcb275ec71aae73b4daba951a819870c6b0c04487d6624b58bde2fac4008aff1b88bf3036e583dc9f33a03ef8f87f70a7275c22a8b902d64fcb02935c20958aed6e6bd0f89dea8deb8bda5ebd9662c954147", 16),
                1, 1,
                mpz_class("de8d8894af94df6b6950c8cc544a3a9ffb5d8a7b5e3da2dfd0f10d556fd8ccb5f3842793b438b20f8aa7d51296b8fcb275ec71aae73b4daba951a819870c6b0c04487d6624b58bde2fac4008aff1b88bf3036e583dc9f33a03ef8f87f70a7275c22a8b902d64fcb02935c20958aed6e6bd0f89dea8deb8bda5ebd9662c954147", 16),
        }
};

std::vector<EgcdTestCaseType> egcdTestCases = {
        __CASE1, __CASE2, __CASE3, __CASE4, __CASE5, __CASE6
};


struct TgcdTestCaseStruct {
    uint primeCount;
    uint primeBits;
    std::vector< std::pair<uint, uint> > prodPairsVec;    // pairs 中所有数字都是不相同的
    TgcdTestCaseStruct(unsigned int pc, unsigned int pb, std::vector< std::pair<uint, uint> > pv) : primeCount(pc), primeBits(pb), prodPairsVec(std::move(pv)) {}
};

std::vector<TgcdTestCaseStruct> tgcdTestCases = {
        TgcdTestCaseStruct(4096u, 1024u, {std::make_pair(2u, 7u), std::make_pair(2000u, 1000u), std::make_pair(16u, 4095u)}),
        TgcdTestCaseStruct(2048u, 1024u, {std::make_pair(2u, 7u), std::make_pair(2000u, 1000u), std::make_pair(16u, 2047u)}),
        TgcdTestCaseStruct(1024u, 1024u, {std::make_pair(0u, 2u), std::make_pair(3u, 1023u)}),
        TgcdTestCaseStruct(512u, 1024u, {std::make_pair(0u, 5u), std::make_pair(3u, 511u)}),
        TgcdTestCaseStruct(512u, 512u, {std::make_pair(0u, 5u), std::make_pair(3u, 511u)}),
        TgcdTestCaseStruct(512u, 256u, {std::make_pair(0u, 5u), std::make_pair(3u, 511u)}),
};

#endif //KEYMININGALGORITHM_EFFICIENTLYGCDTESTCASES_H
