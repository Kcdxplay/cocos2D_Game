#pragma once

#include "Character.h"
#include "Helper.h"

//Ĭ�����͵Ľ�ɫ
#define CT_DefaultInstance CT_Default::Instance()

class CT_Default : public CharacterType
{
public:
	enum enum_Default_Animation
	{
		Respawn=0,	//����
		Walk,		//����
		Dash,		//���
		Falling		//����
	};
private:
	float m_health;			//��ɫ����ֵ
	float m_dump;			//��ɫ������
	float m_aSpeed[3];		//��ɫ���ٶ�	0-����	1-���	2-��Ծ
	float m_maxSpeed[3];	//��ɫ����ٶ�	0-����	1-���	2-����

	map<int, BaseEffect*> m_baseEffectMap;

public:
	//����ģʽ
	static CT_Default* Instance();

	//�Լ��ĳ�ʼ������
	virtual void Init();

	//����ɫ���ö����ĺ���
	virtual void GetSequence(Character* character, int animationType);
	//����ɫ���г�ʼ���ĺ���
	virtual void BootUpCharacter(Character* character);

private:
	CT_Default() { Init(); }
	//~CT_Default(){}

private:

};