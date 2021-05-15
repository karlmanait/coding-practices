#include "hashtable.cpp"
#include "gtest/gtest.h"

struct node
{
    int x;
    int y;
};

TEST(HashtableTest, TestSettingValue)
{
    Hashtable<node> ht = Hashtable<node>();
    char key1[] = "my-first-key";
    char key2[] = "123456789";
    char key3[] = "!@#?";
    ht.set(key1, {12, 27});
    ht.set(key2, {69, 420});
    ht.set(key3, {18, 9});

    EXPECT_EQ(ht[key1].x, 12);
    EXPECT_EQ(ht[key1].y, 27);
    EXPECT_EQ(ht[key2].x, 69);
    EXPECT_EQ(ht[key2].y, 420);
    EXPECT_EQ(ht[key3].x, 18);
    EXPECT_EQ(ht[key3].y, 9);
}

TEST(HashtableTest, TestSettingValueOnTheSameKey)
{
    Hashtable<node> ht = Hashtable<node>();
    char key[] = "very-long-key-name-will-still-work-properly!!!";

    ht.set(key, {12, 27});
    EXPECT_EQ(ht[key].x, 12);
    EXPECT_EQ(ht[key].y, 27);

    ht.set(key, {69, 420});
    EXPECT_EQ(ht[key].x, 69);
    EXPECT_EQ(ht[key].y, 420);

    ht.set(key, {18, 9});
    EXPECT_EQ(ht[key].x, 18);
    EXPECT_EQ(ht[key].y, 9);
}

TEST(HashtableTest, TestUsingInvalidKey)
{
    Hashtable<node> ht = Hashtable<node>();
    char valid_key[] = "valid-key";
    char invalid_key[] = "invalid-key";

    ht.set(valid_key, {12, 27});
    EXPECT_EQ(ht[valid_key].x, 12);
    EXPECT_EQ(ht[valid_key].y, 27);

    EXPECT_THROW({ht[invalid_key];}, const char*);

}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
