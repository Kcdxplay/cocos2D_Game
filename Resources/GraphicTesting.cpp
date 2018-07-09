#include "GraphicTesting.h"
#include <ui\CocosGUI.h>

#include "Helper.h"
#include "InputHelper.h"

#include "Character.h"
#include "CharacterType.h"

USING_NS_CC;

Scene* GraphicTesting::createScene()
{
	auto scene = Scene::create();
	auto layer = GraphicTesting::create();
	scene->addChild(layer);

	return scene;
}

bool GraphicTesting::init()
{
	if (!Layer::init())
	{
		return false;
	}	
	this->addChild(gloableEffect->Get_BasicLayer());
	this->addChild(CAManager_Instance->Get_BasicLayer());
	inputInstance;

	/*gloableEffect->PlayEffectAt(EFT_Explosion, Vec2(0, 0), 3);
	gloableEffect->PlayEffectAt(EFT_Explosion, Vec2(400, 300), 3);
	gloableEffect->PlayEffectAt(EFT_Explosion, Vec2(200, 200), 3);
	gloableEffect->PlayEffectAt(EFT_Explosion, Vec2(400, 200), 4);*/
	
	static Character player(enum_charcterType::CharcterType_Default);

	//this->addChild(player.Get_Sprite());

	/*auto animFrames = getAnimation("Megman_Running (%1d).png", 12);
	auto sprite = Sprite::createWithSpriteFrame(animFrames.front());
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	animation->setLoops(-1);
	auto action = Repeat::create(Animate::create(animation),1);
	auto sequence = Sequence::create(action, nullptr);

	sprite->setPosition(Vec2(200, 300));
	
	sprite->runAction(sequence);
	this->addChild(sprite);*/

	this->scheduleUpdate();
	
	return true;
}

void GraphicTesting::update(float deltaMs)
{
	gloableEffect->UpDate(deltaMs);
}

cocos2d::Vector<SpriteFrame*> GraphicTesting::getAnimation(const char * format, int count)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	char str[100];

	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}

	return animFrames;
}