#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H_
#include <iostream>
#include <string>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
/*
class Creature :public Node {
protected:
	string role;//就是name
	int hp;//基础生命
	int mp;//基础魔力
	int atk;//基础攻击值
	int atk_range;//攻击范围
	int def;//基础防御值
	int speed;//速度
	int level;//等级
	int x;//坐标
	int y;

	Sprite* mySprite;//精灵
	Scene* scene;//所在场景？
public:
	Creature(string role, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y) :
		role(role), hp(hp), mp(mp), atk(atk), atk_range(atk_range), def(def), speed(speed), level(level),
		scene(nullptr), mySprite(nullptr) {
		Level_Bonus();
	}
	// 空的构造函数，供调试
	Creature() {
		hp = 1;
		mp = 1;
		atk = 1;
		atk_range = 20;
		def = 1;
		speed = 10;
		level = 1;
	}
	// 攻击,对s赋值时最好不要使用Player和Monster，或将Monster的图片也装进role/player文件夹里
	//s = "Role/     ->Player<-     /" + name + "/attack" + std::to_string(idx) + "/" + name + "_atk" + std::to_string(idx) + "_";
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
//角色类
class Player :public Creature {
private:
	int current_exp;//角色现有经验值
	int next_level_exp;//达到下一级所需经验值
public:
	Player(string name, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y) :
		Creature(name, hp, mp, atk, atk_range, def, speed, level, x, y), current_exp(0), next_level_exp(100) {
		string s = "Role/Player/" + name + "/" + name;
		auto mySprite = Sprite::create(s + ".png");
		mySprite->setPosition(Vec2(x, y));
		Level_Bonus();
	}
	//装备，加成数值，不考虑贴图,需要与背包对接,参数是一个Equipment结构体，结构体内需要含atk和def，即攻击和防御
	void Equipment() {
		;
	}
	// 技能，以组合技形式出现
	void Combo();
	//获得奖励，参数Bonus结构体,结构体内需含有经验值，物品部分交给背包
	void GetBonus(Bonus bonus);
	//战斗状态
	void IsInCombat();
};
*/
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

#endif __PLAYER_H__