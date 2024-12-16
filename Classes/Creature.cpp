#include "Creature.h"

/* 攻击动画 */
void Creature::Attack(int dir, Creature* opp) {
    // 死了,直接返回
    if (isDead)
        return;

    /* Monster1:树妖 */
    if (role == "Monster1") {
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(8);
        for (int i = 17; i <= 24; i++) {
            auto texture = Director::getInstance()->getTextureCache()->addImage("Role/" + role + "/" + std::to_string(i) + ".png");
            float width = float(texture->getPixelsWide());
            float height = float(texture->getPixelsHigh());
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
        mySprite->stopAllActions();
        mySprite->runAction(animate);
        CCLOG("%s attack", role);
        // 对手受伤动画
        if (opp != nullptr) {
            opp->Hurt();
        }
        // 退出
        return;
    }

    /* 玩家角色+Monster2+Monster3 */
    // 更改面朝方向
    face_to = dir;
    // 图片名前缀:除编号部分
    std::string s = "Role/" + role + "atk/";
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
    auto texture = Director::getInstance()->getTextureCache()->addImage("Role/" + role + "/" + std::to_string(start) + ".png");
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
    mySprite->stopAllActions();
    mySprite->runAction(animate);
    CCLOG("%s attack", role);
    // 对手受伤动画
    if (opp != nullptr) {
        opp->Hurt();
    }
}

/* 受伤动画 */
void Creature::Hurt() {
    // 死了,直接返回
    if (isDead) {
        return;
    }

    /* Monster1:树妖 */
    if (role == "Monster1") {
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(4);
        for (int i = 13; i <= 16; i++) {
            auto texture = Director::getInstance()->getTextureCache()->addImage("Role/" + role + "/" + std::to_string(i) + ".png");
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
        mySprite->stopAllActions();
        mySprite->runAction(animate);
        CCLOG("%s hurt", role);
        return;
    }

    /* 玩家角色+Monster2+Monster3 */
    std::string s = "Role/" + role + "atked/";
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
    mySprite->stopAllActions();
    mySprite->runAction(animate);

    CCLOG("%s hurt", role);
}

/* 恢复动画 */
void Creature::Heal() {
    // 死了,直接返回
    if (isDead)
        return;
    // 不是玩家,直接返回
    if ((role != "Player1" && role != "Player2" && role != "Player3" && role != "Player4" && role != "Player5"))
        return;

    /* 玩家角色 */
    std::string s = "Role/" + role + "atked/";
    // 根据方向确认第一张图片
    int start = 0;
    if (face_to == DOWN)
        start = 0;
    else if (face_to == LEFT)
        start = 1;
    else if (face_to == RIGHT)
        start = 2;
    else if (face_to == UP)
        start = 3;
    // 帧动画
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(4);
    std::vector<int> idx;
    idx.push_back(start * 4 + 2);
    idx.push_back(18 + start);
    idx.push_back(18 + start);
    idx.push_back(start * 4 + 2);
    for (int i = 0; i < 4; i++) {
        auto texture = Director::getInstance()->getTextureCache()->addImage(s + std::to_string(idx[i]) + ".png");
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
    mySprite->stopAllActions();
    mySprite->runAction(animate);

    CCLOG("%s heal", role);
}

/* 走路动画 */
void Creature::Move(int dir) {
    // 死了,直接返回
    if (isDead) {
        return;
    }

    /* 更改面朝方向 */
    face_to = dir;

    /* 图片名前缀:除编号部分 */
    std::string s = "Role/" + role + "/";

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
    mySprite->stopAllActions();
    mySprite->runAction(moveAndAnimate);
}

/* 死亡 */
void Creature::Die() {
    // 已经死了,直接返回
    if (isDead) {
        return;
    }

    isDead = true;
    face_to = DOWN;
    /* Monster1:树妖 */
    if (role == "Monster1") {
        mySprite->stopAllActions();
        mySprite->setTexture("Role/" + role + "/25.png");
        return;
    }
    /* 玩家角色 */
    mySprite->stopAllActions();
    mySprite->setTexture("Role/" + role + "atked/17.png");
    mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y - 30));
}

/* 复活 */
void Creature::Revive() {
    // 还没死或者不是玩家
    if (!isDead || (role != "Player1" && role != "Player2" && role != "Player3" && role != "Player4" && role != "Player5"))
        return;

    isDead = false;
    face_to = DOWN;
    mySprite->stopAllActions();
    mySprite->setTexture("Role/" + role + "atked/17.png");
    mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y + 30));
}

/* 等级加成 */
void Creature::levelBonus() {
    speed = speed * (0.05 * level + 1);
    hp = level * hp;
    mp = mp * level;
    atk = atk * level;
    def = def * level;
}

/* 返回a对b的伤害 */
int Creature::DamageCal(Creature* a, Creature* b) {
    return a->getAtk() - b->getDef();
}

/*设置属性*/
void Creature::setElementType(ElementType _elementType)
{
    elementType = _elementType;
}