#include "MicroMap.h"

USING_NS_CC;

bool MicroMap::init() {
	if (!Layer::init()) {
		return false;
	}

	OnEnterMicroMap();     //初始化大地图

	return true;
}

void MicroMap::OnEnterMicroMap() {
	// 获取屏幕尺寸
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//获取当前大地图尺寸
	Size MapSize = getContentSize();

	//创建大地图精灵
	auto WorldMap = Sprite::create("Maps/MicroMap/WorldMap.png");

	//设置大地图精灵的位置和大小
	WorldMap->setPosition(visibleSize / 2);
	WorldMap->setScale(3.0f);

	//添加大地图精灵到层
	this->addChild(WorldMap);

	//初始化各个区域黑雾
	MapReign.push_back({ 0,MapSize.height / 2 ,MapSize.width / 2,MapSize.height / 2 });    //初始化火山黑雾
	MapReign.push_back({ 0,MapSize.height,MapSize.width / 2,MapSize.height / 2 });    //初始化森林黑雾
	MapReign.push_back({ MapSize.width / 2,MapSize.height / 2,MapSize.width / 2,MapSize.height / 2 });    //初始化雪地黑雾
	MapReign.push_back({ MapSize.width / 2,MapSize.height,MapSize.width / 2,MapSize.height / 2 });    //初始化沙漠黑雾

	//初始化各区域名字
	ReignName.push_back("森林区域");
	ReignName.push_back("火山区域");
	ReignName.push_back("沙漠区域");
	ReignName.push_back("雪地区域");

	// 为每个区域分配空间,否则黑雾层未分配空间会发生向量越界
	BlackFogLayer.resize(MapReign.size()); 

	for (unsigned int i = 0; i < MapReign.size(); ++i) {
		//创建黑雾层
		BlackFogLayer[i] = cocos2d::DrawNode::create();
		
		//设置每个区域的矩形右上角
		cocos2d::Vec2 destination;
		destination.x = MapReign[i].origin.x + MapReign[i].size.width;
		destination.y = MapReign[i].origin.y - MapReign[i].size.height;

		//绘制每个区域黑雾
		BlackFogLayer[i]->drawSolidRect(MapReign[i].origin, destination, Color4F::BLACK);    //设置黑雾的颜色为黑色,透明度为0
		BlackFogLayer[i]->drawRect(MapReign[i].origin, destination, Color4F::WHITE);    //设置白色边框
		IsBlackFogVisited.push_back(false);    //初始化黑雾为未被探索的状态

		this->addChild(BlackFogLayer[i]);    //添加黑雾到层
	}
}

void MicroMap::DisperseBlackFog(int ReignIndex) {
	//驱散黑雾
	BlackFogLayer[ReignIndex]->setVisible(false);

    //设置黑雾为已探索的状态
	IsBlackFogVisited[ReignIndex] = true;
}

void MicroMap::UnlockReign(int ReignIndex) {
	// 设置黑雾为已探索的状态
	IsBlackFogVisited[ReignIndex] = true;

	// 驱散探索图层黑雾
	DisperseBlackFog(ReignIndex);
}

void MicroMap::update(float dt) {
	// 初始化 Label 显示区域名称
	Label* RegionLabel = Label::createWithTTF("", "fonts/arial.ttf", 24);
	RegionLabel->setVisible(false);  // 初始时不可见
	this->addChild(RegionLabel, 10);  // 添加到层中

	// 注册鼠标事件监听器
	auto MouseListener = EventListenerMouse::create();
	MouseListener->onMouseMove = [this, RegionLabel](Event* event) {
		EventMouse* e = static_cast<EventMouse*>(event);
		Vec2 mousePos = e->getLocationInView();  // 获取鼠标位置

		// 转换坐标到屏幕坐标系
		mousePos.y = Director::getInstance()->getVisibleSize().height - mousePos.y;

		bool InFogLayer = false;    // 是否在黑雾层上
		for (unsigned int i = 0; i < MapReign.size(); ++i) {
			// 判断鼠标是否在某个区域内
			if (MapReign[i].containsPoint(mousePos)) {
				RegionLabel->setString(ReignName[i]);    // 更新区域名称
				RegionLabel->setVisible(true);    // 显示区域名称
				RegionLabel->setPosition(mousePos.x, mousePos.y);    // 设置位置

				InFogLayer = true;    // 进入黑雾层
				break;
			}
		}

		if (!InFogLayer) {
			RegionLabel->setVisible(false);    // 隐藏区域名称
		}
		};
}