#include "../table.cpp"
#include "gtest/gtest.h"
namespace {

class Hashtable : public ::testing::Test {
protected:
  HashTable p, h;
};
TEST_F(Hashtable, insert_test) {
  p.insert("key", {12, 100});
  EXPECT_FALSE(p.insert("key", {12, 100}));
}
TEST_F(Hashtable, size_test) {
  p.insert("bbo", {12, 100});
  p.insert("bob", {12, 157});
  EXPECT_EQ(2, p.size());
  p.insert("bbo", {19, 167});
  EXPECT_EQ(2, p.size());
  p.insert("bo", {1, 17});
  EXPECT_EQ(3, p.size());
}
TEST_F(Hashtable, erase_test) {
  h.insert("a", {12, 100});
  h.insert("bob", {12, 157});
  EXPECT_EQ(2, h.size());
  EXPECT_TRUE(h.erase("bob"));
  EXPECT_EQ(1, h.size());
  EXPECT_FALSE(h.erase("b"));
  EXPECT_FALSE(h.erase("bob"));
  EXPECT_TRUE(h.erase("a"));
  EXPECT_EQ(0, h.size());
}
TEST_F(Hashtable, operator1_test) {
  h.insert("key", {12, 100});
  h["key"] = {23, 177};
  EXPECT_EQ(h["key"], Value(23, 177));
  EXPECT_EQ(h["i"], Value());
}

TEST_F(Hashtable, operator2_test) {
  h.insert("a", {1, 3});
  h.insert("b", {8, 5});
  p.insert("a", {1, 3});
  p.insert("b", {8, 5});
  EXPECT_EQ(h, p);
  p.insert("key", {5, 8});
  EXPECT_TRUE(h != p);
  h.insert("bbb", {8, 5});
  EXPECT_FALSE(h == p);
}

TEST_F(Hashtable, resize_test) {
  h.insert("key", {12, 100});
  h.insert("a", {1, 3});
  h.insert("b", {8, 5});
  EXPECT_EQ(h.size(), 3);
  EXPECT_TRUE(h.contains("key"));
  EXPECT_TRUE(h.contains("a"));
  EXPECT_TRUE(h.contains("b"));
  h.insert("p", {12, 100});
  h.insert("c", {1, 3});
  EXPECT_EQ(h.size(), 5);
  EXPECT_TRUE(h.contains("key"));
  EXPECT_TRUE(h.contains("a"));
  EXPECT_TRUE(h.contains("b"));
  EXPECT_TRUE(h.contains("p"));
  EXPECT_TRUE(h.contains("c"));
  h.insert("d", {8, 5});
  EXPECT_EQ(h.size(), 6);
  EXPECT_TRUE(h.contains("key"));
  EXPECT_TRUE(h.contains("a"));
  EXPECT_TRUE(h.contains("b"));
  EXPECT_TRUE(h.contains("p"));
  EXPECT_TRUE(h.contains("c"));
  EXPECT_TRUE(h.contains("d"));
}
TEST_F(Hashtable, copy_test) {
  h.insert("key", {12, 100});
  h.insert("a", {1, 3});
  h.insert("b", {8, 5});
  p = h;
  EXPECT_TRUE(h == p);
  h = h;
  EXPECT_TRUE(h == h);
  HashTable o = h;
  EXPECT_TRUE(o == h);
  h.insert("c", {8, 5});
  p = o = h;
  EXPECT_TRUE(o == h);
  EXPECT_TRUE(h == p);
}

TEST_F(Hashtable, clear_test) {
  h.insert("key", {12, 100});
  h.insert("a", {1, 3});
  h.insert("b", {8, 5});
  h.clear();
  EXPECT_EQ(h.size(), 0);
  EXPECT_TRUE(h.empty());
}

TEST_F(Hashtable, contains_test) {
  h.insert("key", {12, 100});
  h.insert("a", {1, 3});
  h.insert("bbb", {7, 9});
  EXPECT_TRUE(h.contains("key"));
  EXPECT_TRUE(h.contains("a"));
  EXPECT_TRUE(h.contains("bbb"));
  EXPECT_FALSE(h.contains("b"));
  EXPECT_FALSE(h.contains("c"));
  h.erase("a");
  EXPECT_FALSE(h.contains("a"));
}

TEST_F(Hashtable, swap_test) {
  h.insert("i", {12, 100});
  h.insert("a", {1, 3});
  h.insert("b", {8, 5});
  p.insert("c", {5, 8});
  p.insert("d", {0, 7});
  EXPECT_EQ(3, h.size());
  EXPECT_EQ(2, p.size());
  p.swap(h);
  EXPECT_TRUE(h.contains("c"));
  EXPECT_TRUE(h.contains("d"));
  EXPECT_FALSE(h.contains("i"));
  EXPECT_FALSE(h.contains("a"));
  EXPECT_FALSE(h.contains("b"));
  EXPECT_FALSE(p.contains("c"));
  EXPECT_FALSE(p.contains("d"));
  EXPECT_TRUE(p.contains("i"));
  EXPECT_TRUE(p.contains("a"));
  EXPECT_TRUE(p.contains("b"));
  EXPECT_EQ(2, h.size());
  EXPECT_EQ(3, p.size());
}
TEST_F(Hashtable, at_test) {
  h.insert("key", {12, 100});
  h.insert("a", {1, 3});
  EXPECT_EQ(h.at("key"), Value({12, 100}));
  EXPECT_EQ(h.at("a"), Value({1, 3}));
  ASSERT_ANY_THROW(h.at("bob"));
  ASSERT_ANY_THROW(h.at("b"));
}
} // namespace
