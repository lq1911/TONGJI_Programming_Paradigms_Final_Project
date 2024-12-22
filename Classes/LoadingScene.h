#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include <vector>

enum class ResourceType {
    TILE_MAP,
    MUSIC
};

struct ResourceToLoad {
    ResourceType type;
    std::string path;
};

class LoadingScene : public cocos2d::Scene {
private:
	float i = 0.0f;    //进度条进度
	int _SceneChoice;    //场景选择，为0进入教学场景，为1进入游戏场景
    cocos2d::Size VisibleSize;    //屏幕大小
	std::vector<ResourceToLoad> Resources = {
	{ ResourceType::TILE_MAP, "Maps/RebirthTemple/RebirthTemple.tmx" },
	{ ResourceType::TILE_MAP, "Maps/volcano/volcano.tmx" },
	{ ResourceType::TILE_MAP, "Maps/SnowyWinter/SnowyWinter.tmx" },
	{ ResourceType::TILE_MAP, "Maps/DeathDesert/DeathDesert.tmx" },
	{ ResourceType::TILE_MAP, "Maps/BrightForest/BrightForest.tmx" },
	{ ResourceType::TILE_MAP, "Maps/Vol_Snow_Ecotonal/Vol_Snow_Ecotonal.tmx" },
	{ ResourceType::TILE_MAP, "Maps/Vol_Forest_Ecotonal/Vol_Forest_Ecotonal.tmx" },
	{ ResourceType::TILE_MAP, "Maps/Desert_Snow_Ecotonal/Desert_Snow_Ecotonal.tmx" },
	{ ResourceType::TILE_MAP,"Maps/Forest_Desert_Ecotonal/Forest_Desert_Ecotonal.tmx" },
	{ ResourceType::TILE_MAP, "Maps/Indoors/InDoors.tmx" },
	{ ResourceType::TILE_MAP, "Maps/BossFight/BossRoom.tmx" },

	{ ResourceType::MUSIC, "music/accept_task.mp3" },
	{ ResourceType::MUSIC, "music/bag.mp3" },
	{ ResourceType::MUSIC, "music/click.mp3" },
	{ ResourceType::MUSIC, "music/eat.mp3" },
	{ ResourceType::MUSIC, "music/equip.mp3" },
	{ ResourceType::MUSIC, "music/fight.mp3" },
	{ ResourceType::MUSIC, "music/item.mp3" },
	{ ResourceType::MUSIC, "music/lock.mp3" },
	{ ResourceType::MUSIC, "music/peace.mp3" },
	{ ResourceType::MUSIC, "music/upgrade.mp3" },
	};
public:
	/*构造函数*/
	LoadingScene(int SceneChoice);

	/*创建场景*/
    static cocos2d::Scene* createScene(int SceneChoice);    
    
	/*加载UI等等资源*/
	void CreateUI();

	/*初始化场景*/
    virtual bool init();
};

#endif __LOADING_SCENE_H__