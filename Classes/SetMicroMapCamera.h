#pragma once
#include "cocos2d.h"
USING_NS_CC;

class SetMicroMapCamera : public Layer
{
public:
    virtual bool init();

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    CREATE_FUNC(SetMicroMapCamera);

private:
    Camera* miniMapCamera;
    Camera* mainCamera;
    Camera* currentCamera;
};
