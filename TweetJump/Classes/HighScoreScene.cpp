//
//  HighScoreScene.cpp
//  TweetJump-mobile
//
//  Created by Carlos Eduardo Pinan Indacochea on 11/5/19.
//

#include "HighScoreScene.hpp"

using namespace cocos2d;

// POPUP
PlayerPopUp::PlayerPopUp() {
    _popUpLayer = LayerColor::create(Color4B(0, 0, 255, 200));
    _popUpLayer->setContentSize(Size(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.5f));
    _popUpLayer->setPosition(Vec2(25, 120));
    
    auto title = Label::createWithTTF("Change Player", "Arial", 18.0f, Size(250, 40), TextHAlignment::RIGHT, TextVAlignment::CENTER);
    title->setColor(Color3B::BLACK);
    title->setPosition(Vec2(SCREEN_WIDTH * 0.2f, 200));
    
    auto saveLabel = Label::createWithTTF("Save", "Arial", 20.0f);
    auto saveItem = MenuItemLabel::create(saveLabel, CC_CALLBACK_1(PlayerPopUp::_saveAction, this));
    saveItem->setPosition(Vec2(50, 50));
    
    auto cancelLabel = Label::createWithTTF("Cancel", "Arial", 20.0f);
    auto cancelItem = MenuItemLabel::create(cancelLabel, CC_CALLBACK_1(PlayerPopUp::_cancelAction, this));
    cancelItem->setPosition(Vec2(200, 50));
    
    auto menu = Menu::create(saveItem, cancelItem, NULL);
    menu->setPosition(Vec2::ZERO);
}

void PlayerPopUp::_saveAction(Ref* sender) {
    
}

void PlayerPopUp::_cancelAction(Ref* sender) {
    
}

// LAYER
HighScoreLayer::HighScoreLayer(int lastScore) {
    _lastScore = lastScore;
}

// SCENE
Scene* HighScoreScene::createScene(int lastScore) {
    auto scene = Scene::create();
    auto layer = new HighScoreLayer(lastScore);
    scene->addChild(layer);
    layer->autorelease();
    return scene;
}

