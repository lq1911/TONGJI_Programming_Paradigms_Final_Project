#include "NPC.h"

USING_NS_CC;

/* 构造函数 */
NPCManager::NPCManager(Player* playerRef, BagManager* bagManager, Scene* scene, int idx) : player(playerRef), bag(bagManager), NPCscene(scene) {
    // 初始化地点待修改
    auto VisibleSize = Director::getInstance()->getVisibleSize();
    switch (idx) {
    // 初始地图
    case(0) :
        // 复活神塔
        addNPC("npc1", 1298.5f, 1354.7, 0.8f);
        addNPC("npc6", 577.0f, 455.8f, 0.6f);
        // 火山
        addNPC("npc2", -1230.8f, 3366.5f, 0.6f);
        // 雪地
        addNPC("npc3", 2880.0f, 2726.9f, 0.6f);
        // 森林
        addNPC("npc4", -1013.5, -395.0f, 0.6f);

        
        break;
    // 室内地图1
    case(1) :
        // 沙漠
        addNPC("npc5", 1357.0f, 871.0f, 0.6f); //室内
       
        break;
    // 室内地图2
    case(2):
        addNPC("npc7", VisibleSize.width / 2 + 500, VisibleSize.height / 2 - 500, 0.6f);
        break;
    // 室内地图3
    case(3):
        addNPC("npc8", VisibleSize.width / 2 , VisibleSize.height / 2, 0.6f);
        break;
    // 室内地图4
    case(4):
        addNPC("npc9", VisibleSize.width / 2+500, VisibleSize.height / 2, 0.6f);
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