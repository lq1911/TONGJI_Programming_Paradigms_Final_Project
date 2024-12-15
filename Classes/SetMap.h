#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include <vector>
#include "cocos2d.h"
#include "MicroMap.h"
#include "Player.h"
#include "SetPlayerScene.h"
#include "BagManager.h"
#include "NPC.h"
#include "Monster.h"
USING_NS_CC;

class SetMap :public cocos2d::Scene {
private:
	MicroMap* MicroMap;     // 微地图对象
	bool IsMicroMapVisible;     // 微地图是否可见

	int PlayerInWhichMap;  // 当前玩家所在的地图编号

	std::vector<cocos2d::Rect>ObstacleList;  // 障碍物列表

	Camera* camera = getDefaultCamera();
	Camera* camera_in_micro_map;

public:
	////////////////////////////////////////////////////////////////
	/* 按键是否按下:W/S/A/D*/
	std::vector<bool> isKeyPressed = { false,false,false,false };
	// 玩家
	Player* PLAYER;
	// 树妖Monster1
	Monster* Monster1;
	Monster* Monster2;
	// NPC
	NPC* npc1;

	/* 绑定键盘:Released */
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	/* 绑定键盘:Pressed */
	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
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

	/*加载地图*/
	void LoadMap();

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__