#ifndef __NPC_H__
#define __NPC_H__
#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

/* 触发距离 */
const int DIST = 100;

class NPC :public Creature {
private:
	Player* who;   // 玩家
public:
	/* 构造函数 */
	NPC(std::string role, int x, int y, float scale, Scene* scene, Player* player) :Creature(role, 0, 0, 0, 0, 0, 0, 0, x, y, scale, scene) { 
		who = player;
	}

	/* 判断是否在触发范围内 */
	bool isTrigger();

	void Chat();
};


#endif __NPC_H__