#include "LoadingScene.h"
#include "ui/CocosGUI.h"
#include "MainGameScene.h"
#include "LearningScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene(int SceneChoice) {
	LoadingScene* scene = new LoadingScene(SceneChoice);
	if (scene && scene->init()) {
		
	}
	return scene;

}

bool LoadingScene::init() {
	if (!Scene::init()) {
		return false;
	}

	//获取屏幕大小
	VisibleSize = Director::getInstance()->getVisibleSize();

	// 加载UI界面
	this->CreateUI();

	//初始化加载资源数量
	int LoadedResourceCount = 0;
	int TotalResourceCount = Resources.size();

	//添加加载进度条至场景中
	auto LoadingBar = ui::LoadingBar::create("UI/LoadingBar.png");
	LoadingBar->setPercent(0);    //初始化进度为0
	LoadingBar->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 2 + 500));
	this->addChild(LoadingBar);

	// 检查加载完成
	this->schedule([this, LoadingBar](float delta) {
		LoadingBar->setPercent(i);
		i += 5.0f;
		if (i == 100) {
			if (_SceneChoice == 1) {
				auto ToChangeScene = MainGameScene::createScene();
				Director::getInstance()->replaceScene(ToChangeScene);
			}
			else if (_SceneChoice == 0) {
				auto LearningScene = LearningScene::createScene();
				Director::getInstance()->replaceScene(LearningScene);
			}
		}
        }, 0.1f, "check_loading_complete");

	return true;
}

LoadingScene::LoadingScene(int SceneChoice) {
	//初始化场景选择
	_SceneChoice = SceneChoice;
}

void LoadingScene::CreateUI() {
	//添加加载背景图至场景中
	auto LoadingBackground = Sprite::create("UI/Loading.jpg");
	LoadingBackground->setPosition(VisibleSize.width / 2, VisibleSize.height / 2);
	this->addChild(LoadingBackground);
}