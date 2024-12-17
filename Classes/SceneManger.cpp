#include "SceneManager.h"

void SceneManager::ChangeToNextScene(Scene* scene, float delay) {
	if (scene == nullptr) {
		return;
	}

	//新建一个过渡场景，将当前场景淡出，淡入下一个场景
	auto transitionScene = TransitionFade::create(delay, scene, Color3B::BLACK);

	//将过渡场景推入Director的场景栈
	Director::getInstance()->pushScene(transitionScene);
}

void SceneManager::ChangeToPreviousScene(float delay) {
	//弹出Director的场景栈
	Director::getInstance()->popScene();
}