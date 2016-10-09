#include "HelloWorldScene.h"
#include "GameLayer.h"
//#include "GlobalData.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize =  Director::getInstance()->getVisibleSize();
    
    auto logo = Sprite::create("logo.png");
    logo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(logo);
    
//    initUserData();
    //首次运行初始化用户数据
    if (!getBoolFromXML("isExisted")) {
        initUserData();
        setBoolToXML("isExisted", true);
        UserDefault::getInstance()->flush();
    }
    
    _loadedNum = 0;
    _loadingAudioThread = new std::thread(&HelloWorld::loadingAudio, this);
    
//    GlobalData * glData = GlobalData::getInstance();
 //   CC_UNUSED_PARAM(glData);
    
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/explosion.png", CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));
    
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/coin.png", CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));

    return true;
}

void HelloWorld::loadingTextureCallBack(Texture2D *texture)
{
    switch (_loadedNum) {
        case 0:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/explosion.plist", texture);
            schedule(schedule_selector(HelloWorld::nextScene), 1.0, 0, 1.0);
            break;
        case 1:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/coin.plist", texture);
            schedule(schedule_selector(HelloWorld::nextScene), 1.0, 0, 1.0);
            break;
            
        default:
            break;
    }
}

void HelloWorld::loadingAudio()
{
    log("LoadingAudio...");
//    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("");
//    SimpleAudioEngine::getInstance()->preloadEffect("");
}

void HelloWorld::initUserData()
{
    setBoolToXML(SOUND_KEY, true);
    setBoolToXML(MUSIC_KEY, true);
    setFloatToXML(SOUND_VOL, 0.8);
    setFloatToXML(MUSIC_KEY, 0.8);
    setIntToXML(COIN_KEY, 1000);
    setIntToXML(SPEED_X_KEY, 100);
    setIntToXML(SPEED_Y_KEY, 100);
    UserDefault::getInstance()->flush();
}

void HelloWorld::nextScene(float dt)
{
    auto sc = GameLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, sc));
}

void HelloWorld::onExit()
{
    Layer::onExit();
    _loadingAudioThread->join();
    CC_SAFE_DELETE(_loadingAudioThread);
    unschedule(schedule_selector(HelloWorld::nextScene));
}