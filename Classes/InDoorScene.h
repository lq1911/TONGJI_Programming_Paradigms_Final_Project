#ifndef __WINTER_HOUSE_H__
#define __WINTER_HOUSE_H__

#include "MainGameScene.h"
#include "cocos2d.h"

class WinterHouse : public MainGameScene {
private:
	Size VisibleSize;    // 可见屏幕大小

	EventListenerKeyboard* _keyboardListener;    // 键盘监听器
	EventListenerMouse* _mouseListener;    // 鼠标监听器

	CameraManager* _cameraManager;    // 摄像机管理器
	MapManager* _mapManager;    // 地图管理器
	BagManager* _bagManager;    // 背包管理器

	Player* PLAYER;     // 操作用户
	MonsterRespawn* _monsterRespawn;    // 怪物管理器
	NPCManager* _npcManager;   // NPC管理器
	music* _musicManager; // 音乐管理器

	vector<bool> isKeyPressed = { false,false,false,false };    // 按键是否按下:W/S/A/D
public:
	/****************************************************************/
	////////////////以下为本场景所有用到的初始化函数/////////////////
	/*构造函数，从上一个场景传入角色*/
	WinterHouse(Player* origin_player);

	/*生成场景函数*/
	static cocos2d::Scene* createScene(Player* origin_player);

	/*初始化地图函数*/
	virtual bool init();

	/*加载地图，重写父类*/
	void LoadMapToScene() override;

	/*加载人物，重写父类*/
	void LoadPlayerToScene() override;

	/*加载怪物管理器，重写父类*/
	void LoadMonsterRespawnToScene() override;

	/*加载NPC，重写父类*/
	void LoadNPCToScene() override;
};

#endif // __WINTER_HOUSE_H__