#pragma once

#include "gamebase.h"
#include "Character.h"
#include "InputHelper.h"

#define PlayerController_Instance PlayerController::Instance()

enum enum_GameOperation
{
	OPT_Left=0,
	OPT_Right
};

class PlayerController : public Process
{
public:
	map<enum_GameOperation, InputHelper::KeyCode> m_operationMaps;	//用来储存每个操作的对应按键

private:
	GameEntityController<Character>* m_pEntityController;
public:
	//单例模式
	static PlayerController* Instance();

	virtual void VUpDate(unsigned long deltaMs);

	void ChangeCharacter(Character* character) { m_pEntityController->SET_Entity(character); }
private:
	PlayerController() { Init(); }
	PlayerController(Character* character) { Init(character); }
	~PlayerController() {};

	void Init();
	void Init(Character* character);

	void OperationAndKeys();
};