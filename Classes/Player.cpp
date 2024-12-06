#include <iostream>
#include <string>
#include "Player.h"

/* 攻击动画 */
void Player::Attack(int dir) {
    /* 更改面朝方向 */
    face_to = dir;

    /* 图片名前缀:除编号部分 */
    std::string s = "Role/" + who + "atk/";

    /* 根据方向确认第一张图片 */
    int start = 1;
    if (face_to == DOWN)
        start = 1;
    else if (face_to == LEFT)
        start = 5;
    else if (face_to == RIGHT)
        start = 9;
    else if (face_to == UP)
        start = 13;

    // 当前帧索引
    int currentFrame = 0;

    /* 帧动画 */
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(8);
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
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    Animate* animate = Animate::create(animation);

    player->stopAllActions(); // 攻击前可停止之前动作保证连贯性
    player->runAction(animate);

    CCLOG("%s attack", who); 
}

/* 走路动画 */
void Player::Move(int dir) {
    /*
    std::string s;
    s = "Role/" + who + "atk/";
    int start = 1;
    // 根据方向选择帧动画起始帧
    Vec2 moveBy;
    if (face_to == DOWN) {
        start = 1;
        moveBy = Vec2(0, -100);
    }
    else if (face_to == LEFT) {
        start = 5;
        moveBy = Vec2(-100, 0);
    }
    else if (face_to == RIGHT) {
        start = 9;
        moveBy = Vec2(100, 0);
    }
    else if (face_to == UP) {
        start = 13;
        moveBy = Vec2(0, 100);
    }


    // 创建帧动画
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

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    Animate* animate = Animate::create(animation);

    // 创建移动动作
    auto moveAction = MoveBy::create(0.3f, moveBy);

    // 同时执行动画和移动
    auto moveAndAnimate = Spawn::create(animate, moveAction, nullptr);

    // 执行动作
    player->runAction(moveAndAnimate);
    scene->addChild(player);
    */
}

/* 等级加成 */
void Player::Level_Bonus() {
    level++;
}