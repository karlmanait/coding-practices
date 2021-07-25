#include "sizedqueue.cpp"
#include "gtest/gtest.h"

struct node
{
    int x;
    int y;
};

TEST(SizedQueueTest, TestPushAndPop)
{
    SizedQueue<node> sq(2);
    sq.push({1, 2});
    sq.push({12, 27});

    node n1 = sq.pop();
    EXPECT_EQ(n1.x, 1);
    EXPECT_EQ(n1.y, 2);

    sq.push({69, 420});

    node n2 = sq.pop();
    EXPECT_EQ(n2.x, 12);
    EXPECT_EQ(n2.y, 27);

    sq.push({322, 999});

    node n3 = sq.pop();
    EXPECT_EQ(n3.x, 69);
    EXPECT_EQ(n3.y, 420);

    node n4 = sq.pop();
    EXPECT_EQ(n4.x, 322);
    EXPECT_EQ(n4.y, 999);
}

TEST(SizedQueueTest, TestPoppingEmptyQueue)
{
    SizedQueue<node> sq(2);
    sq.push({1, 2});

    node n = sq.pop();
    EXPECT_EQ(n.x, 1);
    EXPECT_EQ(n.y, 2);

    EXPECT_THROW({sq.pop();}, const char*);
}

TEST(SizedQueueTest, TestPushingFullQueue)
{
    SizedQueue<node> sq(2);
    sq.push({1, 2});
    sq.push({12, 27});

    EXPECT_THROW({sq.push({69, 420});}, const char*);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
