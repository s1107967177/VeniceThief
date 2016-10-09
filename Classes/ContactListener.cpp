//
//  ContactListener.cpp
//  VeniceThief
//
//  Created by 唐家琪 on 16/2/8.
//
//

#include "ContactListener.h"
#include "GameLayer.h"

void ContactListener::BeginContact(b2Contact *contact)
{
    log("BeginContact");
    b2Body *bodyA = contact->GetFixtureA()->GetBody();
    b2Body *bodyB = contact->GetFixtureB()->GetBody();
    auto spriteA = (Sprite *)bodyA->GetUserData();
    auto spriteB = (Sprite *)bodyB->GetUserData();
    b2Filter filterA = contact->GetFixtureA()->GetFilterData();
    b2Filter filterB = contact->GetFixtureB()->GetFilterData();
    
    if (spriteA != nullptr && spriteB != nullptr) {
        if (filterA.categoryBits == 1) {
            spriteA->setVisible(false);
    //        bodyA->SetActive(false);
        }
        if (filterB.categoryBits == 1) {
            spriteB->setVisible(false);
  //          bodyB->SetActive(false);
        }
        if ((filterA.categoryBits == 2 && filterB.categoryBits == 4) || (filterA.categoryBits == 4 && filterB.categoryBits == 2)) {
            GameLayer::getInstance()->_isOver = true;
        }
    }
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    log("PreSolve");
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    log("PostSolve");
}

void ContactListener::EndContact(b2Contact *contact)
{
    log("EndContact");
}

