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
	string name;
	cocos2d::Sprite* image;
    item(const string& itemName, const string& imagePath)
        : name(itemName)
    {
        image = cocos2d::Sprite::create(imagePath); // 创建物品图片
    }
    string getName() const
    {
        return name;
    }
};

#endif