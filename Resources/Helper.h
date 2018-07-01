#pragma once
#include "GameBase.h"

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
	Sequence m_effectRunner;	//动画
	Sprite m_effectHolder;	//精灵

	int m_columns;	//帧数
	float m_delay;		//延时

	BaseEffect(){}
	BaseEffect(char* name, int columns, float delay) :m_name(name), m_columns(columns), m_delay(delay) {}
};

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


public:
	static GloableEffect* Instance();	//单例模式
	
	list<EffectPlayer*>* Get_PlayList() { return &m_effectList; }
	list<EffectPlayer*>* Get_RemoveList() { return &m_effectRemoveList; }

	Layer* Get_BasicLayer() { return &m_layer; }

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