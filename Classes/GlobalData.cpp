//
//  GlobalData.cpp
//  VeniceThief
//
//  Created by 唐家琪 on 16/2/8.
//
//

#include "GlobalData.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace std;

GlobalData *GlobalData::pInstance = nullptr;

GlobalData::GlobalData() {
    selectedGate = 1;
    mapLength = 15200;
    
    vector<string> g1_obstacles = {"DaYouLun", "XiaoYouLun"};
    obstacleNamesOfEachGate.push_back(g1_obstacles);
    rootNodes.pushBack(CSLoader::createNode("GateOne.csb"));
}

GlobalData::~GlobalData() {

}

GlobalData *GlobalData::getInstance() {
    if (pInstance == nullptr) {
        pInstance = new GlobalData();
    }
    return pInstance;
}

vector<string> GlobalData::getObstacleNames()
{
    vector<string> names;
    for(auto name : obstacleNamesOfEachGate[selectedGate - 1] ) {
        names.push_back(name);
    }
    return names;
}

Vector<Sprite*> GlobalData::getObstaclesByName(const string name)
{
    Vector<Sprite*> spVec;
//    auto bg = rootNodes.at(selectedGate - 1)->getChildByName<TMXTiledMap*>("Background");
    for (size_t index = 1; ; ++index) {
        __String *sp = __String::createWithFormat("%s%zu",name.c_str(),index);
        auto ob = rootNodes.at(selectedGate - 1)->getChildByName<Sprite*>(sp->getCString());
        if (ob) {
            spVec.pushBack(ob);
        }
        else {
            break;
        }
    }
    return spVec;
}

cocos2d::Node *GlobalData::getRootNode()
{
    return rootNodes.at(selectedGate - 1);
}