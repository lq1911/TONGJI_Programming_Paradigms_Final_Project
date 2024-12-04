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

    // 构造函数，需要给物品的三种成员变量赋值
    item(const string& itemName, const string& imagePath, const string& itemDescription)
        : name(itemName), description(itemDescription)
    {
        image = cocos2d::Sprite::create(imagePath); // 创建物品图片
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

    // 物品发挥功能
    void itemFunction()
    {

    }
    // 添加虚析构函数，使得类变为多态类
    virtual ~item() {}
};
// 
class equipment:public item
{
public:
    equipment(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}
    void equip();
};

class consumable : public item
{
public:
    consumable(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}
    void consume();
};
#endif