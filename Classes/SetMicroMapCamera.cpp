#include "SetMicroMapCamera.h"

bool SetMicroMapCamera::init() {

    //创建小地图摄像机（上帝视角）

    miniMapCamera = Camera::createOrthographic(200.0f, 200.0f, 1.0f, 1000.0f);
    miniMapCamera->setPosition3D(Vec3(0, 0, 1500));  // 将摄像机放置在较高的位置
    miniMapCamera->setDepth(-1);  // 小地图的摄像机深度低于主摄像机
    this->addChild(miniMapCamera);

    // 注册鼠标滚轮事件
    auto listener = EventListenerMouse::create();
    listener->onMouseScroll = [=](EventMouse* event) {
        // 获取滚轮的滚动方向
        float scrollY = event->getScrollY();

        // 获取当前摄像机的位置
        Vec3 cameraPosition = miniMapCamera->getPosition3D();

        // 根据滚轮的方向改变摄像机的Z轴高度
        // 向上滚动，Z轴值增加，摄像机向前
        // 向下滚动，Z轴值减少，摄像机向后
        cameraPosition.z += scrollY * 10.0f;  // 10.0f是控制滚动灵敏度的系数，可以调整

        // 限制摄像机的高度（Z轴范围）
        cameraPosition.z = std::min(cameraPosition.z, 1800.0f);  // 最大高度
        cameraPosition.z = std::max(cameraPosition.z, 1000.0f);  // 最小高度

        // 设置摄像机的位置
        miniMapCamera->setPosition3D(cameraPosition);

        CCLOG("Camera Position: %f, %f, %f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
        };

    // 获取事件调度器并添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

// 按键按下事件，移动小地图摄像机
void  SetMicroMapCamera::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        if (currentCamera == mainCamera) {
            // 切换到小地图摄像机
            //Director::getInstance()->getRunningScene()->setCamera(miniMapCamera);
            currentCamera = miniMapCamera;
        }
    }

    if (currentCamera == miniMapCamera) {
        // 控制小地图摄像机的移动
        Vec3 cameraPos = miniMapCamera->getPosition3D();

        // 使用 WASD 键控制摄像机移动
        if (keyCode == EventKeyboard::KeyCode::KEY_W) {
            cameraPos.y += 10.0f;  // 上移
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
            cameraPos.y -= 10.0f;  // 下移
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
            cameraPos.x -= 10.0f;  // 左移
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
            cameraPos.x += 10.0f;  // 右移
        }

        miniMapCamera->setPosition3D(cameraPos);  // 更新摄像机位置
    }
}

// 按键释放事件，切换回主摄像机
void SetMicroMapCamera::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        if (currentCamera == miniMapCamera) {
            // 切换回主摄像机
            //Director::getInstance()->getRunningScene()->setCamera(mainCamera);
            currentCamera = mainCamera;
        }
    }
}