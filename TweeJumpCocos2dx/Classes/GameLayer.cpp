//
//  GameLayer.cpp
//  TweeJumpCocos2dx
//
//  Created by Carlos Pinan on 13/10/13.
//
//

#include "GameLayer.h"
#include "HighScoreLayer.h"

using namespace cocos2d;

CCScene* GameLayer::scene()
{
    CCScene* scene = CCScene::create();
    GameLayer* gameLayer = new GameLayer();
    gameLayer->autorelease();
    scene->addChild(gameLayer);
    return scene;
}

void GameLayer::didAccelerate(CCAcceleration *pAccelerationValue)
{
    if(gameSuspended)
        return;
    
    float accel_filter = 0.1f;
    bird_velocity.x = bird_velocity.x * accel_filter + pAccelerationValue->x * (1.0f - accel_filter) * 500.0f;
}

GameLayer::GameLayer()
{
    gameSuspended = true;
    CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
    
    _initPlatforms();
    
    CCSprite* bird = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(608, 16, 44, 32));
    batchNode->addChild(bird, 4, kBird);
    
    CCSprite* bonus;
    
    for(int i = 0; i < kNumBonuses; i++)
    {
        bonus = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(608 + i * 32, 256, 25, 25));
        batchNode->addChild(bonus, 4, kBonusStartTag + i);
        bonus->setVisible(false);
    }
    
    CCLabelBMFont* scoreLabel = CCLabelBMFont::create("0", "bitmapFont.fnt");
    addChild(scoreLabel, 5, kScoreLabel);
    scoreLabel->setPosition(ccp(160, 430));
    
    _startGame();
    scheduleUpdate();
    
    setTouchEnabled(false);
    setAccelerometerEnabled(true);
    
}

