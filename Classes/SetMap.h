#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include"cocos2d.h"

class SetMap :public cocos2d::Scene {
public:
	/*生成场景函数*/
	static cocos2d::Scene* createScene();

	/*初始化地图函数*/
	virtual bool init();

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__