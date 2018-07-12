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

	void SetPosition(Vec2* pos) 
	{
		m_pos = *pos; m_sprite.setPosition(m_pos); 
		m_sprite.setAnchorPoint(Vec2(0.5, 0.5));
	}
	void SetScale(float scaleNum) { m_scale[0] = m_scale[1] = scaleNum; }
	void SetScale(float xScaleNum, float yScaleNum) { m_scale[0] = xScaleNum; m_scale[1] = yScaleNum; }

	Sprite* GetSprite() { return &m_sprite; }
};

//��Ϣ�ṹ��
struct Telegram
{
	int Sender;
	int Receiver;
	int Msg;
	double DispatchTime;
	void* ExtraInfo;

	Telegram(int sender, int receiver, int msg, double dispatchTime = 0, void* extraInfo = NULL) :
		Sender(sender),
		Receiver(receiver),
		Msg(msg),
		DispatchTime(dispatchTime),
		ExtraInfo(extraInfo)
	{}
};

//״̬��
template<typename entity_type>
class MotionState
{
public:
	virtual void Enter(entity_type*) = 0;
	virtual void Execute(entity_type*) = 0;
	virtual void Exit(entity_type*) = 0;

	virtual bool OnMessage(entity_type*, const Telegram&) = 0;
	
	virtual ~MotionState() {}
};

//״̬��
template<typename entity_type>
class MotionStateMachine
{
private:
	entity_type* m_pOwner;

	MotionState<entity_type>* m_pCurrentState;	//��ǰ״̬
	MotionState<entity_type>* m_pPreviousState;	//ǰ��״̬
	MotionState<entity_type>* m_pGlobaleState;	//ȫ��״̬

public:
	MotionStateMachine(entity_type* owner) :
		m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobaleState(NULL)
	{}

	//��ʼ����غ���

	void SetCurrentState(MotionState<entity_type>* state) { m_pCurrentState = state; }
	void SetPreviousState(MotionState<entity_type>* state) { m_pPreviousState = state; }
	void SetGlobalState(MotionState<entity_type>* state) { m_pGlobaleState = state; }

	//ÿ�θ��µ���
	void Update() const 
	{
		if (m_pGlobaleState)	m_pGlobaleState->Execute(m_pOwner);
		if (m_pCurrentState)	m_pCurrentState->Execute(m_pOwner);
	}

	//��Ϣ����
	bool HandleMessage(const Telegram& msg);

	//���״̬
	void ChangeState(MotionState<entity_type>* pNewstate)
	{
		if (pNewstate)
		{
			m_pPreviousState = m_pCurrentState;
			m_pCurrentState->Exit(m_pOwner);

			m_pCurrentState = pNewstate;
			m_pCurrentState->Enter(m_pOwner);
		}
	}

	//���״̬Ϊ��һ��״̬
	void RevertToPreviousState() { ChangeState(m_pPreviousState); }

	MotionState<entity_type>* CurrentState() { return m_pCurrentState; }
	MotionState<entity_type>* PreviousState() { return m_pPreviousState; }
	MotionState<entity_type>* GlobalState() { return m_pGlobaleState; }
};


//��ɫ������
template <typename entity_type>
class GameEntityController
{
public:

protected:
	entity_type* m_pEntity;

public:
	GameEntityController() :m_pEntity(NULL) {}
	GameEntityController(entity_type* entity) :m_pEntity(entity) {}

	void SET_Entity(entity_type* entity) { m_pEntity = entity; }
	entity_type* GET_Entity() { return m_pEntity; }
private:
};

template<typename entity_type>
inline bool MotionStateMachine<entity_type>::HandleMessage(const Telegram & msg)
{
	if (m_pCurrentState->OnMessage(m_pOwner, msg))
		return true;

	if (m_pGlobaleState->OnMessage(m_pOwner, msg))
		return true;

	return false;
}
