#ifndef __MICRO_MAP_H__
#define __MICRO_MAP_H__

#include "cocos2d.h"

/*这里的向量一共储存了不同区域的名称以及不同区域的属性，在向量中
0—森林区域，1—火山区域，2—沙漠区域，3—雪地区域，4—初始神庙*/

class MicroMap :public cocos2d::Layer {
private:
    cocos2d::Sprite* MicroMapSprite;    //微缩大地图精灵

    std::vector<cocos2d::DrawNode*> BlackFogLayer;    //绘制黑雾层
    std::vector<cocos2d::Rect> MapReign;    //地图各区域or黑雾层对应区域
    std::vector<std::string> ReignName;    //各区域名称
    std::vector<bool> IsBlackFogVisited;    //是否已经访问过的黑雾层

    cocos2d::Vec2 PlayerPos;    //玩家位置
    cocos2d::Sprite* PlayerSprite;    //玩家精灵

public:

    /*初始化微缩大地图*/
    virtual bool init();
   
    /*进入微缩大地图的初始化操作*/
    void OnEnterMicroMap();

    /*鼠标悬停在区域时触发的事件--解锁传送功能以及显示区域名字*/
    void OnMouseOverReign();

    /*驱散黑雾层*/
    void DisperseBlackFog(int ReignIndex);

    /*解锁区域地图*/
    void UnlockReign(int ReignIndex);

    /*更新微缩大地图*/
    void update(float dt);

   CREATE_FUNC(MicroMap);
};

#endif // __MICRO_MAP_H__