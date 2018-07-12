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
	map<enum_GameOperation, InputHelper::KeyCode> m_operationMaps;	//��������ÿ�������Ķ�Ӧ����

private:
	GameEntityController<Character>* m_pEntityController;
public:
	//����ģʽ
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