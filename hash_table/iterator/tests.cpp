#include "table.h"
#include "gtest/gtest.h"

typedef std::string Key;

struct Value {
  unsigned age = 0;
  unsigned weight = 0;
  friend bool operator==(const Value &a, const Value &b) {
    return a.age == b.age && a.weight == b.weight;
  }
};

class Hashtable : public ::testing::Test {
protected:
  HashTable<Key, Value> p, h;
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
  EXPECT_EQ(h["key"], Value({23, 177}));
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
  std::string a;
  int N = 1000;
  for (int i = 0; i < N; ++i) {
    a += "a";
    h.insert(a, {1, 1});
  }
  EXPECT_TRUE(h.size() == N);
  h.clear();
  EXPECT_TRUE(h.empty());
  N *= 2;
  a = "";
  for (int i = 0; i < N; ++i) {
    a += "a";
    h.insert(a, {1, 1});
  }
  EXPECT_TRUE(h.size() == N);
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
  const HashTable CONST = h;
  EXPECT_EQ(CONST.at("key"), Value({12, 100}));
  EXPECT_EQ(CONST.at("a"), Value({1, 3}));
  ASSERT_ANY_THROW(CONST.at("bob"));
  ASSERT_ANY_THROW(CONST.at("b"));
}
TEST_F(Hashtable, iterator) {
  h.insert("i", {12, 100});
  h.insert("p", {1, 3});
  h.insert("b", {8, 5});
  p.insert("c", {5, 8});
  p.insert("d", {0, 7});
  size_t count = 0;
  for (auto i = h.begin(); i != h.end(); i++) {
    ++count;
  }
  EXPECT_EQ(3, count);
  auto iter = p.begin();
  EXPECT_EQ(Value({0, 7}), (*iter).value);
  ++iter;
  EXPECT_EQ(Value({5, 8}), (*iter).value);
  p.erase("c");
  EXPECT_ANY_THROW(*iter);
  count = 0;
  for (auto i = p.begin(); i != p.end(); ++i) {
    ++count;
  }

  EXPECT_EQ(1, count);
  count = 0;
  std::string a;
  int N = 1000;
  for (int i = 0; i < N; ++i) {
    a += "a";
    h.insert(a, {1, 1});
  }
  for (auto i = h.begin(); i != h.end(); ++i) {
    ++count;
  }
  EXPECT_EQ(N + 3, count);
}