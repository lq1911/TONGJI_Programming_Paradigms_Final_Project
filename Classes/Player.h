#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H_
#include <iostream>
#include <string>
#include "cocos2d.h"
#include "Creature.h"
USING_NS_CC;
using namespace std;

//交由背包完成
struct Equipment {
	int a;
};

struct Object {
	;
};

struct Bonus {
	Object object;
	Equipment equipment;
	int exp = 0;
};



class Player :public Creature {
private:
	int current_exp;       // 角色现有经验值
	int next_level_exp;    // 达到下一级所需经验值
protected:
	// 玩家名字在Creature类里已定义了:(	

   //int x, y;       // 坐标
public:
	// 精灵//Creature中有了:( 

	/* 构造函数 */
	// who:玩家为Player1~Player5,NPC为npc1~npc5
	// 建议:speed默认设为50,atk_range默认设100
	Player(std::string who, Scene* scene, int x, int y, float scale, int hp, int mp, int atk, int atk_range, int def, int speed, int level):
		Creature(who, hp, mp, atk, atk_range, def, speed, level, x, y, scale, scene) {
		// 角色现有经验值、达到下一级所需经验值初始化条件记得改
		current_exp = 0;
		next_level_exp = 0;
	}

	/* 释放攻击技能 */
	// dir为方向:LEFT RIGHT UP DOWN,默认为DOWN
	// 对于部分怪物,无方向一说:Monster1树妖
	// opp为攻击对象
	//virtual void Attack(int dir = DOWN, Player* opp = nullptr);

	//装备，加成数值，不考虑贴图,需要与背包对接,参数是一个Equipment结构体，结构体内需要含atk和def，即攻击和防御
	void Equipment() {
		;
	}

	// 技能，以组合技形式出现
	void Combo();

	//获得奖励，参数Bonus结构体,结构体内需含有经验值，物品部分交给背包
	void GetBonus(Bonus bonus);

};

#endif //__PLAYER_H__