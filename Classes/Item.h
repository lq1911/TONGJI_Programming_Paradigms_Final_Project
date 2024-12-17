#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
#include "ElementType.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class item
{
public:
    // 物品的名称
    string name;
    // 物品的图像
    cocos2d::Sprite* image;
    // 物品的描述
    string description;

    // 物品的图像名称
    string imageName;

    // 构造函数，需要给物品的三种成员变量赋值
    item(const string& itemName, const string& imagePath, const string& itemDescription)
        : name(itemName), description(itemDescription)
    {
        image = cocos2d::Sprite::create(imagePath); // 创建物品图片
        imageName = imagePath;
    }

    // 获取物品的名称
    string getName() const
    {
        return name;
    }

    // 获取物品的属性
    string getDescription() const
    {
        return description;
    }

    // 添加虚析构函数，使得类变为多态类
    virtual ~item() {}
};
// 装备类
class equipment :public item
{
public:
    equipment(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription)
    {
        equipment_level = 1;
        equipment_cost = 100;
    }

    // 添加虚析构函数，使得类变为多态类
    virtual ~equipment() {}

    // 增加角色的属性
    int increase_attribute;

    // 装备的等级
    int equipment_level;

    // 升级装备的消耗
    int equipment_cost;

    // 更新物品描述（虚函数，允许派生类重写）
    virtual void updateDescription() {}
};

// 消耗品类
class consumable : public item
{
public:
    consumable(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {
    }

    // 增加角色的HP
    int add_HP;
};

// 武器类
class weapon : public equipment
{
public:
    weapon(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {
    }

    // 更新物品的描述
    void updateDescription()
    {
        description = "Increase your attack power by " + to_string(this->increase_attribute) + " points\nLevel: " + to_string(equipment_level) + "\nUpgrade needs: " + to_string(equipment_cost);
    }
};

// 护甲类
class armor :public equipment
{
public:
    armor(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {
    }

    // 更新物品的描述
    void updateDescription() override
    {
        description = "Increase your defense by " + to_string(this->increase_attribute) + " points\nLevel: " + to_string(equipment_level) + "\nUpgrade needs: " + to_string(equipment_cost);
    }
};

// 鞋子类
class shoes :public equipment
{
public:
    shoes(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {
    }

    // 更新物品的描述
    void updateDescription() override
    {
        description = "Increase your shoes by " + to_string(this->increase_attribute) + " points\nLevel: " + to_string(equipment_level) + "\nUpgrade needs: " + to_string(equipment_cost);
    }
};

// 饰品类
class accessories :public equipment
{
public:
    accessories(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {
    }

    // 设置角色属性
    ElementType setPlayerElementType;

    // 设置饰品的元素类型
    void SetPlayerElementType(ElementType elementType) { setPlayerElementType = elementType; }
};

// 以下是具体的物品
class goods
{
public:
    // 物品名称：南瓜
    // 物品种类：消耗品
    // 作用：恢复10点生命值
    consumable pumkin;

    // 物品名称：铁剑
    // 物品种类：武器
    // 作用：增加10点攻击力
    weapon icon_sword;

    // 物品名称：铁甲
    // 物品种类：护甲
    // 作用：增加5点防御值
    armor icon_conselet;

    // 物品名称：靴子
    // 物品种类：鞋子
    // 作用：增加5点速度
    shoes boots;

    // 物品名称：火药
    // 物品种类：饰品
    // 作用：将角色设为火属性
    accessories bomb;

    goods()
        : pumkin("pumpkin", "goods/Pumpkin.png", "Restore your health by 10 points"),   // 初始化南瓜
        icon_sword("sword", "goods/sword.png", "Increase your attack power"),  // 初始化铁剑
        icon_conselet("conselet", "goods/conselet.png", "Increase your defense"), // 初始化铁甲
        boots("boots", "goods/boots.png", "Increase your speed"), // 初始化靴子
        bomb("bumb", "goods/bumb.png", "Set your attribute to fire") // 初始化火药
    {
        // 设置数值
        pumkin.add_HP = 10;
        icon_sword.increase_attribute = 10;
        icon_sword.updateDescription();
        icon_conselet.increase_attribute = 5;
        icon_conselet.updateDescription();
        boots.increase_attribute = 5;
        boots.updateDescription();
        bomb.SetPlayerElementType(ElementType::FIRE);
    }
};
#endif