#include "LearningScene.h"

USING_NS_CC;

Scene* LearningScene::createScene() {
    return LearningScene::create();
}

bool LearningScene::init() {
    if (!Scene::init()) {
        return false;
    }

    /* 加载人 */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    LEARNER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 1.0f, 100, 50, 20, 50, 10, 80, 1);

    /* 加载背景图 */
    // 待确认:是否加载地图
    auto background = Sprite::create("Scene/LearningScene.png");
    if (background) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        background->setScale(visibleSize.width / background->getContentSize().width,
            visibleSize.height / background->getContentSize().height);
        this->addChild(background, -10); // 将背景图放置在最底层
    }

    /* 加入对话框chatPanel */
    auto chatPanel = Sprite::create("UI/Panel5.png");
    chatPanel->setContentSize(Size(1500, 300));
    chatPanel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 200));
    chatPanel->setOpacity(190);
    this->addChild(chatPanel, -1);

    welcome();

}

/* 欢迎 */
void LearningScene::welcome() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    /* welcome文字 */
    auto welcomeTxt = Label::createWithTTF("Are you ready to learn some operations?", "fonts/Lacquer.ttf", 60);
    welcomeTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    welcomeTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(welcomeTxt, 0);

    /* Yes */
    auto YesButton = ui::Button::create("Button/YesButton.png", "Button/YesButtonClicked.png");
    YesButton->ignoreContentAdaptWithSize(false);
    YesButton->setContentSize(Size(150, 60));
    YesButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    this->addChild(YesButton, 1);

    /* Yes文字 */
    auto YesTxt = Label::createWithTTF("YES!", "fonts/KuaiLe_Chinese.ttf", 40);
    YesTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    YesTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(YesTxt,2); 

   /* YesButton->addClickEventListener([=](Ref* sender) mutable {
        welcomeTxt->removeFromParent();
        YesButton->removeFromParent();
        YesTxt->removeFromParent();
        
        });*/
}

/* 学走路 */
void LearningScene::learnMove() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto playerAns1 = Label::createWithTTF("How to move?", "fonts/KuaiLe_Chinese.ttf", 25);
    playerAns1->setPosition(Vec2(visibleSize.width / 2 + 50, visibleSize.height - 1080));
    playerAns1->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(playerAns1, 4);
}