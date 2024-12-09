#include <iostream>
#include <string>
#include "Player.h"

/* 攻击动画 */
void Player::Attack(int dir, Player* opp) {
    // 死了,直接返回
    if (isDead)
        return;

    /* Monster1:树妖 */
    if (who == "Monster1") {
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(8);
        for (int i = 17; i <= 24; i++) {
            auto texture = Director::getInstance()->getTextureCache()->addImage("Role/" + who + "/" + std::to_string(i) + ".png");
            float width = texture->getPixelsWide();
            float height = texture->getPixelsHigh();
            Rect rectInPixels(0, 0, width, height);
            auto spriteFrame = SpriteFrame::createWithTexture(
                texture,
                CC_RECT_PIXELS_TO_POINTS(rectInPixels)
            );
            animFrames.pushBack(spriteFrame);
        }
        // 播放
        Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
        Animate* animate = Animate::create(animation);
        player->stopAllActions();
        player->runAction(animate);
        CCLOG("%s attack", who);
        // 对手受伤动画
        if (opp != nullptr) {
            opp->Hurt();
        }
        // 退出
        return;
    }

    /* 玩家角色 */
    // 更改面朝方向
    face_to = dir;
    // 图片名前缀:除编号部分
    std::string s = "Role/" + who + "atk/";
    // 根据方向确认第一张图片 
    int start = 1;
    if (face_to == DOWN)
        start = 1;
    else if (face_to == LEFT)
        start = 5;
    else if (face_to == RIGHT)
        start = 9;
    else if (face_to == UP)
        start = 13;
    // 帧动画
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(9);
    for (int j = 0; j < 2; j++) {
        for (int i = start; i < start + 4; i++) {
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
    }
    auto texture = Director::getInstance()->getTextureCache()->addImage("Role/"+who+"/" + std::to_string(start) + ".png");
    float width = texture->getPixelsWide();
    float height = texture->getPixelsHigh();
    Rect rectInPixels(0, 0, width, height);
    auto spriteFrame = SpriteFrame::createWithTexture(
        texture,
        CC_RECT_PIXELS_TO_POINTS(rectInPixels)
    );
    animFrames.pushBack(spriteFrame);
    // 播放
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);
    player->stopAllActions(); 
    player->runAction(animate);
    CCLOG("%s attack", who); 
    // 对手受伤动画
    if (opp != nullptr) {
        opp->Hurt();
    }
}

/* 受伤动画 */
void Player::Hurt() {
    // 死了,直接返回
    if (isDead) {
        return;
    }

    /* Monster1:树妖 */
    if (who == "Monster1") {
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(4);
        for (int i = 13; i <= 16; i++) {
            auto texture = Director::getInstance()->getTextureCache()->addImage("Role/" + who + "/" + std::to_string(i) + ".png");
            float width = texture->getPixelsWide();
            float height = texture->getPixelsHigh();
            Rect rectInPixels(0, 0, width, height);
            auto spriteFrame = SpriteFrame::createWithTexture(
                texture,
                CC_RECT_PIXELS_TO_POINTS(rectInPixels)
            );
            animFrames.pushBack(spriteFrame);
        }
        // 播放
        Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
        Animate* animate = Animate::create(animation);
        player->stopAllActions();
        player->runAction(animate);
        CCLOG("%s hurt", who);
        return;
    }

    /* 玩家角色 */
    std::string s = "Role/" + who + "atked/";
    // 根据方向确认第一张图片
    int start = 1;
    if (face_to == DOWN)
        start = 1;
    else if (face_to == LEFT)
        start = 5;
    else if (face_to == RIGHT)
        start = 9;
    else if (face_to == UP)
        start = 13;
    // 帧动画
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(4);
    for (int i = start; i < start + 4; i++) {
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
    // 播放
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    Animate* animate = Animate::create(animation);
    player->stopAllActions();
    player->runAction(animate);

    CCLOG("%s hurt", who);
}

/* 走路动画 */
void Player::Move(int dir) {
    // 死了,直接返回
    if (isDead) {
        return;
    }

    /* 更改面朝方向 */
    face_to = dir;

    /* 图片名前缀:除编号部分 */
    std::string s = "Role/" + who + "/";

    /* 根据方向确认第一张图片及移动路径 */
    Vec2 moveBy;
    int start = 1;
    if (face_to == DOWN) {
        start = 1;
        moveBy = Vec2(0, -speed);
    }
    else if (face_to == LEFT) {
        start = 5;
        moveBy = Vec2(-speed, 0);
    }
    else if (face_to == RIGHT) {
        start = 9;
        moveBy = Vec2(speed, 0);
    }
    else if (face_to == UP) {
        start = 13;
        moveBy = Vec2(0, speed);
    }

    // 创建帧动画
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(5);
    for (int i = start; i < start + 4; i++) {
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
    auto texture = Director::getInstance()->getTextureCache()->addImage(s + std::to_string(start) + ".png");
    float width = texture->getPixelsWide();
    float height = texture->getPixelsHigh();
    Rect rectInPixels(0, 0, width, height);
    auto spriteFrame = SpriteFrame::createWithTexture(
        texture,
        CC_RECT_PIXELS_TO_POINTS(rectInPixels)
    );
    animFrames.pushBack(spriteFrame);

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);

    // 创建移动动作
    auto moveAction = MoveBy::create(0.3f, moveBy);

    // 同时执行动画和移动
    auto moveAndAnimate = Spawn::create(animate, moveAction, nullptr);

    // 执行动作
    player->stopAllActions();
    player->runAction(moveAndAnimate);

}

/* 死亡 */
void Player::Die() {
    // 已经死了,直接返回
    if (isDead) {
        return;
    }

    isDead = true;
    face_to = DOWN;
    /* Monster1:树妖 */
    if (who == "Monster1") {
        player->stopAllActions();
        player->setTexture("Role/" + who + "/25.png");
        return;
    }
    /* 玩家角色 */
    player->stopAllActions();
    player->setTexture("Role/" + who + "atked/17.png");
    player->setPosition(Vec2(player->getPosition().x, player->getPosition().y - 30));
}

/* 复活 */
void Player::Revive() {
    isDead = true;
    face_to = DOWN;
    player->stopAllActions();
    player->setTexture("Role/" + who + "atked/17.png");
    player->setPosition(Vec2(player->getPosition().x, player->getPosition().y + 30));
}

/* 等级加成 */
void Player::LevelBonus() {
    level++;
}
/*
//攻击
void Creature::Attack(Node* target, int idx) {
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
//等级加成
void Creature::Level_Bonus() {
    int hp = hp * level;
    int mp = mp * level;
    int atk = atk * level;

    int def = def * level;
    int speed = speed * (0.05 * level + 1);

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
*/