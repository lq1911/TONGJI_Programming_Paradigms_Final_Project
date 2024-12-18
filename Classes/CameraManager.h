#ifndef __CAMERA_MANAGER_H__
#define __CAMERA_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class CameraManager :public Node {
private:
	Size VisibleSize;    //可见区域大小

	Camera* MainCamera;    //主地图摄像机
	Camera* MicroCamera;    //小地图摄像机
public:
	/*构造函数*/
	CameraManager();

	/*获取主地图摄像机*/
	Camera* GetMainCamera() const { return MainCamera; }

   /*获取小地图摄像机*/
	Camera* GetMicroCamera() const { return MicroCamera; }

	/*初始化主地图摄像机*/
	void InitialMainCamera(Scene* TargetScene);

	/*初始化小地图摄像机*/
	void InitialMicroCamera(Scene* TargetScene);

	/*切换到主地图摄像机*/
	void SwitchToMainCamera();

	/*切换到小地图摄像机*/
	void SwitchToMicroCamera();

	/*更新摄像机位置*/
	void UpdateCameraPosition(Camera* Camera, Vec2& Position, float Height);

	CREATE_FUNC(CameraManager);
};

#endif // __CAMERA_MANAGER_H__