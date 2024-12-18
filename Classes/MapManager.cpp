#include "MapManager.h"

void MapManager::InitialMap(const char* mapName, const Vec2& MapPosition, Scene* TargetScene) {
	auto TiledMap = TMXTiledMap::create(mapName);    //创建地图对象
	TiledMap->setAnchorPoint(Vec2(0.5f, 0.5f));    //设置地图的锚点为中心点
	TiledMap->setPosition(MapPosition);    //设置地图的位置
	//this->InitialObstacles(TiledMap);    //初始化障碍物
	TargetScene->addChild(TiledMap);    //将地图添加到场景中

	MapList.push_back(TiledMap);    //将地图添加到已经创建的地图列表中
	IsBlackFogVisible.push_back(true);    //初始化黑色雾的可见性为false
	IsRegionRevealed.push_back(false);    //初始化地图区域是否被揭示为false
}

void MapManager::PlayerPositionInWhichMap(Vec2& PlayerPosition) {
	for (int i = 0; i < (int)MapList.size(); i++) {
		if (MapList[i]->getBoundingBox().containsPoint(PlayerPosition)) {    //判断玩家是否在某个地图的范围内
			PlayerInWhichMap = i;    //将玩家所在的地图的索引保存到PlayerInWhichMap变量中
			return;
		}
	}	
}

void MapManager::InitialObjects(TMXTiledMap* TiledMap) {
	TMXObjectGroup* ObjectLayer = TiledMap->getObjectGroup("Obstacles");    //获取障碍物层
	if (ObjectLayer) {
		//遍历障碍物组，获取障碍物的位置信息
		auto Obstacles = ObjectLayer->getObjects();
		for (auto& Object : Obstacles) {
			ValueMap obstacle = Object.asValueMap();     //获取障碍物的属性
			
			auto objectType=obstacle["type"].asString();    //获取障碍物的类型
			
			if (objectType == "") {
				// 根据对象类型读取其属性
				// 障碍物全为矩形
				float x = obstacle["x"].asFloat();
				float y = obstacle["y"].asFloat();
				float width = obstacle["width"].asFloat();
				float height = obstacle["height"].asFloat();

				// 创建矩形区域
				Rect obstacleRect(x, y, width, height);

				// 这里可以存储或使用这个区域来进行碰撞检测
				// 比如添加到一个障碍物列表中
				ObstacleList.push_back(obstacleRect);
			}
			else if (objectType == "Teleport") {
				// 根据对象类型读取其属性
				// 传送点
				float x = obstacle["x"].asFloat();
				float y = obstacle["y"].asFloat();

				// 保存传送点坐标
				TeleportList.push_back(Vec2(x, y));
			}
			else if (objectType == "Interactional") {
				// 根据对象类型读取其属性
				// 可交互区域
				float x = obstacle["x"].asFloat();
				float y = obstacle["y"].asFloat();

				// 保存可交互区域坐标
				InteractionList.push_back(Vec2(x, y));
			}
			
		}
	}
}

void MapManager::SetBlackFogInMicroMap() {
	for (int i = 0; i < (int)BlackFogList.size(); i++) {
		if (!BlackFogList[i]->getParent()) {
			this->addChild(BlackFogList[i]);
		}
		BlackFogList[i]->setLocalZOrder(100);    //设置黑色雾的图层优先级足够高，保证它在地图上显示在其他元素之上
		// 如果此区域已经被揭示，则隐藏黑色雾，否则在小地图上显示黑色雾
		BlackFogList[i]->setVisible(IsRegionRevealed[i] == true ? false : IsBlackFogVisible[i]);
	}
}

size_t MapManager::GetBlackFogListSize() {
	return BlackFogList.size();
}

bool MapManager::IsMoveable(const Vec2& Position) {
	//遍历障碍物列表中的每一个障碍物
	for (const auto& obstacle : ObstacleList) {
		if (obstacle.containsPoint(Position)) {
			/// 如果位置在障碍物范围内，则不可移动
			return false;
		}
	}

	// 如果位置不在障碍物范围内，则可移动
	return true;
}

Vec2 MapManager::GetTeleportPosition() {
	// 获取指定地图的传送点坐标
	if (IsRegionRevealed[PlayerInWhichMap] == false) {
		// 如果传送点列表为空或玩家不在传送点列表中，则返回Vec2::ZERO
		return Vec2::ZERO;
	}
	return TeleportList[PlayerInWhichMap];
}

void MapManager::ReverseIsBlackFogVisible() {
	// 反转黑色雾的可见性
	for (int i = 0; i < (int)IsBlackFogVisible.size(); i++) {
		IsBlackFogVisible[i] = !IsBlackFogVisible[i];
	}
}

void MapManager::SetIsRegionRevealedTrue() {
	// 解锁小地图以及其相应传送点
	if (IsRegionRevealed[PlayerInWhichMap] == false) {
		IsRegionRevealed[PlayerInWhichMap] = true;
	}
}