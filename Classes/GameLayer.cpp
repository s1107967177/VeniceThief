//
//  GameLayer.cpp
//  VeniceThief
//
//  Created by 唐家琪 on 16/2/7.
//
//

#include "GameLayer.h"
#include "GlobalData.h"
#include "GB2ShapeCache-x.h"
#include "ActionTool.h"

USING_NS_CC;
using namespace cocos2d::ui;

#define PTM_RATIO 32

GameLayer *GameLayer::pInstance = nullptr;

GameLayer *GameLayer::getInstance()
{
    return pInstance;
}

GameLayer::~GameLayer()
{
    CC_SAFE_DELETE(_world);
    CC_SAFE_DELETE(_contactListener);
}

Scene *GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    pInstance = this;
    
    _isOver = false;
    _leftTurning = false;
    _rightTurning = false;
    
    _speedX = getIntFromXML(SPEED_X_KEY);
    _speedY = getIntFromXML(SPEED_Y_KEY);
    
    auto rootNode = GlobalData::getInstance()->getRootNode();
    addChild(rootNode, 0);
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _player = rootNode->getChildByName<Sprite*>("KuaiTing");
    
    for (size_t index = 1; ; ++index) {
        auto sp = __String::createWithFormat("coin%zu", index);
        auto coin = rootNode->getChildByName<Sprite*>(sp->getCString());
        if (coin == nullptr) {
            break;
        }
        else {
            _coinVec.pushBack(coin);
        }
    }
    for (auto coin : _coinVec) {
        Animate *action = ActionTool::animationWithFrameName("coin", 0.1);
        Action *repeatForever = RepeatForever::create(action);
        coin->runAction(repeatForever);
    }
    
    _waterSplash = _player->getChildByName<ParticleSystemQuad*>("WaterSplash");
    
    _left = rootNode->getChildByName<Button*>("Left");
    _right = rootNode->getChildByName<Button*>("Right");
    
    _left->addTouchEventListener(
            Widget::ccWidgetTouchCallback(CC_CALLBACK_2( GameLayer::touchLeft, this)));
    _right->addTouchEventListener(
            Widget::ccWidgetTouchCallback(CC_CALLBACK_2( GameLayer::touchRight, this)));
    
    _graphics = DrawNode::create();
    _graphics->setAnchorPoint(Vec2::ZERO);
    addChild(_graphics, -1);
    
    initPhysics();
    
    scheduleUpdate();
    
    return true;
}

void GameLayer::update(float dt)
{
    if (getPositionY() > - GlobalData::getInstance()->mapLength) {
        setPosition(getPosition() + Vec2(0, - _speedY / 10));
        
        float playerXDelta = 0;
        if (_leftTurning) {
            playerXDelta = _player->getPosition() > 0.30 * _visibleSize ? - _speedX / 10 : 0;
        }
        if (_rightTurning) {
            playerXDelta = _player->getPosition() < 0.70 * _visibleSize ? _speedX / 10 : 0;
        }
        
        _player->setPosition(_player->getPosition() + Vec2(playerXDelta, _speedY / 10));
        _left->setPosition(_left->getPosition() + Vec2(0, _speedY / 10));
        _right->setPosition(_right->getPosition() + Vec2(0, _speedY / 10));
  
        b2Vec2 delta(0, _speedY / PTM_RATIO / 10 );
        _banksBody->SetTransform(_banksBody->GetPosition() + delta, 0);
    }
    
    int32 velocityIterations = 8;
    int32 positionIterations = 1;
    
    _graphics->clear();
    _world->Step(dt, velocityIterations, positionIterations);
    _world->DrawDebugData();
    
    for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
        if (b->GetUserData() != nullptr) {
            Sprite *sprite = (Sprite*)b->GetUserData();
            if (sprite->getName() == _player->getName()) {
                float angle = sprite->getRotation();
                Vec2 curPos = sprite->getPosition();
                b2Vec2 shapeCenter(curPos.x/PTM_RATIO, curPos.y/PTM_RATIO);
                b->SetTransform(shapeCenter, CC_DEGREES_TO_RADIANS(360-angle) );
            }
            else {
                sprite->setPosition(
                    Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
                sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
            }
        }
    }
    //检查是否结束
    if (_isOver == true) {
        unscheduleUpdate();
        Animate *action = ActionTool::animationWithFrameName("explosion", 0.07);
        CallFunc *func = CallFunc::create(CC_CALLBACK_0(GameLayer::gameOver, this));
        auto *seq = Sequence::create(action, func, NULL);
        _waterSplash->setVisible(false);
        _player->runAction(seq);
    }
}

