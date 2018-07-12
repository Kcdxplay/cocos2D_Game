#include "Character.h"
#include "CharacterType.h"
#include "CharacterOwnedStates.h"
#include "Helper.h"



void Character::BootUp(enum_characterType type)
{
	

	//初始化运动状态机
	m_pMotionStateMachine = new MotionStateMachine<Character>(this);

	m_pMotionStateMachine->SetCurrentState(CMotionState_Respawn::Instance());

	//初始化Sprite
	m_basicLayer = Sprite::create();
	CAManager_Instance->Get_BasicLayer()->addChild(m_basicLayer);

	switch (type)
	{
	case enum_characterType::CharcterType_Default:
		m_pCType = CT_Default::Instance();
		m_pCType->BootUpCharacter(this);

		m_pMotionStateMachine->SetCurrentState(CMotionState_Respawn::Instance());
		m_pMotionStateMachine->CurrentState()->Enter(this);
		break;
	case enum_characterType::CharcterTypey_Heavy:
		break;
	case enum_characterType::CharcterType_Stalker:
		break;
	default:
		break;
	}
}

void Character::Update()
{
	m_pMotionStateMachine->Update();
}

bool Character::HandleMessage(const Telegram & msg)
{
	return m_pMotionStateMachine->HandleMessage(msg);
}

void Character::RunAnimation()
{
	m_basicLayer->stopAllActions();
	m_basicLayer->runAction(m_pAnimation); 
}

void Character::Stand()
{
	{
		if (m_pMotionStateMachine->CurrentState() != CMotionState_Respawn::Instance()
			&& m_pMotionStateMachine->CurrentState() != CMotionState_Stand::Instance())
		{
			m_pMotionStateMachine->ChangeState(CMotionState_Stand::Instance());
		}
	}
}

void Character::Walk()
{
	{
		if (m_pMotionStateMachine->CurrentState() != CMotionState_Respawn::Instance()
			&& m_pMotionStateMachine->CurrentState() != CMotionState_Walk::Instance())
		{
			m_pMotionStateMachine->ChangeState(CMotionState_Walk::Instance());
		}
	}
}
