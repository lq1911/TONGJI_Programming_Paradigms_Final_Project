#include "BagManager.h"
#include "audio/include/AudioEngine.h"

// µ¥ÀıÊµÀı 
BagManager* BagManager::_instance = nullptr;

// »ñÈ¡µ¥ÀıÊµÀı 
BagManager* BagManager::getInstance()
{
    // Èç¹ûÊµÀı²»´æÔÚ£¬´´½¨Ò»¸öĞÂµÄÊµÀı
    if (_instance == nullptr) 
    {
        _instance = new BagManager();  // ´´½¨ÊµÀı
        _instance->init();  // ³õÊ¼»¯ÊµÀı
    }
    return _instance;  // ·µ»ØÊµÀıÖ¸Õë
}

// ¹¹Ôìº¯Êı
BagManager::BagManager() : _isBagOpen(false), _bagPanel(nullptr)
{
    for (int i = 0; i < 40; i++)
        items[i] = nullptr;
    items_num = 0;
    // ½«ÏÔÊ¾½ğ±ÒÊıÁ¿µÄ±êÇ©ÖÃ¿Õ
    coinsLabel = nullptr;
}

// Îö¹¹º¯Êı
BagManager::~BagManager()
{
    if (_bagPanel) 
        _bagPanel->removeFromParent();
    if (_bagBackground) 
        _bagBackground->release();
    if (_characterBackground)
        _characterBackground->release();
}

// ³õÊ¼»¯±³°ü¹ÜÀíÆ÷
bool BagManager::init()
{
    if (!Node::init()) 
        return false;  // ³õÊ¼»¯Ê§°Ü

    // ´´½¨±³°üÃæ°å£¬×÷Îª±³°üUIµÄÈİÆ÷
    _bagPanel = Node::create();
    this->addChild(_bagPanel);  // ½«±³°üÃæ°åÌí¼Óµ½µ±Ç°½Úµã
    _bagPanel->setVisible(false);  // Ä¬ÈÏÇé¿öÏÂ±³°üÊÇÒş²ØµÄ
    
    return true;  // ³õÊ¼»¯³É¹¦
}

// ÏÔÊ¾±³°ü
void BagManager::showBag(Player& _player)
{
    player = _player;
    player.x = _player.getXY().x;
    player.y = _player.getXY().y;
    // Èç¹û±³°üÉĞÎ´´ò¿ª£¬Ôò´´½¨²¢ÏÔÊ¾±³°ü±³¾°
    if (!_isBagOpen)
    {
        // ÓÎÏ·ÔİÍ£
        //Director::getInstance()->pause();

        // ²¥·Å±³°ü´ò¿ªµÄÒôĞ§
        cocos2d::AudioEngine::play2d("music/bag.mp3");

        // Èç¹û´ò¿ªÁËÈÎÎñÃæ°å£¬¾Í¹Ø±ÕÈÎÎñÃæ°å
        if (_taskBackground)
        {
            _bagPanel->removeAllChildren();
            _taskBackground = nullptr;
        }

        // ´´½¨±³°ü±³¾°
        createBagBackground();

        // ¸üĞÂÎïÆ·À¸ÄÚµÄÎïÆ·
        updateBagUI();

        // ´´½¨½ÇÉ«Ãæ°å
        createCharacterPanel();

        // ´ò¿ªÈÎÎñÃæ°å°´Å¥
        createTaskButton();

        // ²¥·Å±³°ü´ò¿ªµÄÒôĞ§
        cocos2d::AudioEngine::play2d("music/bag.mp3");

        _bagPanel->setVisible(true);  // ÏÔÊ¾±³°üÃæ°å
        _isBagOpen = true;
    }
}

// ÏÔÊ¾±³°ü(ÖØÔØº¯Êı)
void BagManager::showBag()
{
    // Èç¹û±³°üÉĞÎ´´ò¿ª£¬Ôò´´½¨²¢ÏÔÊ¾±³°ü±³¾°
    if (!_isBagOpen)
    {
        // ÓÎÏ·ÔİÍ£
        //Director::getInstance()->pause();

        // Èç¹û´ò¿ªÁËÈÎÎñÃæ°å£¬¾Í¹Ø±ÕÈÎÎñÃæ°å
        if (_taskBackground)
        {
            _bagPanel->removeAllChildren();
            _taskBackground = nullptr;
        }

        // ´´½¨±³°ü±³¾°
        createBagBackground();

        // ¸üĞÂÎïÆ·À¸ÄÚµÄÎïÆ·
        updateBagUI();

        // ´´½¨½ÇÉ«Ãæ°å
        createCharacterPanel();

        // ´ò¿ªÈÎÎñÃæ°å°´Å¥
        createTaskButton();

        _bagPanel->setVisible(true);  // ÏÔÊ¾±³°üÃæ°å
        _isBagOpen = true;
    }
}

// Òş²Ø±³°ü
void BagManager::hideBag(Player& _player)
{
    if (_isBagOpen)
    {
        // »Ö¸´ÓÎÏ·
        //Director::getInstance()->resume();
        // ²¥·Å¹Ø±Õ±³°üµÄÒôĞ§
        cocos2d::AudioEngine::play2d("music/bag.mp3");
        _bagPanel->setVisible(false);  // Òş²Ø±³°üÃæ°å
        _bagPanel->removeAllChildren(); // Çå³ı×Ó½Úµã
        _bagBackground = nullptr;  // Çå³ı±³¾°Ö¸Õë
        _characterBackground = nullptr;
        coinsLabel = nullptr;
        _isBagOpen = false;  // ¸üĞÂ×´Ì¬
        _player = player;
    }
}

// Òş²Ø±³°ü(ÖØÔØº¯Êı)
void BagManager::hideBag()
{
    if (_isBagOpen)
    {
        _bagPanel->setVisible(false);  // Òş²Ø±³°üÃæ°å
        _bagPanel->removeAllChildren(); // Çå³ı×Ó½Úµã
        _bagBackground = nullptr;  // Çå³ı±³¾°Ö¸Õë
        _characterBackground = nullptr;
        coinsLabel = nullptr;
        _isBagOpen = false;  // ¸üĞÂ×´Ì¬
    }
}