void GameLayer::update(float dt)
{
    if(gameSuspended)
        return;
    
    MainLayer::update(dt);
    
    CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
    CCSprite* bird = dynamic_cast<CCSprite*>(batchNode->getChildByTag(kBird));
    
    bird_position.x += bird_velocity.x * dt;
    if(bird_velocity.x < -30.0f && birdLookingRight)
    {
        birdLookingRight = false;
        bird->setScaleX(-1.0f);
    }
    else if(bird_velocity.x > 30.0f && !birdLookingRight)
    {
        birdLookingRight = true;
        bird->setScaleX(1.0f);
    }
    
    CCSize bird_size = bird->getContentSize();
    float max_x = SCREEN_WIDTH + bird_size.width * 0.5f;
    float min_x = -bird_size.width * 0.5f;
    
    if(bird_position.x > max_x)
        bird_position.x = min_x;
    
    if(bird_position.x < min_x)
        bird_position.x = max_x;
    
    bird_velocity.y += bird_acceleration.y * dt;
    bird_position.y += bird_velocity.y * dt;
    
    CCSprite* bonus = dynamic_cast<CCSprite*>(batchNode->getChildByTag(kBonusStartTag + currentBonusType));
    if(bonus->isVisible())
    {
        CCPoint bonus_position = bonus->getPosition();
        float range = 20.0f;
        if(bird_position.x > bonus_position.x - range &&
           bird_position.x < bonus_position.x + range &&
           bird_position.y > bonus_position.y - range &&
           bird_position.y < bonus_position.y + range)
        {
            switch(currentBonusType)
            {
                case kBonus5:
                    score += 5000;
                    break;
                case kBonus10:
                    score += 10000;
                    break;
                case kBonus50:
                    score += 50000;
                    break;
                case kBonus100:
                    score += 100000;
                    break;
            }
            
            CCString* scoreStr = CCString::createWithFormat("%d", score);
            CCLabelBMFont* scoreLabel = dynamic_cast<CCLabelBMFont*>(getChildByTag(kScoreLabel));
            scoreLabel->setString(scoreStr->getCString());
            
            CCScaleTo* action1 = CCScaleTo::create(0.2f, 1.5f, 0.8f);
            CCScaleTo* action2 = CCScaleTo::create(0.2f, 1.0f, 1.0f);
            CCSequence* action3 = CCSequence::create(action1, action2, action1, action2, action1, action2, NULL);
            scoreLabel->runAction(action3);
            _resetBonus();
            _superJump();
            
        }
    }
    
    int cloudTag;
    int platformTag;
    
    if(bird_velocity.y < 0)
    {
        for(platformTag = kPlatformsStartTag; platformTag < kPlatformsStartTag + K_NUM_PLATFORMS; platformTag++)
        {
            CCSprite* platform = dynamic_cast<CCSprite*>(batchNode->getChildByTag(platformTag));
            CCSize platform_size = platform->getContentSize();
            CCPoint platform_position = platform->getPosition();
            
            max_x = platform_position.x - platform_size.width * 0.5f - 10;
            min_x = platform_position.x + platform_size.width * 0.5f + 10;
            float min_y = platform_position.y + (platform_size.height + bird_size.height) * 0.5f - K_PLATFORM_TOP_PADDING;
            
            if(bird_position.x > max_x && bird_position.x < min_x &&
               bird_position.y > platform_position.y && bird_position.y < min_y)
                _jump();
        }
        
        if(bird_position.y < - bird_size.height)
            _showHighScores();
        
    }
    else if(bird_position.y > SCREEN_HEIGHT * 0.5f)
    {
        float delta = bird_position.y - SCREEN_HEIGHT * 0.5f;
        bird_position.y = SCREEN_HEIGHT * 0.5f;
        currentPlatformY -= delta;
        
        for(cloudTag = kCloudsStartTag; cloudTag < kCloudsStartTag + K_NUM_CLOUDS; cloudTag++)
        {
            CCSprite* cloud = dynamic_cast<CCSprite*>(batchNode->getChildByTag(cloudTag));
            CCPoint position = cloud->getPosition();
            position.y -= delta * cloud->getScaleY() * 0.8f;
            
            if(position.y < -cloud->getContentSize().height * 0.5f)
            {
                currentCloudTag = cloudTag;
                resetCloud();
            }
            else
            {
                cloud->setPosition(position);
            }
        }
        
        for(platformTag = kPlatformsStartTag; platformTag < kPlatformsStartTag + K_NUM_PLATFORMS; platformTag++)
        {
            CCSprite* platform = dynamic_cast<CCSprite*>(batchNode->getChildByTag(platformTag));
            CCPoint position = platform->getPosition();
            position = ccp(position.x, position.y - delta);
            if(position.y < -platform->getContentSize().height * 0.5f)
            {
                currentPlatformTag = platformTag;
                _resetPlatform();
            }
            else
            {
                platform->setPosition(position);
            }
        }
        
        if(bonus->isVisible())
        {
            CCPoint position = bonus->getPosition();
            position.y -= delta;
            if(position.y < -bonus->getContentSize().height * 0.5f)
            {
                _resetBonus();
            }
            else
            {
                bonus->setPosition(position);
            }
        }
        
        score += (int) delta;
        CCString* scoreStr = CCString::createWithFormat("%d", score);
        CCLabelBMFont* scoreLabel = dynamic_cast<CCLabelBMFont*>(getChildByTag(kScoreLabel));
        scoreLabel->setString(scoreStr->getCString());
    }
    bird->setPosition(bird_position);
}

void GameLayer::_initPlatform()
{
    CCRect rect;
    switch((int)CCRANDOM_0_1() * 2)
    {
        case 0:
            rect = CCRectMake(608, 64, 102, 36);
            break;
        case 1:
            rect = CCRectMake(608, 128, 90, 32);
            break;
    }
    CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
    CCSprite* platform = CCSprite::createWithTexture(batchNode->getTexture(), rect);
    batchNode->addChild(platform, 3, currentPlatformTag);
}

void GameLayer::_initPlatforms()
{
    currentPlatformTag = kPlatformsStartTag;
    while(currentPlatformTag < kPlatformsStartTag + K_NUM_PLATFORMS)
    {
        _initPlatform();
        currentPlatformTag++;
    }
}

