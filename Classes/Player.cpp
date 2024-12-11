#include <iostream>
#include <string>
#include "Player.h"

//Player获得奖励
void Player::GetBonus(Bonus bonus) {
    //经验奖励
    current_exp += bonus.exp;

    //报错，暂时注释掉
    //Creature::levelBonus;
    
    //升级
    while (current_exp >= next_level_exp) {
        current_exp -= next_level_exp;
        level++;
        //报错，暂时注释掉
        //Creature::levelBonus;
        next_level_exp *= (1 + level * 0.1);
    }
    //物品奖励
    //暂待，需物品和装备
    
}