// ´´½¨´ò¿ªÈÎÎñÃæ°å°´Å¥
void BagManager::createTaskButton()
{
    // ´´½¨´ò¿ªÈÎÎñÃæ°å°´Å¥
    auto taskButton = Button::create("Button/Button2.png");
    // ½«°´Å¥ÉèÖÃÔÚ±³°üÃæ°å×ó²à
    taskButton->setAnchorPoint(Vec2(0.75, 0));
    taskButton->setPosition(Vec2(0, _bagBackground->getContentSize().height * 3 / 4));
    _bagBackground->addChild(taskButton);
    // Ìí¼ÓÎÄ×Ö
    auto taskLabel = Label::createWithTTF("MY Task", "fonts/arial.ttf", 16);
    taskLabel->setPosition(Vec2(taskButton->getContentSize().width / 2, taskButton->getContentSize().height / 2));
    // ÉèÖÃ×ÖÌåÑÕÉ«Îª½ğÉ« (RGB: 255, 215, 0)
    taskLabel->setTextColor(Color4B(255, 215, 0, 255));
    taskButton->addChild(taskLabel);
    // ÉèÖÃ°´Å¥µã»÷ÊÂ¼ş
    taskButton->addClickEventListener([=](Ref* sender) {
        hideBag();
        createTaskPanel();
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
}

// ´´½¨ÈÎÎñÃæ°å
void BagManager::createTaskPanel()
{
    _bagPanel->setVisible(true);
    // ÓÎÏ·ÔİÍ£
    //Director::getInstance()->pause();
    // ÉèÖÃÈÎÎñÃæ°å±³¾°Í¼Æ¬
    _taskBackground = Sprite::create("Bag/task_background.png");
    _taskBackground->setPosition(Vec2(player.x, player.y));
    _bagPanel->addChild(_taskBackground);

    // ´´½¨±êÌâ
    auto titleLabel = Label::createWithTTF("MY TASK", "fonts/Bebas.ttf", 32);
    titleLabel->setPosition(Vec2(_taskBackground->getContentSize().width / 2, _taskBackground->getContentSize().height - 20));
    // ÉèÖÃ×ÖÌåÑÕÉ«Îª½ğÉ« (RGB: 255, 215, 0)
    titleLabel->setTextColor(Color4B(255, 215, 0, 255));
    _taskBackground->addChild(titleLabel);

    // ´´½¨´ò¿ª±³°üÃæ°å°´Å¥
    auto bagButton = Button::create("Button/Button2.png");
    // ½«°´Å¥ÉèÖÃÔÚ±³°üÃæ°å×ó²à
    bagButton->setAnchorPoint(Vec2(0.75, 0));
    bagButton->setPosition(Vec2(0, _taskBackground->getContentSize().height * 3 / 4));
    _taskBackground->addChild(bagButton);
    // Ìí¼ÓÎÄ×Ö
    auto bagLabel = Label::createWithTTF("MY BAG", "fonts/arial.ttf", 16);
    bagLabel->setPosition(Vec2(bagButton->getContentSize().width / 2, bagButton->getContentSize().height / 2));
    // ÉèÖÃ×ÖÌåÑÕÉ«Îª½ğÉ« (RGB: 255, 215, 0)
    bagLabel->setTextColor(Color4B(255, 215, 0, 255));
    bagButton->addChild(bagLabel);
    // ÉèÖÃ°´Å¥µã»÷ÊÂ¼ş
    bagButton->addClickEventListener([=](Ref* sender) {
        _bagPanel->removeChild(_taskBackground);
        _taskBackground = nullptr;
        showBag();
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
    updateTaskUI();
    
}

// ¸üĞÂÈÎÎñ½çÃæUI
void BagManager::updateTaskUI()
{
    // ÏÔÊ¾Ö§ÏßÈÎÎñ
    // ÉèÖÃ¹öÂÖ
    createScrollView(Vec2(0, 40), myLineQuest);
    // Ìí¼ÓÖ§ÏßÈÎÎñ±êÌâ
    auto sideQuestLabel = Label::createWithTTF("My Side Quest", "fonts/arial.ttf", 16);
    sideQuestLabel->setTextColor(Color4B(255, 215, 0, 255));
    sideQuestLabel->setPosition(Vec2(_taskBackground->getContentSize().width / 2, 180));
    _taskBackground->addChild(sideQuestLabel);

    // ÏÔÊ¾Ö÷ÏßÈÎÎñ
    // ÉèÖÃ¹öÂÖ
    createScrollView(Vec2(0, 220), myMainlineTask);
    // Ìí¼ÓÖ§ÏßÈÎÎñ±êÌâ
    auto mainlineTaskLabel = Label::createWithTTF("My Mainline Task", "fonts/arial.ttf", 16);
    mainlineTaskLabel->setTextColor(Color4B(255, 215, 0, 255));
    mainlineTaskLabel->setPosition(Vec2(_taskBackground->getContentSize().width / 2, 360));
    _taskBackground->addChild(mainlineTaskLabel);
}

// ´´½¨ ScrollView
void BagManager::createScrollView(Vec2 position, vector<task*> myTask)
{
    // ´´½¨ ScrollView
    auto scrollView = ScrollView::create();
    // ÉèÖÃ¹ö¶¯ÇøÓòµÄ´óĞ¡£¬ÏÔÊ¾Á½¸ö°´Å¥
    float scrollHeight = 2 * 50.0f + 30.0f;
    scrollView->setContentSize(Size(_taskBackground->getContentSize().width, scrollHeight));
    scrollView->setPosition(position);  // ÉèÖÃ¹ö¶¯ÇøÓòµÄÎ»ÖÃ
    scrollView->setDirection(ScrollView::Direction::VERTICAL);  // ×İÏò¹ö¶¯
    scrollView->setBounceEnabled(true);  // ÆôÓÃ»Øµ¯Ğ§¹û
    scrollView->setTouchEnabled(true);  // ÆôÓÃ´¥ÃşÊÂ¼ş
    _taskBackground->addChild(scrollView);

    // ´´½¨Ò»¸öÄÚÈİ½Úµã£¨ÈİÄÉËùÓĞ°´Å¥£©
    auto contentNode1 = Node::create();
    scrollView->addChild(contentNode1);

    const int taskCount = 10;  // ×î¶àÓĞ10¸öÈÎÎñ°´Å¥
    float buttonHeight = 50.0f;
    float gap = 20.0f;  // °´Å¥Ö®¼äµÄ¼ä¸ô

    // ´´½¨ÈÎÎñ°´Å¥
    for (int i = 0; i < taskCount; ++i)
    {
        // ´´½¨ÈÎÎñ°´Å¥
        auto taskButton = Button::create("Bag/taskName.png");
        taskButton->setPosition(Vec2(_taskBackground->getContentSize().width / 2, (taskCount - i - 0.5) * (buttonHeight + gap)));
        contentNode1->addChild(taskButton);

        if (i >= myTask.size())
        {
            // Ìí¼ÓÈÎÎñ±êÇ©
            auto taskLabel = Label::createWithTTF("Task " + std::to_string(i + 1), "fonts/arial.ttf", 16);
            taskLabel->setPosition(Vec2(taskButton->getContentSize().width / 2, taskButton->getContentSize().height / 2));
            taskButton->addChild(taskLabel);

            // ÉèÖÃ°´Å¥µã»÷ÊÂ¼ş
            taskButton->addClickEventListener([=](Ref* sender) {
                cocos2d::AudioEngine::play2d("music/lock.mp3");
                });
            // ±íÊ¾ÈÎÎñÎ´½âËø
            auto lock = Button::create("Bag/lock.png");
            lock->setPosition(Vec2(taskButton->getContentSize().width, taskButton->getContentSize().height));
            taskButton->addChild(lock);
        }
        else
        {
            // Ìí¼ÓÈÎÎñ±êÇ©
            auto taskLabel = Label::createWithTTF(myTask[i]->taskName, "fonts/arial.ttf", 12);
            taskLabel->setPosition(Vec2(taskButton->getContentSize().width / 2, taskButton->getContentSize().height / 2));
            taskLabel->setTextColor(Color4B(255, 215, 0, 255));
            taskButton->addChild(taskLabel);
            // ÉèÖÃ°´Å¥µã»÷ÊÂ¼ş
            taskButton->addClickEventListener([=](Ref* sender) {
                createTaskInfoPanel(myTask, i);
                cocos2d::AudioEngine::play2d("music/click.mp3");
                });
        }
    }
    // ÉèÖÃÄÚÈİÇøÓò¸ß¶È£¨ÄÚÈİÇøÓòµÄ×Ü¸ß¶ÈÒª´óÓÚ¹ö¶¯ÇøÓòµÄ¸ß¶È£©
    contentNode1->setContentSize(Size(_taskBackground->getContentSize().width, taskCount * (buttonHeight + gap) + 5));

    // ÉèÖÃ ScrollView ÄÚ²¿ÈİÆ÷µÄ´óĞ¡
    scrollView->setInnerContainerSize(contentNode1->getContentSize());
}

// ´´½¨ÈÎÎñĞÅÏ¢Ãæ°å
void BagManager::createTaskInfoPanel(vector<task*> myTask, int index)
{
    // ´ò¿ªÈÎÎñĞÅÏ¢Ãæ°å
    auto taskInfoBackground = Sprite::create("Bag/task_info_background.png");
    float taskInfoBackground_x = _taskBackground->getPositionX() + _taskBackground->getContentSize().width / 2 + taskInfoBackground->getContentSize().width / 2;
    float taskInfoBackground_y = _taskBackground->getPositionY() + _taskBackground->getContentSize().height / 2 - taskInfoBackground->getContentSize().height / 2;
    taskInfoBackground->setPosition(Vec2(taskInfoBackground_x, taskInfoBackground_y));
    _bagPanel->addChild(taskInfoBackground);

    // ´´½¨²¢ÏÔÊ¾ÈÎÎñÃû×Ö
    auto taskNameLabel = Label::createWithSystemFont(myTask[index]->taskName, "Arial", 24);
    // ÉèÖÃ×ÖÌåÑÕÉ«Îª½ğÉ« (RGB: 255, 215, 0)
    taskNameLabel->setTextColor(Color4B(255, 215, 0, 255));
    taskNameLabel->setPosition(Vec2(taskInfoBackground->getContentSize().width / 2, taskInfoBackground->getContentSize().height - 15));  // ·ÅÖÃÔÚ±³¾°ÉÏ·½
    taskInfoBackground->addChild(taskNameLabel);

    // ´´½¨²¢ÏÔÊ¾ÎïÆ·ÃèÊöµÄ Label
    auto taskDescriptionLabel = Label::createWithSystemFont(myTask[index]->description, "Arial", 16);
    // ÉèÖÃÃªµã
    taskDescriptionLabel->setAnchorPoint(Vec2(0, 1));
    // ÉèÖÃÎÄ±¾×î´ó¿í¶ÈÎªÎïÆ·ĞÅÏ¢±³¾°µÄ¿í¶È£¨¿ÉÒÔÊÊµ±Áô¸ö±ß¾à£©
    float maxWidth = taskInfoBackground->getContentSize().width - 10;  // Áôµã×óÓÒ±ß¾à
    // ÉèÖÃ×î´ó¿í¶ÈºÍ¸ß¶È
    taskDescriptionLabel->setDimensions(maxWidth, 0);
    taskDescriptionLabel->setPosition(Vec2(10, taskInfoBackground->getContentSize().height - 40));  // ·ÅÖÃÔÚ±³¾°ÉÏ·½
    taskInfoBackground->addChild(taskDescriptionLabel);

    // ÏÔÊ¾ÈÎÎñ½ø¶È
    if (myTask[index]->isFinished) // ÈÎÎñÍê³É
    {
        auto taskProgressLabel = Label::createWithSystemFont("Finished", "Arial", 16);
        // ÉèÖÃÃªµã
        taskProgressLabel->setAnchorPoint(Vec2(0, 0.5));
        // ÉèÖÃÎÄ×ÖÑÕÉ«ÎªÂÌÉ«
        taskProgressLabel->setTextColor(Color4B(0, 255, 0, 255));
        taskProgressLabel->setPosition(15, 15);
        taskInfoBackground->addChild(taskProgressLabel);
    }
    else
    {
        auto taskProgressLabel = Label::createWithSystemFont("Going", "Arial", 16);
        // ÉèÖÃÃªµã
        taskProgressLabel->setAnchorPoint(Vec2(0, 0.5));
        // ÉèÖÃÎÄ×ÖÑÕÉ«Îª½ğÉ«
        taskProgressLabel->setTextColor(Color4B(255, 215, 0, 255));
        taskProgressLabel->setPosition(15, 15);
        taskInfoBackground->addChild(taskProgressLabel);
    }

    // ´´½¨¹Ø±Õ°´Å¥£¨¡Á°´Å¥£©
    auto closeButton = Button::create("Bag/close_button.png");
    closeButton->setPosition(Vec2(taskInfoBackground->getContentSize().width, taskInfoBackground->getContentSize().height)); // ÓÒÉÏ½ÇÎ»ÖÃ
    closeButton->addClickEventListener([=](Ref* sender) {
        // µã»÷¡Á°´Å¥Ê±ÒÆ³ı itemInfoBackground
        taskInfoBackground->removeFromParent();  // ´Ó¸¸½ÚµãÒÆ³ı
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
    
    // ½«¹Ø±Õ°´Å¥Ìí¼Óµ½±³¾°ÖĞ
    taskInfoBackground->addChild(closeButton);
}

// ¸üĞÂ±³°üUI
void BagManager::updateBagUI()
{
    // ÉèÖÃÎïÆ·À¸¸ñ×Ó³ß´çºÍ¼ä¸ô
    float xStart = 75.0f;  // ÆğÊ¼XÎ»ÖÃ
    float yStart = _bagBackground->getContentSize().height - 80.0f;  // ÆğÊ¼YÎ»ÖÃ£¨¿¿½ü±³°ü±êÌâÏÂ·½£©

    // ´´½¨5x8µÄÎïÆ·¸ñ×Ó
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 5; ++col)
        {
            // ¼ÆËãÃ¿¸ö¸ñ×ÓµÄ×ø±ê
            float xPos = xStart + col * 80;
            float yPos = yStart - row * 70;
            int index = row * 5 + col;

            // Ìí¼ÓÎïÆ·À¸
            auto slot = Button::create("Bag/item_slot.png");
            slot->setPosition(Vec2(xPos, yPos));
            slot->addClickEventListener([=](Ref* sender) {
                slot_click(slot, row, col);
                });
            _bagBackground->addChild(slot);
            if (items[index] != NULL)
            {
                if (items[index]->image->getParent() == nullptr)// Í¼ÏñÊÇ·ñÓĞ¸¸½Úµã
                {
                    // ÉèÖÃÎïÆ·Í¼ÏñµÄÎ»ÖÃ²¢Ìí¼Óµ½°´Å¥¸ñ×Ó
                    items[index]->image->setPosition(Vec2(slot->getContentSize().width / 2, slot->getContentSize().height / 2));
                    slot->addChild(items[index]->image);// Ìí¼Ó¸¸½Úµã
                    items[index]->image->retain();
                }
                else
                {
                    items[index]->image->removeFromParent();// ÒÆ³ıµ±Ç°µÄ¸¸½Úµã
                    items[index]->image->setPosition(Vec2(slot->getContentSize().width / 2, slot->getContentSize().height / 2));
                    slot->addChild(items[index]->image);
                    items[index]->image->retain();// ±£Ö¤Í¼Ïñ¶ÔÏó²»±»Ïú»Ù
                }
            }
        }
    // ¸üĞÂ½ÇÉ«Ãæ°å
    createCharacterPanel();
}

// ´´½¨±³°ü±³¾°
void BagManager::createBagBackground()
{
    // ÉèÖÃ±³°ü±³¾°Í¼Æ¬
    _bagBackground = Sprite::create("Bag/bag_background.png");
    _bagBackground->setPosition(Vec2(player.x - 200, player.y));
    _bagPanel->addChild(_bagBackground);

    // ´´½¨±³°ü±êÌâ
    auto titleLabel = Label::createWithTTF("MY BAG", "fonts/Bebas.ttf", 32);
    titleLabel->setPosition(Vec2(_bagBackground->getContentSize().width / 2, _bagBackground->getContentSize().height - 20));
    // ÉèÖÃ×ÖÌåÑÕÉ«Îª½ğÉ« (RGB: 255, 215, 0)
    titleLabel->setTextColor(Color4B(255, 215, 0, 255));
    _bagBackground->addChild(titleLabel);

    showcoins();
}

// ÏÔÊ¾½ğ±ÒÊıÁ¿
void BagManager::showcoins()
{
   // ÏÔÊ¾µ±Ç°ÈËÎïµÄ½ğ±ÒÊı
   // Èç¹û½ğ±Ò±êÇ©ÒÑ¾­´æÔÚ£¬¸üĞÂÆäÄÚÈİ£»·ñÔò£¬´´½¨ĞÂµÄ½ğ±Ò±êÇ©
    if (coinsLabel) 
        // ¸üĞÂÏÖÓĞ±êÇ©µÄÄÚÈİ
        coinsLabel->setString(to_string(player.coins));
    else
    {
        // ÉèÖÃ½ğ±ÒÍ¼±ê
        auto coinsIcon = Sprite::create("Bag/coins.png");
        coinsIcon->setPosition(Vec2(_bagBackground->getContentSize().width - 120, 20));
        _bagBackground->addChild(coinsIcon);
        // ´´½¨½ğ±ÒÊıÁ¿±êÇ©
        coinsLabel = Label::createWithTTF(to_string(player.coins), "fonts/arial.ttf", 16);
        // ½«±êÇ©ÉèÖÃÔÚÍ¼ÏñÓÒ²à
        coinsLabel->setAnchorPoint(Vec2(0, 0.5));
        coinsLabel->setPosition(Vec2(_bagBackground->getContentSize().width - 90, 20));
        _bagBackground->addChild(coinsLabel);
    }
}

// ´´½¨½ÇÉ«Ãæ°å
void BagManager::createCharacterPanel()
{
    // »æÖÆ½ÇÉ«Ãæ°åUI
    createCharacterPanelUI();

    // ÏÔÊ¾½ÇÉ«ĞÅÏ¢
    showCharacterInfo();

    // ÔÚ½ÇÉ«Ãæ°åÁ½±ßÌí¼Ó×°±¸À¸
    float borderWidth = _characterBackground->getContentSize().width / 2;
    float borderHeight = _characterBackground->getContentSize().height / 2;
    Vec2 borderPosition = Vec2(borderWidth, borderHeight);
    // ÎäÆ÷
    auto button1 = Button::create("Bag/item_slot.png");// Ìí¼Ó°´Å¥
    button1->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 40, borderPosition.y + borderHeight / 2 - 30));
    button1->addClickEventListener([=](Ref* sender) {
        // µã»÷¸ñ×ÓÒôĞ§
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });// Ìí¼Ó°´Å¥µã»÷ÊÂ¼ş
    _characterBackground->addChild(button1);
    auto label1 = Label::createWithTTF("Weapon", "fonts/arial.ttf", 12);// Ìí¼ÓÎÄ×Ö 
    label1->setPosition(Vec2(20, -6));
    button1->addChild(label1);

    // »ñÈ¡Íæ¼ÒµÄÎäÆ÷Í¼Ïñ²¢ÉèÖÃµ½ÎäÆ÷À¸
    if (player._weapon != nullptr) 
    {
        // »ñÈ¡ÎäÆ÷Í¼Ïñ²¢ÉèÖÃ
        auto weaponImage = player._weapon->image;
        weaponImage->retain(); // ±£Ö¤Í¼Ïñ¶ÔÏó²»±»Ïú»Ù
        weaponImage->removeFromParent(); // ÒÆ³ıµ±Ç°µÄ¸¸½Úµã
        if (weaponImage != nullptr) 
        {
            weaponImage->setPosition(Vec2(button1->getContentSize().width / 2, button1->getContentSize().height / 2));
            button1->addChild(weaponImage);  // ½«Í¼ÏñÌí¼Óµ½ÎäÆ÷À¸°´Å¥ÖĞ
        }
    }

    // Ìí¼Ó¹Ø±Õ°´Å¥£¬Èç¹û×°±¸À¸ÓĞ×°±¸£¬¾ÍĞ¶ÏÂ×°±¸
    auto closeButton1 = Button::create("Bag/close_button.png");
    closeButton1->setPosition(Vec2(button1->getContentSize().width, button1->getContentSize().height)); // ÓÒÉÏ½ÇÎ»ÖÃ
    closeButton1->addClickEventListener([=](Ref* sender) {
        cocos2d::AudioEngine::play2d("music/click.mp3");
        if (player._weapon != nullptr)
        {
            player.atk -= player._weapon->increase_attribute;
            player.criticalChance -= player._weapon->increase_criticalChance;
            auto _item = dynamic_cast<item*>(player._weapon); // ½«ÎäÆ÷ÀàÖ¸Õë×ª»»ÎªÎïÆ·ÀàÖ¸Õë
            player._weapon = nullptr; // ½«½ÇÉ«ÎäÆ÷Ö¸ÕëÖÃÎª¿ÕÖ¸Õë
            addItem(_item); // ½«Ğ¶ÏÂµÄ×°±¸·Å»ØÎïÆ·À¸
        }
        });
    button1->addChild(closeButton1);


    // »¤¼×
    auto button2 = Button::create("Bag/item_slot.png");
    button2->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 40, borderPosition.y - borderHeight / 2 + 30));
    button2->addClickEventListener([=](Ref* sender) {
        // µã»÷¸ñ×ÓÒôĞ§
        cocos2d::AudioEngine::play2d("music/click.mp3"); 
        });
    _characterBackground->addChild(button2);
    auto label2 = Label::createWithTTF("Armor", "fonts/arial.ttf", 12);
    label2->setPosition(Vec2(20, -6));
    button2->addChild(label2);

    // »ñÈ¡Íæ¼ÒµÄ»¤¼×Í¼Ïñ²¢ÉèÖÃµ½»¤¼×À¸
    if (player._armor != nullptr)
    {
        // »ñÈ¡»¤¼×Í¼Ïñ²¢ÉèÖÃ
        auto armorImage = player._armor->image;
        armorImage->retain(); // ±£Ö¤Í¼Ïñ¶ÔÏó²»±»Ïú»Ù
        armorImage->removeFromParent(); // ÒÆ³ıµ±Ç°µÄ¸¸½Úµã
        if (armorImage != nullptr)
        {
            armorImage->setPosition(Vec2(button2->getContentSize().width / 2, button2->getContentSize().height / 2));
            button2->addChild(armorImage);  // ½«Í¼ÏñÌí¼Óµ½»¤¼×À¸°´Å¥ÖĞ
        }
    }

    // Ìí¼Ó¹Ø±Õ°´Å¥£¬Èç¹û×°±¸À¸ÓĞ×°±¸£¬¾ÍĞ¶ÏÂ×°±¸
    auto closeButton2 = Button::create("Bag/close_button.png");
    closeButton2->setPosition(Vec2(button2->getContentSize().width, button2->getContentSize().height)); // ÓÒÉÏ½ÇÎ»ÖÃ
    closeButton2->addClickEventListener([=](Ref* sender) {
        cocos2d::AudioEngine::play2d("music/click.mp3");
        if (player._armor != nullptr)
        {
            player.def -= player._armor->increase_attribute;
            auto _item = dynamic_cast<item*>(player._armor);
            player._armor = nullptr;
            addItem(_item);
        }
        });
    button2->addChild(closeButton2);


    // Ğ¬×Ó
    auto button3 = Button::create("Bag/item_slot.png");
    button3->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 40, borderPosition.y + borderHeight / 2 - 30));
    button3->addClickEventListener([=](Ref* sender) {
        // µã»÷¸ñ×ÓÒôĞ§
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
    _characterBackground->addChild(button3);
    auto label3 = Label::createWithTTF("Shoes", "fonts/arial.ttf", 12);
    label3->setPosition(Vec2(20, -6));
    button3->addChild(label3);

    // »ñÈ¡Íæ¼ÒµÄĞ¬×ÓÍ¼Ïñ²¢ÉèÖÃµ½Ğ¬×ÓÀ¸
    if (player._shoes != nullptr)
    {
        // »ñÈ¡Ğ¬×ÓÍ¼Ïñ²¢ÉèÖÃ
        auto shoesImage = player._shoes->image;
        shoesImage->retain(); // ±£Ö¤Í¼Ïñ¶ÔÏó²»±»Ïú»Ù
        shoesImage->removeFromParent(); // ÒÆ³ıµ±Ç°µÄ¸¸½Úµã
        if (shoesImage != nullptr)
        {
            shoesImage->setPosition(Vec2(button3->getContentSize().width / 2, button3->getContentSize().height / 2));
            button3->addChild(shoesImage);  // ½«Í¼ÏñÌí¼Óµ½Ğ¬×ÓÀ¸°´Å¥ÖĞ
        }
    }

    // Ìí¼Ó¹Ø±Õ°´Å¥£¬Èç¹û×°±¸À¸ÓĞ×°±¸£¬¾ÍĞ¶ÏÂ×°±¸
    auto closeButton3 = Button::create("Bag/close_button.png");
    closeButton3->setPosition(Vec2(0, button3->getContentSize().height)); // ÓÒÉÏ½ÇÎ»ÖÃ
    closeButton3->addClickEventListener([=](Ref* sender) {
        cocos2d::AudioEngine::play2d("music/click.mp3");
        if (player._shoes != nullptr)
        {
            player.speed -= player._shoes->increase_attribute;
            auto _item = dynamic_cast<item*>(player._shoes);
            player._shoes = nullptr;
            addItem(_item);
        }
        });
    button3->addChild(closeButton3);


    // ÊÎÆ·
    auto button4 = Button::create("Bag/item_slot.png");
    button4->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 40, borderPosition.y - borderHeight / 2 + 30));
    button4->addClickEventListener([=](Ref* sender) {
        // µã»÷¸ñ×ÓÒôĞ§
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
    _characterBackground->addChild(button4);
    auto label4 = Label::createWithTTF("Accessories", "fonts/arial.ttf", 12);
    label4->setPosition(Vec2(20, -6));
    button4->addChild(label4);

    // »ñÈ¡Íæ¼ÒµÄÊÎÆ·Í¼Ïñ²¢ÉèÖÃµ½ÊÎÆ·À¸
    if (player._accessories != nullptr)
    {
        // »ñÈ¡ÊÎÆ·Í¼Ïñ²¢ÉèÖÃ
        auto accessoriesImage = player._accessories->image;
        accessoriesImage->retain(); // ±£Ö¤Í¼Ïñ¶ÔÏó²»±»Ïú»Ù
        accessoriesImage->removeFromParent(); // ÒÆ³ıµ±Ç°µÄ¸¸½Úµã
        if (accessoriesImage != nullptr)
        {
            accessoriesImage->setPosition(Vec2(button4->getContentSize().width / 2, button4->getContentSize().height / 2));
            button4->addChild(accessoriesImage);  // ½«Í¼ÏñÌí¼Óµ½ÊÎÆ·À¸°´Å¥ÖĞ
        }
    }

    // Ìí¼Ó¹Ø±Õ°´Å¥£¬Èç¹û×°±¸À¸ÓĞ×°±¸£¬¾ÍĞ¶ÏÂ×°±¸
    auto closeButton4 = Button::create("Bag/close_button.png");
    closeButton4->setPosition(Vec2(0, button4->getContentSize().height)); // ÓÒÉÏ½ÇÎ»ÖÃ
    closeButton4->addClickEventListener([=](Ref* sender) {
        cocos2d::AudioEngine::play2d("music/click.mp3");
        if (player._accessories != nullptr)
        {
            // ½ÇÉ«ÊôĞÔÎª¿Õ
            player.setElementType(NONE);
            auto _item = dynamic_cast<item*>(player._accessories);
            player._accessories = nullptr;
            addItem(_item);
        }
        });
    button4->addChild(closeButton4);
}

// »æÖÆ½ÇÉ«Ãæ°åUI
void BagManager::createCharacterPanelUI()
{
    // ÉèÖÃ½ÇÉ«Ãæ°å±³¾°
    _characterBackground = Sprite::create("Bag/character_background.png");
    float characterBackground_x = _bagBackground->getPositionX() + _bagBackground->getContentSize().width / 2 + _characterBackground->getContentSize().width / 2;
    float characterBackground_y = _bagBackground->getPositionY() + _bagBackground->getContentSize().height / 2 - _characterBackground->getContentSize().height / 2;
    _characterBackground->setPosition(Vec2(characterBackground_x, characterBackground_y));
    _bagPanel->addChild(_characterBackground, -1);

    // ´´½¨½ÇÉ«Ãæ°å±êÌâ
    auto characterTitleLabel = Label::createWithTTF("MY CHARACTER", "fonts/Bebas.ttf", 32);
    characterTitleLabel->setPosition(Vec2(_characterBackground->getContentSize().width / 2, _characterBackground->getContentSize().height - 20));
    // ÉèÖÃ×ÖÌåÑÕÉ«Îª½ğÉ« (RGB: 255, 215, 0)
    characterTitleLabel->setTextColor(Color4B(255, 215, 0, 255));
    _characterBackground->addChild(characterTitleLabel);

    // »æÖÆ±ß¿ò
    float borderWidth = _characterBackground->getContentSize().width / 2;
    float borderHeight = _characterBackground->getContentSize().height / 2;

    Vec2 borderPosition = Vec2(borderWidth, borderHeight);

    auto drawNode = DrawNode::create();
    _characterBackground->addChild(drawNode);

    drawNode->drawRect(
        Vec2(borderPosition.x - borderWidth / 2, borderPosition.y - borderHeight / 2),
        Vec2(borderPosition.x + borderWidth / 2, borderPosition.y + borderHeight / 2),
        Color4F(1.0f, 1.0f, 1.0f, 1.0f)
    );

    // ½«½ÇÉ«Í¼Ïñ·ÅÖÃÔÚ±ß¿òÖĞ
    player.mySprite->setVisible(true); // ÉèÖÃÎª¿É¼û
    player.mySprite->setPosition(Vec2(_characterBackground->getContentSize().width / 2, _characterBackground->getContentSize().height / 2)); // ·ÅÖÃÔÚ±ß¿òÖĞĞÄ
    if (player.mySprite->getParent() != nullptr)
    { // Èç¹ûÓĞ¸¸½Úµã£¬¾ÍÏÈ±£´æ×Ó½Úµã£¬ÔÙ´Ó¸¸½ÚµãÒÆ³ı
        player.mySprite->retain();
        player.mySprite->removeFromParent();
    }
    _characterBackground->addChild(player.mySprite);
}

// ÏÔÊ¾½ÇÉ«ĞÅÏ¢
void BagManager::showCharacterInfo()
{
    //ÏÔÊ¾½ÇÉ«µÄÊôĞÔ¡¢HP¡¢MP
    // ÊôĞÔ
    string PlayerElementType;
    switch (player.elementType)
    {
    case 0:
        PlayerElementType = "None";
        break;
    case 1:
        PlayerElementType = "Fire";
        break;
    case 2:
        PlayerElementType = "Grass";
        break;
    case 3:
        PlayerElementType = "Ice";
        break;
    case 4:
        PlayerElementType = "Rock";
        break;
    }
    string player_elementType = "ElementType: " + PlayerElementType;
    auto elementTypeLabel = Label::createWithTTF(player_elementType, "fonts/arial.ttf", 16);
    // ÉèÖÃÃªµã£¬´Ó×ó±ß¿ªÊ¼
    elementTypeLabel->setAnchorPoint(Vec2(0, 0.5));
    elementTypeLabel->setPosition(Vec2(200, 320));
    _characterBackground->addChild(elementTypeLabel);
    // HP
    string player_HP = "HP: " + to_string(player.current_hp);
    auto characterHP = Label::createWithTTF(player_HP, "fonts/arial.ttf", 16);
    // ÉèÖÃÃªµã£¬´Ó×ó±ß¿ªÊ¼
    characterHP->setAnchorPoint(Vec2(0, 0.5));
    characterHP->setPosition(Vec2(1, 320));
    _characterBackground->addChild(characterHP);
    // µÈ¼¶
    string player_level = "level: " + to_string(player.level);
    auto characterLevel = Label::createWithTTF(player_level, "fonts/arial.ttf", 16);
    // ÉèÖÃÃªµã£¬´Ó×ó±ß¿ªÊ¼
    characterLevel->setAnchorPoint(Vec2(0, 0.5));
    characterLevel->setPosition(Vec2(1, 300));
    _characterBackground->addChild(characterLevel);

    // ÏÔÊ¾½ÇÉ«µÄ¹¥»÷Á¦¡¢·ÀÓùÁ¦¡¢ËÙ¶È
    // ¹¥»÷Á¦
    string player_attack = "Attack: " + to_string(player.atk);
    auto characterAttack = Label::createWithTTF(player_attack, "fonts/arial.ttf", 16);
    // ÉèÖÃÃªµã£¬´Ó×ó±ß¿ªÊ¼
    characterAttack->setAnchorPoint(Vec2(0, 0.5));
    characterAttack->setPosition(Vec2(80, 320));
    _characterBackground->addChild(characterAttack);
    // ·ÀÓùÁ¦
    string player_defense = "Defense: " + to_string(player.def);
    auto characterDefense = Label::createWithTTF(player_defense, "fonts/arial.ttf", 16);
    // ÉèÖÃÃªµã£¬´Ó×ó±ß¿ªÊ¼
    characterDefense->setAnchorPoint(Vec2(0, 0.5));
    characterDefense->setPosition(Vec2(80, 300));
    _characterBackground->addChild(characterDefense);

    // ËÙ¶È
    string player_speed = "Speed: " + to_string(player.speed);
    auto characterSpeed = Label::createWithTTF(player_speed, "fonts/arial.ttf", 16);
    // ÉèÖÃÃªµã£¬´Ó×ó±ß¿ªÊ¼
    characterSpeed->setAnchorPoint(Vec2(0, 0.5));
    characterSpeed->setPosition(Vec2(200, 300));
    _characterBackground->addChild(characterSpeed);
}

// µã»÷ÎïÆ·À¸ÊÂ¼ş
void BagManager::slot_click(Button* slot, int row, int col)
{
    // µã»÷¸ñ×ÓÒôĞ§
    cocos2d::AudioEngine::play2d("music/click.mp3"); 

    // µã»÷¸ñ×ÓÊ±¼ì²éÊÇ·ñÓĞÎïÆ·
    if (items[row * 5 + col] != NULL)
    {
        // ´ò¿ªÎïÆ·ĞÅÏ¢Ãæ°å
        auto itemInfoBackground = Sprite::create("Bag/item_info_background.png");
        float itemInfoBackground_x = slot->getPosition().x + itemInfoBackground->getContentSize().width / 2 + slot->getContentSize().width / 2;
        float itemInfoBackground_y = slot->getPosition().y - itemInfoBackground->getContentSize().height / 2 + slot->getContentSize().height / 2;
        itemInfoBackground->setPosition(Vec2(itemInfoBackground_x, itemInfoBackground_y)); // ½«±³¾°·ÅÖÃÔÚ¸ñ×ÓÅÔ±ß
        _bagBackground->addChild(itemInfoBackground, 10);

        // ´´½¨¹Ø±Õ°´Å¥£¨¡Á°´Å¥£©
        auto closeButton = Button::create("Bag/close_button.png");
        closeButton->setPosition(Vec2(itemInfoBackground->getContentSize().width, itemInfoBackground->getContentSize().height)); // ÓÒÉÏ½ÇÎ»ÖÃ
        closeButton->addClickEventListener([=](Ref* sender) {
            // µã»÷¡Á°´Å¥Ê±ÒÆ³ı itemInfoBackground
            itemInfoBackground->removeFromParent();  // ´Ó¸¸½ÚµãÒÆ³ı
            cocos2d::AudioEngine::play2d("music/click.mp3");
            });

        // ½«¹Ø±Õ°´Å¥Ìí¼Óµ½±³¾°ÖĞ
        itemInfoBackground->addChild(closeButton);

        // »ñÈ¡ÎïÆ·Ãû×Ö
        string itemName = items[row * 5 + col]->getName();
        string itemDescription = items[row * 5 + col]->getDescription();

        // ´´½¨²¢ÏÔÊ¾ÎïÆ·Ãû×ÖµÄ Label
        auto itemNameLabel = Label::createWithSystemFont(itemName, "Arial", 24);
        // ÉèÖÃ×ÖÌåÑÕÉ«Îª½ğÉ« (RGB: 255, 215, 0)
        itemNameLabel->setTextColor(Color4B(255, 215, 0, 255)); // Color4BµÄµÚËÄ¸ö²ÎÊıÊÇÍ¸Ã÷¶È
        itemNameLabel->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 10));  // ·ÅÖÃÔÚ±³¾°ÉÏ·½
        itemInfoBackground->addChild(itemNameLabel);

        // ´´½¨²¢ÏÔÊ¾ÎïÆ·ÃèÊöµÄ Label
        auto itemDescriptionLabel = Label::createWithSystemFont(itemDescription, "Arial", 16);
        // ÉèÖÃÃªµã
        itemDescriptionLabel->setAnchorPoint(Vec2(0, 1));
        // ÉèÖÃÎÄ±¾×î´ó¿í¶ÈÎªÎïÆ·ĞÅÏ¢±³¾°µÄ¿í¶È£¨¿ÉÒÔÊÊµ±Áô¸ö±ß¾à£©
        float maxWidth = itemInfoBackground->getContentSize().width - 10;  // Áôµã×óÓÒ±ß¾à
        // ÉèÖÃ×î´ó¿í¶ÈºÍ¸ß¶È
        itemDescriptionLabel->setDimensions(maxWidth, 0);
        itemDescriptionLabel->setPosition(Vec2(10, itemInfoBackground->getContentSize().height - 30));  // ·ÅÖÃÔÚ±³¾°ÉÏ·½
        itemInfoBackground->addChild(itemDescriptionLabel);

        // ´´½¨Ê¹ÓÃÎïÆ·°´Å¥
        auto useButton = Button::create("Bag/use_button.png");
        useButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 150));
        useButton->addClickEventListener([=](Ref* sender) {
            if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col]))
            {
                // ×°±¸¸ÃÎïÆ·
                if (equipItem(row * 5 + col))
                    itemInfoBackground->removeFromParent();  // ¶ªÆúºó¹Ø±ÕÎïÆ·ĞÅÏ¢Ãæ°å
            }
            else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col]))
            {
                auto consumption=dynamic_cast<consumable*>(items[row * 5 + col]);
                if (player.current_hp + consumption->add_HP <= player.hp)
                    player.current_hp += consumption->add_HP;
                else
                    player.current_hp = player.hp;
                dynamic_cast<item*>(items[row * 5 + col]);
                // ²¥·ÅÒôĞ§
                cocos2d::AudioEngine::play2d("music/eat.mp3");

                // ¶ªÆú¸ÃÎïÆ·
                discardItems(row * 5 + col);
                itemInfoBackground->removeFromParent();  // ¶ªÆúºó¹Ø±ÕÎïÆ·ĞÅÏ¢Ãæ°å
            }
            }); // Ìí¼ÓÊó±êµã»÷ÊÂ¼ş
        itemInfoBackground->addChild(useButton);

        // ¸ù¾İÎïÆ·µÄÀàĞÍÎª°´Å¥Ìí¼Ó²»Í¬µÄÎÄ×Ö
        if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col])) // ÎïÆ·ÊÇ×°±¸Àà
        {
            auto itemEquipLabel = Label::createWithSystemFont("equip", "Arial", 16); // °´Å¥ÉÏÏÔÊ¾µÄÊÇ×°±¸
            itemEquipLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // ÉèÖÃÎ»ÖÃ
            useButton->addChild(itemEquipLabel);
        }
        else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col])) // ÎïÆ·ÊÇÏûºÄÆ·Àà
        {
            auto itemConsumeLabel = Label::createWithSystemFont("consume", "Arial", 16); // °´Å¥ÉÏÏÔÊ¾µÄÊÇÏûºÄ
            itemConsumeLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // ÉèÖÃÎ»ÖÃ
            useButton->addChild(itemConsumeLabel);
        }

        // ´´½¨¶ªÆúÎïÆ·°´Å¥
        auto dicardButton = Button::create("Bag/use_button.png");
        dicardButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 180));
        dicardButton->addClickEventListener([=](Ref* sender) {
            // ¶ªÆú¸ÃÎïÆ·
            discardItems(row * 5 + col);
            cocos2d::AudioEngine::play2d("music/item.mp3");
            itemInfoBackground->removeFromParent();  // ¶ªÆúºó¹Ø±ÕÎïÆ·ĞÅÏ¢Ãæ°å
            }); // Ìí¼ÓÊó±êµã»÷ÊÂ¼ş
        itemInfoBackground->addChild(dicardButton);
        // Îª°´Å¥Ìí¼ÓÎÄ×Ö
        auto itemDiscardLabel = Label::createWithSystemFont("discard", "Arial", 16); // °´Å¥ÉÏÏÔÊ¾µÄÊÇ¶ªÆú
        itemDiscardLabel->setPosition(Vec2(dicardButton->getContentSize().width / 2, dicardButton->getContentSize().height / 2)); // ÉèÖÃÎ»ÖÃ
        dicardButton->addChild(itemDiscardLabel);

        // Éı¼¶×°±¸ÏµÍ³
        // ´´½¨Éı¼¶×°±¸°´Å¥
        equipment* equipmentNeedsUpgraded = nullptr;
        // Ö»ÓĞ×°±¸ÊÇÎäÆ÷Àà¡¢»¤¼×Àà¡¢Ğ¬×ÓÀà²Å¿ÉÒÔÉı¼¶
        if ((equipmentNeedsUpgraded = dynamic_cast<weapon*>(items[row * 5 + col])) != nullptr ||
            (equipmentNeedsUpgraded = dynamic_cast<armor*>(items[row * 5 + col])) != nullptr ||
            (equipmentNeedsUpgraded = dynamic_cast<shoes*>(items[row * 5 + col])) != nullptr)
        {
            // ÉèÖÃ°´Å¥µÄÎ»ÖÃ
            auto upgradeButton = Button::create("Bag/use_button.png");
            upgradeButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 210));
            upgradeButton->addClickEventListener([=](Ref* sender) {
                if (player.coins >= equipmentNeedsUpgraded->equipment_cost && equipmentNeedsUpgraded->equipment_level < equipmentNeedsUpgraded->equipment_levelMax)
                {
                    // ½ÇÉ«½ğ±ÒÊı¼õÉÙ
                    player.coins -= equipmentNeedsUpgraded->equipment_cost;
                    // ¸üĞÂÏÔÊ¾½ğ±ÒÊıÁ¿
                    showcoins();
                    // ÎäÆ÷Éı¼¶£¬Ôö¼ÓÊıÖµºÍÉı¼¶ÏûºÄ
                    equipmentNeedsUpgraded->increase_attribute *= 2;
                    equipmentNeedsUpgraded->equipment_level++;
                    equipmentNeedsUpgraded->equipment_cost *= 2;
                    equipmentNeedsUpgraded->updateDescription();
                    itemInfoBackground->removeFromParent();
                    slot_click(slot, row, col);
                    // ÎäÆ÷Éı¼¶ÒôĞ§
                    cocos2d::AudioEngine::play2d("music/upgrade.mp3");
                }
                else
                    cocos2d::AudioEngine::play2d("music/lock.mp3");
                });
            itemInfoBackground->addChild(upgradeButton);
            // Îª°´Å¥Ìí¼ÓÎÄ×Ö
            auto equipmentUpgraddeLabel = Label::createWithSystemFont("upgrade", "Arial", 16); 
            equipmentUpgraddeLabel->setPosition(Vec2(upgradeButton->getContentSize().width / 2, upgradeButton->getContentSize().height / 2)); // ÉèÖÃÎ»ÖÃ
            upgradeButton->addChild(equipmentUpgraddeLabel);
        }
    }
}

