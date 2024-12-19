#include "CameraManager.h"

CameraManager::CameraManager() {
	//摄像机获得屏幕大小
	VisibleSize = Director::getInstance()->getVisibleSize();
}

void CameraManager::InitialMainCamera(Scene* TargetScene) {
	//主地图摄像机初始化为默认摄像机
	MainCamera = TargetScene->getDefaultCamera();
}

void CameraManager::InitialMicroCamera(Scene* TargetScene) {
	//小地图摄像机初始化为透视摄像机，可以自由移动
	MicroCamera = Camera::createPerspective(60.0f, VisibleSize.width / VisibleSize.height, 100.0f, 4000.0f);    //最后两项为摄像机的最小高度和最大高度

	//小地图摄像机默认设置为不可见
	MicroCamera->setVisible(false);

	//将小地图摄像机添加到场景中
	TargetScene->addChild(MicroCamera);
}

void CameraManager::SwitchToMainCamera() {
	//小地图摄像机设置为不可见
	MicroCamera->setVisible(false);

	//主地图摄像机设置为可见
	MainCamera->setVisible(true);
}

void CameraManager::SwitchToMicroCamera() {
	//主地图摄像机设置为不可见
	MainCamera->setVisible(false);

	//小地图摄像机设置为可见
	MicroCamera->setVisible(true);	
}

void CameraManager::UpdateCameraPosition(Camera* Camera, Vec2& Position, float Height) {
	//更新摄像机的位置
	Camera->setPosition3D(Vec3(Position.x, Position.y, Height));
}

bool CameraManager::IsInMicroMap() {
	//判断当前是否在小地图摄像机中
	return MicroCamera->isVisible();
}