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
#define CharacterManaer_Instance CharacterManager::Instance()

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

//管理实体
class CharacterManager : public Process
{
public:
private:
	list<Character*> m_enityList;
	map<int, Character*> m_characterMap;

public:
	static CharacterManager* Instance();

	//进程的对于状态函数

	virtual void VOnInit();
	virtual void VUpDate(unsigned long deltaMs);
	virtual void VOnFail() {}
	virtual void VOnAbort() {}

	//接口与功能

	//增加一个玩家	会顶替之前的角色
	Character* AddPlayer(enum_characterType type);
	//增加一个敌人
	void AddEnemy(enum_characterType type);
	//增加一个角色
	void AddCharacter(enum_characterType type);

	Character* GetCharacterByID(int ID) { return m_characterMap[ID]; }
	//注册角色至消息处理图
	void RegistCharacter(Character* pCharacter);

private:
	CharacterManager() { VOnInit(); }
};

//================游戏AI相关=================//

//消息类型
enum enum_MsgType
{
	//控制部分
	ConMSG_StopedWalking,

};

class MessageDispatcher : public Process
{
public:
	set<Telegram> m_msgPriority;

private:

public:
	//单例模式
	static MessageDispatcher* Instance();
	//需要发送消息时调用此函数
	void DispatchMessage(int sender, int receiver, int msg, double delay = 0, void* ExtraInfo = NULL);

	virtual void VUpDate(unsigned long DeltaMs);

private:
	MessageDispatcher() {}
	~MessageDispatcher() {}

	//调用对应对象的消息处理函数  类型需要再修改
	void Dischare(Character* pReciver, Telegram& msg);
};

