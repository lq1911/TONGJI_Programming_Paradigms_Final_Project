#include "BagManager.h"
#include "ui/CocosGUI.h"
#include <vector>
#include "Item.h"

USING_NS_CC;
using namespace ui;
using namespace std;

BagManager* BagManager::_instance = nullptr;

BagManager* BagManager::getInstance()
{
    // 如果实例不存在，创建一个新的实例
    if (_instance == nullptr)
    {
        _instance = new BagManager();  // 创建实例
        _instance->init();  // 初始化实例
    }
    return _instance;  // 返回实例指针
}

BagManager::BagManager() : _isBagOpen(false), _bagPanel(nullptr)
{
    for (int i = 0; i < 40; i++)
        items[i] = nullptr;
    items_num = 0;
}

BagManager::~BagManager()
{
    if (_bagPanel)
        _bagPanel->removeFromParent();
    if (_bagBackground)
        _bagBackground->release();
    if (_characterBackground)
        _characterBackground->release();
}

bool BagManager::init()
{
    if (!Node::init())
        return false;  // 初始化失败

    // 创建背包面板，作为背包UI的容器
    _bagPanel = Node::create();
    this->addChild(_bagPanel);  // 将背包面板添加到当前节点
    _bagPanel->setVisible(false);  // 默认情况下背包是隐藏的

    return true;  // 初始化成功
}

void BagManager::showBag(Player& _player)
{
    player = _player;
    // 如果背包尚未打开，则创建并显示背包背景
    if (!_isBagOpen)
    {
        // 创建背包背景
        createBagBackground();

        // 更新物品栏内的物品
        updateBagUI();

        // 创建角色面板
        createCharacterPanel();

        _bagPanel->setVisible(true);  // 显示背包面板
        _isBagOpen = true;
    }
}

void BagManager::hideBag(Player& _player)
{
    if (_isBagOpen)
    {
        _bagPanel->setVisible(false);  // 隐藏背包面板
        _bagPanel->removeChild(_bagBackground);  // 移除背景
        _bagPanel->removeChild(_characterBackground);  // 移除角色面板背景
        _bagBackground = nullptr;  // 清除背景指针
        _characterBackground = nullptr;
        _isBagOpen = false;  // 更新状态
        _player = player;
    }
}

void BagManager::updateBagUI()
{
    // 设置物品栏格子尺寸和间隔
    float xStart = 75.0f;  // 起始X位置
    float yStart = _bagBackground->getContentSize().height - 80.0f;  // 起始Y位置（靠近背包标题下方）

    // 创建5x8的物品格子
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 5; ++col)
        {
            // 计算每个格子的坐标
            float xPos = xStart + col * 80;
            float yPos = yStart - row * 70;
            int index = row * 5 + col;

            // 添加物品栏
            auto slot = Button::create("Bag/item_slot.png");
            slot->setPosition(Vec2(xPos, yPos));
            slot->addClickEventListener([=](Ref* sender) {
                slot_click(slot, row, col);
                });
            _bagBackground->addChild(slot);
            if (items[index] != NULL)
            {
                if (items[index]->image->getParent() == nullptr)// 图像是否有父节点
                {
                    // 设置物品图像的位置并添加到按钮格子
                    items[index]->image->setPosition(Vec2(slot->getContentSize().width / 2, slot->getContentSize().height / 2));
                    slot->addChild(items[index]->image);// 添加父节点
                    items[index]->image->retain();
                }
                else
                {
                    items[index]->image->removeFromParent();// 移除当前的父节点
                    items[index]->image->setPosition(Vec2(slot->getContentSize().width / 2, slot->getContentSize().height / 2));
                    slot->addChild(items[index]->image);
                    items[index]->image->retain();// 保证图像对象不被销毁
                }
            }
        }
    // 更新角色面板
    createCharacterPanel();
}

