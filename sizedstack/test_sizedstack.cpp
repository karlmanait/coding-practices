#include "sizedstack.cpp"
#include "gtest/gtest.h"

struct node
{
    int x;
    int y;
};

TEST(SizedStackTest, TestPushAndPop)
{
    SizedStack<node> ss(20);
    ss.push({1, 2});
    ss.push({69, 420});

    node n1 = ss.pop();
    EXPECT_EQ(n1.x, 69);
    EXPECT_EQ(n1.y, 420);

    ss.push({322, 999});

    node n2 = ss.pop();
    EXPECT_EQ(n2.x, 322);
    EXPECT_EQ(n2.y, 999);

    node n3 = ss.pop();
    EXPECT_EQ(n3.x, 1);
    EXPECT_EQ(n3.y, 2);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
