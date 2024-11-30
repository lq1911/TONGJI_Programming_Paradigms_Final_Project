#ifndef __MICRO_MAP_H__
#define __MICRO_MAP_H__

#include "cocos2d.h"
#include<string>

class MicroMap : public cocos2d::Node {
private:


public:
    /*创建微缩大地图*/
    static MicroMap* create(const std::string& mapName);

    /*初始化微缩大地图*/
    bool init(const std::string& mapName);




};

#endif // __MICRO_MAP_H__