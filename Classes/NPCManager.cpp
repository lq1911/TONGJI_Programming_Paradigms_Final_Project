#include "NPC.h"

USING_NS_CC;

/* 构造函数 */
NPCManager::NPCManager(Player* playerRef, BagManager* bagManager, Scene* scene, int idx) : player(playerRef), bag(bagManager), NPCscene(scene) {
    // 初始化地点待修改
    auto VisibleSize = Director::getInstance()->getVisibleSize();
    switch (idx) {
    // 初始地图
    case(0) :
        addNPC("npc9", VisibleSize.width / 2 , VisibleSize.height / 2, 0.6f);
        //addNPC("npc1", VisibleSize.width / 2, VisibleSize.height / 2, 0.8f);
        addNPC("npc8", VisibleSize.width / 2 + 500, VisibleSize.height / 2, 0.6f);
        addNPC("npc3", VisibleSize.width / 2 + 500, VisibleSize.height / 2 + 500, 0.6f);
        addNPC("npc4", VisibleSize.width / 2 - 500, VisibleSize.height / 2, 0.6f);
        addNPC("npc5", VisibleSize.width / 2 - 500, VisibleSize.height / 2 - 500, 0.6f);
        break;
    // 室内地图1
    case(1) :
        addNPC("npc6", VisibleSize.width / 2 - 500, VisibleSize.height / 2 + 500, 0.6f);
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