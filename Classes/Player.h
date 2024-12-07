#pragma once

#include <iostream>
#include <string>
#include "cocos2d.h"

USING_NS_CC;

/*
class Creature :public Node {
	//以下几个函数相同
	virtual void Attack(Node* target, int idx);
	//受伤
	void Hurt(int atk);
	//死亡
	virtual void Die();
	//恢复
	virtual void Heal();
	// 静止
	virtual void Show();
	//移动
	virtual void Move();
	//等级加成
	virtual void Level_Bonus();
	// 转变场景
	virtual void ChangeScene(Scene* sc) {//需要修改，与地图对接，需要地图类返回GetScene的值（一个类型为Scene*的scene)
		scene = sc;
	}
};
*/


enum dir {
	LEFT,    // 0
	RIGHT,   // 1
	UP,      // 2
	DOWN     // 3
};

class Player :public Node {
protected:
	/* 玩家角色 */
	std::string who; // 玩家名字

	Scene* scene;    // 场景指针

	float scale;     // 缩放比例

	int face_to;    // 面朝方向dir
	int x, y;       // 坐标

	int hp;          // 基础生命
	int mp;          // 基础魔力
	int atk;         // 基础攻击值
	int atk_range;   // 攻击范围
	int def;         // 基础防御值
	int speed;       // 速度
	int level;       // 等级

	bool isDead;     // 生死状态

public:
	/* 精灵 */
	Sprite* player;

	/* 构造函数 */
	// who:玩家为Player1~Player5,NPC为npc1~npc5
	// speed默认设为50,atk_range默认设100
	Player(std::string who,Scene* scene,int x,int y,float scale, int hp, int mp, int atk, int atk_range, int def, int speed, int level) :
		who(who), scene(scene), x(x), y(y), scale(scale), hp(hp), mp(mp), atk(atk), atk_range(atk_range), def(def), speed(speed), level(level) {
		face_to = DOWN;
		isDead = false;
		player = Sprite::create("Role/" + who + "/1.png" );
		player->setPosition(Vec2(x, y));
		player->setScale(scale);
		scene->addChild(player);
	}

	/* 获取攻击范围 */
	int getAtkRange() { return atk_range; }

	/* 复活 */
	virtual void Revive();

	/* 释放攻击技能 */
	// dir为方向:LEFT RIGHT UP DOWN,默认为DOWN
	// 对于部分怪物,无方向一说:Monster1树妖
	// opp为攻击对象
	virtual void Attack(int dir = DOWN, Player* opp = nullptr);

	/* 受伤动画 */
	virtual void Hurt();
	
	/* 走路动画 */
	virtual void Move(int dir);

	/* 死亡 */
	virtual void Die();

	/* 等级加成 */
	virtual void LevelBonus();
};

