#pragma once

#include "gamebase.h"

class CharacterType;

//临时放置于此的，所有实体的ID部分
class ActorID
{
public:
protected:
	int m_ID;		//每个实体的独立ID
public:
	explicit ActorID() :m_ID(NextID()) {}
	
	//获取该实体ID
	const int& GET_ID() const { return m_ID; }
private:
	int NextID() 
	{
		static int nextID;	//下一个可用ID
		return nextID++;
	}
};

//角色类型的枚举
enum class enum_characterType
{
	CharcterType_Default = 0,	//默认
	CharcterTypey_Heavy,		//重甲
	CharcterType_Stalker,		//猎人
};

//暂时没啥用，到时候需修改Character类
class Entity
{

};

class Character : public Entity
{
protected:
	float m_health;		//角色的生命值
	float m_speed;		//角色当前速度
	float m_dump;		//角色阻滞力

	float m_aSpeed[3];		//角色运动加速度	0-行走	1-冲刺	2-跳跃
	float m_maxSpeed[3];	//角色最大速度	0-行走	1-冲刺	2-掉落

	bool m_towarding = true;	//角色朝向	true-向右	false-向左	
	ActorID m_ID;		//角色ID
	Vec2 m_pos;			//角色位置

	MotionStateMachine<Character>* m_pMotionStateMachine;	//角色的运动状态机

	Sprite* m_basicLayer;		//角色的精灵本体
	Sequence* m_pAnimation;		//角色的动画指针
	CharacterType* m_pCType;	//角色的角色类型指针

public:
	explicit Character(enum_characterType type) { BootUp(type); }
	~Character() { delete m_pMotionStateMachine; }

	//角色初始化函数
	void BootUp(enum_characterType type);		
	//角色每次更新调用
	void Update();
	//角色消息处理
	bool HandleMessage(const Telegram& msg);
	//角色动画播放
	void RunAnimation();

	//=====运动行为接口=====

	//尝试站立
	void Stand();
	//尝试走动
	void Walk();


	//=====大量的接口=====

	//角色动画序列接口
	Sequence* Get_Sequence() { return m_pAnimation; }
	void Set_Sequence(Sequence* pSequence) { m_pAnimation = pSequence; }

	Sprite* Get_Sprite() { return m_basicLayer; }
	
	//获取ID
	int Get_ID() { return m_ID.GET_ID(); }

	//设置位置
	void Set_Pos(Vec2 pos) 
	{
		m_pos = pos;
		m_basicLayer->setPosition(pos); 
	}

	//基础数据设置
	void Set_Health(float health) { m_health = health; }
	void Set_Speed(float speed) { m_speed = speed; }
	void Set_Dump(float dump) { m_dump = dump; }

	//设置角色运动加速度	0-行走	1-冲刺	2-跳跃
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

	//设置角色朝向	true-向右	false-向左	
	void Set_Towarding(bool towarding) { m_towarding = towarding; }

	MotionStateMachine<Character>* Get_MotionStateMachine() { return m_pMotionStateMachine; }
	CharacterType* Get_CharacterType() { return m_pCType; }

private:

};

//||=====工厂应生成对应类型=====||
//角色的各种类型
class CharacterType
{
public:
	//自己的初始化函数
	virtual void Init() = 0;

	//给角色配置动画的函数
	virtual void GetSequence(Character* charcter, int animationType) = 0;
	//给角色进行初始化的函数
	virtual void BootUpCharacter(Character* charcter) = 0;

	virtual ~CharacterType() {}
};

//储存不同角色的动画==============================================||暂时没用||
//class Animation_Sequence
//{
//
//};