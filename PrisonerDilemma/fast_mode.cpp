#include "fast_mode.h"
#include "factory.h"

namespace {
    PlayMode *createFastMode() {
        return new Fast;
    }
    bool gen() {
        Factory<PlayMode, std::string, PlayMode *(*) ()>::getInstance()->addCreator("fast", createFastMode);
        return true;
    }
    static bool d = gen();
}// namespace


void Fast::play(Gamer gamer) {
    Initial(names_, configs);
    for (size_t i = 0; i < steps; ++i) {
        OneGame();
    }
    print.fast();
}
