#include "CharacterType.h"
#include "CharacterOwnedStates.h"

CT_Default * CT_Default::Instance()
{
	static CT_Default instance;
	return &instance;
}

void CT_Default::Init()
{
	m_health = 300;
	m_dump = 0.25;
	m_aSpeed[0] = 1; m_aSpeed[1] = 7; m_aSpeed[2] = 5;
	m_maxSpeed[0] = 3; m_maxSpeed[1] = 10; m_maxSpeed[2] = 7;

	//下面开始构造各个特效相关信息
	BaseEffect* pBE;

	//重生动画
	pBE = new BaseEffect("Megman_IN (%1d).png", 13, 0.05f);
	m_baseEffectMap.insert(make_pair(Respawn, pBE));
	//行走动画
	pBE = new BaseEffect("Megman_Running (%1d).png", 12, 0.05f);
	m_baseEffectMap.insert(make_pair(Walk, pBE));
}

void CT_Default::GetSequence(Character * character, int animationType)
{
	auto animation = CAManager_Instance->GetAnimation(m_baseEffectMap[animationType]);

	switch (animationType)
	{
		{
		case CT_Default::Respawn:
		//auto animation = CAManager_Instance->GetAnimation(m_baseEffectMap[animationType]);

		auto callFunc = CallFunc::create([character]()
		{
			character->Get_MotionStateMachine()->ChangeState(CMotionState_Walk::Instance());
		});

		character->Set_Sequence(Sequence::create(
			Repeat::create(Animate::create(animation), 1),
			callFunc,
			nullptr));

		break;
		}
	case CT_Default::Walk:
		//auto animation = CAManager_Instance->GetAnimation(m_baseEffectMap[animationType]);
		animation->setLoops(-1);
		character->Set_Sequence(Sequence::create(
			Repeat::create(Animate::create(animation), 1), 
			nullptr));
		break;
	case CT_Default::Dash:
		break;
	case CT_Default::Falling:
		break;
	default:
		break;
	}
}

void CT_Default::BootUpCharacter(Character * character)
{
	character->Set_Health(m_health);
	character->Set_Dump(m_dump);
	character->Set_ASpeed(m_aSpeed[0], m_aSpeed[1], m_aSpeed[2]);
	character->Set_MaxSpeed(m_maxSpeed[0], m_maxSpeed[1], m_maxSpeed[2]);
}
