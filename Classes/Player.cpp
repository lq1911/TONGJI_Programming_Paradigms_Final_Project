#include <iostream>
#include <string>
#include "Player.h"

/* 显示玩家 */
void Player::showPlayer(std::string who, Scene* scene, float scale, int x, int y) {
    std::string str;
    str = "Role/Player/" + who + "/" + who + ".png";
    auto mySprite = Sprite::create(str);
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);
    scene->addChild(mySprite);
}

/* 攻击动画 */
void Player::PlayerAttack(std::string who, Scene* scene, int idx, float scale, int x, int y) {
    // 图片名前缀:除编号部分
    std::string s;
    if (idx == 1 || idx == 2)
        s = "Role/Player/" + who + "/attack" + std::to_string(idx) + "/" + who + "_atk" + std::to_string(idx) + "_";
    else if (idx == 3)
        s = "Role/Player/" + who + "/attack_final/" + who + "_final_";

    // 精灵初始化
    auto mySprite = Sprite::create(s + "0.png");
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);

    // 帧数
    int count = 0;  
    if (who == "Arthur") {
        if (idx == 1) 
            count = 10;   
        else if (idx == 2) 
            count = 12;
        else if (idx == 3) 
            count = 15;
    }
    else if (who == "Longbow") {
        if (idx == 1)
            count = 7;
        else if (idx == 2)
            count = 12;
        else if (idx == 3)
            count = 18;
    }
    Vector<SpriteFrame*> animFrames;
   
    // 模拟动画
    animFrames.reserve(count);
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

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);
    // mySprite->runAction(RepeatForever::create(animate));
    mySprite->runAction(animate);  // 播放一次
    scene->addChild(mySprite);
}

/* 走路动画 */
void Player::PlayerMove(std::string who, Scene* scene, float scale, int x, int y, int direction) {
    // 图片名前缀
    std::string s = "Role/Player/" + who + "/move/" + who + "_move_";

    // 精灵初始化
    auto mySprite = Sprite::create(s + "0.png");
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);


}