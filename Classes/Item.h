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
        equipment_levelMax = 10;
    }

    // 添加虚析构函数，使得类变为多态类
    virtual ~equipment() {}

    // 增加角色的属性
    int increase_attribute;

    // 装备的等级
    int equipment_level;

    // 装备的最大等级
    int equipment_levelMax;

    // 升级装备的消耗
    int equipment_cost;

    // 更新物品描述（虚函数，允许派生类重写）
    virtual void updateDescription(){}
};

// 消耗品类
class consumable : public item
{
public:
    consumable(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}

    // 增加角色的HP
    int add_HP;
};

// 武器类
class weapon : public equipment
{
public:
    weapon(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {}

    // 更新物品的描述
    void updateDescription()
    {
        if (increase_criticalChance <= 0)
            description = "Increase your attack power by " + to_string(this->increase_attribute) + " points\nLevel: " + to_string(equipment_level) + "\nUpgrade needs: " + to_string(equipment_cost);
        else
            description = "Increase your attack power by " + to_string(this->increase_attribute) + " points and increase your critical chance by " + to_string(int(this->increase_criticalChance * 100)) + "%\nLevel: " + to_string(equipment_level) + "\nUpgrade needs : " + to_string(equipment_cost);
    }

    // 武器暴击率
    float increase_criticalChance = 0.0f;
};

// 护甲类
class armor :public equipment
{
public:
    armor(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {}
    
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
        : equipment(itemName, imagePath, itemDescription) {}

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
        : equipment(itemName, imagePath, itemDescription){} 

    // 设置角色属性
    ElementType setPlayerElementType;

    // 设置饰品的元素类型
    void SetPlayerElementType(ElementType elementType) { setPlayerElementType = elementType; }
};

// 以下是具体的物品
class goods
{
public:
    // 物品名称：铁剑
    // 物品种类：武器
    // 作用：增加10点攻击力
    weapon icon_sword;

    // 物品名称：大剑
    // 物品种类：武器
    // 作用：增加20点攻击力和10%暴击率
    weapon great_sword;

    // 物品名称：长剑
    // 物品种类：武器
    // 作用：增加30点攻击力
    weapon long_sword;

    // 物品名称：匕首
    // 物品种类：武器
    // 作用：增加10点攻击力和25%暴击率
    weapon dagger;
    
    // 物品名称：最终之剑
    // 物品种类：武器
    // 作用：增加50点攻击力和50%暴击率
    weapon final_weapon;

    // 物品名称：铁甲
    // 物品种类：护甲
    // 作用：增加5点防御值
    armor icon_conselet;

    // 物品名称：盾牌
    // 物品种类：护甲
    // 作用：增加20点防御值
    armor shield;

    // 物品名称：头盔
    // 物品种类：护甲
    // 作用：增加15点防御值
    armor helmet;

    // 物品名称：最终之甲
    // 物品种类：护甲
    // 作用：增加50点防御值
    armor final_armor;

    // 物品名称：靴子
    // 物品种类：鞋子
    // 作用：增加5点速度
    shoes boots;

    // 物品名称：钻石靴
    // 物品种类：鞋子
    // 作用：增加7点速度
    shoes diamond_shoes;

    // 物品种类：最终之靴
    // 物品种类：鞋子
    // 作用：增加12点速度
    shoes final_shoes;

    // 物品名称：火焰戒指
    // 物品种类：饰品
    // 作用：将玩角色设置为火属性
    accessories fire_ring;

    // 物品名称：寒冰项链
    // 物品种类：饰品
    // 作用：将角色设置为冰属性
    accessories ice_nacklace;

    // 物品名称：森林权杖
    // 物品种类：饰品
    // 作用：将角色设置为草属性
    accessories forest_scepter;
    // 物品名称：岩石披风
    // 物品种类：饰品
    // 作用：将角色设置为土属性
    accessories rack_cape;

    // 物品名称：南瓜
    // 物品种类：消耗品
    // 作用：恢复10点生命值
    consumable pumkin;

    // 物品名称：苹果
    // 物品种类：消耗品
    // 作用：恢复5点生命值
    consumable apple;

