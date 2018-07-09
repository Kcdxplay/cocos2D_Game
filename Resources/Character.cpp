#include "Character.h"
#include "CharacterType.h"
#include "CharacterOwnedStates.h"
#include "Helper.h"



void Character::BootUp(enum_charcterType type)
{
	

	//初始化运动状态机
	m_pMotionStateMachine = new MotionStateMachine<Character>(this);
	//初始化Sprite
	m_basicLayer = Sprite::create();
	CAManager_Instance->Get_BasicLayer()->addChild(m_basicLayer);

	switch (type)
	{
	case enum_charcterType::CharcterType_Default:
		m_pCType = CT_Default::Instance();
		m_pCType->BootUpCharacter(this);

		m_pMotionStateMachine->SetCurrentState(CMotionState_Respawn::Instance());
		m_pMotionStateMachine->CurrentState()->Enter(this);
		break;
	case enum_charcterType::CharcterTypey_Heavy:
		break;
	case enum_charcterType::CharcterType_Stalker:
		break;
	default:
		break;
	}
}

void Character::Update()
{
	m_pMotionStateMachine->Update();
}