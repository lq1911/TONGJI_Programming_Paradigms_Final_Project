#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include "cocos2d.h"
#include "MicroMap.h"

class SetMap :public cocos2d::Scene {
private:
	MicroMap* MicroMap;
	bool IsMicroMapVisible;
public:
	/*生成场景函数*/
	static cocos2d::Scene* createScene();

	/*初始化地图函数*/
	virtual bool init();

	// 键盘事件处理,按下M键切换显示微地图
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__