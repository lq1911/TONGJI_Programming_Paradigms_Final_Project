#ifndef __SET_PLAYER_SCENE_H__
#define __SET_PLAYER_SCENE_H__

#include <string>
#include "cocos2d.h"

class SetPlayerScene : public cocos2d::Scene {
public:
    std::string name;   // Íæ¼ÒÐÕÃû

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SetPlayerScene);
};

#endif // __SET_PLAYER_SCENE_H__
