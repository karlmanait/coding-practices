#include "bitset.cpp"
#include "gtest/gtest.h"

TEST(BitsetTest, SetBitUsingBool)
{
    Bitset bs(30);
    bs.set(0, true);
    bs.set(3, false);
    bs.set(5, true);
    bs.set(29, true);

    EXPECT_EQ(bs[0], true);
    EXPECT_EQ(bs[3], false);
    EXPECT_EQ(bs[5], true);
    EXPECT_EQ(bs[29], true);

    bs.set(0, false);
    bs.set(3, true);
    EXPECT_EQ(bs[0], false);
    EXPECT_EQ(bs[3], true);
}

TEST(BitsetTest, SetBitUsingInt)
{
    Bitset bs(20);
    bs.set(8, 1);
    bs.set(9, 1);
    bs.set(10, 0);

    EXPECT_EQ(bs[8], 1);
    EXPECT_EQ(bs[9], 1);
    EXPECT_EQ(bs[10], 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
