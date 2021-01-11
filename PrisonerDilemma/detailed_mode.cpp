#include "detailed_mode.h"
#include "factory.h"

namespace {
    PlayMode *createDetailedMode() {
        return new Detailed;
    }
    bool gen() {
        Factory<PlayMode, std::string, PlayMode *(*) ()>::getInstance()->addCreator("detailed", createDetailedMode);
        return true;
    }
    static bool d = gen();
}// namespace


void Detailed::play(Gamer gamer) {
    Initial(names_, configs);
    while (!gamer.Exit()) {
        OneGame(true);
    }
}
