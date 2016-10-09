//
//  ActionTool.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/13.
//
//

#include "ActionTool.h"

USING_NS_CC;

Animate *ActionTool::animationWithFrameName(const char *frameName, float delay)
{
    SpriteFrame *frame = NULL;
    Animation *animation = Animation::create();
    int index = 1;
    while(true) {
        __String *name = __String::createWithFormat("%s%d.png", frameName, index++);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
        if (frame == NULL) {
            break;
        }
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(delay);
    animation->setRestoreOriginalFrame(true);
    Animate* animate = Animate::create(animation);
    return animate;
}

std::string ActionTool::getLastFrameName(const char *frameName)
{
    SpriteFrame *frame = NULL;
    int index = 1;
    while(true) {
        __String *name = __String::createWithFormat("%s%d.png", frameName, index++);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
        if (frame == NULL) {
            break;
        }
    }
    std::string lastFrameName = __String::createWithFormat("%s%d.png", frameName, index - 2)->getCString();
    return lastFrameName;
}