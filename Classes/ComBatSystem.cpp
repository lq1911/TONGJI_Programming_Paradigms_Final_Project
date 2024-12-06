/*
#include "CombatSystem.h"
USING_NS_CC;


// 基本动作
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));


//攻击
void Creature::Attack(Node* target,int idx) {
	//计算攻击范围
	//如果target在攻击范围内
	//target.Hurt(atk);
	//动画实现
	// 图片名前缀:除编号部分
	string s;
	if (idx == 1 || idx == 2)
		s = "Role/Player/" + role + "/attack" + std::to_string(idx) + "/" + role + "_atk" + std::to_string(idx) + "_";
	else if (idx == 3)
		s = "Role/Player/" + role + "/attack_final/" + role + "_final_";
	// 帧数
	int count = 0;
	if (role == "Arthur") {
		if (idx == 1)
			count = 10;
		else if (idx == 2)
			count = 12;
		else if (idx == 3)
			count = 15;
	}
	else if (role == "Longbow") {
		if (idx == 1)
			count = 7;
		else if (idx == 2)
			count = 12;
		else if (idx == 3)
			count = 18;
	}
	// 帧动画准备
	Vector<SpriteFrame*> animFrames;//储存动画帧的容器
	animFrames.reserve(count);//分配内存
	//创建（单个）动画对象，将其装入容器中
	for (int i = 1; i <= count; i++) {
		auto texture = Director::getInstance()->getTextureCache()->addImage(s + std::to_string(i) + ".png");
		float width = texture->getPixelsWide();
		float height = texture->getPixelsHigh();
		Rect rectInPixels(0, 0, width, height);
		auto spriteFrame = SpriteFrame::createWithTexture(
			texture,
			CC_RECT_PIXELS_TO_POINTS(rectInPixels)
		);
		animFrames.pushBack(spriteFrame);
	}
	//动画
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	//Animate动作
	Animate* animate = Animate::create(animation);
	// mySprite->runAction(RepeatForever::create(animate));
	mySprite->runAction(animate);  // 播放一次
	scene->addChild(mySprite);//添加至场景
}
//静止
void Creature::Show() {
	mySprite->setPosition(Vec2(x, y));
	scene->addChild(mySprite);
}
//移动
void Creature::Move() {

}
//Player获得奖励
void Player::GetBonus(Bonus bonus) {
	//经验奖励
	current_exp += bonus.exp;
	//升级
	while (current_exp >= next_level_exp) {
		current_exp -= next_level_exp;
		level++;
		Creature::Level_Bonus;
		next_level_exp *= (1 + level * 0.1);
	}
	//物品奖励
	//暂待，需物品和装备
}


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
//等级加成
void Creature::Level_Bonus() {
	int hp = hp * level;
	int mp = mp * level;
	int atk = atk * level;
	
	int def = def * level;
	int speed = speed * (0.05 * level + 1);

}
//怪物等级加成
void Monster::Level_Bonus() {
	Creature::Level_Bonus();
	base_exp = base_exp * level;
}
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
//返回现状态
MonsterState MonsterAI::GetState()const {
	return currentState;
}

*/