
#include "Monster.h"
USING_NS_CC;


// 基本动作
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));




//update的重写
//距离小于怪物攻击距离时，怪物攻击
//距离小于怪物跟随距离时，怪物跟随
//距离超过怪物跟随距离，怪物的状态回原态
void Monster::update(float dt) {
	//怪物AI
	ai.update(dt);
	state = ai.GetState();
	//根据状态实现对应行为
}
//怪物死亡机制
void Monster::Die() {

	target->GetBonus(bonus);

	Creature::Die();
}

void Monster::Chase() {
	Vec2 direction = target->getPosition() - this->getPosition();//方向
	direction.normalize();//单位化
	Vec2 newPosition = this->getPosition() + direction * this->getSpeed() * DELTATIME;//这一帧移动方向
	this->setPosition(newPosition);
}
//怪物等级加成
void Monster::levelBonus() {
	Creature::levelBonus();
	base_exp = base_exp * level;
}
//返回follow_range
int Monster::GetFollowRange()const {
	return follow_range;
}


//ai的update
void MonsterAI::update(float dt) {
	switch (currentState) {
	case MonsterState::PATROLLING:// 执行巡逻逻辑

		if (shouldChasePlayer()) {
			currentState = MonsterState::CHASE;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		break;
	case MonsterState::CHASE:// 执行追踪玩家逻辑

		if (shouldAttackPlayer()) {
			currentState = MonsterState::ATTACK;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		break;
	case MonsterState::ATTACK:	// 执行攻击逻辑

		if (!shouldAttackPlayer()) {
			currentState = MonsterState::CHASE;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		break;
	}
}
//判断是否攻击
bool MonsterAI::shouldAttackPlayer() {
	float distance = monster->getPosition().distance(target->getPosition());
	if (distance <= monster->getAtkRange()) {
		return true;
	}
	return false;
}
//判断是否追踪
bool MonsterAI::shouldChasePlayer() {
	float distance = monster->getPosition().distance(target->getPosition());
	if (distance < monster->GetFollowRange()&&distance>monster->getAtkRange()) {
		return true;
	}
	return false;
}
bool MonsterAI::shouldFlee() {
	if (monster->getCurrentHp() < monster->getHp() / 10) {
		return true;
	}
	else if (monster->getCurrentHp() < 3 * target->DamageCal(target,monster)) {
		return true;
	}


}
//返回现状态
MonsterState MonsterAI::GetState()const {
	return currentState;
}

