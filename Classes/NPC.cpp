#include <iostream>
#include "NPC.h"

/* 交互提示 */
void NPC::update() {
	if (isTrigger()) {
		triggerTip();  // 玩家进入触发范围
	}
	else {
		trggerTipRemove();   // 玩家离开触发范围
	}
}

/* 判断是否在触发范围内 */
bool NPC::isTrigger() {
	if (who == nullptr)
		return false;

	int dx = who->mySprite->getPosition().x - x;
	int dy = who->mySprite->getPosition().y - y;

	return std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(DIST, 2);
}

/* 与NPC交互 */
void NPC::Chat() {
	/* 判断是否在触发范围内 */
	if (!this->isTrigger())
		return;

    /* 加入对话框chatPanel */
    auto winSize = Director::getInstance()->getWinSize();
	Vec2 where = Vec2(who->getXY().x , who->getXY().y- 180);
	if (role == "npc0")
		where = Vec2(winSize.width / 2, winSize.height - 1100);
    auto chatPanel = Sprite::create("UI/Panel5.png");

    chatPanel->setContentSize(Size(1800, 350));
    chatPanel->setPosition(where); 
	chatPanel->setOpacity(220);
    scene->addChild(chatPanel, 2);

	/* 加入npc */
	auto npcSprite = Sprite::create("Role/" + role + "/1.png");
	npcSprite->setPosition(Vec2(who->getXY().x - 430, who->getXY().y - 140));

	if (role == "npc0")
		npcSprite->setPosition(Vec2(winSize.width / 2 - 430, winSize.height - 1000));
	npcSprite->setScale(1.5f);
	scene->addChild(npcSprite, 3);

	/* 根据npc创建互动 */
	std::unordered_map<std::string, int> stringMap = {
		{"npc0", 0},
		{"npc1", 1},
		{"npc2", 2},
		{"npc3", 3},
		{"npc4", 4},
		{"npc5", 5},
		{"npc6", 6},
		{"npc7", 7},
		{"npc8", 8},
		{"npc9", 9},
		{"npc10", 10}
	};

	switch (stringMap[role]) {
	/* 教学npc */
	case 0:
		npc0([=]() {
			// 当npc0的对话逻辑完成后，移除UI
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	/* 解锁主线任务的npc */
	case 1:
		npc1([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	case 2:
		npc2([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	case 3:
		npc3([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	case 4:
		npc4([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	case 5:
		npc5([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	/* 其它npc */
	case 6:
		npc6([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	case 7:
		npc7([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	case 8:
		npc8([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	case 9:
		npc9([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	case 10:
		npc9([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			});
		break;
	default:
		break;
	}
}

/* npc对应任务 */
void NPC::setTasks() {
	/*************** 主线任务 ***************/
	// 复活神庙
	if (role == "npc1") {
		npc_task = new task("Revival Temple", "The Tower of Rebirth has chosen to resurrect you, a brave soul, to take on the task of defeating the monsters and saving this world.", 1, 0);
	}
	// 火山
	else if (role == "npc2") {
		npc_task = new task("Rift of the Firebound", "Defeati the monsters and restore peace to this place.", 1, 0);
	}
	// 雪地
	else if (role == "npc3") {
		npc_task = new task("Glacier of Silence", "Defeat the monster and bring hope back to this desolate land.", 1, 0);
	}
	// 森林
	else if (role == "npc4") {
		npc_task= new task("Realm of Verdant Woods", "Help defeat the monster that have taken over this place.", 1, 0);
	}
	// 沙漠
	else if (role == "npc5") {
		npc_task = new task("Crimson Wasteland", "Your mission is to traverse this blazing desert, defeat the lurking monsters, and bring life back to this land.", 1, 0);
	}
	/*************** 支线任务 ***************/
	// 给食物
	else if (role == "npc6") {
		npc_task = new task("GET FOOD", "Go to the Revival Temple and find Evan, chat with him and get something to eat.", 0, 0);
	}
	// 买东西
	else if (role == "npc7") {
		npc_task = new task("SHOPPING", "Go to the Crimson Wasteland and find Celeste, buy some equipment from her.", 0, 0);
	}
	else if (role == "npc8") {
		npc_task = new task("LTask 3", "This is the 3rd task.", 0, 0);
	}
	else if (role == "npc9") {
		npc_task = new task("LTask 4", "This is the 4th task.", 0, 0);
	}
	else if (role == "npc9") {
		npc_task = new task("LTask 4", "This is the 4th task.", 0, 0);
	}
}

/* NPC解锁任务 */
void NPC::NPCunlockTask(bool idx) {
	if (idx) {
		bag->taskUnlock(1, npc_task);
	}
	else {
		bag->taskUnlock(0, npc_task);
	}
}

/* NPC完成任务 */
void NPC::NPCfinishTask() {
	npc_task->isFinished = true;
}

/* npc对话逻辑 */
/************ 教学npc ************/
void NPC::npc0(std::function<void()> callback) {
	auto winSize = Director::getInstance()->getWinSize();
	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Hello! Welcome to this new world!", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1000));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 4);

	/* player回答选择1 */
	auto playerAns1 = Label::createWithTTF("Nice to meet you!", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 4);
	/* player回答选择2 */
	auto playerAns2 = Label::createWithTTF("I like this world.", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1160));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 4);

	/* player回答选择1提交按钮 */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1080));
	scene->addChild(Ans1Button, 4);
	/* player回答选择2提交按钮 */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1160));
	scene->addChild(Ans2Button, 4);

	/* 回答选择1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		// 移除第一次问答的元素
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("Nice to meet you too!", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* 回答选择2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("Enjoy yourself here!", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_2->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});
		});
}

/******** 解锁主线任务npc ********/
void NPC::npc1(std::function<void()> callback) {
	isChatting = true;

	/* npc说话 */
	auto npcTxt1 = Label::createWithTTF("You have been resurrected! This is the site of a once-glorious\ncivilization, home to the Tower of Rebirth, which bridges\nthe boundary between life and death. Only the bravest\nsouls are granted the chance of resurrection.", "fonts/Lacquer.ttf", 25);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);
	/* NextButton1 */
	auto NextButton1 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton1->ignoreContentAdaptWithSize(false);
	NextButton1->setContentSize(Size(40, 40));
	NextButton1->setPosition(Vec2(who->getXY().x, who->getXY().y - 250));
	NextButton1->setOpacity(220);
	scene->addChild(NextButton1, 2);
	/* NextButton1监听 */
	NextButton1->addClickEventListener([=](Ref* sender)mutable {
		npcTxt1->setString("After monsters took over this world, most people were killed.\n The Tower of Rebirth has chosen to resurrect you,\na brave soul,to take on the task of defeating the\nmonsters and saving this world.");
		NextButton1->removeFromParent();
		NextButton1 = nullptr;
		/* NextButton2 */
		auto NextButton2 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
		NextButton2->ignoreContentAdaptWithSize(false);
		NextButton2->setContentSize(Size(40, 40));
		NextButton2->setPosition(Vec2(who->getXY().x, who->getXY().y - 250));
		NextButton2->setOpacity(220);
		scene->addChild(NextButton2, 2);
		/* NextButton2监听 */
		NextButton2->addClickEventListener([=](Ref* sender)mutable {
			NextButton2->removeFromParent();
			NextButton2 = nullptr;
			/* 解锁任务 **************************************************************/
			if (!Mtasks[0]) {
				Mtasks[0] = true;
				if (bag) {
					NPCunlockTask(1);
				}
				// 对话
				npcTxt1->setString("It's time to overcome the monster.\nClose the chat window and checkout your task!");
			}
			else {
				npcTxt1->setString("Have you overcome the monster?\nClose the chat window and checkout your task!");
			}
			// 下一步:结束对话
			auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
			CloseButton->ignoreContentAdaptWithSize(false);
			CloseButton->setContentSize(Size(40, 40));
			CloseButton->setTitleFontSize(24);
			CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));
			scene->addChild(CloseButton, 4);
			CloseButton->addClickEventListener([=](Ref* sender) mutable {
				npcTxt1->removeFromParent();
				npcTxt1 = nullptr;
				CloseButton->removeFromParent();
				isChatting = false;
				if (callback) {
					callback();
				}
				return;
				});
			});
		});	
}

void NPC::npc2(std::function<void()> callback) {
	isChatting = true;

	/* npc说话 */
	auto npcTxt1 = Label::createWithTTF("This is the Rift of the Firebound. A thousand years ago,\nit was thesacred land of the Fire Giants,who carved the \nunderground magma into temples to protect this land.", "fonts/Lacquer.ttf", 25);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);
	/* NextButton1 */
	auto NextButton1 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton1->ignoreContentAdaptWithSize(false);
	NextButton1->setContentSize(Size(40, 40));
	NextButton1->setPosition(Vec2(who->getXY().x, who->getXY().y - 240));
	NextButton1->setOpacity(220);
	scene->addChild(NextButton1, 2);
	/* NextButton1监听 */
	NextButton1->addClickEventListener([=](Ref* sender)mutable {
		npcTxt1->setString(" Now, the land has become extremely dangerous,overrun by\nmonsters. Only by defeating the monsters can the unrest \nbe quelled and peace restored to this place.");
		NextButton1->removeFromParent();
		NextButton1 = nullptr;
		/* NextButton2 */
		auto NextButton2 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
		NextButton2->ignoreContentAdaptWithSize(false);
		NextButton2->setContentSize(Size(40, 40));
		NextButton2->setPosition(Vec2(who->getXY().x, who->getXY().y - 240));
		NextButton2->setOpacity(220);
		scene->addChild(NextButton2, 2);
		/* NextButton2监听 */
		NextButton2->addClickEventListener([=](Ref* sender)mutable {
			NextButton2->removeFromParent();
			NextButton2 = nullptr;
			/* 解锁任务 **************************************************************/
			if (!Mtasks[1]) {
				Mtasks[1] = true;
				if (bag) {
					NPCunlockTask(1);
				}
				// 对话
				npcTxt1->setString("It's time to overcome the monster.\nClose the chat window and checkout your task!");
			}
			else {
				npcTxt1->setString("Have you overcome the monster?\nClose the chat window and checkout your task!");
			}
			// 下一步:结束对话
			auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
			CloseButton->ignoreContentAdaptWithSize(false);
			CloseButton->setContentSize(Size(40, 40));
			CloseButton->setTitleFontSize(24);
			CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));
			scene->addChild(CloseButton, 4);
			CloseButton->addClickEventListener([=](Ref* sender) mutable {
				npcTxt1->removeFromParent();
				npcTxt1 = nullptr;
				CloseButton->removeFromParent();
				isChatting = false;
				if (callback) {
					callback();
				}
				return;
				});
			});
		});
}

void NPC::npc3(std::function<void()> callback) {
	isChatting = true;

	/* npc说话 */
	auto npcTxt1 = Label::createWithTTF("The Glacier of Silence is a wasteland frozen in eternal\nwinter, where icy winds cut through the air like blades.\nA thousand years ago, this was a prosperous kingdom.", "fonts/Lacquer.ttf", 25);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);
	/* NextButton1 */
	auto NextButton1 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton1->ignoreContentAdaptWithSize(false);
	NextButton1->setContentSize(Size(40, 40));
	NextButton1->setPosition(Vec2(who->getXY().x, who->getXY().y - 250));
	NextButton1->setOpacity(220);
	scene->addChild(NextButton1, 2);
	/* NextButton1监听 */
	NextButton1->addClickEventListener([=](Ref* sender)mutable {
		npcTxt1->setString("But a monster came, turning this snowy land into a realm\nfull of hidden dangers. Brave warrior, your mission is to\ndefeat the monster and bring hope back to this desolate land.");
		NextButton1->removeFromParent();
		NextButton1 = nullptr;
		/* NextButton2 */
		auto NextButton2 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
		NextButton2->ignoreContentAdaptWithSize(false);
		NextButton2->setContentSize(Size(40, 40));
		NextButton2->setPosition(Vec2(who->getXY().x, who->getXY().y - 250));
		NextButton2->setOpacity(220);
		scene->addChild(NextButton2, 2);
		/* NextButton2监听 */
		NextButton2->addClickEventListener([=](Ref* sender)mutable {
			NextButton2->removeFromParent();
			NextButton2 = nullptr;
			/* 解锁任务 **************************************************************/
			if (!Mtasks[2]) {
				Mtasks[2] = true;
				if (bag) {
					NPCunlockTask(1);
				}
				// 对话
				npcTxt1->setString("It's time to overcome the monster.\nClose the chat window and checkout your task!");
			}
			else {
				npcTxt1->setString("Have you overcome the monster?\nClose the chat window and checkout your task!");
			}
			// 下一步:结束对话
			auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
			CloseButton->ignoreContentAdaptWithSize(false);
			CloseButton->setContentSize(Size(40, 40));
			CloseButton->setTitleFontSize(24);
			CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));
			scene->addChild(CloseButton, 4);
			CloseButton->addClickEventListener([=](Ref* sender) mutable {
				npcTxt1->removeFromParent();
				npcTxt1 = nullptr;
				CloseButton->removeFromParent();
				isChatting = false;
				if (callback) {
					callback();
				}
				return;
				});
			});
		});
}

void NPC::npc4(std::function<void()> callback) {
	isChatting = true;

	/* npc说话 */
	auto npcTxt1 = Label::createWithTTF("The Realm of Verdant Woods is an ancient forest filled\nwith vitality and light, with each tree carrying\nblessings from ancient times, whispering peace and wisdom.", "fonts/Lacquer.ttf", 25);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);
	/* NextButton1 */
	auto NextButton1 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton1->ignoreContentAdaptWithSize(false);
	NextButton1->setContentSize(Size(40, 40));
	NextButton1->setPosition(Vec2(who->getXY().x, who->getXY().y - 250));
	NextButton1->setOpacity(220);
	scene->addChild(NextButton1, 2);
	/* NextButton1监听 */
	NextButton1->addClickEventListener([=](Ref* sender)mutable {
		npcTxt1->setPosition(Vec2(who->getXY().x + 50, who->getXY().y - 160));
		npcTxt1->setString("However, ever since it was taken over by monsters,\neverything has changed, and the forest is no longer\nserene. Brave warrior,we implore you to help us\ndefeat the monsters that have stolen our home!");
		NextButton1->removeFromParent();
		NextButton1 = nullptr;
		/* NextButton2 */
		auto NextButton2 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
		NextButton2->ignoreContentAdaptWithSize(false);
		NextButton2->setContentSize(Size(40, 40));
		NextButton2->setPosition(Vec2(who->getXY().x, who->getXY().y - 250));
		NextButton2->setOpacity(220);
		scene->addChild(NextButton2, 2);
		/* NextButton2监听 */
		NextButton2->addClickEventListener([=](Ref* sender)mutable {
			NextButton2->removeFromParent();
			NextButton2 = nullptr;
			/* 解锁任务 **************************************************************/
			if (!Mtasks[3]) {
				Mtasks[3] = true;
				if (bag) {
					NPCunlockTask(1);
				}
				// 对话
				npcTxt1->setString("It's time to overcome the monster.\nClose the chat window and checkout your task!");
			}
			else {
				npcTxt1->setString("Have you overcome the monster?\nClose the chat window and checkout your task!");
			}
			// 下一步:结束对话
			auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
			CloseButton->ignoreContentAdaptWithSize(false);
			CloseButton->setContentSize(Size(40, 40));
			CloseButton->setTitleFontSize(24);
			CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));
			scene->addChild(CloseButton, 4);
			CloseButton->addClickEventListener([=](Ref* sender) mutable {
				npcTxt1->removeFromParent();
				npcTxt1 = nullptr;
				CloseButton->removeFromParent();
				isChatting = false;
				if (callback) {
					callback();
				}
				return;
				});
			});
		});
}

void NPC::npc5(std::function<void()> callback) {
	isChatting = true;

	/* npc说话 */
	auto npcTxt1 = Label::createWithTTF("The Crimson Wasteland is an endless sea of scorching sands under\nthe blazing sun, once a land of prosperity. However, monsters\nsuddenly attacked, wiping out all life and turning it\ninto a barren, desolate land.", "fonts/Lacquer.ttf", 25);
	npcTxt1->setPosition(Vec2(who->getXY().x+20, who->getXY().y - 160));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);
	/* NextButton1 */
	auto NextButton1 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton1->ignoreContentAdaptWithSize(false);
	NextButton1->setContentSize(Size(40, 40));
	NextButton1->setPosition(Vec2(who->getXY().x, who->getXY().y - 250));
	NextButton1->setOpacity(220);
	scene->addChild(NextButton1, 2);
	/* NextButton1监听 */
	NextButton1->addClickEventListener([=](Ref* sender)mutable {
		npcTxt1->setPosition(Vec2(who->getXY().x+30, who->getXY().y - 160));
		npcTxt1->setString("These monsters have made the desert their lair, devouring any\nlife that dares to enter. Your mission is to traverse this blazing\ndesert, defeat the lurking monsters, and bring life back to this land.");
		NextButton1->removeFromParent();
		NextButton1 = nullptr;
		/* NextButton2 */
		auto NextButton2 = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
		NextButton2->ignoreContentAdaptWithSize(false);
		NextButton2->setContentSize(Size(40, 40));
		NextButton2->setPosition(Vec2(who->getXY().x, who->getXY().y - 250));
		NextButton2->setOpacity(220);
		scene->addChild(NextButton2, 2);
		/* NextButton2监听 */
		NextButton2->addClickEventListener([=](Ref* sender)mutable {
			NextButton2->removeFromParent();
			NextButton2 = nullptr;
			/* 解锁任务 **************************************************************/
			if (!Mtasks[4]) {
				Mtasks[4] = true;
				if (bag) {
					NPCunlockTask(1);
				}
				// 对话
				npcTxt1->setString("It's time to overcome the monster.\nClose the chat window and checkout your task!");
			}
			else {
				npcTxt1->setString("Have you overcome the monster?\nClose the chat window and checkout your task!");
			}
			// 下一步:结束对话
			auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
			CloseButton->ignoreContentAdaptWithSize(false);
			CloseButton->setContentSize(Size(40, 40));
			CloseButton->setTitleFontSize(24);
			CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));
			scene->addChild(CloseButton, 4);
			CloseButton->addClickEventListener([=](Ref* sender) mutable {
				npcTxt1->removeFromParent();
				npcTxt1 = nullptr;
				CloseButton->removeFromParent();
				isChatting = false;
				if (callback) {
					callback();
				}
				return;
				});
			});
		});
}

