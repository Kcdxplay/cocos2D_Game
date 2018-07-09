#pragma once

#include "Character.h"
#include "Helper.h"

//默认类型的角色
#define CT_DefaultInstance CT_Default::Instance()

class CT_Default : public CharacterType
{
public:
	enum enum_Default_Animation
	{
		Respawn=0,	//重生
		Walk,		//行走
		Dash,		//冲刺
		Falling		//掉落
	};
private:
	float m_health;			//角色生命值
	float m_dump;			//角色阻滞力
	float m_aSpeed[3];		//角色加速度	0-行走	1-冲刺	2-跳跃
	float m_maxSpeed[3];	//角色最大速度	0-行走	1-冲刺	2-掉落

	map<int, BaseEffect*> m_baseEffectMap;

public:
	//单例模式
	static CT_Default* Instance();

	//自己的初始化函数
	virtual void Init();

	//给角色配置动画的函数
	virtual void GetSequence(Character* character, int animationType);
	//给角色进行初始化的函数
	virtual void BootUpCharacter(Character* character);

private:
	CT_Default() { Init(); }
	//~CT_Default(){}

private:

};