#include "EventManager.h"

void EventManager::AddKeyBoardListener(Node* TargetNode,
	function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyPressed,
	function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyReleased) {

	if (!TargetNode)
		return;    //如果目标节点或者监听器为空，则直接返回

	//创建键盘监听器
	auto Listener = EventListenerKeyboard::create();

	//设置监听器的回调函数
	Listener->onKeyPressed = OperationWhenKeyPressed;
	Listener->onKeyReleased = OperationWhenKeyReleased;

	//添加监视器到目标节点并且绑定到场景图的优先级
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, TargetNode);

	//将监听器添加到键盘事件监听器列表中
	KeyBoardListenerList.push_back(Listener);
}

void EventManager::AddKeyBoardListener(Node* TargetNode,
	function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyPressed) {
	if (!TargetNode)
		return;    //如果目标节点或者监听器为空，则直接返回

	//创建键盘监听器
	auto Listener = EventListenerKeyboard::create();

	//设置监听器的回调函数
	Listener->onKeyPressed = OperationWhenKeyPressed;

	//添加监视器到目标节点并且绑定到场景图的优先级
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, TargetNode);

	//将监听器添加到键盘事件监听器列表中
	KeyBoardListenerList.push_back(Listener);
}

void EventManager::AddMouseListener(Node* TargetNode,function<void(EventMouse*)> OperationWhenMouseScroll) {
	if (!TargetNode)
		return;    //如果目标节点或者监听器为空，则直接返回

	//创建鼠标监听器
	auto Listener = EventListenerMouse::create();

	//设置监听器的回调函数
	Listener->onMouseScroll = OperationWhenMouseScroll;

	//添加监视器到目标节点并且绑定到场景图的优先级
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, TargetNode);

	//将监听器添加到鼠标事件监听器列表中
	MouseListenerList.push_back(Listener);
}

void EventManager::RemoveAllListenersInTheNode(Node* TargetNode) {
	if (!TargetNode) 
		return;    //

	// 移除与节点绑定的所有监听器
	_eventDispatcher->removeEventListenersForTarget(TargetNode);
}