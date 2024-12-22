#ifndef __NPC_H__
#define __NPC_H__
#include <vector>
#include <functional>
#include "cocos2d.h"
#include "Player.h"
#include "BagManager.h"


USING_NS_CC;

/************************ NPC类 ************************/
class NPC :public Creature {
private:
	Player* who;      // 玩家
    BagManager* bag;  // 玩家背包
    bool isChatting = false;  // 是否正在对话
    std::vector<bool> Mtasks = { false,false,false,false,false};  // 主线任务是否已解锁
    task* npc_task;
public:
	/* 构造函数 */
	NPC(std::string role, int x, int y, float scale, Scene* scene, Player* player, BagManager* bagManager) 
        :Creature(role, 0, 0, 0, 0, 0, 0, 0, x, y, scale, scene) {
		who = player;
        bag = bagManager;
        setTasks();
	}

    /* 玩家靠近:npc提示(换图) */
    inline void triggerTip() { mySprite->setTexture("Role/" + role + "/2.png"); }
    inline void trggerTipRemove(){ mySprite->setTexture("Role/" + role + "/1.png"); }
    void update();

	/* 判断是否在触发范围内 */
	bool isTrigger();

    /* 返回对话状态 */
    bool getChattingState() { return isChatting; }
	
    /* 互动 */
	void Chat();

    /* npc对应任务 */
    void setTasks();

    /* 解锁任务 */
    // idx:1主线/0支线
    void NPCunlockTask(bool idx);

    /* 完成任务 */
    void NPCfinishTask();

	/* npc */
    // 教学npc
	void npc0(std::function<void()> callback); 
    // 解锁主线任务npc
	void npc1(std::function<void()> callback);
    void npc2(std::function<void()> callback);
    void npc3(std::function<void()> callback);
    void npc4(std::function<void()> callback);
    void npc5(std::function<void()> callback);
	// 其它npc
    void npc6(std::function<void()> callback);
    void npc7(std::function<void()> callback);
    void npc8(std::function<void()> callback);
    void npc9(std::function<void()> callback);
    void npc10(std::function<void()> callback);
};
/********************** END/NPC类 **********************/


/********************** NPC管理类 **********************/
class NPCManager {
private:
    std::vector<NPC*> npcList;  // 存储所有npc
    Player* player;             // 玩家对象的引用
    BagManager* bag;            // 玩家背包
    Scene* NPCscene;
public:
    /* 构造函数 */
    //idx:场景
    NPCManager(Player* playerRef, BagManager* bagManager, Scene* scene, int idx);

    /* 析构函数 */
    ~NPCManager();

    /* 访问npc */
    vector<NPC*> visitNPC() { return npcList; }

    /* 添加npc */
    void addNPC(std::string role, int x, int y, float scale);

    /* 全部npc触发检测 */
    void checkTriggers();

    /* 检测对话状态 */
    bool getChattingStates();
   
    /* 清理所有NPC */
    void clearAllNPCs();

};
/******************** END/NPC管理类 ********************/

#endif __NPC_H__