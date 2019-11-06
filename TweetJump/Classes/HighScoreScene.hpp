//
//  HighScoreScene.hpp
//  TweetJump-mobile
//
//  Created by Carlos Eduardo Pinan Indacochea on 11/5/19.
//

#ifndef HighScoreScene_hpp
#define HighScoreScene_hpp

#include "BaseScene.hpp"

class HighScoreScene : public BaseScene {
public:
    static cocos2d::Scene* createScene(int lastScore);
};

class HighScoreLayer : public cocos2d::Layer {
public:
    HighScoreLayer(int lastScore);
private:
    int _lastScore;
    int _currentScore;
    int _currentScorePosition;
    std::string _currentPlayer;
};

class PlayerPopUp{
public:
    PlayerPopUp();
private:
    cocos2d::Layer* _popUpLayer;
    void _saveAction(cocos2d::Ref* sender);
    void _cancelAction(cocos2d::Ref* sender);
};

#endif /* HighScoreScene_hpp */