/************ 其它npc ************/
// 给食物
void NPC::npc6(std::function<void()> callback) {
	isChatting = true; // 更新chatting状态
	
	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Hello, I am Evan. Do you want to eat something?", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 110));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* player回答选择1 */
	auto playerAns1 = Label::createWithTTF("Sure! Could you give me an apple?", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(who->getXY().x, who->getXY().y - 170));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 2);
	/* player回答选择2 */
	auto playerAns2 = Label::createWithTTF("Yes! I'd like something to drink.", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 2);

	/* player回答选择1提交按钮 */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 170));
	scene->addChild(Ans1Button, 2);
	/* player回答选择2提交按钮 */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 230));
	scene->addChild(Ans2Button, 2);

	/* 回答选择1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		// 修改任务状态
		if (npc_task->isFinished == false) {
			npc_task->isFinished = true;
		}
		// 背包加苹果
		goods _goods;
		consumable* it = new consumable(_goods.apple);
		bag->addItem(it);
		// 移除第一次问答的元素
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("No problem. Here you are!\nPlease open your bag and check it.", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 2);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(50, 50));
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 190));
		scene->addChild(CloseButton, 2);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			isChatting = false;   // 更新chatting状态
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* 回答选择2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		// 修改任务状态
		if (npc_task->isFinished == false) {
			npc_task->isFinished = true;
		}
		// 背包加啤酒
		goods _goods;
		consumable* it = new consumable(_goods.beer);
		bag->addItem(it);
		// 移除UI组件
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("Then let me give you a cup of beer.\nPlease open your bag and check it!", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 2);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			isChatting = false;
			npcTxt2_2->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});
		});
}

// 买东西
void NPC::npc7(std::function<void()> callback) {
	isChatting = true;
	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Hello, I am Celeste. What do you want to buy?", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 110));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* player回答选择1 */ 
	auto playerAns1 = Label::createWithTTF("I want to buy some weapons.", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(who->getXY().x, who->getXY().y - 170));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 2);
	/* player回答选择2 */
	auto playerAns2 = Label::createWithTTF("Sorry, I don't want to buy anything.", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 2);

	/* player回答选择1提交按钮 */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(who->getXY().x - 270, who->getXY().y - 170));
	scene->addChild(Ans1Button, 2);
	/* player回答选择2提交按钮 */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(who->getXY().x - 270, who->getXY().y - 230));
	scene->addChild(Ans2Button, 2);

	/* 回答选择1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		npc_task->isFinished = true;
		// 移除第一次问答的元素
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();

		/* npc说话-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("Choose one!", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(who->getXY().x, who->getXY().y - 110));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 2);

		/* player回答选择3 */
		auto playerAns3 = Label::createWithTTF("Icon Sword : Attack+10 [price:100coins]", "fonts/KuaiLe_Chinese.ttf", 25);
		playerAns3->setPosition(Vec2(who->getXY().x, who->getXY().y - 170));
		playerAns3->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(playerAns3, 2);
		/* player回答选择4 */
		auto playerAns4 = Label::createWithTTF("Long Sword : Attack+30 [price:200coins]", "fonts/KuaiLe_Chinese.ttf", 25);
		playerAns4->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));
		playerAns4->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(playerAns4, 2);

		/* player回答选择3提交按钮 */
		auto Ans3Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
		Ans3Button->ignoreContentAdaptWithSize(false);
		Ans3Button->setContentSize(Size(40, 40));
		Ans3Button->setTitleFontSize(24);
		Ans3Button->setPosition(Vec2(who->getXY().x - 300, who->getXY().y - 170));
		scene->addChild(Ans3Button, 2);
		/* player回答选择4提交按钮 */
		auto Ans4Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
		Ans4Button->ignoreContentAdaptWithSize(false);
		Ans4Button->setContentSize(Size(40, 40));
		Ans4Button->setTitleFontSize(24);
		Ans4Button->setPosition(Vec2(who->getXY().x - 300, who->getXY().y - 230));
		scene->addChild(Ans4Button, 2);
		/* 回答选择3提交按钮监控 */
		Ans3Button->addClickEventListener([=](Ref* sender) mutable {
			playerAns3->removeFromParent();
			playerAns4->removeFromParent();
			Ans3Button->removeFromParent();
			Ans4Button->removeFromParent();
			/* 修改任务状态 */
			if (npc_task->isFinished == false) {
				npc_task->isFinished = true;
			}
			/* 消耗金币,加武器 */
			if (who->coins >= 100) {
				who->coins -= 100;
				goods _goods;
				weapon* it = new weapon(_goods.iron_sword);
				bag->addItem(it);
				npcTxt2_1->setString("OK!");  // npc说话
			}
			else {
				npcTxt2_1->setString("Sorry, you don't have enough money!"); // npc说话
			}
			npcTxt2_1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
			/* 结束对话 */
			auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
			CloseButton->ignoreContentAdaptWithSize(false);
			CloseButton->setContentSize(Size(40, 40));
			CloseButton->setTitleFontSize(24);
			CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));
			scene->addChild(CloseButton, 2);
			CloseButton->addClickEventListener([=](Ref* sender) mutable {
				isChatting = false;
				npcTxt2_1->removeFromParent();
				CloseButton->removeFromParent();
				if (callback) {
					callback();
				}
				return;
				});
			});
		/* 回答选择4提交按钮监控 */
		Ans4Button->addClickEventListener([=](Ref* sender) mutable {
			playerAns3->removeFromParent();
			playerAns4->removeFromParent();
			Ans3Button->removeFromParent();
			Ans4Button->removeFromParent();
			/* 修改任务状态 */
			if (npc_task->isFinished == false) {
				npc_task->isFinished = true;
			}
			/* 消耗金币,加武器 */
			if (who->coins >= 200) {
				who->coins -= 200;
				goods _goods;
				weapon* it = new weapon(_goods.long_sword);
				bag->addItem(it);
				npcTxt2_1->setString("OK!");   // npc说话
			}
			else {
				npcTxt2_1->setString("Sorry, you don't have enough coins!");   // npc说话
			}
			npcTxt2_1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
			/* 结束对话 */
			auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
			CloseButton->ignoreContentAdaptWithSize(false);
			CloseButton->setContentSize(Size(40, 40));
			CloseButton->setTitleFontSize(24);
			CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 260));
			scene->addChild(CloseButton, 2);
			CloseButton->addClickEventListener([=](Ref* sender) mutable {
				isChatting = false;
				npcTxt2_1->removeFromParent();
				CloseButton->removeFromParent();
				if (callback) {
					callback();
				}
				return;
				});
			});

		});
	/* 回答选择2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("See you next time!", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 2);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			isChatting = false;
			npcTxt2_2->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
}

void NPC::npc8(std::function<void()> callback) {
	isChatting = true;
	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("This is npc6 speaking 1", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 110));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* player回答选择1 */
	auto playerAns1 = Label::createWithTTF("This is player's answer 1", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 2);
	/* player回答选择2 */
	auto playerAns2 = Label::createWithTTF("This is player's answer 2", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(who->getXY().x, who->getXY().y - 220));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 2);

	/* player回答选择1提交按钮 */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 160));
	scene->addChild(Ans1Button, 2);
	/* player回答选择2提交按钮 */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 220));
	scene->addChild(Ans2Button, 2);

	/* 回答选择1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		// 移除第一次问答的元素
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("This is npc6 speaking 2-1", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 2);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			isChatting = false;
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* 回答选择2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		isChatting = false;
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("This is npc6 speaking 2-2", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 2);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_2->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
}

void NPC::npc10(std::function<void()> callback) {
	isChatting = true;

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Taskkkkkk 5", "fonts/Lacquer.ttf", 30);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));///////////
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* NextButton */
	auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton->ignoreContentAdaptWithSize(false);
	NextButton->setContentSize(Size(60, 60));
	NextButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
	NextButton->setOpacity(220);
	scene->addChild(NextButton, 2);
	/* NextButton监听 */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// 解锁任务
		NextButton->removeFromParent();
		NextButton = nullptr;
		npcTxt1->setString("hahaha");
		
		// 下一步:结束对话
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			CloseButton->removeFromParent();
			isChatting = false;
			if (callback) {
				callback();
			}
			return;
			});
		});
}

void NPC::npc9(std::function<void()> callback) {
	isChatting = true;

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Taskkkkkk 5", "fonts/Lacquer.ttf", 30);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));///////////
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* NextButton */
	auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton->ignoreContentAdaptWithSize(false);
	NextButton->setContentSize(Size(60, 60));
	NextButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
	NextButton->setOpacity(220);
	scene->addChild(NextButton, 2);
	/* NextButton监听 */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// 解锁任务
		NextButton->removeFromParent();
		NextButton = nullptr;
		npcTxt1->setString("hahaha");

		// 下一步:结束对话
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			CloseButton->removeFromParent();
			isChatting = false;
			if (callback) {
				callback();
			}
			return;
			});
		});
}