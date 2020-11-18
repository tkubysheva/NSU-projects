#include "detailed_mode.h"
#include "factory.h"
#include "mode.h"
#include "table.h"
#include "gameplay_creator.h"
#include <gtest/gtest.h>
#include <memory>

class FirstTest : public ::testing::Test {
protected:
    std::shared_ptr<PlayMode> InitialMode(const std::string &mode_name) {
        std::shared_ptr<PlayMode> game(Factory<PlayMode, std::string,
                                               PlayMode *(*) ()>::getInstance()
                                               ->makeObject(mode_name));
        return game;
    }

};
TEST_F(FirstTest, detailed) {
    char C[] = "test";
    char a[]= "poor-trusting-fool", b[]= "all-defect", c[] = "random", d[] = "asdfg",
         e[] = "--mode=fast", f[] ="--mode=fff", g[]= "--mote=fast", h[] = "--mode=detailed", k[] = "soft-tit-for-tat";
    char* argv_0[] = {C,a, a, c};
    EXPECT_ANY_THROW(creator(4, argv_0));
    char* argv_2[] = {C,d, a, c};
    EXPECT_NO_THROW(creator(4, argv_2));
    Mode m = creator(4, argv_2);
    EXPECT_ANY_THROW(m.game->play(m.matrix, m.names, m.step, m.configs_dir));
    char* argv_1[] = {C,a, c, e};
    EXPECT_ANY_THROW(creator(4, argv_1));
    argv_1[3] = f;
    EXPECT_ANY_THROW(creator(4, argv_1));
    char* argv_3[] = {C,a, c, b};
    EXPECT_NO_THROW(creator(4, argv_3));
    m = creator(4, argv_3);
    Gamer gamer;
    gamer.Test = true;
    gamer.Button = {13, 13, 13, 13, 13, 13, 13, 'q'};
    EXPECT_NO_THROW(m.game->play(m.matrix, m.names, m.step, m.configs_dir, gamer));
    EXPECT_EQ(m.game->steps_counter, 8);
    char* argv_4[] = {C, a, b, c, k, h};
    EXPECT_ANY_THROW(creator(4, argv_4));
    char* argv_5[] = {C, a, b, c, g};
    EXPECT_ANY_THROW(creator(4, argv_5));
}


TEST_F(FirstTest, g) {
    //char* argv[] = {"poor-trusting-fool", "poor-trusting-fool", "random"};
    //EXPECT_ANY_THROW(creator(5, argv));
}


/*
TEST_F(FirstTest, detailed) {
    auto names = std::set<std::string>{"forgive-revenge", "soft-tit-for-tat", "poor-trusting-fool"};
    std::shared_ptr<PlayMode> game = InitialMode("detailed");
    game->gamer.Test = true;
    game->gamer.Button = {13, 13, 13, 13, 13, 13, 13, 'q'};
    MATRIX_ m = CreateMatrix("");
    game->play(m, names, 1, "");
    EXPECT_EQ(game->steps_counter, 7);
    EXPECT_EQ(game->str[0]->score, game->str[1]->score);
    EXPECT_EQ(game->str[2]->score, game->str[1]->score);
    EXPECT_EQ(game->str[0]->score, 7 * 7);
}*/