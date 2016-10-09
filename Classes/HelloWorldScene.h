#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "GlobalDefine.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void onExit();

    CREATE_FUNC(HelloWorld);
    
    void loadingTextureCallBack(cocos2d::Texture2D *texture);
    void loadingAudio();
    void initUserData();
    void nextScene(float dt);
    
private:
    int _loadedNum;
    std::thread *_loadingAudioThread;
};

#endif // __HELLOWORLD_SCENE_H__
