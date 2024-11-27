#include <iostream>
#include "SetPlayerScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* SetPlayerScene::createScene() {
    return SetPlayerScene::create();
}

bool SetPlayerScene::init() {
    if (!Scene::init()) {
        return false;
    }

    /* 文字提示欢迎来到本游戏 */ 
    auto WelcomeTxt = Label::createWithTTF("Welcome to the Genshin-Style-Open-World-Adventure-Game!", "fonts/Marker Felt.ttf", 70);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    WelcomeTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 600));
    this->addChild(WelcomeTxt);

    /* 输入玩家姓名 */
    // 创建输入框
    auto textField = ui::TextField::create("Enter Name Here", "Arial", 40);
    textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 750));
    textField->setMaxLength(20);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(Color4B::WHITE);
    textField->setCursorEnabled(true); // 启用光标显示
    this->addChild(textField);

    // 提交按钮
    auto SubmitButton = ui::Button::create("Button/SubmitButton.png", "Button/SubmitButtonClicked.png");
    SubmitButton->setTitleText("");
    SubmitButton->ignoreContentAdaptWithSize(false);  
    SubmitButton->setContentSize(Size(60, 60));
    SubmitButton->setTitleFontSize(24);
    SubmitButton->setPosition(Vec2(visibleSize.width / 2 + 300, visibleSize.height - 750));
    this->addChild(SubmitButton);

    // 监听输入框事件
    textField->addEventListener([=](Ref* sender, ui::TextField::EventType type) {
        auto textField = dynamic_cast<ui::TextField*>(sender);
        switch (type) {
        case ui::TextField::EventType::ATTACH_WITH_IME: // 点击输入框时，键盘弹出
            CCLOG("Input started");
            textField->setPlaceHolder(""); // 清空占位符文字
            break;
        case ui::TextField::EventType::DETACH_WITH_IME: // 键盘关闭
            CCLOG("Input ended");
            if (textField->getString().empty()) {
                textField->setPlaceHolder("Enter Name Here"); // 恢复占位符文字
            }
            break;
        case ui::TextField::EventType::INSERT_TEXT: // 插入文字
            CCLOG("Text inserted: %s", textField->getString().c_str());
            break;
        case ui::TextField::EventType::DELETE_BACKWARD: // 删除文字
            CCLOG("Text deleted");
            break;
        default:
            break;
        }
        });

    // 按钮点击事件
    SubmitButton->addClickEventListener([=](Ref* sender) mutable {
        name = textField->getString(); // 获取输入框的文本内容
        if (name.empty()) {
            // 如果输入框为空，提示用户输入名字
            auto warningLabel = Label::createWithSystemFont("Name cannot be empty!", "Arial", 24);
            warningLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 550));
            warningLabel->setTextColor(Color4B::RED);
            this->addChild(warningLabel);
            // 2秒后移除警告
            this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]() {
                this->removeChild(warningLabel);
                }), nullptr));
        }
        else {
            CCLOG("Player Name: %s", name.c_str()); // 打印玩家姓名
            // 可以将 name 保存到文件或传递到下一个场景
            // Director::getInstance()->replaceScene(TransitionFade::create(1.0f, NextScene::createScene(), Color3B::BLACK));
        }
        });



    return true;
}
