#pragma once

#include "gamebase.h"

class CharacterType;


//��ɫ���͵�ö��
enum class enum_charcterType
{
	CharcterType_Default = 0,	//Ĭ��
	CharcterTypey_Heavy,		//�ؼ�
	CharcterType_Stalker,		//����
};

class Character
{
protected:
	float m_health;		//��ɫ������ֵ
	float m_speed;		//��ɫ��ǰ�ٶ�
	float m_dump;		//��ɫ������

	float m_aSpeed[3];		//��ɫ�˶����ٶ�	0-����	1-���	2-��Ծ
	float m_maxSpeed[3];	//��ɫ����ٶ�	0-����	1-���	2-����

	MotionStateMachine<Character>* m_pMotionStateMachine;	//��ɫ���˶�״̬��

	Sprite* m_basicLayer;		//��ɫ�ľ��鱾��
	Sequence* m_pAnimation;		//��ɫ�Ķ���ָ��
	CharacterType* m_pCType;	//��ɫ�Ľ�ɫ����ָ��

public:
	explicit Character(enum_charcterType type) { BootUp(type); }
	~Character() { delete m_pMotionStateMachine; }

	//��ɫ��ʼ������
	void BootUp(enum_charcterType type);		
	//��ɫÿ�θ��µ���
	void Update();

	void RunAnimation() { m_basicLayer->runAction(m_pAnimation); }

	//=====�����Ľӿ�=====

	//��ɫ�������нӿ�
	Sequence* Get_Sequence() { return m_pAnimation; }
	void Set_Sequence(Sequence* pSequence) { m_pAnimation = pSequence; }

	Sprite* Get_Sprite() { return m_basicLayer; }
	void Set_Pos(Vec2 pos) { m_basicLayer->setPosition(pos); }

	void Set_Health(float health) { m_health = health; }
	void Set_Speed(float speed) { m_speed = speed; }
	void Set_Dump(float dump) { m_dump = dump; }
	void Set_ASpeed(float speed0, float speed1, float speed2) 
	{ 
		m_aSpeed[0] = speed0; 
		m_aSpeed[1] = speed1;
		m_aSpeed[2] = speed2;
	}
	void Set_MaxSpeed(float speed0, float speed1, float speed2)
	{
		m_maxSpeed[0] = speed0;
		m_maxSpeed[1] = speed1;
		m_maxSpeed[2] = speed2;
	}

	MotionStateMachine<Character>* Get_MotionStateMachine() { return m_pMotionStateMachine; }
	CharacterType* Get_CharacterType() { return m_pCType; }

private:

};

//||=====����Ӧ���ɶ�Ӧ����=====||
//��ɫ�ĸ�������
class CharacterType
{
public:
	//�Լ��ĳ�ʼ������
	virtual void Init() = 0;

	//����ɫ���ö����ĺ���
	virtual void GetSequence(Character* charcter, int animationType) = 0;
	//����ɫ���г�ʼ���ĺ���
	virtual void BootUpCharacter(Character* charcter) = 0;

	virtual ~CharacterType() {}
};

//���治ͬ��ɫ�Ķ���==============================================||��ʱû��||
//class Animation_Sequence
//{
//
//};