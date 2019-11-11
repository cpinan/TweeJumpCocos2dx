//
//  HighScoreScene.hpp
//  TweetJump-mobile
//
//  Created by Carlos Eduardo Pinan Indacochea on 11/5/19.
//

#ifndef HighScoreScene_hpp
#define HighScoreScene_hpp

#include "BaseScene.hpp"

class HighScoreScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene(int lastScore);
};

class HighScoreLayer : public BaseScene {
public:
    HighScoreLayer(int lastScore);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    
private:
    int _lastScore;
    int _currentScore;
    int _currentScorePosition;
    std::string _currentPlayer;
    
    void _loadHighScores();
    void _playAgainAction(cocos2d::Ref* sender);
    void _changePlayerAction(cocos2d::Ref* sender);
};

class PlayerPopUp : public cocos2d::Layer {
public:
    PlayerPopUp();
private:
    cocos2d::Layer* _popUpLayer;
    void _saveAction(cocos2d::Ref* sender);
    void _cancelAction(cocos2d::Ref* sender);
};

#endif /* HighScoreScene_hpp */
