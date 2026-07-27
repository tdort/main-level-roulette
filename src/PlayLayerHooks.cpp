#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "MainLevelRoulette.hpp"

using namespace geode::prelude;

class $modify(RoulettePlayLayer, PlayLayer) {

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        if (MainLevelRoulette::get()->isActive()) {
            auto winSize = CCDirector::sharedDirector()->getWinSize();

            auto label = CCLabelBMFont::create(
                fmt::format(
                    "Roulette {}/{} - reach {}% to advance",
                    MainLevelRoulette::get()->currentPosition(),
                    MainLevelRoulette::get()->totalLevels(),
                    static_cast<int>(MainLevelRoulette::PASS_THRESHOLD)
                ).c_str(),
                "bigFont.fnt"
            );
            label->setScale(0.35f);
            label->setPosition({ winSize.width / 2, winSize.height - 20.f });
            label->setZOrder(1000);
            label->setID("main-level-roulette-hud"_spr);
            this->addChild(label);
        }

        return true;
    }

    // Fires when the player dies. We check progress *after* letting the
    // original run, since GD's own death handling (particles, restart
    // countdown, etc.) still needs to happen normally.
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        PlayLayer::destroyPlayer(player, object);

        if (!MainLevelRoulette::get()->isActive()) return;

        float percent = this->getCurrentPercent();
        if (percent >= MainLevelRoulette::PASS_THRESHOLD) {
            // Small delay so the death animation/UI has a moment to play
            // before we yank the scene away.
            this->runAction(CCSequence::create(
                CCDelayTime::create(0.5f),
                CCCallFunc::create(this, callfunc_selector(RoulettePlayLayer::onRouletteAdvance)),
                nullptr
            ));
        }
    }

    void levelComplete() {
        PlayLayer::levelComplete();

        if (MainLevelRoulette::get()->isActive()) {
            this->runAction(CCSequence::create(
                CCDelayTime::create(1.0f),
                CCCallFunc::create(this, callfunc_selector(RoulettePlayLayer::onRouletteComplete)),
                nullptr
            ));
        }
    }

    void onRouletteAdvance() {
        MainLevelRoulette::get()->advance();
    }

    void onRouletteComplete() {
        MainLevelRoulette::get()->onLevelComplete();
    }
};
