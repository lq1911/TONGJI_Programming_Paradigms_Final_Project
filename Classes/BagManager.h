#pragma once
#ifndef __BAG_MANAGER_H__
#define __BAG_MANAGER_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include "Item.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class BagManager : public cocos2d::Node 
{
public:
    // 获取单例实例
    static BagManager* getInstance();

    // 初始化背包管理器
    bool init();

    // 显示背包
    void showBag();

    // 隐藏背包
    void hideBag();

    // 判断背包是否可见
    bool isBagVisible() const { return _isBagOpen; }

    //更新背包UI
    void updateBagUI();

private:
    // 私有构造函数，禁止外部直接实例化
    BagManager();
    // 析构函数
    ~BagManager();

    // 背包的显示状态
    bool _isBagOpen;

    // 背包内的物品
    item* items[40];

    // 背包的UI面板
    cocos2d::Node* _bagPanel;

    // 背包背景
    cocos2d::Sprite* _bagBackground;

    // 角色面板背景
    cocos2d::Sprite* _characterBackground;

    // 静态成员变量，用于存储单例实例
    static BagManager* _instance;

    // 创建背包背景
    void createBagBackground();

    // 创建角色面板
    void createCharacterPanel();

    // 禁止拷贝构造函数和赋值操作符
    BagManager(const BagManager&) = delete;
    BagManager& operator=(const BagManager&) = delete;
};

#endif // __BAG_MANAGER_H__
