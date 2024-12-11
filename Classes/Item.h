#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"

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

    // 赋值运算符重载
    item& operator=(const item& other)
    {
        if (this != &other) // 避免自我赋值
        {  
            // 复制基础成员
            name = other.name;
            description = other.description;
            image = cocos2d::Sprite::create(other.imageName);  // 创建新副本
        }
        return *this;
    }

    // 添加虚析构函数，使得类变为多态类
    virtual ~item() {}
};
// 装备类
class equipment:public item
{
public:
    equipment(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}
    // 添加虚析构函数，使得类变为多态类
    virtual ~equipment() {}
};

// 消耗品类
class consumable : public item
{
public:
    consumable(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}
    int add_HP;

    // 赋值运算符重载
    consumable& operator=(const consumable& other) 
    {
        if (this != &other) // 避免自我赋值
        {  
            // 赋值基类 item 的成员
            item::operator=(other);
            // 赋值 consumable 类的成员
            add_HP = other.add_HP;
        }
        return *this;
    }
};

// 武器类
class weapon : public equipment
{
public:
   weapon(const string& itemName, const string& imagePath, const string& itemDescription)
       : equipment(itemName, imagePath, itemDescription) {}
   // 增加角色的攻击力
   int increase_attack;

   // 赋值运算符重载
   weapon& operator=(const weapon& other)
   {
       if (this != &other) // 避免自我赋值
       {
           // 赋值基类 item 的成员
           item::operator=(other);
           // 赋值 weapon 类的成员
           increase_attack = other.increase_attack;
       }
       return *this;
   }
};

// 护甲类
class armor :public equipment
{
public:
    armor(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {}
    // 增加角色的防御值
    int increase_defense;

    // 赋值运算符重载
    armor& operator=(const armor& other)
    {
        if (this != &other) // 避免自我赋值
        {
            // 赋值基类 item 的成员
            item::operator=(other);
            // 赋值 armor 类的成员
            increase_defense = other.increase_defense;
        }
        return *this;
    }
};

// 鞋子类
class shoes :public equipment
{
public:
    shoes(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {}
    // 增加角色的速度
    int increase_speed;

    // 赋值运算符重载
    shoes& operator=(const shoes& other)
    {
        if (this != &other) // 避免自我赋值
        {
            // 赋值基类 item 的成员
            item::operator=(other);
            // 赋值 shoes 类的成员
            increase_speed = other.increase_speed;
        }
        return *this;
    }
};

// 饰品类
class accessories :public equipment
{
public:
    accessories(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) 
    {
        increase_attack = 0;
        increase_defense = 0;
        increase_speed = 0;
    }
    // 增加角色的攻击力
    int increase_attack;
    // 增加角色的防御值
    int increase_defense;
    // 增加角色的速度
    int increase_speed;

    // 赋值运算符重载
    accessories& operator=(const accessories& other)
    {
        if (this != &other) // 避免自我赋值
        {
            // 赋值基类 item 的成员
            item::operator=(other);
            // 赋值 accessories 类的成员
            increase_attack = other.increase_attack;
            increase_defense = other.increase_defense;
            increase_speed = other.increase_speed;
        }
        return *this;
    }
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
    // 作用：增加20点攻击力和3点速度
    accessories bomb;

    goods()
        : pumkin("pumpkin", "Pumpkin.png", "Restore your health"),   // 初始化南瓜
        icon_sword("sword", "sword.png", "Increase your attack power"),  // 初始化铁剑
        icon_conselet("conselet", "conselet.png", "Increase your defense"), // 初始化铁甲
        boots("boots", "boots.png", "Increase your speed"), // 初始化靴子
        bomb("bumb", "bumb.png", "Increase your attack power") // 初始化火药
    {
        // 设置数值
        pumkin.add_HP = 10;  
        icon_sword.increase_attack = 10;  
        icon_conselet.increase_defense = 5; 
        boots.increase_speed = 5;
        bomb.increase_attack = 20;
        bomb.increase_speed = 3;
    }
};
#endif