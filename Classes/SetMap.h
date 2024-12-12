#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include <vector>
#include "cocos2d.h"
#include "MicroMap.h"
#include "Player.h"
#include "SetPlayerScene.h"
#include "BagManager.h"

USING_NS_CC;

class SetMap :public cocos2d::Scene {
private:
	MicroMap* MicroMap;     // 微地图对象
	bool IsMicroMapVisible;     // 微地图是否可见

	int PlayerInWhichMap;  // 当前玩家所在的地图编号

	std::vector<cocos2d::Rect>ObstacleList;  // 障碍物列表

public:
	////////////////////////////////////////////////////////////////
	/* 按键是否按下:W/S/A/D*/
	std::vector<bool> isKeyPressed = { false,false,false,false };
	// 玩家
	Player* PLAYER;
	// 树妖Monster1
	Player* Monster1;
	Player* Monster2;
	// NPC
	Player* npc1;


	
	
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			if (isKeyPressed[0]) {
				isKeyPressed[0] = false;
				this->unschedule("MoveUP");
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
			if (isKeyPressed[1]) {
				isKeyPressed[1] = false;
				this->unschedule("MoveDOWN");
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
			if (isKeyPressed[2]) {
				isKeyPressed[2] = false;
				this->unschedule("MoveLEFT");
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
			if (isKeyPressed[3]) {
				isKeyPressed[3] = false;
				this->unschedule("MoveRIGHT");
			}
		}
	}

	// 按键绑定
	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
		Vec2 moveBy;
		int speed = 1;
		/* 攻击:I/K/J/L */
		if (keyCode == EventKeyboard::KeyCode::KEY_I)
			PLAYER->Attack(UP);
		else if (keyCode == EventKeyboard::KeyCode::KEY_K)
			PLAYER->Attack(DOWN);
		else if (keyCode == EventKeyboard::KeyCode::KEY_J)
			PLAYER->Attack(LEFT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_L)
			PLAYER->Attack(RIGHT);
		/* 移动:W/S/A/D */
		else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
			if (IsMoveable(targetPosition)) {
				if (!isKeyPressed[0]) {
					isKeyPressed[0] = true;
					this->schedule([&](float dt) {
						PLAYER->Move(UP);
						}, 0.34f, "MoveUP");
				}
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S){
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
			if (IsMoveable(targetPosition)) {
				if (!isKeyPressed[1]) {
					isKeyPressed[1] = true;
					this->schedule([&](float dt) {
						PLAYER->Move(DOWN);
						}, 0.34f, "MoveDOWN");
				}
			}	
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A){
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
			if (IsMoveable(targetPosition)) {
				if (!isKeyPressed[2]) {
					isKeyPressed[2] = true;
					this->schedule([&](float dt) {
						PLAYER->Move(LEFT);
						}, 0.34f, "MoveLEFT");
				}
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D){ 
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
			if (IsMoveable(targetPosition)) {
				if (!isKeyPressed[3]) {
					isKeyPressed[3] = true;
					this->schedule([&](float dt) {
						PLAYER->Move(RIGHT);
						}, 0.34f, "MoveRIGHT");
				}
			}
		}

		// 测试Monster1攻击效果用，记得删
		else if (keyCode == EventKeyboard::KeyCode::KEY_T) {
			int dx = Monster1->mySprite->getPosition().x - PLAYER->mySprite->getPosition().x;
			int dy = Monster1->mySprite->getPosition().y - PLAYER->mySprite->getPosition().y;
			if (std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(Monster1->getAtkRange(), 2))
				Monster1->Attack(DOWN, PLAYER);
			else
				Monster1->Attack();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_Y) {
			Monster2->Attack(UP);
			//PLAYER->Heal();
			//PLAYER->Die();
		}

		// 按下B键之后的逻辑:背包
		else if (keyCode == EventKeyboard::KeyCode::KEY_B) {
			
			if (BagManager::getInstance()->isBagVisible())
				// 隐藏背包
				BagManager::getInstance()->hideBag(*PLAYER);
			else
				// 打开背包
				BagManager::getInstance()->showBag(*PLAYER);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_P){
			goods _goods;
			if (BagManager::getInstance()->getItemsNum() % 5 == 0)
			{
				weapon* it1 = new weapon(_goods.icon_sword);
				BagManager::getInstance()->addItem(it1);
				return;
			}

			if (BagManager::getInstance()->getItemsNum() % 5 == 1)
			{
				consumable* it2 = new consumable(_goods.pumkin);
				BagManager::getInstance()->addItem(it2);
				return;
			}

			if (BagManager::getInstance()->getItemsNum() % 5 == 2)
			{
				accessories* it3 = new accessories(_goods.bomb);
				BagManager::getInstance()->addItem(it3);
				return;
			}

			if (BagManager::getInstance()->getItemsNum() % 5 == 3)
			{
				armor* it4 = new armor(_goods.icon_conselet);
				BagManager::getInstance()->addItem(it4);
				return;
			}

			if (BagManager::getInstance()->getItemsNum() % 5 == 4)
			{
				shoes* it5 = new shoes(_goods.boots);
				BagManager::getInstance()->addItem(it5);
				return;
			}
		}
	}
	//////////////////////////////////////////////////////////////


	/*生成场景函数*/
	static cocos2d::Scene* createScene();

	/*初始化地图函数*/
	virtual bool init();

	// 键盘事件处理,按下M键切换显示微地图
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	/*设置摄像机跟随玩家移动*/
	void CameraFollowPlayer();

	/*初始化障碍物*/
	void InitialObstacle(cocos2d::TMXTiledMap* tileMap);

	/*判断某个位置是否可以移动*/
	bool IsMoveable(cocos2d::Vec2& pos);

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__