#include <iostream>
#include <string>
#include "Player.h"

/* 攻击动画 */
void Player::Attack(int dir) {
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
        // 退出
        return;
    }

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

    /* 帧动画 */
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
}

/* 受伤动画 */
void Player::Hurt() {
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
    /* 更改面朝方向 */
    face_to = dir;

    /* 图片名前缀:除编号部分 */
    std::string s = "Role/" + who + "/";

    /* 根据方向确认第一张图片及移动路径 */
    Vec2 moveBy;
    int start = 1;
    if (face_to == DOWN) {
        start = 1;
        moveBy = Vec2(0, -50);
    }
    else if (face_to == LEFT) {
        start = 5;
        moveBy = Vec2(-50, 0);
    }
    else if (face_to == RIGHT) {
        start = 9;
        moveBy = Vec2(50, 0);
    }
    else if (face_to == UP) {
        start = 13;
        moveBy = Vec2(0, 50);
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

/* 等级加成 */
void Player::Level_Bonus() {
    level++;
}