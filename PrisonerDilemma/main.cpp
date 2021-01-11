
#include "gameplay_creator.h"

int main(int argc, char *argv[]) {
    Gameplay m(argc, argv);
    m.creator()->play();
}
