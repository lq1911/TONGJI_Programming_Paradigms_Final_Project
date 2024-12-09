
#ifndef __Combat_System_H__
#define __Combat_System_H__
#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;
#define deltatime 1/60// 默认的帧数
using namespace std;


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


//怪物类
class Monster :public Creature {
private:
	int follow_range;
	Bonus bonus;//击杀奖励
	int base_exp;//怪物的基础经验值
	Player* target;
	MonsterAI ai{ target,this };
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
	// 返回follow_range
	int GetFollowRange()const;

};
//怪物AI类
class MonsterAI {
private:
	MonsterState currentState;//怪物状态
	Player* target;
	Monster* monster;

public:
	MonsterAI(Player* target,Monster*monster) : currentState(MonsterState::PATROLLING), target(target),monster(monster) {}//默认为巡逻
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

