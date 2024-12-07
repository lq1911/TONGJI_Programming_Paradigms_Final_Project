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
	/* 玩家 */
	Player* PLAYER;
	/* 树妖Monster1 */
	Player* Monster1;
	/* NPC */
	Player* npc1;
	/* 按键绑定 */
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
		// 测试Monster1攻击效果用，记得删
		else if (keyCode == EventKeyboard::KeyCode::KEY_T) {
			int dx = Monster1->player->getPosition().x - PLAYER->player->getPosition().x;
			int dy = Monster1->player->getPosition().y - PLAYER->player->getPosition().y;
			if (std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(Monster1->getAtkRange(), 2))
				Monster1->Attack(DOWN, PLAYER);
			else
				Monster1->Attack();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_Y) {
			PLAYER->Die();
		}
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