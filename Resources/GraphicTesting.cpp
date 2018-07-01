#include "GraphicTesting.h"
#include <ui\CocosGUI.h>

#include "Header\Helper.h"

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

	gloableEffect->PlayEffectAt(EFT_Explosion, Vec2(200, 300), 3);
	gloableEffect->PlayEffectAt(EFT_Explosion, Vec2(400, 300), 3);
	gloableEffect->PlayEffectAt(EFT_Explosion, Vec2(200, 200), 3);
	gloableEffect->PlayEffectAt(EFT_Explosion, Vec2(400, 200), 4);

	this->scheduleUpdate();
	
	return true;
}

void GraphicTesting::update(float deltaMs)
{
	gloableEffect->UpDate(deltaMs);
}

//cocos2d::Vector<SpriteFrame*> GraphicTesting::getAnimation(const char * format, int count)
//{
//	auto spriteCache = SpriteFrameCache::getInstance();
//	Vector<SpriteFrame*> animFrames;
//	char str[100];
//
//	for (int i = 1; i <= count; i++)
//	{
//		sprintf(str, format, i);
//		animFrames.pushBack(spriteCache->getSpriteFrameByName(str));
//	}
//
//	return animFrames;
//}