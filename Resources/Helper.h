#pragma once
#include "GameBase.h"

//================���鶯�����=================//
#define spriteFrameCache SpriteFrameCache::getInstance()
#define gloableEffect GloableEffect::Instance()

class EffectPlayer;

//��Ч���ͷ�������
enum EffectType
{
	EFT_Explosion = 0
};

struct BaseEffect
{
	char* m_name;	//��ȡ���ļ�������ʽ
	Sequence m_effectRunner;	//����
	Sprite m_effectHolder;	//����

	int m_columns;	//֡��
	float m_delay;		//��ʱ

	BaseEffect(){}
	BaseEffect(char* name, int columns, float delay) :m_name(name), m_columns(columns), m_delay(delay) {}
};

class GloableEffect : public Process
{

private:
	Layer m_layer;

	map<int, BaseEffect*> effectMap;

	list<EffectPlayer*> m_effectList;		//��Ч���Ŷ���
	list<EffectPlayer*> m_effectRemoveList;	//��Ч�Ƴ�����

protected:
	

	virtual void VOnInit();
	virtual void VUpDate(unsigned long deltaMs);
	//virtual void VOnAbort();

private:
	GloableEffect() { VOnInit(); }
public:


public:
	static GloableEffect* Instance();	//����ģʽ
	
	list<EffectPlayer*>* Get_PlayList() { return &m_effectList; }
	list<EffectPlayer*>* Get_RemoveList() { return &m_effectRemoveList; }

	Layer* Get_BasicLayer() { return &m_layer; }

	//��ָ��λ�ò��Ŷ���
	bool PlayEffectAt(EffectType effect, Vec2 pos, int repeatTimes=1);	
};

//��Ч���ŵ�Ԫ
class EffectPlayer : public BaseGraphic
{
private:
	Sequence* m_sequence;

public:
	EffectPlayer() {}
	//~EffectPlayer() {}

	void PlayThisAction(Repeat* action);

	//�����ӿ�
	void SetSequence(Sequence* sequence) { m_sequence = sequence; }


private:
	void Finished() { gloableEffect->Get_RemoveList()->push_back(this); }
};