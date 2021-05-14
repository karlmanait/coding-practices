#include "sizedqueue.cpp"
#include "gtest/gtest.h"

struct node
{
    int x;
    int y;
};

TEST(SizedQueueTest, TestPushAndPop)
{
    SizedQueue<node> sq(20);
    sq.push({1, 2});
    sq.push({69, 420});

    node n1 = sq.pop();
    EXPECT_EQ(n1.x, 1);
    EXPECT_EQ(n1.y, 2);

    sq.push({322, 999});

    node n2 = sq.pop();
    EXPECT_EQ(n2.x, 69);
    EXPECT_EQ(n2.y, 420);

    node n3 = sq.pop();
    EXPECT_EQ(n3.x, 322);
    EXPECT_EQ(n3.y, 999);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
