#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MapManager :public Node {
private:
	int PlayerInWhichMap = 0;    //玩家所在的地图编号

	vector<TMXTiledMap*> MapList;     //储存已经加载的瓦片地图

	vector<Rect>ObstacleList;    //储存障碍物的矩形区域
	vector<Vec2>TeleportList;    //储存传送门的位置
	vector<Vec2>InteractionList;    //储存交互区域的位置

	vector<TMXLayer*> BlackFogList;    //储存黑雾的图层
	vector<bool> IsBlackFogVisible;    //黑雾是否可见
	vector<bool> IsRegionRevealed;    //是否已经显示过某个区域

	const int MapField = 1600;    //单张瓦片地图的大小
public:
	/*初始化地图障碍物*/
	void InitialObjects(TMXTiledMap* TiledMap);
	
	/*初始化瓦片地图*/
	void InitialMap(const char* mapName, const Vec2& MapPosition, Scene* TargetScene);
	
	/*设置某张瓦爿地图的黑雾*/
	void SetBlackFogInMicroMap(TMXTiledMap* TiledMap);
	
	/*判断某个位置是否可以被移动到*/
	bool IsMoveable(const Vec2& pos);

	/*判断玩家所在的地图编号*/
	void PlayerPositionInWhichMap(Vec2& PlayerPosition);

	CREATE_FUNC(MapManager);
};

#endif // __MAP_MANAGER_H__