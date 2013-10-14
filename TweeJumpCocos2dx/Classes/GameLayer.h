//
//  GameLayer.h
//  TweeJumpCocos2dx
//
//  Created by Carlos Pinan on 13/10/13.
//
//

#ifndef __TweeJumpCocos2dx__GameLayer__
#define __TweeJumpCocos2dx__GameLayer__

#include "MainLayer.h"

class GameLayer : public MainLayer
{
public:
    GameLayer();
    void update(float dt);
    static cocos2d::CCScene* scene();
    
    void didAccelerate(cocos2d::CCAcceleration *pAccelerationValue);
    
private:
    cocos2d::CCPoint bird_position;
    cocos2d::ccVertex2F bird_velocity;
    cocos2d::ccVertex2F bird_acceleration;
    
    bool gameSuspended;
    bool birdLookingRight;
    
    int score;
    int platformCount;
    int currentBonusType;
    float currentPlatformY;
    int currentPlatformTag;
    float currentMaxPlatformStep;
    int currentBonusPlatformIndex;
    
private:
    void _initPlatform();
    void _initPlatforms();
    void _resetPlatform();
    void _resetPlatforms();
    void _resetBird();
    void _resetBonus();
    void _startGame();
    void _jump();
    void _superJump();
    void _showHighScores();
    
};

#endif /* defined(__TweeJumpCocos2dx__GameLayer__) */
