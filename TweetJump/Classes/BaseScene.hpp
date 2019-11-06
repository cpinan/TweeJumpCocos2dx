//
//  BaseScene.hpp
//  TweetJump-mobile
//
//  Created by Carlos Eduardo Pinan Indacochea on 11/5/19.
//

#ifndef BaseScene_hpp
#define BaseScene_hpp

#include "cocos2d.h"
#include "GameConfig.h"

class BaseScene : public cocos2d::Scene {
public:
    void prepare();
protected:
    void initCloud();
    void initClouds();
    void resetCloud();
    void resetClouds();
    virtual void update(float dt);
    
    int currentCloudTag;
};

#endif /* BaseScene_hpp */
