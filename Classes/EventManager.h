#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class EventManager :public Node {
private:
	vector<EventListenerMouse*> MouseListenerList;    //用来存储鼠标事件监听器
	vector<EventListenerKeyboard*> KeyBoardListenerList;    //用来存储键盘事件监听器

public:
	/* 添加键盘事件监听器，按下键盘的时候与松开键盘的时候都会触发回调函数 */
	void AddKeyBoardListener(Node* TargetNode,
		function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyPressed,
		function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyReleased);

	/* 添加键盘事件监听器，只在按下键盘的时候触发回调函数 */
	void AddKeyBoardListener(Node* TargetNode,
		function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyPressed);

	/* 添加鼠标事件监听器, 鼠标滚动的时候触发回调函数 */
	void AddMouseListener(Node* TargetNode,
		function<void(EventMouse*)> OperationWhenMouseScroll);

	/*移除绑定至某个节点的所有监听器*/
	void RemoveAllListenersInTheNode(Node* TargetNode);

	CREATE_FUNC(EventManager);
}

#endif // __EVENT_MANAGER_H__