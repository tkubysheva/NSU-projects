#include "detailed_mode.h"
#include "factory.h"
#include "gameplay_creator.h"
#include <gtest/gtest.h>
#include <memory>

class FirstTest : public ::testing::Test {
protected:
};
TEST_F(FirstTest, trow) {
    char C[] = "test";
    char a[] = "poor-trusting-fool", b[] = "all-defect", c[] = "random", d[] = "asdfg",
         e[] = "--mode=fast", f[] = "--mode=fff", g[] = "--mote=fast", h[] = "--mode=detailed", k[] = "soft-tit-for-tat";
    char *argv_0[] = {C, a, a, c};
    Gameplay m1(4, argv_0);
    EXPECT_ANY_THROW(m1.creator());
    char *argv_2[] = {C, d, a, c};
    Gameplay m2(4, argv_2);
    EXPECT_NO_THROW(m2.creator());
    Gamer gamer;
    gamer.Test = true;
    gamer.Button = {13, 13, 13, 13, 13, 13, 13, 'q'};
    Gameplay m3(4, argv_2);
    EXPECT_ANY_THROW(m3.creator()->play(gamer));
    char *argv_1[] = {C, a, c, e};
    Gameplay m4(4, argv_1);
    EXPECT_ANY_THROW(m4.creator());
    argv_1[3] = f;
    Gameplay m5(4, argv_1);
    EXPECT_ANY_THROW(m5.creator());
    char *argv_3[] = {C, a, c, b};
    Gameplay m6(4, argv_3);
    EXPECT_NO_THROW(m6.creator());
    EXPECT_NO_THROW(m6.creator()->play(gamer));
    char *argv_4[] = {C, a, b, c, k, h};
    Gameplay m7(4, argv_4);
    EXPECT_ANY_THROW(m7.creator());
    char *argv_5[] = {C, a, b, c, g};
    Gameplay m8(4, argv_5);
    EXPECT_ANY_THROW(m8.creator());
}
