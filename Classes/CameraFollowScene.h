#ifndef __CAMERA_FOLLOW_SCENE_H__
#define __CAMERA_FOLLOW_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class CameraFollowScene : public Scene {
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(CameraFollowScene);
};
#endif // __CAMERA_FOLLOW_SCENE_H__

