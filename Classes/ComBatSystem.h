#ifndef __Combat_System_H__
#define __Combat_System_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
struct Equipment {//交由背包完成
	int a;
};
struct Bonus {
	int exp;
	int object;
	Equipment equipment;
};
class Creature {
private:
	string name;//就是name
	int hp;//基础生命
	int mp;//基础魔力
	int atk;//基础攻击值
	int atk_range;//攻击范围
	int def;//基础防御值
	int speed;//速度
	int level;//等级
	Scene* scene;//所在场景？
	int x;//坐标
	int y;
	Sprite* mySprite;//精灵

public:
	Creature(string name,int hp, int mp, int atk, int def, int speed, int level,int x,int y) :
		name(name),hp(hp), mp(mp), atk(atk), def(def), speed(speed), level(level) {//缺少对scene的初始化
		Level_Bonus();
	}
	// 空的构造函数，供调试
	Creature() {
		hp = 1;
		mp = 1;
		atk = 1;
		def = 1;
		speed = 10;
		level = 1;
	}
	// 攻击,对s赋值时最好不要使用Player和Monster，或将Monster的图片也装进role/player文件夹里
	//s = "Role/     ->Player<-     /" + name + "/attack" + std::to_string(idx) + "/" + name + "_atk" + std::to_string(idx) + "_";
	//以下几个函数相同
	virtual void Attack(Creature target,int idx);
	//受伤
	void Hurt(int atk);
	//死亡
	void Die();
	//恢复
	virtual void Heal();

	// 静止
	virtual void Show();
	//移动
	virtual void Move();
	//等级加成
	virtual void Level_Bonus();
	// 转变场景
	virtual void ChangeScene(Scene* sc)  {//需要修改，与地图对接，需要地图类返回GetScene的值（一个类型为Scene*的scene)
		scene = sc;
	}
};
//角色类
class Player :public Creature {
private:
	int current_exp;//角色现有经验值
	int next_level_exp;//达到下一级所需经验值
public:
	Player(string name, int hp, int mp, int atk, int def, int speed, int level, int x, int y) :
		Creature(name, hp, mp, atk, def, speed, level, x, y) {
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
	 void GetBonus() {
		 ;
	 }
	 //战斗状态
	 void IsInCombat();
};
//怪物类
class Monster :public Creature {
private:
	Bonus bonus;
	int base_exp;//怪物的基础经验值
public:
	Monster(string name, int hp, int mp, int atk, int def, int speed, int level, int x, int y) :
		Creature(name, hp, mp, atk, def, speed, level, x, y) {
		Level_Bonus();
		;//暂待
	}
	//奖励
	void Bonus();
	//触发战斗
	void StartFight();
	//寻路，徘徊，或静止

};

#endif// __Combat_System_H__
