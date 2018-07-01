#pragma once

#include <stdio.h>
#include <iostream>

#include "AppDelegate.h"

using namespace std;

class Process;
class ProcessManager;
typedef shared_ptr<Process> StrongProcessPtr;
typedef weak_ptr<Process> WeakProcessPtr;


//������
class Process
{
	friend class ProcessManager;

public:
	enum State
	{
		UNINITIALIZED = 0,	//δ��ʼ��
		REMOVED,	//�Ƴ���������
		RUNNING,	//��������
		PAUSED,		//�Ѿ�ֹͣ

		SUCCEEDED,	//
		FAILED,		
		ABORTED,	
	};
private:
	State m_state;
	StrongProcessPtr m_child;

public:
	Process();
	virtual ~Process();

protected:
	virtual void VOnInit() {	}
	virtual void VUpDate(unsigned long deltaMs) = 0;
	virtual void VOnSuccess() {}
	virtual void VOnFail() {}
	virtual void VOnAbort() {}

public:
	inline void Succeed();
	inline void Fail();

	inline void Pause();
	inline void UnPause();

	//�ӿ�
	State GetState() const { return m_state; }
	bool IsAlive() const { return (m_state == RUNNING || m_state == PAUSED); }
	bool IsDead() const { return (m_state == SUCCEEDED || m_state == FAILED || m_state == ABORTED); }
	bool IsRemoved() const { return m_state == REMOVED; }
	bool IsPaused() const { return m_state == PAUSED; }

	//�ӽ������
	inline void AttachChild(StrongProcessPtr pChild);
	StrongProcessPtr RemoveChild();
	StrongProcessPtr PeekChild() { return m_child; }

private:
	void SetState(State newState) { m_state = newState; }
};

//ͼ����
class BaseGraphic
{
protected:
	Sprite m_sprite;	//����

	Vec2 m_pos;	//����λ��

	float m_scale[2];	//����	0-X������ 1-Y������

public:
	BaseGraphic();
	virtual ~BaseGraphic();

	//�����ӿ�

	void SetPosition(Vec2* pos) { m_pos = *pos; m_sprite.setPosition(m_pos); }
	void SetScale(float scaleNum) { m_scale[0] = m_scale[1] = scaleNum; }
	void SetScale(float xScaleNum, float yScaleNum) { m_scale[0] = xScaleNum; m_scale[1] = yScaleNum; }

	Sprite* GetSprite() { return &m_sprite; }
};