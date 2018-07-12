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
	//=====Ӧʹ�ù�������=====
	//��ʼ�������밴���Ķ�Ӧͼ
	m_operationMaps.insert(make_pair(OPT_Left, InputHelper::KEY_A));
	m_operationMaps.insert(make_pair(OPT_Right, InputHelper::KEY_D));

	//��ʼ��ʵ��������
	m_pEntityController = new GameEntityController<Character>();
}

void PlayerController::Init(Character* character)
{
	m_pEntityController = new GameEntityController<Character>(character);
}
















//���������
void PlayerController::OperationAndKeys()
{
	bool* keys = inputInstance->GetKeys();	//���̰�������

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