// ½«ÎïÆ·Ìí¼Óµ½±³°ü
void BagManager::addItem(item* it)
{
    if (it == nullptr || it->image == nullptr)
        return; // ÎŞĞ§ÎïÆ·£¬ÍË³öº¯Êı
    if (items_num < 40) // ±³°üÃ»ÓĞÂúÊ±²Å¿ÉÒÔÌí¼ÓÎïÆ·
    {
        int location = 0;
        // ÕÒµ½¿ÕµÄÎïÆ·À¸
        for (int i = 0; i < 40; i++)
            if (items[i] == NULL)
            {
                location = i;
                break;
            }
        items[location] = it; // ¸üĞÂÎïÆ·À¸
        it->image->retain(); // ±£Ö¤ÎïÆ·Í¼ÏñµÄÉúÃüÖÜÆÚ
        if (_isBagOpen)
            updateBagUI();
        items_num++; // ÎïÆ·ÊıÁ¿¼Ó1
        // Ìí¼ÓÎïÆ·ÒôĞ§
        cocos2d::AudioEngine::play2d("music/item.mp3");
    }
    else
        cocos2d::AudioEngine::play2d("music/lock.mp3");
}

// ½«ÎïÆ·´Ó±³°üÖĞ¶ªÆú
void BagManager::discardItems(int index)
{
    // È·±£ÎïÆ·´æÔÚ
    if (items[index] != nullptr)
    {
        // ÒÆ³ıÎïÆ·µÄÍ¼Ïñ£¨´ÓÆä¸¸½ÚµãÒÆ³ı£©
        items[index]->image->removeFromParent();
        // Çå³ıÎïÆ·Êı¾İ
        delete items[index];  // É¾³ıÎïÆ·¶ÔÏó
        items[index] = nullptr; // Çå¿Õ¸ÃÎ»ÖÃ
        // ¸üĞÂÎïÆ·ÊıÁ¿
        items_num--;
        // Èç¹û±³°üUIÒÑ¾­ÏÔÊ¾£¬Ë¢ĞÂUI
        if (_isBagOpen)
            updateBagUI();
    }
}