void GameLayer::initPhysics()
{

    b2Vec2 gravity;
    gravity.Set(0, 0);
    _world = new b2World(gravity);
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);
    
    auto debugDraw = new Box2DDebugDraw(_graphics, PTM_RATIO);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    flags += b2Draw::e_centerOfMassBit;
    debugDraw->SetFlags(flags);   //需要显示那些东西
    _world->SetDebugDraw(debugDraw);    //设置
    
    _contactListener = new ContactListener;
    _world->SetContactListener(_contactListener);
    
    b2BodyDef banksBodyDef;
    banksBodyDef.position.Set(0,0);
    
    _banksBody = _world->CreateBody(&banksBodyDef);
    
    b2EdgeShape banksParallel;
    banksParallel.Set(
        b2Vec2(0.25 * _visibleSize.width / PTM_RATIO, 0),
        b2Vec2(0.25 * _visibleSize.width / PTM_RATIO, _visibleSize.height / PTM_RATIO));
    _banksBody->CreateFixture(&banksParallel, 0);
    
    banksParallel.Set(
        b2Vec2(0.75 * _visibleSize.width / PTM_RATIO, 0),
        b2Vec2(0.75 * _visibleSize.width / PTM_RATIO, _visibleSize.height / PTM_RATIO));
    _banksBody->CreateFixture(&banksParallel, 0);
    
    GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
    sc->addShapesWithFile("GateOnePE.plist");
    
    b2BodyDef bodyDef;
    for (auto name : GlobalData::getInstance()->getObstacleNames()) {
        for(auto sprite : GlobalData::getInstance()->getObstaclesByName(name)) {
            bodyDef.type = b2_dynamicBody;
            bodyDef.position.Set(
                sprite->getPositionX() / PTM_RATIO, sprite->getPositionY() /PTM_RATIO);
            bodyDef.userData = sprite;
            b2Body *body = _world->CreateBody(&bodyDef);
            sc->addFixturesToBody(body, name);
            sprite->setAnchorPoint(sc->anchorPointForShape(name));
        }
    }
    
    for (auto coin : _coinVec) {
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(
            coin->getPositionX() / PTM_RATIO, coin->getPositionY() / PTM_RATIO);
        bodyDef.userData = coin;
        b2Body *body = _world->CreateBody(&bodyDef);
        
        b2CircleShape staticBall;
        staticBall.m_radius = coin->getBoundingBox().size.width / 2 / PTM_RATIO;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &staticBall;
        b2Filter circleFilter;
        circleFilter.categoryBits = 1;
        circleFilter.maskBits = 2;
        fixtureDef.filter = circleFilter;
        body->CreateFixture(&fixtureDef);
    }
    
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(
        _player->getPositionX() / PTM_RATIO, _player->getPositionY() /PTM_RATIO);
    bodyDef.userData = _player;
    b2Body *body = _world->CreateBody(&bodyDef);
    sc->addFixturesToBody(body, _player->getName());
    _player->setAnchorPoint(sc->anchorPointForShape(_player->getName()));
}

void GameLayer::touchLeft(Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            log("TOUCH_EVENT_BEGIN");
            _leftTurning = true;
            _rightTurning = false;
            break;
        case Widget::TouchEventType::MOVED:
            log("TOUCH_EVENT_MOVED");
            break;
        case Widget::TouchEventType::ENDED:
            log("TOUCH_EVENT_ENDED");
            _leftTurning = false;
            break;
        case Widget::TouchEventType::CANCELED:
            log("TOUCH_EVENT_CANCELED");
            _leftTurning = false;
            break;
        default:
            break;
    }
}

void GameLayer::touchRight(Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            log("TOUCH_EVENT_BEGIN");
            _rightTurning = true;
            _leftTurning = false;
            break;
        case Widget::TouchEventType::MOVED:
            log("TOUCH_EVENT_MOVED");
            break;
        case Widget::TouchEventType::ENDED:
            log("TOUCH_EVENT_ENDED");
            _rightTurning = false;
            break;
        case Widget::TouchEventType::CANCELED:
            log("TOUCH_EVENT_CANCELED");
            _rightTurning = false;
            break;
        default:
            break;
    }
}

void GameLayer::gameOver()
{
    log("game over");
    _player->setVisible(false);
}