void GameLayer::_resetPlatform()
{
    if(currentPlatformY < 0)
        currentPlatformY = 30.0f;
    else
    {
        currentPlatformY += CCRANDOM_0_1() * (int)(currentMaxPlatformStep - K_MIN_PLATFORM_STEP) + K_MIN_PLATFORM_STEP;
        if(currentMaxPlatformStep < K_MAX_PLATFORM_STEP)
            currentMaxPlatformStep += 0.5f;
    }
    
    CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
    CCSprite* platform = dynamic_cast<CCSprite*>(batchNode->getChildByTag(currentPlatformTag));
    
    if(CCRANDOM_0_1() * 2 == 1)
        platform->setScaleX(-1.0f);
    
    float x;
    
    CCSize size = platform->getContentSize();
    
    if(currentPlatformY == 30.0f)
        x = SCREEN_WIDTH * 0.5f;
    else
        x = CCRANDOM_0_1() * (SCREEN_WIDTH - (int) size.width) + size.width * 0.5f;
    
    platform->setPosition(ccp(x, currentPlatformY));
    platformCount++;
    
    if(platformCount == currentBonusPlatformIndex)
    {
        CCSprite* bonus = dynamic_cast<CCSprite*>(batchNode->getChildByTag(kBonusStartTag + currentBonusType));
        bonus->setPosition(ccp(x, currentPlatformY + 30));
        bonus->setVisible(true);
    }
    
}

void GameLayer::_resetPlatforms()
{
    currentPlatformY = -1;
    currentPlatformTag = kPlatformsStartTag;
    currentMaxPlatformStep = 60.0f;
    currentBonusPlatformIndex = 0;
    currentBonusType = 0;
    platformCount = 0;
    
    while(currentPlatformTag < kPlatformsStartTag + K_NUM_PLATFORMS)
    {
        _resetPlatform();
        currentPlatformTag++;
    }
    
    gameSuspended = false;
}

void GameLayer::_resetBird()
{
    CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
    CCSprite* bird = dynamic_cast<CCSprite*>(batchNode->getChildByTag(kBird));
    
    bird_position.x = SCREEN_WIDTH * 0.5f;
    bird_position.y = SCREEN_WIDTH * 0.5f;
    bird->setPosition(bird_position);
    
    bird_velocity.x = 0;
    bird_velocity.y = 0;
    
    bird_acceleration.x = 0;
    bird_acceleration.y = -550.0f;
    
    birdLookingRight = true;
    bird->setScaleX(1.0f);
}

void GameLayer::_resetBonus()
{
    CCSpriteBatchNode* batchNode = dynamic_cast<CCSpriteBatchNode*>(getChildByTag(kSpriteManager));
    CCSprite* bonus = dynamic_cast<CCSprite*>(batchNode->getChildByTag(kBonusStartTag + currentBonusType));
    bonus->setVisible(false);
    
    currentBonusPlatformIndex += CCRANDOM_0_1() * (K_MAX_BONUS_STEP - K_MIN_BONUS_STEP) + K_MIN_BONUS_STEP;
    
    if(score < 10000)
        currentBonusType = 0;
    else if(score < 50000)
        currentBonusType = CCRANDOM_0_1() * 2;
    else if(score < 100000)
        currentBonusType = CCRANDOM_0_1() * 3;
    else
        currentBonusType = CCRANDOM_0_1() * 2 + 2;
    
}

void GameLayer::_startGame()
{
    score = 0;
    resetClouds();
    _resetPlatforms();
    _resetBird();
    _resetBonus();
}

void GameLayer::_jump()
{
    bird_velocity.y = 350.0f + fabsf(bird_velocity.x);
}

void GameLayer::_superJump()
{
    bird_velocity.y = 1000.0f + fabsf(bird_velocity.x);
}

void GameLayer::_showHighScores()
{
    gameSuspended = true;
    stopAllActions();
    unscheduleUpdate();
    
    CCTransitionFade* scene = CCTransitionFade::create(1.0f, HighScoreLayer::scene(score), ccWHITE);
    CCDirector::sharedDirector()->replaceScene(scene);
}


