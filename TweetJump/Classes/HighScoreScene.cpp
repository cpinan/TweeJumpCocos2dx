//
//  HighScoreScene.cpp
//  TweetJump-mobile
//
//  Created by Carlos Eduardo Pinan Indacochea on 11/5/19.
//

#include "HighScoreScene.hpp"

#define RESET_DEFAULTS true

using namespace cocos2d;
using namespace std;

vector<string> split(string str, string value) {
    vector<string> split;
    char *line = strtok(const_cast<char*>(str.c_str()), value.c_str());
    while (line) {
        split.push_back(line);
        line = strtok(NULL, value.c_str());
    }
    return split;
}

// POPUP
PlayerPopUp::PlayerPopUp() {
    _popUpLayer = LayerColor::create(Color4B(0, 0, 255, 200));
    _popUpLayer->setContentSize(Size(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.5f));
    _popUpLayer->setPosition(Vec2(25, 120));
    
    // TITLE
    auto title = Label::createWithTTF("Change Player", ARIAL, 18.0f, Size(250, 40), TextHAlignment::RIGHT, TextVAlignment::CENTER);
    title->setColor(Color3B::BLACK);
    title->setPosition(Vec2(SCREEN_WIDTH * 0.2f, 200));
    
    auto saveLabel = Label::createWithTTF("Save", ARIAL, 20.0f);
    auto saveItem = MenuItemLabel::create(saveLabel, CC_CALLBACK_1(PlayerPopUp::_saveAction, this));
    saveItem->setPosition(Vec2(50, 50));
    
    auto cancelLabel = Label::createWithTTF("Cancel", ARIAL, 20.0f);
    auto cancelItem = MenuItemLabel::create(cancelLabel, CC_CALLBACK_1(PlayerPopUp::_cancelAction, this));
    cancelItem->setPosition(Vec2(200, 50));
    
    auto menu = Menu::create(saveItem, cancelItem, NULL);
    menu->setPosition(Vec2::ZERO);
    
    // Player Name
    auto playerName = TextFieldTTF::textFieldWithPlaceHolder("Insert your name: ", Size(230, 40), TextHAlignment::LEFT, ARIAL, 14.0f);
    playerName->setTextColor(Color4B::RED);
    playerName->setPosition(Vec2(125, 150));
    playerName->setCursorEnabled(true);
    playerName->setCursorPosition(0);
    playerName->setCursorChar('|');
    
    _popUpLayer->addChild(title);
    _popUpLayer->addChild(menu, 100, kPopUpPlayerTag);
    _popUpLayer->addChild(playerName, 150, kPopUpEditBoxTag);
    
    addChild(_popUpLayer);
    
}

void PlayerPopUp::_saveAction(Ref* sender) {
    
}

void PlayerPopUp::_cancelAction(Ref* sender) {
    if(isVisible()) {
        setVisible(false);
    }
}

// LAYER
HighScoreLayer::HighScoreLayer(int lastScore) {
    auto defaults = UserDefault::getInstance();
    _currentPlayer = defaults->getStringForKey(KEY_PLAYER, "anonymous");
    
    _loadHighScores();
    
    _lastScore = lastScore;
    auto popUp = new PlayerPopUp();
    popUp->setVisible(false);
    popUp->autorelease();
    this->addChild(popUp);
    
    auto batchNode = getChildByTag<SpriteBatchNode*>(kSpriteManager);
    auto title = Sprite::createWithTexture(batchNode->getTexture(), Rect(608, 192, 225, 57));
    batchNode->addChild(title, 5);
    title->setPosition(Vec2(160, 420));
    
    float startY = 360.0f;
    float step = 27.0f;
    int count = 0;
    
    string highscores = defaults->getStringForKey(KEY_HIGHSCORE, "");
    vector<string> vectorScores = split(highscores, "\n");
    
   if(vectorScores.size() > 0) {
        for(int i = 0; i < vectorScores.size(); i++) {
            vector<string> data = split(vectorScores[i], ";");
            if(data.size() > 0) {
                string player = data[0];
                int score = atoi(data[1].c_str());
                
                CCLabelTTF* label1 = CCLabelTTF::create(CCString::createWithFormat("%d", (count + 1))->getCString(), ARIAL, 14, CCSizeMake(30, 40), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
                addChild(label1, 5);
                label1->setColor(ccBLACK);
                label1->setOpacity(200);
                label1->setPosition(ccp(15, startY - count * step - 2.0f));
                
                CCLabelTTF* label2 = CCLabelTTF::create(player.c_str(), "Arial", 16, CCSizeMake(240, 40), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
                addChild(label2, 5);
                label2->setColor(ccBLACK);
                label2->setPosition(ccp(160, startY - count * step));
                
                CCLabelTTF* label3 = CCLabelTTF::create(CCString::createWithFormat("%d", score)->getCString(), "Arial", 16, CCSizeMake(290, 40), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
                addChild(label3, 5);
                label3->setColor(ccBLACK);
                label3->setOpacity(200);
                label3->setPosition(ccp(160, startY - count * step));
                
                count++;
                if(count == 10)
                    break;
                
            }
        }
    }
    
    auto playAgainButton = MenuItemImage::create(PLAY_AGAIN, PLAY_AGAIN, CC_CALLBACK_1(HighScoreLayer::_playAgainAction, this));
    
    auto changePlayerButton = MenuItemImage::create(CHANGE_PLAYER, CHANGE_PLAYER, CC_CALLBACK_1(HighScoreLayer::_changePlayerAction, this));
    
    auto menu = Menu::create(playAgainButton, changePlayerButton, NULL);
    menu->alignItemsVerticallyWithPadding(9.0f);
    menu->setPosition(Vec2(160, 58));
    this->addChild(menu, 10000);
    
}

void HighScoreLayer::_playAgainAction(cocos2d::Ref* sender) {
    
}

void HighScoreLayer::_changePlayerAction(cocos2d::Ref* sender) {
    
}

void HighScoreLayer::_loadHighScores() {
    auto defaults = UserDefault::getInstance();
    
    #ifdef RESET_DEFAULTS
        defaults->setStringForKey(KEY_HIGHSCORE, "");
        defaults->flush();
    #endif
    
    string highscores = defaults->getStringForKey(KEY_HIGHSCORE, "");
    
    if(highscores.length() == 0) {
        string save_scores = "";
        save_scores += "tweejump;750000\n";
        save_scores += "tweejump;500000\n";
        save_scores += "tweejump;250000\n";
        save_scores += "tweejump;100000\n";
        save_scores += "tweejump;50000\n";
        save_scores += "tweejump;20000\n";
        save_scores += "tweejump;10000\n";
        save_scores += "tweejump;5000\n";
        save_scores += "tweejump;1000\n";
        defaults->setStringForKey(KEY_HIGHSCORE, save_scores);
        defaults->flush();
    }
}

void HighScoreLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    BaseScene::draw(renderer, transform, flags);
    
    if(_currentScorePosition < 0)
        return;
    
    float width = 320.0f;
    float height = 27.0f;
    float x = (320.0f - width) / 2.0f;
    float y = 348 - _currentScorePosition * height;
    
    auto drawNode = DrawNode::create();
    this->addChild(drawNode, 0);
    drawNode->drawSolidRect(Vec2(x,y), Vec2(x+width, y + height), Color4F(1.0f, 0.0f, 0.0f, 0.1f));
    
}

// SCENE
Scene* HighScoreScene::createScene(int lastScore) {
    auto scene = Scene::create();
    auto layer = new HighScoreLayer(lastScore);
    scene->addChild(layer);
    layer->autorelease();
    return scene;
}

