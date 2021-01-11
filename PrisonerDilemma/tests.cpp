#include <gtest/gtest.h>
#include "detailed_mode.h"
#include "factory.h"
#include "gameplay_creator.h"
#include <memory>
#include "strategies/all-defect.h"
#include "strategies/change-choice.h"
#include "strategies/forgive-revenge.h"
#include "strategies/poor-trusting-fool.h"
#include "strategies/soft-tit-for-tat.h"
#include "strategies/tough-tit-for-tat.h"

class FirstTest : public ::testing::Test {
protected:
    std::shared_ptr<Strategy> InitialStr(const std::string &mode_name) {
        std::shared_ptr<Strategy> game(Factory<Strategy, std::string,
                Strategy *(*) ()>::getInstance()
                                               ->makeObject(mode_name));
        return game;
    }

};
TEST_F(FirstTest, trow) {
    char C[] = "test";
    char a[] = "poor-trusting-fool", b[] = "all-defect", c[] = "random", d[] = "asdfg",
         e[] = "--mode=fast", f[] = "--mode=fff", g[] = "--mote=fast", h[] = "--mode=detailed", k[] = "soft-tit-for-tat";
    char *argv_0[] = {C, a, a, c};
    EXPECT_ANY_THROW(Gameplay m1(4, argv_0));
    char *argv_2[] = {C, d, a, c};
    EXPECT_NO_THROW(Gameplay m2(4, argv_2));
    Gamer gamer;
    gamer.Test = true;
    gamer.Button = {13, 13, 13, 13, 13, 13, 13, 'q'};
    EXPECT_NO_THROW(Gameplay m3(4, argv_2));
    char *argv_1[] = {C, a, c, e};
    EXPECT_ANY_THROW(Gameplay m4(4, argv_1));
    argv_1[3] = f;
    EXPECT_ANY_THROW(Gameplay m5(4, argv_1));
    char *argv_3[] = {C, a, c, b};
    EXPECT_NO_THROW(Gameplay m6(4, argv_3));
    char *argv_4[] = {C, a, b, c, k, h};
    EXPECT_NO_THROW(Gameplay m7(4, argv_4));
    char *argv_5[] = {C, a, b, c, g};
    EXPECT_NO_THROW(Gameplay m8(4, argv_5));
}


TEST_F(FirstTest, strategy) {

    std::vector<std::vector<CHOICE>> history;
    {
        AllD s;
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(s.choice(history), DEFECT);
        }
    }
    {
        PTF s;
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(s.choice(history), COOPERATE);
        }
    }
    {
        TTFT s;
        history.push_back({COOPERATE, COOPERATE, COOPERATE});
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(s.choice(history), COOPERATE);
        }
    }
    {
        TTFT s;
        history.push_back({DEFECT, DEFECT, DEFECT});
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(s.choice(history), DEFECT);
        }
    }
    {
        STFT s;
        history.push_back({COOPERATE, COOPERATE, COOPERATE});
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(s.choice(history), COOPERATE);
        }
    }
    {
        STFT s;
        history.push_back({DEFECT, DEFECT, DEFECT});
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(s.choice(history), DEFECT);
        }
    }
    {
        FR s;
        history.push_back({COOPERATE, COOPERATE, COOPERATE});
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(s.choice(history), COOPERATE);
        }
        history.push_back({DEFECT, DEFECT, DEFECT});
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(s.choice(history), DEFECT);
        }
        history.push_back({COOPERATE, COOPERATE, COOPERATE});
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(s.choice(history), COOPERATE);
        }
    }
    {
        CChoice s;
        history.push_back({COOPERATE, COOPERATE, COOPERATE});
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(s.choice(history), COOPERATE);
            history.push_back({COOPERATE, COOPERATE, COOPERATE});
        }

    }
}
