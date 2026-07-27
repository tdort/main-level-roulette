#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "MainLevelRoulette.hpp"

using namespace geode::prelude;

class $modify(RouletteMenuLayer, MenuLayer) {

    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) return true;

        auto spr = ButtonSprite::create("Roulette");
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(RouletteMenuLayer::onStartRoulette)
        );
        btn->setID("main-level-roulette-button"_spr);
        menu->addChild(btn);
        menu->updateLayout();

        return true;
    }

    void onStartRoulette(CCObject*) {
        MainLevelRoulette::get()->start();
    }
};
