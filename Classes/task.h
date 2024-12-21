#pragma once
#ifndef __TASK_H__
#define __TASK_H__
#include <string>

class task
{
public:
	std::string taskName; // 任务的名称
	std::string description; // 对任务的描述
	bool isMainlineTask; // 是否主线任务，1表示主线任务，0表示支线任务
	bool isFinished; // 任务是否完成，1表示已完成，0表示未完成

	// 构造函数
	task(std::string name, std::string desc, bool isMainline, bool isFinished)
		: taskName(name), description(desc), isMainlineTask(isMainline), isFinished(isFinished) {
		// 使用初始化列表将值赋给成员变量
	}
};
#endif