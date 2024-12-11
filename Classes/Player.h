#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H_
#include <iostream>
#include <string>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

struct Object {
	;
};

struct Bonus {
	Object object;
	Equipment equipment;
	int exp = 0;
};

/* 方向 */
enum dir {
	LEFT,    // 0
	RIGHT,   // 1
	UP,      // 2
	DOWN     // 3
};

/* 生物基类 */
class Creature :public Node {
protected:
	string role;     // 角色名:用于检索图片素材

	bool isDead;     // 生死状态
	int hp;          // 基础生命
	int mp;          // 基础魔力
	int atk;         // 基础攻击值
	int atk_range;   // 攻击范围
	int def;         // 基础防御值
	int speed;       // 速度
	int level;       // 等级

	float scale;     // 缩放比例
	Scene* scene;    // 场景指针
public:
	Sprite* mySprite; // 精灵
	int face_to;      // 面朝方向

	/* levelBonus */
	void levelBonus() {
		speed = speed * (0.05 * level + 1);
		hp = level * hp;
		mp = mp * level;
		atk = atk * level;
		def = def * level;
	}

	/* 构造函数 */
	// who:玩家为Player1~Player5,NPC为npc1~npc5
	// 建议:speed默认设为50,atk_range默认设100
	Creature(string role, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y,float scale,Scene* scene) :
		role(role), hp(hp), mp(mp), atk(atk), atk_range(atk_range), def(def), speed(speed), level(level),scale(scale),
		face_to(DOWN), isDead(false), scene(scene), mySprite(nullptr) {
		// 精灵初始化
		mySprite = Sprite::create("Role/" + role + "/1.png");
		mySprite->setPosition(Vec2(x, y));
		mySprite->setScale(scale);
		scene->addChild(mySprite);
		
		levelBonus();
	}

	// 空的构造函数，供调试
	Creature() {
		scale = 1.0f;
		scene = nullptr;
		face_to = DOWN;
		mySprite = nullptr;
		isDead = false;
		hp = 1;
		mp = 1;
		atk = 1;
		atk_range = 20;
		def = 1;
		speed = 10;
		level = 1;
	}

	/* 释放攻击技能 */
	// dir为方向:LEFT RIGHT UP DOWN,默认为DOWN
	// 对于部分怪物,无方向一说:Monster1树妖
	// opp为攻击对象
	virtual void Attack(int dir = DOWN, Creature* opp = nullptr);

	/* 受伤 */
	virtual void Hurt();

	/* 死亡 */
	// 死亡后移动、攻击技能均被锁定，直至复活
	virtual void Die();

	/* 复活 */
	virtual void Revive();

	/* 恢复 */
	virtual void Heal();

	/* 移动 */
	// Monster1:树妖,无法移动
	// Monster2:哥布林,可四方向移动
	virtual void Move(int dir);

	/* 等级加成 */
	//virtual void Level_Bonus();

	/* 转变场景 */
	virtual void ChangeScene(Scene* sc) { //需要修改，与地图对接，需要地图类返回GetScene的值（一个类型为Scene*的scene)
		scene = sc;
	}

	/* 获取速度speed */
	int getSpeed()const { return speed; }

	/* 获取攻击范围atk_range */
	int getAtkRange()const { return atk_range; }
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

	// 角色的武器
	weapon* _weapon;

	// 角色的护甲
	armor* _armor;

	// 角色的鞋子
	shoes* _shoes;

	// 角色的饰品
	accessories* _accessories;

	// 技能，以组合技形式出现
	void Combo();

	//获得奖励，参数Bonus结构体,结构体内需含有经验值，物品部分交给背包
	void GetBonus(Bonus bonus);

	// 赋值运算符重载
	Player& operator=(const Player& other)
	{
		if (this == &other)  // 自赋值检查
			return *this;
		level = other.level;
		hp = other.hp;
		mp = other.hp;
		atk = other.atk;
		def = other.def;
		speed = other.speed;
		_weapon = other._weapon;
		_armor = other._armor;
		_shoes = other._shoes;
		_accessories = other._accessories;

		return *this;
	}
};

#endif //__PLAYER_H__