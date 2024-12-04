#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s/n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp/n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    //获取屏幕大小和原点
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->CreateBackground(visibleSize);    //创建游戏开始界面背景

    // 开始游戏按钮
    auto button = cocos2d::ui::Button::create("Button/PlayButton.png", "Button/PlayButtonClicked.png", "Button/PlayButtonClicked.png");
    button->ignoreContentAdaptWithSize(false);  // 启用内容大小适配
    button->setContentSize(Size(300, 150));
    button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 300));

    // 按钮点击事件监听器
    button->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto Map = SetMap::createScene();
            Director::getInstance()->replaceScene(Map); // 场景切换
            /*
        auto scene = SetPlayerScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK)); // 场景切换
        CCLOG("Button clicked, switching to SetPlayerScene.");
        */
        }
        });
    this->addChild(button);

    //进入地图
    /*auto button = cocos2d::ui::Button::create("Button/PlayButton.png", "Button/PlayButtonClicked.png", "Button/PlayButtonClicked.png");
    button->ignoreContentAdaptWithSize(false);  // 启用内容大小适配
    button->setContentSize(Size(300, 150));
    button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 300));
    button->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            CCLOG("Button Map Pressed");
            break;
        case ui::Widget::TouchEventType::ENDED:
            CCLOG("Button Map Released");
            break;
        default:
            break;
        }
        });
    // 按钮点击事件监听器
    button->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scene = SetPlayerScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK)); // 场景切换
            CCLOG("Button clicked, switching to SetPlayerScene.");
        }
        });
    this->addChild(button);*/
    return true;
}

void HelloWorld::CreateBackground(Size& visibleSize) {
     //设置游戏的开始界面
    auto Background = Sprite::create("StartBackground.jpg");    //游戏开始界面背景图
    Background->setPosition(visibleSize.width / 2, visibleSize.height / 2);    // 设置背景图的位置为屏幕中心
    Background->setScale(1.08f);    // 设置背景图的缩放比例
    Background->setScaleY(1.4f);
    this->addChild(Background);    //将背景图添加至当前场景
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}