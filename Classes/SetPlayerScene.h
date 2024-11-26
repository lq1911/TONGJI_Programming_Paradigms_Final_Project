
#ifndef __SET_PLAYER_SCENE_H__
#define __SET_PLAYER_SCENE_H__

#include "cocos2d.h"

class SetPlayerScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SetPlayerScene);
};

#endif // __SET_PLAYER_SCENE_H__
