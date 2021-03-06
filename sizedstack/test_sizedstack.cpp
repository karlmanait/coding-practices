#include "sizedstack.cpp"
#include "gtest/gtest.h"

struct node
{
    int x;
    int y;
};

TEST(SizedStackTest, TestPushAndPop)
{
    SizedStack<node> ss(2);
    ss.push({1, 2});
    ss.push({12, 27});

    node n1 = ss.pop();
    EXPECT_EQ(n1.x, 12);
    EXPECT_EQ(n1.y, 27);

    ss.push({69, 420});

    node n2 = ss.pop();
    EXPECT_EQ(n2.x, 69);
    EXPECT_EQ(n2.y, 420);

    ss.push({322, 999});

    node n3 = ss.pop();
    EXPECT_EQ(n3.x, 322);
    EXPECT_EQ(n3.y, 999);

    node n4 = ss.pop();
    EXPECT_EQ(n4.x, 1);
    EXPECT_EQ(n4.y, 2);
}

TEST(SizedStackTest, TestPoppingEmptyStack)
{
    SizedStack<node> ss(2);
    ss.push({1, 2});

    node n = ss.pop();
    EXPECT_EQ(n.x, 1);
    EXPECT_EQ(n.y, 2);

    EXPECT_THROW({ss.pop();}, const char*);
}

TEST(SizedQueueTest, TestPushingFullStack)
{
    SizedStack<node> ss(2);
    ss.push({1, 2});
    ss.push({12, 27});

    EXPECT_THROW({ss.push({69, 420});}, const char*);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
