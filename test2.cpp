#include "../table.cpp"
#include "test1.cpp"
#include "gtest/gtest.h"
namespace {

  class Hashtable: public ::testing::Test {
  protected:
    void SetUp() override {
      p.insert("key", {12, 100});
    }

    HashTable p;
  };

TEST_F(Hashtable, test){
  EXPECT_EQ(1, p.size());
}
} // namespace
