#include "Player.h"
#include "Helper.h"
#include "CharacterOwnedStates.h"


#define Player m_pEntityController->GET_Entity()

PlayerController * PlayerController::Instance()
{
	static PlayerController instance;
	return &instance;
}

void PlayerController::VUpDate(unsigned long deltaMs)
{
	OperationAndKeys();
}

void PlayerController::Init()
{
	//=====应使用工厂构造=====
	//初始化操作与按键的对应图
	m_operationMaps.insert(make_pair(OPT_Left, InputHelper::KEY_A));
	m_operationMaps.insert(make_pair(OPT_Right, InputHelper::KEY_D));

	//初始化实例控制器
	m_pEntityController = new GameEntityController<Character>();
}

void PlayerController::Init(Character* character)
{
	m_pEntityController = new GameEntityController<Character>(character);
}
















//按键与更新
void PlayerController::OperationAndKeys()
{
	bool* keys = inputInstance->GetKeys();	//键盘按键集合

	bool moveX = false;

	if (keys[m_operationMaps[OPT_Left]])
	{
		Player->Set_Towarding(false);
		moveX = true;
	}
	if(keys[m_operationMaps[OPT_Right]])
	{
		Player->Set_Towarding(true);
		moveX = true;
	}

	if (moveX)
	{
		Player->Walk();
	}
	else
	{
		Player->Stand();
	}
}