#pragma once

#include "gamebase.h"
#include "Character.h"

//出生状态
class CMotionState_Respawn : public MotionState<Character>
{
public:
	static CMotionState_Respawn* Instance();

	virtual void Enter(Character* pCharacter);
	virtual void Execute(Character* pCharacter);
	virtual void Exit(Character* pCharacter);

	virtual bool OnMessage(Character* pCharacter, const Telegram& msg);
private:
	CMotionState_Respawn() {}
	~CMotionState_Respawn() {}
};

//站立状态
class CMotionState_Stand : public MotionState<Character>
{
public:
	static CMotionState_Stand* Instance();

	virtual void Enter(Character* pCharacter);
	virtual void Execute(Character* pCharacter);
	virtual void Exit(Character* pCharacter);

	virtual bool OnMessage(Character* pCharacter, const Telegram& msg);
};

//行走状态
class CMotionState_Walk : public MotionState<Character>
{
public:
	static CMotionState_Walk* Instance();

	virtual void Enter(Character* pCharacter);
	virtual void Execute(Character* pCharacter);
	virtual void Exit(Character* pCharacter);

	virtual bool OnMessage(Character* pCharacter, const Telegram& msg);
private:
	CMotionState_Walk() {}
	~CMotionState_Walk() {}
};