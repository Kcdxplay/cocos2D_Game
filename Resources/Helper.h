#pragma once
#include "GameBase.h"
#include "Character.h"
#include "SimpleAudioEngine.h"

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
	int m_columns;	//֡��
	float m_delay;		//��ʱ

	BaseEffect(){}
	BaseEffect(char* name, int columns, float delay) :m_name(name), m_columns(columns), m_delay(delay) {}
};

//��Ч������
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
	static GloableEffect* Instance();	//����ģʽ
	
	list<EffectPlayer*>* Get_PlayList() { return &m_effectList; }
	list<EffectPlayer*>* Get_RemoveList() { return &m_effectRemoveList; }

	Layer* Get_BasicLayer() { return &m_layer; }

	void UpDate(float deltaMs) { VUpDate(deltaMs); };

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

//================����Ч�����=================//
#define audioInstance Audio::Instance()

class Audio : public Process
{
public:
private:
	CocosDenshion::SimpleAudioEngine* m_pAudioEngine;
	//��������һ��MAP  Ч����������Ӧ�����֡�w��

public:
	static Audio* Instance();

	void playEffectSound(EffectType type);
private:
	Audio() { VOnInit(); }
	~Audio() {}

protected:
	virtual void VOnInit();
	virtual void VUpDate(unsigned long DeltaMs);
	virtual void VOnAbort();
};


//================��Ϸ��ɫ���=================//
#define CAManager_Instance CharacterAnimationManager::Instance()

class CharacterAnimationManager
{
public:
	
private:
	Layer m_layer;
public:
	//����ģʽ
	static CharacterAnimationManager* Instance();

	Layer* Get_BasicLayer() { return &m_layer; }

	Animation* GetAnimation(BaseEffect* pBaseEffect);

private:
	CharacterAnimationManager() { Init(); }

	void Init();
};