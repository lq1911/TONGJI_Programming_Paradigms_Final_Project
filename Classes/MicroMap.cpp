#include "MicroMap.h"

USING_NS_CC;

bool MicroMap::init() {
	if (!Layer::init()) {
		return false;
	}

	this->OnEnterMicroMap();     //初始化大地图

	RegionLabel = Label::createWithTTF("", "fonts/arial.ttf", 48);
	RegionLabel->setTextColor(cocos2d::Color4B::WHITE);
	this->addChild(RegionLabel);

	// 注册鼠标事件监听器
	if(this->isVisible()){
	auto MouseListener = EventListenerMouse::create();
	MouseListener->onMouseMove = CC_CALLBACK_1(MicroMap::OnMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);
	}
	return true;  
}

void MicroMap::OnEnterMicroMap() {
	// 获取屏幕尺寸
	visibleSize = Director::getInstance()->getVisibleSize();
	
	//创建大地图精灵
	auto WorldMap = Sprite::create("Maps/MicroMap/WorldMap.png");

	//设置大地图精灵的位置和大小
	WorldMap->setPosition(visibleSize / 2);
	WorldMap->setScale(3.0f);

	//添加大地图精灵到层
	this->addChild(WorldMap);

	//初始化各个区域黑雾
	//此处必须严格按照地图的索引顺序初始化，否则发生不可逆的错误
	MapReign.push_back({ 0,visibleSize.height,visibleSize.width / 2,visibleSize.height / 2 });    //初始化森林黑雾
	MapReign.push_back({ 0,visibleSize.height / 2 ,visibleSize.width / 2,visibleSize.height / 2 });    //初始化火山黑雾
	MapReign.push_back({ visibleSize.width / 2,visibleSize.height,visibleSize.width / 2,visibleSize.height / 2 });    //初始化沙漠黑雾
	MapReign.push_back({ visibleSize.width / 2,visibleSize.height / 2,visibleSize.width / 2,visibleSize.height / 2 });    //初始化雪地黑雾

	//初始化各区域名字
	ReignName.push_back("ForestArea");
	ReignName.push_back("VolcanoArea");
	ReignName.push_back("DesertArea");
	ReignName.push_back("SnowyArea");

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
	this->DisperseBlackFog(ReignIndex);
}

bool MicroMap::IsContainedReign(cocos2d::Rect& rect, cocos2d::Vec2& Pos) {
	//判断Pos是否在rect内
	if (Pos.x >= rect.origin.x && Pos.x <= rect.origin.x + rect.size.width &&
		Pos.y <= rect.origin.y && Pos.y >= rect.origin.y - rect.size.height)
		return true;
	else
		return false;
}

void MicroMap::OnMouseMove(Event* event) {
	//获取鼠标位置
	auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
	float mouseX = mouseEvent->getCursorX();
	float mouseY = mouseEvent->getCursorY();

	//将屏幕坐标转换为世界坐标，非常重要，
	//屏幕坐标以左上角为原点，而世界坐标以左下角为原点，所以要进行坐标转换
	//用屏幕大小减去鼠标位置，得到世界坐标
	Vec2 ScreenSize;
	ScreenSize.x = mouseX;
	ScreenSize.y = visibleSize.height - mouseY;

	for (unsigned int i = 0; i < MapReign.size(); ++i) {
		if (IsContainedReign(MapReign[i], ScreenSize)&&IsBlackFogVisited[i]) {
			RegionLabel->setString(ReignName[i]);
			break;
		}
	}

	RegionLabel->setPosition(mouseX, mouseY + 20);
}