// 创建背包背景
void BagManager::createBagBackground()
{
    // 设置背包背景图片
    _bagBackground = Sprite::create("Bag/bag_background.png");
    //  _bagBackground->setPosition(Vec2(player.mySprite->getPosition().x, player.mySprite->getPosition().y));
    _bagBackground->setPosition(Director::getInstance()->getVisibleSize() / 2);
    _bagPanel->addChild(_bagBackground);

    // 创建背包标题
    auto titleLabel = Label::createWithTTF("MY_BAG", "fonts/arial.ttf", 32);
    titleLabel->setPosition(Vec2(_bagBackground->getContentSize().width / 2, _bagBackground->getContentSize().height - 20));
    // 设置字体颜色为金色 (RGB: 255, 215, 0)
    titleLabel->setTextColor(Color4B(255, 215, 0, 255));
    _bagBackground->addChild(titleLabel);
}

// 创建角色面板
void BagManager::createCharacterPanel()
{
    // 设置角色面板背景
    _characterBackground = Sprite::create("Bag/character_background.png");
    float characterBackground_x = _bagBackground->getPositionX() + _bagBackground->getContentSize().width / 2 + _characterBackground->getContentSize().width / 2;
    float characterBackground_y = _bagBackground->getPositionY() + _bagBackground->getContentSize().height / 2 - _characterBackground->getContentSize().height / 2;
    _characterBackground->setPosition(Vec2(characterBackground_x, characterBackground_y));
    _bagPanel->addChild(_characterBackground, -1);

    // 创建角色面板标题
    auto characterTitleLabel = Label::createWithTTF("MY_CHARACTER", "fonts/arial.ttf", 32);
    characterTitleLabel->setPosition(Vec2(_characterBackground->getContentSize().width / 2, _characterBackground->getContentSize().height - 20));
    // 设置字体颜色为金色 (RGB: 255, 215, 0)
    characterTitleLabel->setTextColor(Color4B(255, 215, 0, 255));
    _characterBackground->addChild(characterTitleLabel);

    // 绘制边框
    float borderWidth = _characterBackground->getContentSize().width / 2;
    float borderHeight = _characterBackground->getContentSize().height / 2;

    Vec2 borderPosition = Vec2(borderWidth, borderHeight);

    auto drawNode = DrawNode::create();
    _characterBackground->addChild(drawNode);

    drawNode->drawRect(
        Vec2(borderPosition.x - borderWidth / 2, borderPosition.y - borderHeight / 2),
        Vec2(borderPosition.x + borderWidth / 2, borderPosition.y + borderHeight / 2),
        Color4F(1.0f, 1.0f, 1.0f, 1.0f)
    );
    // 在角色面板两边添加装备栏

    // 武器
    auto button1 = Button::create("Bag/item_slot.png");// 添加按钮
    button1->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 40, borderPosition.y + borderHeight / 2 - 30));
    button1->addClickEventListener([](Ref* sender) {});// 添加按钮点击事件
    _characterBackground->addChild(button1);
    auto label1 = Label::createWithTTF("Weapon", "fonts/arial.ttf", 16);// 添加文字 
    label1->setPosition(Vec2(20, -6));
    button1->addChild(label1);

    // 获取玩家的武器图像并设置到武器栏
    if (player._weapon != nullptr)
    {
        // 获取武器图像并设置
        auto weaponImage = player._weapon->image;
        weaponImage->retain(); // 保证图像对象不被销毁
        weaponImage->removeFromParent(); // 移除当前的父节点
        if (weaponImage != nullptr)
        {
            weaponImage->setPosition(Vec2(button1->getContentSize().width / 2, button1->getContentSize().height / 2));
            button1->addChild(weaponImage);  // 将图像添加到武器栏按钮中
        }
    }

    // 添加关闭按钮，如果装备栏有装备，就卸下装备
    auto closeButton1 = Button::create("Bag/close_button.png");
    closeButton1->setPosition(Vec2(button1->getContentSize().width, button1->getContentSize().height)); // 右上角位置
    closeButton1->addClickEventListener([=](Ref* sender) {
        if (player._weapon != nullptr)
        {
            player.atk -= player._weapon->increase_attack;
            auto _item = dynamic_cast<item*>(player._weapon); // 将武器类指针转换为物品类指针
            player._weapon = nullptr; // 将角色武器指针置为空指针
            addItem(_item); // 将卸下的装备放回物品栏
        }
        });
    button1->addChild(closeButton1);


    // 护甲
    auto button2 = Button::create("Bag/item_slot.png");
    button2->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 40, borderPosition.y - borderHeight / 2 + 30));
    button2->addClickEventListener([](Ref* sender) {});
    _characterBackground->addChild(button2);
    auto label2 = Label::createWithTTF("Armor", "fonts/arial.ttf", 16);
    label2->setPosition(Vec2(20, -6));
    button2->addChild(label2);

    // 获取玩家的护甲图像并设置到护甲栏
    if (player._armor != nullptr)
    {
        // 获取护甲图像并设置
        auto armorImage = player._armor->image;
        armorImage->retain(); // 保证图像对象不被销毁
        armorImage->removeFromParent(); // 移除当前的父节点
        if (armorImage != nullptr)
        {
            armorImage->setPosition(Vec2(button2->getContentSize().width / 2, button2->getContentSize().height / 2));
            button2->addChild(armorImage);  // 将图像添加到护甲栏按钮中
        }
    }

    // 添加关闭按钮，如果装备栏有装备，就卸下装备
    auto closeButton2 = Button::create("Bag/close_button.png");
    closeButton2->setPosition(Vec2(button2->getContentSize().width, button2->getContentSize().height)); // 右上角位置
    closeButton2->addClickEventListener([=](Ref* sender) {
        if (player._armor != nullptr)
        {
            player.def -= player._armor->increase_defense;
            auto _item = dynamic_cast<item*>(player._armor);
            player._armor = nullptr;
            addItem(_item);
        }
        });
    button2->addChild(closeButton2);


    // 鞋子
    auto button3 = Button::create("Bag/item_slot.png");
    button3->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 40, borderPosition.y + borderHeight / 2 - 30));
    button3->addClickEventListener([](Ref* sender) {});
    _characterBackground->addChild(button3);
    auto label3 = Label::createWithTTF("Shoes", "fonts/arial.ttf", 16);
    label3->setPosition(Vec2(20, -6));
    button3->addChild(label3);

    // 获取玩家的鞋子图像并设置到鞋子栏
    if (player._shoes != nullptr)
    {
        // 获取鞋子图像并设置
        auto shoesImage = player._shoes->image;
        shoesImage->retain(); // 保证图像对象不被销毁
        shoesImage->removeFromParent(); // 移除当前的父节点
        if (shoesImage != nullptr)
        {
            shoesImage->setPosition(Vec2(button3->getContentSize().width / 2, button3->getContentSize().height / 2));
            button3->addChild(shoesImage);  // 将图像添加到鞋子栏按钮中
        }
    }

    // 添加关闭按钮，如果装备栏有装备，就卸下装备
    auto closeButton3 = Button::create("Bag/close_button.png");
    closeButton3->setPosition(Vec2(0, button3->getContentSize().height)); // 右上角位置
    closeButton3->addClickEventListener([=](Ref* sender) {
        if (player._shoes != nullptr)
        {
            player.speed -= player._shoes->increase_speed;
            auto _item = dynamic_cast<item*>(player._shoes);
            player._shoes = nullptr;
            addItem(_item);
        }
        });
    button3->addChild(closeButton3);


    // 饰品
    auto button4 = Button::create("Bag/item_slot.png");
    button4->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 40, borderPosition.y - borderHeight / 2 + 30));
    button4->addClickEventListener([](Ref* sender) {});
    _characterBackground->addChild(button4);
    auto label4 = Label::createWithTTF("Accessories", "fonts/arial.ttf", 16);
    label4->setPosition(Vec2(20, -6));
    button4->addChild(label4);

    // 获取玩家的饰品图像并设置到饰品栏
    if (player._accessories != nullptr)
    {
        // 获取饰品图像并设置
        auto accessoriesImage = player._accessories->image;
        accessoriesImage->retain(); // 保证图像对象不被销毁
        accessoriesImage->removeFromParent(); // 移除当前的父节点
        if (accessoriesImage != nullptr)
        {
            accessoriesImage->setPosition(Vec2(button4->getContentSize().width / 2, button4->getContentSize().height / 2));
            button4->addChild(accessoriesImage);  // 将图像添加到饰品栏按钮中
        }
    }

    // 添加关闭按钮，如果装备栏有装备，就卸下装备
    auto closeButton4 = Button::create("Bag/close_button.png");
    closeButton4->setPosition(Vec2(0, button4->getContentSize().height)); // 右上角位置
    closeButton4->addClickEventListener([=](Ref* sender) {
        if (player._accessories != nullptr)
        {
            player.atk -= player._accessories->increase_attack;
            player.def -= player._accessories->increase_defense;
            player.speed -= player._accessories->increase_speed;
            auto _item = dynamic_cast<item*>(player._accessories);
            player._accessories = nullptr;
            addItem(_item);
        }
        });
    button4->addChild(closeButton4);

    //显示角色的等级、HP、MP
    // 等级
    string player_level = "Level: " + to_string(player.level);
    auto characterLevel = Label::createWithTTF(player_level, "fonts/arial.ttf", 16);
    // 设置锚点，从左边开始
    characterLevel->setAnchorPoint(Vec2(0, 0.5));
    characterLevel->setPosition(Vec2(200, 320));
    _characterBackground->addChild(characterLevel);
    // HP
    string player_HP = "HP: " + to_string(player.hp);
    auto characterHP = Label::createWithTTF(player_HP, "fonts/arial.ttf", 16);
    // 设置锚点，从左边开始
    characterHP->setAnchorPoint(Vec2(0, 0.5));
    characterHP->setPosition(Vec2(1, 320));
    _characterBackground->addChild(characterHP);
    // MP
    string player_MP = "MP: " + to_string(player.mp);
    auto characterMP = Label::createWithTTF(player_MP, "fonts/arial.ttf", 16);
    // 设置锚点，从左边开始
    characterMP->setAnchorPoint(Vec2(0, 0.5));
    characterMP->setPosition(Vec2(1, 300));
    _characterBackground->addChild(characterMP);

    // 显示角色的攻击力、防御力、速度
    // 攻击力
    string player_attack = "Attack: " + to_string(player.atk);
    auto characterAttack = Label::createWithTTF(player_attack, "fonts/arial.ttf", 16);
    // 设置锚点，从左边开始
    characterAttack->setAnchorPoint(Vec2(0, 0.5));
    characterAttack->setPosition(Vec2(80, 320));
    _characterBackground->addChild(characterAttack);
    // 防御力
    string player_defense = "Defense: " + to_string(player.def);
    auto characterDefense = Label::createWithTTF(player_defense, "fonts/arial.ttf", 16);
    // 设置锚点，从左边开始
    characterDefense->setAnchorPoint(Vec2(0, 0.5));
    characterDefense->setPosition(Vec2(80, 300));
    _characterBackground->addChild(characterDefense);

    // 速度
    string player_speed = "Speed: " + to_string(player.speed);
    auto characterSpeed = Label::createWithTTF(player_speed, "fonts/arial.ttf", 16);
    // 设置锚点，从左边开始
    characterSpeed->setAnchorPoint(Vec2(0, 0.5));
    characterSpeed->setPosition(Vec2(200, 300));
    _characterBackground->addChild(characterSpeed);
}

