#ifndef __Battle_System_H__
#define __Battle_System_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
// 基本动作
auto attackAction =  MoveBy::create(1.0f,  Vec2(100, 0));



class Creature {
private:
	string name;//就是who
	int hp;
	int mp;
	int atk;
	int def;
	int speed;
	int level;
	
public:
	Creature(string name,int hp, int mp, int atk, int def, int speed, int level) :
		name(name),hp(hp), mp(mp), atk(atk), def(def), speed(speed), level(level) {
		;
	}
	Creature() {
		hp = 1;
		mp = 1;
		atk = 1;
		def = 1;
		speed = 10;
		level = 1;
	}
	virtual void Attack();
	virtual void Combo();
};
void Creature::Attack() {
	int a;
}
class Player :public Creature {
private:
	
public:
	Player(string name,int hp, int mp, int atk, int def, int speed, int level) :
		Creature(name,hp, mp, atk, def, speed, level) {
		
	}
	void Attack() override {
		;
	}

};

class Monster :public Creature {
private:
public:
	
};













#endif// __Battle_System_H__
