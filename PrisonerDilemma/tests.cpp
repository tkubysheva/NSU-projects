#include "detailed_mode.h"
#include "factory.h"
#include "mode.h"
#include "table.h"
#include "gtest/gtest.h"
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
}