// 点击物品栏事件
void BagManager::slot_click(Button* slot, int row, int col)
{
    // 点击格子时检查是否有物品
    if (items[row * 5 + col] != NULL)
    {
        // 打开物品信息面板
        auto itemInfoBackground = Sprite::create("Bag/item_info_background.png");
        float itemInfoBackground_x = slot->getPosition().x + itemInfoBackground->getContentSize().width / 2 + slot->getContentSize().width / 2;
        float itemInfoBackground_y = slot->getPosition().y - itemInfoBackground->getContentSize().height / 2 + slot->getContentSize().height / 2;
        itemInfoBackground->setPosition(Vec2(itemInfoBackground_x, itemInfoBackground_y)); // 将背景放置在格子旁边
        _bagBackground->addChild(itemInfoBackground, 10);

        // 创建关闭按钮（×按钮）
        auto closeButton = Button::create("Bag/close_button.png");
        closeButton->setPosition(Vec2(itemInfoBackground->getContentSize().width, itemInfoBackground->getContentSize().height)); // 右上角位置
        closeButton->addClickEventListener([=](Ref* sender) {
            // 点击×按钮时移除 itemInfoBackground
            itemInfoBackground->removeFromParent();  // 从父节点移除
            });

        // 将关闭按钮添加到背景中
        itemInfoBackground->addChild(closeButton);

        // 获取物品名字
        string itemName = items[row * 5 + col]->getName();
        string itemDescription = items[row * 5 + col]->getDescription();

        // 创建并显示物品名字的 Label
        auto itemNameLabel = Label::createWithSystemFont(itemName, "Arial", 24);
        // 设置字体颜色为金色 (RGB: 255, 215, 0)
        itemNameLabel->setTextColor(Color4B(255, 215, 0, 255)); // Color4B的第四个参数是透明度
        itemNameLabel->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 10));  // 放置在背景上方
        itemInfoBackground->addChild(itemNameLabel);

        // 创建并显示物品描述的 Label
        auto itemDescriptionLabel = Label::createWithSystemFont(itemDescription, "Arial", 16);
        // 设置锚点
        itemDescriptionLabel->setAnchorPoint(Vec2(0, 0.5));
        // 设置文本最大宽度为物品信息背景的宽度（可以适当留个边距）
        float maxWidth = itemInfoBackground->getContentSize().width - 10;  // 留点左右边距
        // 设置最大宽度和高度
        itemDescriptionLabel->setDimensions(maxWidth, 0);
        itemDescriptionLabel->setPosition(Vec2(10, itemInfoBackground->getContentSize().height - 30));  // 放置在背景上方
        itemInfoBackground->addChild(itemDescriptionLabel);

        // 创建使用物品按钮
        auto useButton = Button::create("Bag/use_button.png");
        useButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 100));
        useButton->addClickEventListener([=](Ref* sender) {
            if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col]))
            {
                // 装备该物品
                equipItem(row * 5 + col);
                itemInfoBackground->removeFromParent();  // 丢弃后关闭物品信息面板
            }
            else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col]))
            {
                auto consumption = dynamic_cast<consumable*>(items[row * 5 + col]);
                player.hp += consumption->add_HP;
                dynamic_cast<item*>(items[row * 5 + col]);
                // 丢弃该物品
                discardItems(row * 5 + col);
                itemInfoBackground->removeFromParent();  // 丢弃后关闭物品信息面板
            }
            }); // 添加鼠标点击事件
        itemInfoBackground->addChild(useButton);

        // 根据物品的类型为按钮添加不同的文字
        if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col])) // 物品是装备类
        {
            auto itemEquipLabel = Label::createWithSystemFont("equip", "Arial", 16); // 按钮上显示的是装备
            itemEquipLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // 设置位置
            useButton->addChild(itemEquipLabel);
        }
        else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col])) // 物品是消耗品类
        {
            auto itemConsumeLabel = Label::createWithSystemFont("consume", "Arial", 16); // 按钮上显示的是消耗
            itemConsumeLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // 设置位置
            useButton->addChild(itemConsumeLabel);
        }

        // 创建丢弃物品按钮
        auto dicardButton = Button::create("Bag/use_button.png");
        dicardButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 130));
        dicardButton->addClickEventListener([=](Ref* sender) {
            // 丢弃该物品
            discardItems(row * 5 + col);
            itemInfoBackground->removeFromParent();  // 丢弃后关闭物品信息面板
            }); // 添加鼠标点击事件
        itemInfoBackground->addChild(dicardButton);
        // 为按钮添加文字
        auto itemDiscardLabel = Label::createWithSystemFont("discard", "Arial", 16); // 按钮上显示的是丢弃
        itemDiscardLabel->setPosition(Vec2(dicardButton->getContentSize().width / 2, dicardButton->getContentSize().height / 2)); // 设置位置
        dicardButton->addChild(itemDiscardLabel);
    }
}

