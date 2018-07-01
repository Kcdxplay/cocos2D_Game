#pragma once

#include "cocos2d.h"

class GraphicTesting : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GraphicTesting);

	void update(float delta) override;

private:	
	cocos2d::Vector<cocos2d::SpriteFrame *> getAnimation(const char *format, int count);
};
