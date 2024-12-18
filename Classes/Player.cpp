#include <string>
#include "Player.h"
#include "Monster.h"

// update
void Player::update(float dt) {
    Vec2 pos = mySprite->getPosition();
    static int nums = 50;
    if (nums < 60) {
        nums++;
    }
    else {
        nums = 0;
        /*
        log("player**********************************");
        log("position:%f %f", pos.x, pos.y);
        log("hp:%d", hp);
        log("mp:%d", mp);
        log("atk:%d", atk);
        log("def:%d", def);
    */
    }
}

void Player::InitMonster(vector<Monster*>monster) {
    this->monster = monster;
}

// 人物攻击
// 攻击范围是扇形
Animate* Player::Attack(int dir, vector<Monster*> monster) {
    Vec2 pos_player = mySprite->getPosition();
    for (int i = 0; i < monster.size(); i++) {
        Vec2 pos_monster = monster[i]->mySprite->getPosition();
        float distance = pos_monster.distance(pos_player);
        if (distance < atk_range) {
            Vec2 direction = pos_monster - pos_player;// 人物指向怪物
            float k = (direction.x+1.0-1.0) / direction.y;// 斜率
          if(dir==0&&k<1&&k>-1&&direction.x<0)// 向左
            Creature::Attack(dir, monster[i]);
          else if(dir == 1 && k<1 && k>-1 && direction.x > 0)// 右
              Creature::Attack(dir, monster[i]);
          else if(dir == 2 && (k<-1 || k>1) && direction.y > 0)// 上
              Creature::Attack(dir, monster[i]);
          else if(dir == 3 && (k < -1 || k>1) && direction.y < 0)// 下
              Creature::Attack(dir, monster[i]);
        }
    }
    return nullptr;
}

// Player获得奖励
void Player::GetBonus(Bonus bonus) {
    //经验奖励
    current_exp += bonus.exp;
    //升级
    while (current_exp >= next_level_exp) {
        current_exp -= next_level_exp;
        level++;
        next_level_exp *= (1 + level * 0.1);
    }

    //物品奖励
    //暂待，需物品和装备
    
}

// 判断交互范围
bool Player::isTrigger(const Vec2& pos) {
   
    int dx = mySprite->getPosition().x - x;
    int dy = mySprite->getPosition().y - y;

    return std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(DIST, 2);

}
