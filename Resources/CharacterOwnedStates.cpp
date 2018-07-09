#include "CharacterOwnedStates.h"
#include "CharacterType.h"


//=======����״̬���=======
CMotionState_Respawn * CMotionState_Respawn::Instance()
{
	static CMotionState_Respawn instance;
	return &instance;
}

void CMotionState_Respawn::Enter(Character * pCharacter)
{

	pCharacter->Set_Pos(Vec2(200, 300));
	//���ö�Ӧ�Ķ���
	pCharacter->Get_CharacterType()->GetSequence(pCharacter, 0);	
	//ִ����Ӧ����
	pCharacter->RunAnimation();
}

void CMotionState_Respawn::Execute(Character * pCharacter)
{
}

void CMotionState_Respawn::Exit(Character * pCharacter)
{
	//pCharacter->Get_Sequence()->autorelease();
}


//=======����״̬���=======
CMotionState_Walk * CMotionState_Walk::Instance()
{
	static CMotionState_Walk instance;
	return &instance;
}

void CMotionState_Walk::Enter(Character * pCharacter)
{
	pCharacter->Set_Pos(Vec2(200, 300));
	//���ö�Ӧ�Ķ���
	pCharacter->Get_CharacterType()->GetSequence(pCharacter, 1);
	//ִ����Ӧ����
	pCharacter->RunAnimation();
}

void CMotionState_Walk::Execute(Character * pCharacter)
{
}

void CMotionState_Walk::Exit(Character * pCharacter)
{
}


