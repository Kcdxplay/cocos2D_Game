#include "Helper.h"
#include "Player.h"

void GloableEffect::VOnInit()
{
	spriteFrameCache->addSpriteFramesWithFile("boom.plist");
	
	//��ʱ�滻Ϊ�������� XD
	BaseEffect* explosion = new BaseEffect("explosion (%1d).png",16,0.05f);
	effectMap.insert(make_pair(EFT_Explosion, explosion));
}

void GloableEffect::VUpDate(unsigned long deltaMs)
{
	//��λ���Ƴ����е���Чɾ��
	for each (EffectPlayer* var in m_effectRemoveList)
	{
		try
		{
			//�����Ƴ��ˣ��������Ͳ��ɼ���
			//m_effectRemoveList.remove(var);
			gloableEffect->Get_BasicLayer()->removeChild(var->GetSprite());

			delete var;
			var++;
		}
		catch (const std::exception&)
		{

		}
	}

	//��������Ƴ��б��ܾ��úܲ��õĽ�������� :P
	m_effectRemoveList.clear();
}

GloableEffect * GloableEffect::Instance()
{
	static GloableEffect instance;
	return &instance;
}

bool GloableEffect::PlayEffectAt(EffectType effect, Vec2 pos, int repeatTimes)
{
	BaseEffect* pBaseEffect = effectMap[effect];
	if (pBaseEffect == nullptr)
		return false;

	//��ʼ�����µĶ���Ƭ��
	char str[100];
	Vector<SpriteFrame*> animFrames;	//������"֡����"

	for (int i = 1; i <= pBaseEffect->m_columns; i++)
	{
		sprintf(str, pBaseEffect->m_name, i);
		animFrames.pushBack(spriteFrameCache->getSpriteFrameByName(str));
	}
	if (animFrames.empty())
		return false;

	auto animation = Animation::createWithSpriteFrames(animFrames, pBaseEffect->m_delay);
	auto action = Repeat::create(Animate::create(animation), repeatTimes);

	EffectPlayer* pEP = new EffectPlayer();
	pEP->SetPosition(&pos);
	pEP->PlayThisAction(action);

	//��ӵ���Ч����
	m_layer.addChild(pEP->GetSprite());
	//���Ŷ�Ӧ��Ч
	audioInstance->playEffectSound(effect);

	//������Ч�б����棨������ҪҲ��
	//gloableEffect->Get_PlayList()->push_back(pEP);
	return true;
}

void EffectPlayer::PlayThisAction(Repeat * action)
{

	auto func = CallFunc::create(std::bind(&EffectPlayer::Finished, this));

	m_sequence = Sequence::create(action, func, nullptr);
	
	m_sprite.runAction(m_sequence);
}


//================����Ч�����=================//
Audio * Audio::Instance()
{
	static Audio instance;
	return &instance;
}

void Audio::playEffectSound(EffectType type)
{
	switch (type)
	{
	case EFT_Explosion:
		m_pAudioEngine->playEffect("Explosion_03.wav");
		break;
	default:
		break;
	}
}

void Audio::VOnInit()
{
	m_pAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pAudioEngine->preloadEffect("Explosion_03.wav");
}

void Audio::VUpDate(unsigned long DeltaMs)
{
}

void Audio::VOnAbort()
{
}

CharacterAnimationManager * CharacterAnimationManager::Instance()
{
	static CharacterAnimationManager instance;
	return &instance;
}

Animation * CharacterAnimationManager::GetAnimation(BaseEffect* pBaseEffect)
{
	char str[100];
	Vector<SpriteFrame*> animFrames;	//������"֡����"

	for (int i = 1; i <= pBaseEffect->m_columns; i++)
	{
		sprintf(str, pBaseEffect->m_name, i);
		animFrames.pushBack(spriteFrameCache->getSpriteFrameByName(str));
	}
	if (animFrames.empty())
		return false;

	return Animation::createWithSpriteFrames(animFrames, pBaseEffect->m_delay);
}

void CharacterAnimationManager::Init()
{
	spriteFrameCache->addSpriteFramesWithFile("Megman.plist");
}

CharacterManager * CharacterManager::Instance()
{
	static CharacterManager instance;
	return &instance;
}

void CharacterManager::VOnInit()
{
}

void CharacterManager::VUpDate(unsigned long deltaMs)
{

}

Character * CharacterManager::AddPlayer(enum_characterType type)
{
	Character* pC = new Character(type);

	m_enityList.push_back(pC);

	PlayerController_Instance->ChangeCharacter(pC);

	return pC;
}

void CharacterManager::AddCharacter(enum_characterType type)
{
	Character* pC = new Character(type);

	m_enityList.push_back(pC);
}

void CharacterManager::RegistCharacter(Character * pCharacter)
{
	m_characterMap.insert(make_pair(pCharacter->Get_ID(), pCharacter));
}

//=======��Ϣ����=======

MessageDispatcher * MessageDispatcher::Instance()
{
	static MessageDispatcher instance;
	return &instance;
}

//��Ϣ���ͣ���Ҫ���޸�
void MessageDispatcher::DispatchMessage(int sender, int receiver, int msg, double delay, void * ExtraInfo)
{
	Character* pReceiver = CharacterManaer_Instance->GetCharacterByID(receiver);

	Telegram telegram(sender, receiver, msg, delay, ExtraInfo);
	if (delay <= 0)
	{
		Dischare(pReceiver, telegram);
	}
	else
	{
		double currentTime = clock();
		telegram.DispatchTime = currentTime + delay;

		//m_msgPriority.insert(telegram);
	}
}

void MessageDispatcher::VUpDate(unsigned long DeltaMs)
{
}

void MessageDispatcher::Dischare(Character * pReciver, Telegram & msg)
{
}
