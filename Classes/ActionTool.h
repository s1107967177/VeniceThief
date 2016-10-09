//
//  ActionTool.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/13.
//
//

#ifndef ActionTool_h
#define ActionTool_h

#include "cocos2d.h"

class ActionTool
{
public:
    static cocos2d::Animate *animationWithFrameName(const char *frameName, float delay);
   
    static std::string getLastFrameName(const char *frameName);
};

#endif /* ActionTool_h */
