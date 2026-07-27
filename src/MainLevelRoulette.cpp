#include "MainLevelRoulette.hpp"

using namespace geode::prelude;

void MainLevelRoulette::loadCurrentLevel() {
    int id = currentLevelID();
    if (id < 0) return;

    // `getMainLevel(id, unlockIfNeeded)` pulls one of the 22 built-in levels.
    // We force-unlock so the roulette can hand you a level you haven't
    // beaten yet (its stars/orbs will just show as locked-completed state).
    auto level = GameLevelManager::sharedState()->getMainLevel(id, true);
    if (!level) {
        log::error("MainLevelRoulette: could not load main level id {}", id);
        return;
    }

    auto scene = PlayLayer::scene(level, false, false);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
}
