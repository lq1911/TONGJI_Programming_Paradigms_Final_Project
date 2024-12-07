#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include "cocos2d.h"
#include "MicroMap.h"
#include "Player.h"
#include "SetPlayerScene.h"


class SetMap :public cocos2d::Scene {
private:


	MicroMap* MicroMap;     // 微地图对象
	bool IsMicroMapVisible;     // 微地图是否可见

	int PlayerInWhichMap;  // 当前玩家所在的地图编号
public:
	Player* PLAYER;

	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
			PLAYER->Attack(UP);
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
			PLAYER->Attack(DOWN);
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)
			PLAYER->Attack(LEFT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
			PLAYER->Attack(RIGHT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
			PLAYER->Move(DOWN);
		else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
			PLAYER->Move(UP);
		else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			PLAYER->Move(LEFT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			PLAYER->Move(RIGHT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_T)
			PLAYER->Hurt();
	}

	/*生成场景函数*/
	static cocos2d::Scene* createScene();

	/*初始化地图函数*/
	virtual bool init();

	// 键盘事件处理,按下M键切换显示微地图
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__