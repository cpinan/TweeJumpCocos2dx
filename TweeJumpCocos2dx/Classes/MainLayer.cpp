//
//  MainLayer.cpp
//  TweeJumpCocos2dx
//
//  Created by Carlos Pinan on 13/10/13.
//
//

#include "MainLayer.h"

using namespace cocos2d;

MainLayer::MainLayer()
{
    RANDOM_SEED();
    
    CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("sprites.png", 10);
    batchNode->setAnchorPoint(ccp(0,0));
    addChild(batchNode, -1, kSpriteManager);
    
    CCSprite* background = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    batchNode->addChild(background);
    background->setPosition(ccp(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f));
    
    initClouds();
}

void MainLayer::initClouds()
{
    currentCloudTag = kCloudsStartTag;
    while(currentCloudTag < kCloudsStartTag + K_NUM_CLOUDS)
    {
        initCloud();
        currentCloudTag++;
    }
    resetClouds();
}

void MainLayer::initCloud()
{
    CCRect rect;
    switch((int) CCRANDOM_0_1() * 3)
    {
        case 0:
            rect = CCRectMake(336, 16, 256, 108);
            break;
            
        case 1:
            rect = CCRectMake(336, 128, 257, 110);
            break;
            
        case 2:
            rect = CCRectMake(336, 240, 252, 119);
            break;
    }
    
    CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
    CCSprite* cloud = CCSprite::createWithTexture(batchNode->getTexture(), rect);
    batchNode->addChild(cloud, 3, currentCloudTag);
    
    cloud->setOpacity(128);
    
}

void MainLayer::resetClouds()
{
    currentCloudTag = kCloudsStartTag;
    while(currentCloudTag < kCloudsStartTag + K_NUM_CLOUDS)
    {
        resetCloud();
        
        CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
        CCSprite* cloud = dynamic_cast<CCSprite*>(batchNode->getChildByTag(currentCloudTag));
        CCPoint position = cloud->getPosition();
        position.y -= SCREEN_HEIGHT;
        cloud->setPosition(position);
        
        currentCloudTag++;
    }
}

void MainLayer::resetCloud()
{
    CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
    CCSprite* cloud = dynamic_cast<CCSprite*>(batchNode->getChildByTag(currentCloudTag));
    
    float distance = CCRANDOM_0_1() * 20 + 5;
    float scale = 5.0f / distance;
    cloud->setScale(scale);
    
    if(CCRANDOM_0_1() * 2 == 1)
        cloud->setScaleX(-cloud->getScaleX());
    
    CCSize size = cloud->getContentSize();
    float scaled_width = size.width * scale;
    float x = CCRANDOM_0_1() * (SCREEN_WIDTH + (int) scaled_width) - scaled_width * 0.5f;
    float y = CCRANDOM_0_1() * (SCREEN_HEIGHT - (int) scaled_width) + scaled_width * 0.5f + SCREEN_HEIGHT;
    
    cloud->setPosition(ccp(x, y));
    
    
}

void MainLayer::update(float dt)
{
    CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
    for(int cloudTag = kCloudsStartTag; cloudTag < kCloudsStartTag + K_NUM_CLOUDS; cloudTag++)
    {
        CCSprite* cloud = dynamic_cast<CCSprite*>(batchNode->getChildByTag(cloudTag));
        CCSize size = cloud->getContentSize();
        CCPoint position = cloud->getPosition();
        
        position.x += 0.1f * cloud->getScaleY();
        if(position.x > SCREEN_WIDTH + size.width * 0.5f)
            position.x = -size.width * 0.5f;
        cloud->setPosition(position);

    }
    
}



