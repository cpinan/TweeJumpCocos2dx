//
//  GameConfig.h
//  TweeJumpCocos2dx
//
//  Created by Carlos Pinan on 13/10/13.
//
//

#ifndef TweeJumpCocos2dx_GameConfig_h
#define TweeJumpCocos2dx_GameConfig_h

#include <ctime>
#include <cstdlib>

#define RANDOM_SEED() srand(time(0))

// #define RESET_DEFAULTS

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

#endif
