#include "priorityqueue.cpp"
#include "gtest/gtest.h"

struct node
{
    int x;
    int y;
};

TEST(PriorityQueueTest, TestPushAndPop)
{
    PriorityQueue<node> pq;
    node n;
    pq.push(999, {12, 27});
    pq.push(42069, {69, 420});
    pq.push(-10, {322, 999});
    pq.push(0, {1, 2});
    pq.push(555, {8, 18});
    pq.push(444, {9, 9});

    n = pq.pop(); // 42069
    EXPECT_EQ(n.x, 69);
    EXPECT_EQ(n.y, 420);

    n = pq.pop(); // 999
    EXPECT_EQ(n.x, 12);
    EXPECT_EQ(n.y, 27);

    n = pq.pop(); // 555
    EXPECT_EQ(n.x, 8);
    EXPECT_EQ(n.y, 18);

    n = pq.pop(); // 444
    EXPECT_EQ(n.x, 9);
    EXPECT_EQ(n.y, 9);

    n = pq.pop(); // 0
    EXPECT_EQ(n.x, 1);
    EXPECT_EQ(n.y, 2);

    n = pq.pop(); // -10
    EXPECT_EQ(n.x, 322);
    EXPECT_EQ(n.y, 999);
}

TEST(PriorityQueueTest, TestPoppingEmptyQueue)
{
    PriorityQueue<node> pq;
    pq.push((1 << 31), {12, 27});

    node n = pq.pop();
    EXPECT_EQ(n.x, 12);
    EXPECT_EQ(n.y, 27);

    EXPECT_THROW({pq.pop();}, const char*);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
