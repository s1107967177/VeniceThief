//
//  GameLayer.h
//  VeniceThief
//
//  Created by 唐家琪 on 16/2/7.
//
//

#ifndef GameLayer_h
#define GameLayer_h

#include "GlobalDefine.h"
#include "Box2D/Box2D.h"
#include "ContactListener.h"
#include "Box2DDebugDraw.h"

class GameLayer : public Layer
{
public:
    virtual ~GameLayer();    
    static GameLayer *getInstance();
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void update(float dt);
    
    CREATE_FUNC(GameLayer);
    
    void initPhysics();
    
    void touchLeft(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void touchRight(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void gameOver();
    
    bool _isOver;
    bool _leftTurning;
    bool _rightTurning;
    
private:
    static GameLayer *pInstance;
    
    cocos2d::ui::Button *_left;
    cocos2d::ui::Button *_right;
    
    float _speedX;
    float _speedY;
    
    b2Body *_banksBody;
    cocos2d::Sprite *_player;
    cocos2d::Vector<cocos2d::Sprite*> _coinVec;
    cocos2d::ParticleSystemQuad *_waterSplash;
    cocos2d::Size _visibleSize;
    cocos2d::DrawNode *_graphics;
    b2World *_world;
    ContactListener *_contactListener;
    Node *_rootNode;
};

#endif /* GameLayer_h */
