#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include <iostream>
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
	Size visibleSize;

	MicroMap* MicroMap;     // 微地图对象
	bool IsMicroMapVisible;     // 微地图是否可见

	int PlayerInWhichMap;  // 当前玩家所在的地图编号

	std::vector<cocos2d::Rect>ObstacleList;  // 障碍物列表

	Camera* camera;    // 主地图摄像机
	Camera* camera_in_micro_map;    // 小地图摄像机

	EventListenerMouse* mainMapListener = nullptr;     // 主地图监听器
	EventListenerMouse* microMapListener = nullptr;     // 小地图监听器

	const float ScrollSpeed = 40.0f;    // 滚轮滚动速度

	vector<TMXLayer*> BlackFogList;    //储存黑雾的图层
	vector<bool> IsBlackFogVisible;    //黑雾是否可见
	vector<bool> IsRegionRevealed;    //是否已经显示过某个区域


public:
	 
	/* 人物 */
	// 玩家
	Player* PLAYER;
	// 怪物
	MonsterRespawn* monster_respawn;
	// NPC
	NPC* npc1;

	/* 绑定键盘 */
	std::vector<bool> isKeyPressed = { false,false,false,false }; // 按键是否按下:W/S/A/D
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	/*生成场景函数*/
	static cocos2d::Scene* createScene();

	/*初始化地图函数*/
	virtual bool init();

	/*键盘事件处理, 按下M键切换显示微地图*/
	void KeyPressedForMicroMap(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	/*键盘事件处理，按下相应按键移动地图*/
	void createKeyboardListenerForCamera(Camera* camera, float moveSpeed, float MaxWidth, float MinWidth, float MaxHeigth, float MinHeigth);

	/*鼠标事件处理，滚动滚轮控制地图缩放*/
	EventListenerMouse* createMouseListenerForCameraScroll(Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed);

	/*设置摄像机跟随玩家移动*/
	void CameraFollowController();

	/*设置主地图摄像机随玩家移动*/
	void MainCameraFollowPlayer();

	/*设置小地图摄像机随玩家移动*/
	void MicroCameraFollowPlayer();

	/*更新摄像机的位置*/
	void UpdateCameraPosition(Camera* camera, Vec2& TargetPos, float Height);

	/*初始化障碍物*/
	void InitialObstacle(cocos2d::TMXTiledMap* tileMap);

	/*判断某个位置是否可以移动*/
	bool IsMoveable(cocos2d::Vec2& pos);

	/*处理玩家移动*/
	void HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction);

	/*加载地图*/
	void LoadMap();

	/*初始化摄像机*/
	void InitalCamera();

	/*设置黑色雾层仅对小地图摄像机可见*/
	void SetBlackFogInMicroMap();

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__