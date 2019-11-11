//
//  GameConfig.h
//  TweetJump
//
//  Created by Carlos Eduardo Pinan Indacochea on 10/1/19.
//

#ifndef GameConfig_h
#define GameConfig_h

#include <ctime>
#include <cstdlib>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#define DISPLAY_STATS true

#define K_NUM_CLOUDS 12
#define K_MIN_PLATFORM_STEP 50
#define K_MAX_PLATFORM_STEP 300
#define K_NUM_PLATFORMS 15
#define K_PLATFORM_TOP_PADDING 10

#define K_MIN_BONUS_STEP 30
#define K_MAX_BONUS_STEP 50

#define SPRITE_SHEET "Images/sprites.png"
#define SPRITE_SHEET_SIZE 10
#define PLAY_AGAIN "Images/playAgainButton.png"
#define CHANGE_PLAYER "Images/changePlayerButton.png"

#define ARIAL "fonts/arial.ttf"

#define KEY_HIGHSCORE "highscores"
#define KEY_PLAYER "player"

enum {
    kSpriteManager = 0,
    kBird,
    kScoreLabel,
    kCloudsStartTag = 1000,
    kPlatformsStartTag = 2000,
    kBonusStartTag = 3000,
    kPopUpPlayerTag = 10000,
    kPopUpEditBoxTag = 150000
};

enum
{
    kBonus5 = 0,
    kBonus10,
    kBonus50,
    kBonus100,
    kNumBonuses
};


#endif /* GameConfig_h */
