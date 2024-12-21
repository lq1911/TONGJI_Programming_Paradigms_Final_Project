#ifndef __LEARNING_SCENE_H__
#define __LEARNING_SCENE_H__

#include <iostream>
#include <cocos2d.h>
#include "Player.h"
#include "SetPlayerScene.h"
#include "NPC.h"
#include "BagManager.h"
#include "MainGameScene.h"

class LearningScene :public cocos2d::Scene {
private:
	Player* LEARNER;
	NPC* CHATNPC;
public:
	/* 初始化场景 */
	static cocos2d::Scene* createScene();
	virtual bool init();

	/* 欢迎 */
	virtual void welcome();

	/* 学走路 */
	virtual void learnMove();
	// 键盘监听
	void MoveKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	// 按键是否按下:W/S/A/D
	std::vector<bool> isKeyPressed = { false,false,false,false };

	/* 学攻击 */
	virtual void learnAttack();
	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	/* 学跟npc交流 */
	virtual void learnChat();
	void ChatKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	/* 学交互 */
	virtual void learnInteract();

	/* 学背包 */
	virtual void learnBag();
	void BagKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	/* 完成教程提示 */
	virtual void finish();

	CREATE_FUNC(LearningScene);
};



#endif // __LEARNING_SCENE_H__