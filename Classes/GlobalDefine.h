//
//  GlobalDefine.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/15.
//
//

#ifndef GlobalDefine_h
#define GlobalDefine_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define     WINSIZE                       Director::getInstance()->getWinSize()

#define     setIntToXML                UserDefault::getInstance()->setIntegerForKey
#define     setFloatToXML            UserDefault::getInstance()->setFloatForKey
#define     setBoolToXML             UserDefault::getInstance()->setBoolForKey
#define     getIntFromXML           UserDefault::getInstance()->getIntegerForKey
#define     getFloatFromXML       UserDefault::getInstance()->getFloatForKey
#define     getBoolFromXML        UserDefault::getInstance()->getBoolForKey

#define     SOUND_KEY                   "soundClose"
#define     MUSIC_KEY                   "musicClose"
#define     SOUND_VOL                   "soundVolume"
#define     MUSIC_VOL                   "musicVolume"
#define     COIN_KEY                       "coinNumber"
#define     SPEED_Y_KEY               "speedY"
#define     SPEED_X_KEY               "speedX"

#define     audioEngine                 SimpleAudioEngine::getInstance()

#define     PLAY_EFFECT     if (getBoolFromXML(SOUND_KEY)) { \
                                                    audioEngine->setEffectsVolume(getFloatFromXML(SOUND_VOL)); \
                                                    audioEngine->playEffect("Sound/button.wav"); \
                                                }

#endif /* GlobalDefine_h */
