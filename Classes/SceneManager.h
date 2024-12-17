#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneManager:public Node {
public:
	void ChangeToNextScene(Scene* scene, float delay = 0.5f);    //切换到下一个场景，用场景栈实现，保存上一个场景
	void ChangeToPreviousScene(float delay = 0.5f);    //返回上一个场景
};


#endif // __SCENE_MANAGER_H__