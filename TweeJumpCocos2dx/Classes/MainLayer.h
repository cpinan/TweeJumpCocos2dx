//
//  MainLayer.h
//  TweeJumpCocos2dx
//
//  Created by Carlos Pinan on 13/10/13.
//
//

#ifndef __TweeJumpCocos2dx__MainLayer__
#define __TweeJumpCocos2dx__MainLayer__

#include "cocos2d.h"
#include "GameConfig.h"

class MainLayer : public cocos2d::CCLayer
{
public:
    
    MainLayer();
    
    void initCloud();
    void initClouds();
    void resetCloud();
    void resetClouds();
    virtual void update(float dt);
    
protected:
    int currentCloudTag;
    
};

#endif /* defined(__TweeJumpCocos2dx__MainLayer__) */
