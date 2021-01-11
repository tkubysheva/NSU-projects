#pragma once
#include "strategies/all-defect.h"
#include "strategies/change-choice.h"
#include "strategies/forgive-revenge.h"
#include "strategies/poor-trusting-fool.h"
#include "strategies/random.h"
#include "strategies/soft-tit-for-tat.h"
#include "strategies/tough-tit-for-tat.h"

Strategy *createAllD() {
    return new AllD;
}
Strategy *createCChoice() {
    return new CChoice;
}
Strategy *createFR() {
    return new FR;
}
Strategy *createPTF() {
    return new PTF;
}
Strategy *createRand() {
    return new Rand;
}
Strategy *createSTFT() {
    return new STFT;
}
Strategy *createTTFT() {
    return new TTFT;
}
void sign_up_for_strategies(){
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("all-defect", createAllD);
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("change-choice", createCChoice);
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("forgive-revenge", createFR);
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("poor-trusting-fool", createPTF);
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("random", createRand);
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("soft-tit-for-tat", createSTFT);
    Factory<Strategy, std::string, Strategy *(*) ()>::getInstance()->addCreator("tough-tit-for-tat", createTTFT);
}