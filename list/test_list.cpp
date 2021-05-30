#include "list.cpp"
#include "gtest/gtest.h"

struct node
{
    int x;
    int y;
};

TEST(ListTest, TestInsert)
{
    List<node> list;
    list.insert({1, 2});
    list.insert({69, 420});
    list.insert({322, 999});
    // Iterate
    int ctr = 0;
    node result[3];
    for (List<node>::iterator* it = list.begin(); it != list.end(); it = it->next)
    {
        result[ctr] = it->data;
        ctr++;
    }
    EXPECT_EQ(result[0].x, 1);
    EXPECT_EQ(result[0].y, 2);
    EXPECT_EQ(result[1].x, 69);
    EXPECT_EQ(result[1].y, 420);
    EXPECT_EQ(result[2].x, 322);
    EXPECT_EQ(result[2].y, 999);
}

TEST(ListTest, Test1stRemoval)
{
    List<node> list;
    list.insert({1, 2});
    list.insert({69, 420});
    list.insert({322, 999});
    // Remove
    list.remove(list.begin());
    // Iterate
    int ctr = 0;
    node result[2];
    for (List<node>::iterator* it = list.begin(); it != list.end(); it = it->next)
    {
        result[ctr] = it->data;
        ctr++;
    }
    EXPECT_EQ(result[0].x, 69);
    EXPECT_EQ(result[0].y, 420);
    EXPECT_EQ(result[1].x, 322);
    EXPECT_EQ(result[1].y, 999);
}

TEST(ListTest, Test2ndRemoval)
{
    List<node> list;
    list.insert({1, 2});
    list.insert({69, 420});
    list.insert({322, 999});
    // Remove
    list.remove(list.begin()->next);
    // Iterate
    int ctr = 0;
    node result[2];
    for (List<node>::iterator* it = list.begin(); it != list.end(); it = it->next)
    {
        result[ctr] = it->data;
        ctr++;
    }
    EXPECT_EQ(result[0].x, 1);
    EXPECT_EQ(result[0].y, 2);
    EXPECT_EQ(result[1].x, 322);
    EXPECT_EQ(result[1].y, 999);
}

TEST(ListTest, Test3rdRemoval)
{
    List<node> list;
    list.insert({1, 2});
    list.insert({69, 420});
    list.insert({322, 999});
    // Remove
    list.remove(list.begin()->next->next);
    // Iterate
    int ctr = 0;
    node result[2];
    for (List<node>::iterator* it = list.begin(); it != list.end(); it = it->next)
    {
        result[ctr] = it->data;
        ctr++;
    }
    EXPECT_EQ(result[0].x, 1);
    EXPECT_EQ(result[0].y, 2);
    EXPECT_EQ(result[1].x, 69);
    EXPECT_EQ(result[1].y, 420);
}

TEST(ListTest, TestAllRemoval)
{
    List<node> list;
    list.insert({1, 2});
    list.insert({69, 420});
    list.insert({322, 999});
    // Remove
    list.remove(list.begin());
    list.remove(list.begin());
    list.remove(list.begin());
    // Iterate
    for (List<node>::iterator* it = list.begin(); it != list.end(); it = it->next)
    {
        FAIL();
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