    // 物品名称：奶酪
    // 物品种类：消耗品
    // 作用：恢复15点生命值
    consumable cheese;

    // 物品名称：鸡腿
    // 物品种类：消耗品
    // 作用：恢复20点生命值
    consumable chicken_leg;

    // 物品名称：啤酒
    // 物品种类：消耗品
    // 作用：恢复10点生命值
    consumable beer;

    // 物品名称：生命药水
    // 物品种类：消耗品
    // 作用：恢复50点生命值
    consumable life_potion;
    goods()
        : pumkin("pumpkin", "goods/Pumpkin.png", "Restore your health by 10 points"),
        icon_sword("sword", "goods/sword.png", "Increase your attack power"),
        icon_conselet("conselet", "goods/conselet.png", "Increase your defense"),
        boots("boots", "goods/boots.png", "Increase your speed"),
        great_sword("great sword", "goods/great_sword.png", "Increase your attack power"),
        long_sword("long sword", "goods/long_sword.png", "Increase your attack power"),
        dagger("dagger", "goods/dagger.png", "Increase your attack power and critical chance"),
        final_weapon("final sword", "goods/final_sword.png", "Increase your attack power and critical chance"),
        shield("shield", "goods/shield.png", "Increase your defense"),
        helmet("helmet", "goods/helmet.png", "Increase your defense"),
        final_armor("final armor", "goods/final_armor.png", "Increase your defense"),
        diamond_shoes("diamond shoes", "goods/diamond_shoes.png", "Increase your speed"),
        final_shoes("final shoes", "goods/final_shoes.png", "Increase your speed"),
        fire_ring("fire ring", "goods/fire_ring.png", "Set your element to Fire"),
        ice_nacklace("ice necklace", "goods/ice_nacklace.png", "Set your element to Ice"),
        forest_scepter("forest scepter", "goods/forest_scepter.png", "Set your element to Earth"),
        rack_cape("rack cape", "goods/rack_cape.png", "Set your element to Rock"),
        apple("apple", "goods/apple.png", "Restore your health by 5 points"),
        cheese("cheese", "goods/cheese.png", "Restore your health by 15 points"),
        chicken_leg("chicken_leg", "goods/chicken_leg.png", "Restore your health by 20 points"),
        beer("beer", "goods/beer.png", "Restore your health by 10 points"),
        life_potion("life potion", "goods/life_potion.png", "Restore your health by 50 points")
    {
        // 设置数值
        pumkin.add_HP = 10;
        apple.add_HP = 5;
        cheese.add_HP = 15;
        chicken_leg.add_HP = 20;
        beer.add_HP = 10;
        life_potion.add_HP = 50;

        icon_sword.increase_attribute = 10;
        icon_sword.updateDescription();

        great_sword.increase_attribute = 20;
        great_sword.increase_criticalChance = 0.1f;
        great_sword.updateDescription();

        long_sword.increase_attribute = 30;
        long_sword.updateDescription();

        dagger.increase_attribute = 10;
        dagger.increase_criticalChance = 0.25f;
        dagger.updateDescription();

        final_weapon.increase_attribute = 50;
        final_weapon.increase_criticalChance = 0.5f;
        final_weapon.updateDescription();

        icon_conselet.increase_attribute = 5;
        icon_conselet.updateDescription();

        shield.increase_attribute = 20;
        shield.updateDescription();

        helmet.increase_attribute = 15;
        helmet.updateDescription();

        final_armor.increase_attribute = 50;
        final_armor.updateDescription();

        boots.increase_attribute = 5;
        boots.updateDescription();

        diamond_shoes.increase_attribute = 7;
        diamond_shoes.updateDescription();

        final_shoes.increase_attribute = 12;
        final_shoes.updateDescription();

        fire_ring.SetPlayerElementType(ElementType::FIRE);
        ice_nacklace.SetPlayerElementType(ElementType::ICE);
        forest_scepter.SetPlayerElementType(ElementType::GRASS);
        rack_cape.SetPlayerElementType(ElementType::ROCK);
    }
};
#endif