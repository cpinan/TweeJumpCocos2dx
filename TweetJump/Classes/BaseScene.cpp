//
//  BaseScene.cpp
//  TweetJump-mobile
//
//  Created by Carlos Eduardo Pinan Indacochea on 11/5/19.
//

#include "BaseScene.hpp"
#include "GameConfig.h"

using namespace cocos2d;

BaseScene::BaseScene() {
    arc4random();
    
    auto batchNode = SpriteBatchNode::create(SPRITE_SHEET, SPRITE_SHEET_SIZE);
    batchNode->setAnchorPoint(Vec2::ZERO);
    addChild(batchNode, -1, kSpriteManager);
    
    auto background = Sprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    batchNode->addChild(background);
    background->setPosition(Vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f));
    
    initClouds();
}

void BaseScene::initCloud() {
    Rect cloudsRect;
    
    int randValue = (int) random(0, 1) * 3;
    if(randValue == 1)
        cloudsRect = Rect(336, 16, 256, 108);
    else if(randValue == 2)
        cloudsRect = Rect(336, 128, 257, 110);
    else
        cloudsRect = Rect(336, 240, 252, 119);
    
    auto batchNode = getChildByTag<SpriteBatchNode*>(kSpriteManager);
    auto cloud = Sprite::createWithTexture(batchNode->getTexture(), cloudsRect);
    batchNode->addChild(cloud, 3, currentCloudTag);
    cloud->setOpacity(128);
}

void BaseScene::initClouds() {
    currentCloudTag = kCloudsStartTag;
    while(currentCloudTag < kCloudsStartTag + K_NUM_CLOUDS) {
        initCloud();
        currentCloudTag++;
    }
    resetClouds();
}

void BaseScene::resetCloud() {
    auto batchNode = getChildByTag<SpriteBatchNode*>(kSpriteManager);
    auto cloud = dynamic_cast<Sprite*>(batchNode->getChildByTag(currentCloudTag));
    
    float distance = random(0, 1) * 20 + 5;
    float scale = 5.0f / distance;
    cloud->setScale(scale);
    
    int randValue = (int) random(0, 1) * 2;
    if(randValue == 1)
        cloud->setScale(-cloud->getScaleX());
    
    Size size = cloud->getContentSize();
    float scaledWidth = size.width * scale;
    
    float x = random(0, 1) * (SCREEN_WIDTH + (int) scaledWidth) - scaledWidth * 0.5f;
    float y = random(0, 1) * (SCREEN_HEIGHT - (int) scaledWidth) + scaledWidth * 0.5f + SCREEN_HEIGHT;
    
    cloud->setPosition(Vec2(x, y));
}

void BaseScene::resetClouds() {
    currentCloudTag = kCloudsStartTag;
    while(currentCloudTag < kCloudsStartTag + K_NUM_CLOUDS) {
        resetCloud();
    
        auto batchNode = getChildByTag<SpriteBatchNode*>(kSpriteManager);
        auto cloud = dynamic_cast<Sprite*>(batchNode->getChildByTag(currentCloudTag));
        auto cloudPosition = cloud->getPosition();
        cloudPosition.y -= SCREEN_HEIGHT;
        cloud->setPosition(cloudPosition);
        
        currentCloudTag++;
    }
}

void BaseScene::update(float dt) {
    auto batchNode = getChildByTag<SpriteBatchNode*>(kSpriteManager);
    for(int cloudTag = kCloudsStartTag; cloudTag < kCloudsStartTag + K_NUM_CLOUDS; cloudTag++) {
        auto cloud = dynamic_cast<Sprite*>(batchNode->getChildByTag(cloudTag));
        auto size = cloud->getContentSize();
        auto position = cloud->getPosition();
        position.x += 0.1f * cloud->getScaleY();
        
        if(position.x > SCREEN_WIDTH + size.width* 0.5f)
            position.x = -size.width * 0.5f;
        cloud->setPosition(position);
    }
}
