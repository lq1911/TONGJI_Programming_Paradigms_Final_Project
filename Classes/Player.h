#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H_
#include <iostream>
#include <string>
#include "cocos2d.h"

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

	/* 构造函数 */
	// who:玩家为Player1~Player5,NPC为npc1~npc5
	// 建议:speed默认设为50,atk_range默认设100
	Creature(string role, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y) :
		role(role), hp(hp* level), mp(mp* level), atk(atk* level), atk_range(atk_range), def(def* level), speed(speed* (0.05 * level + 1)), level(level),
		scene(nullptr), mySprite(nullptr), face_to(DOWN), isDead(false) {
		
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

	/* 析构函数 */
	~Creature() { 
		scene = nullptr;
		mySprite = nullptr;
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

	/* 构造函数的辅助函数 */
	void playerInit(string Role, Scene* Scene, int Scale, int Hp, int Mp, int Atk, int Atk_range, int Def, int Speed, int Level, int x, int y) {
		// 基本信息初始化
		role = Role;
		scene = Scene;
		scale = Scale;
		// 属性初始化
		face_to = DOWN;
		isDead = false;
		hp = Hp;
		mp = Mp;
		atk = Atk;
		atk_range = Atk_range;
		def = Def;
		speed = Speed;
		level = Level;
		// 精灵初始化
		mySprite= Sprite::create("Role/" + role + "/1.png");
		mySprite->setPosition(Vec2(x, y));
		mySprite->setScale(scale);
		scene->addChild(mySprite);
		// 其它
		// Level_Bonus();
	}

	/* 构造函数 */
	// who:玩家为Player1~Player5,NPC为npc1~npc5
	// 建议:speed默认设为50,atk_range默认设100
	Player(std::string who,Scene* scene,int x,int y,float scale, int hp, int mp, int atk, int atk_range, int def, int speed, int level) {
		playerInit(who, scene, scale, hp, mp, atk, atk_range, def, speed, level, x, y);
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

#endif __PLAYER_H__