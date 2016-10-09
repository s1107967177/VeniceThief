//
//  ContactListener.h
//  VeniceThief
//
//  Created by 唐家琪 on 16/2/8.
//
//

#ifndef ContactListener_h
#define ContactListener_h

#include "cocos2d.h"
#include "Box2D/Box2d.h"

USING_NS_CC;

class ContactListener : public b2ContactListener
{
private:
    //两个物体开始接触时会响应
    virtual void BeginContact(b2Contact *contact);
    //持续接触时响应
    virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
    //持续接触时响应，调用完PreSolve后调用
    virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
    //分离时响应
    virtual void EndContact(b2Contact *contact);
};

#endif /* ContactListener_h */
