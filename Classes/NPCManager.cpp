#include "NPC.h"

USING_NS_CC;

/* 构造函数 */
NPCManager::NPCManager(Player* playerRef, BagManager* bagManager, Scene* scene, int idx) : player(playerRef), bag(bagManager), NPCscene(scene) {
    auto VisibleSize = Director::getInstance()->getVisibleSize();
    switch (idx) {
    /* 初始地图 */
    case(0) :
        // 复活神塔
        addNPC("npc1", 1298.5f, 1354.7, 0.8f);    // 解锁主线任务
        addNPC("npc6", 577.0f, 455.8f, 0.6f);     // 给食物
        if (TASK[0] == false) {
            npcList[1]->NPCunlockTask(0);         // 解锁支线任务
            TASK[0] = true;
        }
        // 火山
        addNPC("npc2", -538.39, 2933.09, 0.6f);   // 解锁主线任务
        // 雪地
        addNPC("npc3", 2880.0f, 2726.9f, 0.6f);   // 解锁主线任务
        addNPC("npc10", 3656.0f, 3283.0f, 0.6f);  // 钓鱼
        if (TASK[1] == false) {
            npcList[4]->NPCunlockTask(0);         // 解锁支线任务
            TASK[1] = true;
        }
        // 森林
        addNPC("npc8", -1013.5, -395.0f, 0.6f);
        if (TASK[2] == false) {
            npcList[5]->NPCunlockTask(0);         // 解锁支线任务
            TASK[2] = true;
        }
        break;
    /* 沙漠室内1 */
    case(31) :
        addNPC("npc5", 1357.0f, 871.0f, 0.6f);    // 解锁主线任务
        break;
    /* 沙漠室内2 */
    case(32):
        addNPC("npc7", 1357.0f, 871.0f, 0.6f);    // 买武器
        if (TASK[3] == false) {
            npcList[0]->NPCunlockTask(0);         // 解锁支线任务
            TASK[3] = true;
        }
        break;
    /* 森林室内1 */
    case(41):
        addNPC("npc4", 1357.0f, 871.0f, 0.6f);   // 解锁主线任务
        break; 
    /* 森林室内2 */
    case(42):
        addNPC("npc9", 1357.0f, 871.0f, 0.6f);
        break;
    default:
        break;
    }
    
    // 监测npc是否在有效触发范围内
    NPCscene->schedule([=](float dt) {
        for (auto npc : npcList) {
            npc->update();
        }
        }, 0.1f, "npc_check_scheduler");

}

/* 析构函数 */
NPCManager::~NPCManager() {
    clearAllNPCs();
}

/* 添加NPC */
void NPCManager::addNPC(std::string role, int x, int y, float scale) {
    NPC* newNpc = new NPC(role, x, y, scale, NPCscene, player, bag);
    npcList.push_back(newNpc);
}

/* 全部npc触发检测 */
void NPCManager::checkTriggers() {
    for (auto npc : npcList) {
        if (npc->isTrigger()) {
            npc->Chat();
        }
    }
}

/* 检测对话状态 */
bool NPCManager::getChattingStates() {
    for (auto npc : npcList) {
        if (npc->getChattingState())
            return true;
    }
    return false;
}

/* 清理所有NPC */
void NPCManager::clearAllNPCs() {
    for (auto npc : npcList) {
        delete npc;
    }
    npcList.clear();
}