// ½«±³°üÄÚµÄÎïÆ·×°±¸µ½½ÇÉ«ÉíÉÏ
bool BagManager::equipItem(int index)
{
    bool flag = true;
    if (items[index] != nullptr)
    {
        if (auto weaponItem = dynamic_cast<weapon*>(items[index])) // ÎïÆ·ÊÇÎäÆ÷Àà
        {
            if (player._weapon == nullptr)
            {
                // ¸üĞÂ½ÇÉ«ÎäÆ÷Ö¸Õë
                player._weapon = weaponItem;
                // Ôö¼Ó½ÇÉ«¹¥»÷Á¦
                player.atk += player._weapon->increase_attribute;
                // Ôö¼Ó½ÇÉ«±©»÷ÂÊ
                player.criticalChance += player._weapon->increase_criticalChance;
                // ²»¿ÉÒÔÇå³ıÎïÆ·ĞÅÏ¢
                items[index] = nullptr; // Çå¿Õ¸ÃÎ»ÖÃ
                // ¸üĞÂÎïÆ·ÊıÁ¿
                items_num--;
                // Èç¹û±³°üUIÒÑ¾­ÏÔÊ¾£¬Ë¢ĞÂUI
                if (_isBagOpen)
                    updateBagUI();
            }
            else
            {
                flag = false;
                cocos2d::AudioEngine::play2d("music/lock.mp3");
            }
        }
        else if (auto armorItem = dynamic_cast<armor*>(items[index])) // ÎïÆ·ÊÇ»¤¼×Àà
        {
            if (player._armor == nullptr)
            {
                // ¸üĞÂ½ÇÉ«»¤¼×Ö¸Õë
                player._armor = armorItem;
                // Ôö¼Ó½ÇÉ«µÄ·ÀÓùÖµ
                player.def += player._armor->increase_attribute;
                // ²»¿ÉÒÔÇå³ıÎïÆ·ĞÅÏ¢
                items[index] = nullptr; // Çå¿Õ¸ÃÎ»ÖÃ
                // ¸üĞÂÎïÆ·ÊıÁ¿
                items_num--;
                // Èç¹û±³°üUIÒÑ¾­ÏÔÊ¾£¬Ë¢ĞÂUI
                if (_isBagOpen)
                    updateBagUI();
            }
            else
            {
                flag = false;
                cocos2d::AudioEngine::play2d("music/lock.mp3");
            }
        }
        else if (auto shoesItem = dynamic_cast<shoes*>(items[index])) // ÎïÆ·ÊÇĞ¬×ÓÀà
        {
            if (player._shoes == nullptr)
            {
                // ¸üĞÂ½ÇÉ«Ğ¬×ÓÖ¸Õë
                player._shoes = shoesItem;
                // Ôö¼Ó½ÇÉ«µÄËÙ¶È
                player.speed += player._shoes->increase_attribute;
                // ²»¿ÉÒÔÇå³ıÎïÆ·ĞÅÏ¢
                items[index] = nullptr; // Çå¿Õ¸ÃÎ»ÖÃ
                // ¸üĞÂÎïÆ·ÊıÁ¿
                items_num--;
                // Èç¹û±³°üUIÒÑ¾­ÏÔÊ¾£¬Ë¢ĞÂUI
                if (_isBagOpen)
                    updateBagUI();
            }
            else
            {
                flag = false;
                cocos2d::AudioEngine::play2d("music/lock.mp3");
            }
        }
        else if (auto accessoriesItem = dynamic_cast<accessories*>(items[index])) // ÎïÆ·ÊÇÊÎÆ·Àà
        {
            if (player._accessories == nullptr)
            {
                // ¸üĞÂ½ÇÉ«ÊÎÆ·Ö¸Õë
                player._accessories = accessoriesItem;
                // ¸Ä±ä½ÇÉ«µÄÊôĞÔ
                player.setElementType(player._accessories->setPlayerElementType);
                // ²»¿ÉÒÔÇå³ıÎïÆ·ĞÅÏ¢
                items[index] = nullptr; // Çå¿Õ¸ÃÎ»ÖÃ
                // ¸üĞÂÎïÆ·ÊıÁ¿
                items_num--;
                // Èç¹û±³°üUIÒÑ¾­ÏÔÊ¾£¬Ë¢ĞÂUI
                if (_isBagOpen)
                    updateBagUI();
            }
            else
            {
                flag = false;
                cocos2d::AudioEngine::play2d("music/lock.mp3");
            }
        }
        cocos2d::AudioEngine::play2d("music/equip.mp3");
    }
    return flag;
}


// ½âËøÈÎÎñ(type:1Ö÷Ïß/0Ö§Ïß)
void BagManager::taskUnlock(const bool type, task* newTask){
    if (type)
        myMainlineTask.push_back(newTask);
    else
        myLineQuest.push_back(newTask);

<<<<<<< HEAD
}
=======
}
>>>>>>> 8d552d0 (20241222:ä¿®æ”¹äº†Bagmanagerçš„æŠ¥é”™)
