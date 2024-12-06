/*
#ifndef __Combat_System_H__
#define __Combat_System_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

struct Equipment {//交由背包完成
	int a;
};
struct Object {
	;
};
struct Bonus {
	Object object;
	Equipment equipment;
	int exp=0;
};
enum class State {
	IDLE, //空闲，静止，用于Npc
	WALKING, //行走，随机，用于Npc和怪物
	COMBATING // 战斗，用于怪物
};
enum class MonsterState {
	PATROLLING,//巡逻
	CHASE,//追踪
	ATTACK,//攻击
	FLEE//逃跑
};
class Creature:public Node {
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
	Creature(string role,int hp, int mp, int atk,int atk_range, int def, int speed, int level,int x,int y) :
		role(role),hp(hp), mp(mp), atk(atk),atk_range(atk_range), def(def), speed(speed), level(level),
		scene(nullptr),mySprite(nullptr) {
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
	virtual void Attack(Node* target,int idx);
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
	Player(string name, int hp, int mp, int atk,int atk_range, int def, int speed, int level, int x, int y) :
		Creature(name, hp, mp, atk,atk_range, def, speed, level, x, y),current_exp(0),next_level_exp(100) {
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
//怪物类
class Monster :public Creature {
private:
	int follow_range;
	Bonus bonus;//击杀奖励
	int base_exp;//怪物的基础经验值
	Player* target;
	MonsterAI ai = MonsterAI(target);
	MonsterState state;
public:
	Monster(string name, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y,
		MonsterState state, int exp, Bonus bonus, Player* player, int follow_range) :
		Creature(name, hp, mp, atk, atk_range, def, speed, level, x, y),
		base_exp(exp), bonus(bonus), follow_range(follow_range),state(state) {
		Level_Bonus();
		bonus.exp = base_exp;
		;//暂待
		target = player;
		//需要GameScene中添下这一句
		// this->scheduleUpdate();
	}
	void update(float dt)override;
	void Level_Bonus()override;
	//死亡
	void Die()override;
	// 执行巡逻逻辑
	void Patrol();
	// 追踪
	void Chase();
	// 攻击玩家
	void Attack();
	//寻路，徘徊，或静止
};
//怪物AI类
class MonsterAI {
private:
	MonsterState currentState;//怪物状态
	Player* target;
	
public:
	MonsterAI(Player* target) : currentState(MonsterState::PATROLLING), target(target) {}//默认为巡逻
	//判断是否追踪
	bool shouldChasePlayer();
	//判断是否攻击
	bool shouldAttackPlayer();
	//判断是否逃跑
	bool shouldFlee();
	//update函数
	void update(float dt);
	//返回现状态
	MonsterState GetState()const;
};
#endif// __Combat_System_H__

*/