#pragma once
#include "GameBase.h"
#include "Character.h"
#include "SimpleAudioEngine.h"

//================精灵动画相关=================//
#define spriteFrameCache SpriteFrameCache::getInstance()
#define gloableEffect GloableEffect::Instance()

class EffectPlayer;

//特效类型放在这里
enum EffectType
{
	EFT_Explosion = 0
};

struct BaseEffect
{
	char* m_name;	//读取用文件名及格式
	int m_columns;	//帧数
	float m_delay;		//延时

	BaseEffect(){}
	BaseEffect(char* name, int columns, float delay) :m_name(name), m_columns(columns), m_delay(delay) {}
};

//特效管理类
class GloableEffect : public Process
{

private:
	Layer m_layer;

	map<int, BaseEffect*> effectMap;

	list<EffectPlayer*> m_effectList;		//特效播放队列
	list<EffectPlayer*> m_effectRemoveList;	//特效移除队列

protected:
	

	virtual void VOnInit();
	virtual void VUpDate(unsigned long deltaMs);
	//virtual void VOnAbort();

private:
	GloableEffect() { VOnInit(); }

public:
	static GloableEffect* Instance();	//单例模式
	
	list<EffectPlayer*>* Get_PlayList() { return &m_effectList; }
	list<EffectPlayer*>* Get_RemoveList() { return &m_effectRemoveList; }

	Layer* Get_BasicLayer() { return &m_layer; }

	void UpDate(float deltaMs) { VUpDate(deltaMs); };

	//在指定位置播放动画
	bool PlayEffectAt(EffectType effect, Vec2 pos, int repeatTimes=1);	
};

//特效播放单元
class EffectPlayer : public BaseGraphic
{
private:
	Sequence* m_sequence;

public:
	EffectPlayer() {}
	//~EffectPlayer() {}

	void PlayThisAction(Repeat* action);

	//大量接口
	void SetSequence(Sequence* sequence) { m_sequence = sequence; }


private:
	void Finished() { gloableEffect->Get_RemoveList()->push_back(this); }
};

//================声音效果相关=================//
#define audioInstance Audio::Instance()

class Audio : public Process
{
public:
private:
	CocosDenshion::SimpleAudioEngine* m_pAudioEngine;
	//这里大概是一个MAP  效果和声音对应的那种←w←

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


//================游戏角色相关=================//
#define CAManager_Instance CharacterAnimationManager::Instance()

class CharacterAnimationManager
{
public:
	
private:
	Layer m_layer;
public:
	//单例模式
	static CharacterAnimationManager* Instance();

	Layer* Get_BasicLayer() { return &m_layer; }

	Animation* GetAnimation(BaseEffect* pBaseEffect);

private:
	CharacterAnimationManager() { Init(); }

	void Init();
};