#pragma once

#include <iostream>
#include <string>
#include "cocos2d.h"

USING_NS_CC;

class Player {
public:
	/* 显示玩家 */
	// who:角色名字
	//	   Arthur/Longbow
	// scene:场景指针,要将角色打印在哪个场景中
	// scale:缩放比例
	// (x,y)打印坐标
	void showPlayer(std::string who, Scene* scene, float scale, int x, int y);
	/* 玩家释放攻击技能 */
	// who:角色名字
	// scene:场景指针,要将角色打印在哪个场景中
	// idx:技能种类(1/2/3),1/2是普通攻击3是大招
	// scale:缩放比例
	// (x,y)打印坐标
	void PlayerAttack(std::string who, Scene* scene, int idx, float scale, int x, int y);
	/* 走路动画 */
	void PlayerMove(std::string who, Scene* scene, float scale, int x, int y, int direction);
};