// 将物品添加到背包
void BagManager::addItem(item* it)
{
    if (it == nullptr || it->image == nullptr)
        return; // 无效物品，退出函数
    if (items_num < 40) // 背包没有满时才可以添加物品
    {
        int location = 0;
        // 找到空的物品栏
        for (int i = 0; i < 40; i++)
            if (items[i] == NULL)
            {
                location = i;
                break;
            }
        items[location] = it; // 更新物品栏
        it->image->retain(); // 保证物品图像的生命周期
        if (_isBagOpen)
            updateBagUI();
        items_num++; // 物品数量加1
    }
}

// 将物品从背包中丢弃
void BagManager::discardItems(int index)
{
    // 确保物品存在
    if (items[index] != nullptr)
    {
        // 移除物品的图像（从其父节点移除）
        items[index]->image->removeFromParent();
        // 清除物品数据
        delete items[index];  // 删除物品对象
        items[index] = nullptr; // 清空该位置
        // 更新物品数量
        items_num--;
        // 如果背包UI已经显示，刷新UI
        if (_isBagOpen)
            updateBagUI();
    }
}

// 将背包内的物品装备到角色身上
void BagManager::equipItem(int index)
{
    if (items[index] != nullptr)
    {
        if (auto weaponItem = dynamic_cast<weapon*>(items[index])) // 物品是武器类
        {
            if (player._weapon == nullptr)
            {
                // 更新角色武器指针
                player._weapon = weaponItem;
                // 增加角色攻击力
                player.atk += player._weapon->increase_attack;
                // 不可以清除物品信息
                items[index] = nullptr; // 清空该位置
                // 更新物品数量
                items_num--;
                // 如果背包UI已经显示，刷新UI
                if (_isBagOpen)
                    updateBagUI();
            }
        }
        else if (auto armorItem = dynamic_cast<armor*>(items[index])) // 物品是护甲类
        {
            if (player._armor == nullptr)
            {
                // 更新角色护甲指针
                player._armor = armorItem;
                // 增加角色的防御值
                player.def += player._armor->increase_defense;
                // 不可以清除物品信息
                items[index] = nullptr; // 清空该位置
                // 更新物品数量
                items_num--;
                // 如果背包UI已经显示，刷新UI
                if (_isBagOpen)
                    updateBagUI();
            }
        }
        else if (auto shoesItem = dynamic_cast<shoes*>(items[index])) // 物品是鞋子类
        {
            if (player._shoes == nullptr)
            {
                // 更新角色鞋子指针
                player._shoes = shoesItem;
                // 增加角色的速度
                player.speed += player._shoes->increase_speed;
                // 不可以清除物品信息
                items[index] = nullptr; // 清空该位置
                // 更新物品数量
                items_num--;
                // 如果背包UI已经显示，刷新UI
                if (_isBagOpen)
                    updateBagUI();
            }
        }
        else if (auto accessoriesItem = dynamic_cast<accessories*>(items[index])) // 物品是饰品类
        {
            if (player._accessories == nullptr)
            {
                // 更新角色饰品指针
                player._accessories = accessoriesItem;
                // 增加角色攻击力
                player.atk += player._accessories->increase_attack;
                // 增加角色的防御值
                player.def += player._accessories->increase_defense;
                // 增加角色的速度
                player.speed += player._accessories->increase_speed;
                // 不可以清除物品信息
                items[index] = nullptr; // 清空该位置
                // 更新物品数量
                items_num--;
                // 如果背包UI已经显示，刷新UI
                if (_isBagOpen)
                    updateBagUI();
            }
        }
    }

}