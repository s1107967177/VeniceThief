//
//  GlobalData.h
//  VeniceThief
//
//  Created by 唐家琪 on 16/2/8.
//
//

#ifndef GlobalData_h
#define GlobalData_h

#include "cocos2d.h"

class GlobalData
{
public:
    static GlobalData *getInstance();
    //当前选择关卡
    ssize_t selectedGate;
    //地图长度
    float mapLength;
    
    cocos2d::Node *getRootNode();
    std::vector<std::string> getObstacleNames();
    cocos2d::Vector<cocos2d::Sprite*> getObstaclesByName(const std::string name);
    
private:
    GlobalData();
    virtual ~GlobalData();
    
    static GlobalData *pInstance;
    
    cocos2d::Vector<cocos2d::Node*> rootNodes;
    std::vector<std::vector<std::string> > obstacleNamesOfEachGate;
};

#endif /* GlobalData_h */
