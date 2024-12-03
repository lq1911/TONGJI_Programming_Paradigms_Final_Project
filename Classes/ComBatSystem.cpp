#include "CombatSystem.h"
USING_NS_CC;


// 基本动作
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));


//攻击
void Creature::Attack(Creature target,int idx) {
	//计算攻击范围
	//如果target在攻击范围内
	//target.Hurt(atk);
	//动画实现
	// 图片名前缀:除编号部分
	string s;
	if (idx == 1 || idx == 2)
		s = "Role/Player/" + name + "/attack" + std::to_string(idx) + "/" + name + "_atk" + std::to_string(idx) + "_";
	else if (idx == 3)
		s = "Role/Player/" + name + "/attack_final/" + name + "_final_";
	// 帧数
	int count = 0;
	if (name == "Arthur") {
		if (idx == 1)
			count = 10;
		else if (idx == 2)
			count = 12;
		else if (idx == 3)
			count = 15;
	}
	else if (name == "Longbow") {
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
