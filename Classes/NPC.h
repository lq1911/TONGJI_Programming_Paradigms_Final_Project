#ifndef __NPC_H__
#define __NPC_H__
#include <vector>
#include <functional>
#include "cocos2d.h"
#include "Player.h"
#include "BagManager.h"

USING_NS_CC;

/* 触发距离 */
const int DIST = 150;

class NPC :public Creature {
private:
	Player* who;   // 玩家
public:
	/* 构造函数 */
	NPC(std::string role, int x, int y, float scale, Scene* scene, Player* player) :Creature(role, 0, 0, 0, 0, 0, 0, 0, x, y, scale, scene) { 
		who = player;
        this->scheduleUpdate();
	}

    /* 玩家靠近:npc提示(换图) */
    inline void triggerTip() { mySprite->setTexture("Role/" + role + "/2.png"); }
    inline void trggerTipRemove(){ mySprite->setTexture("Role/" + role + "/1.png"); }
    void update(float dt = 0.3f);

    
	/* 判断是否在触发范围内 */
	bool isTrigger();

	/* 互动 */
	void Chat();

	/* npc */
	void npc0(std::function<void()> callback);  // 教学用
	void npc1(std::function<void()> callback);
    void npc2(std::function<void()> callback);

	
};




/* npc管理类 */
class NPCManager {
private:
    std::vector<NPC*> npcList;  // 存储所有npc
    Player* player;             // 玩家对象的引用

public:
    /* 构造函数 */
    NPCManager(Player* playerRef) : player(playerRef) {  }

    /* 添加 NPC */
    void addNPC(std::string role, int x, int y, float scale, Scene* scene) {
        NPC* newNpc = new NPC(role, x, y, scale, scene, player);
        npcList.push_back(newNpc);
    }

    /* 移除npc */
    void removeNPC(NPC* npc) {
        npcList.erase(std::remove(npcList.begin(), npcList.end(), npc), npcList.end());
        delete npc; 
    }

    /* 全部npc触发检测 */
    void checkTriggers() {
        for (auto npc : npcList) {
            if (npc->isTrigger()) {
                npc->Chat();
            }
        }
    }

    /* 执行全局更新逻辑（如动画或行为） */
    void updateNPCs(float delta) {
        for (auto npc : npcList) {
            // 例如，可以在这里更新每个NPC的状态
        }
    }

    /* 清理所有 NPC */
    void clearAllNPCs() {
        for (auto npc : npcList) {
            delete npc;
        }
        npcList.clear();
    }
};


#endif __NPC_H__