#include "InputHelper.h"
#include "Helper.h"

#define inputInstance InputHelper::Instance()

InputHelper * InputHelper::Instance()
{
	static InputHelper instance;
	return &instance;
}

void InputHelper::VOnInit()
{
	m_MouseListener = EventListenerMouse::create();
	m_KeyboardListener = EventListenerKeyboard::create();

	m_MouseListener->onMouseDown = std::bind(&InputHelper::MouseDown, this, std::placeholders::_1);
	//m_KeyboardListener->onKeyPressed = std::bind(&InputHelper::KeyDown, this, std::placeholders::_1);

	//¿ªÊ¼¼àÌý

	auto _eventlistener = Director::getInstance()->getEventDispatcher();
	_eventlistener->addEventListenerWithFixedPriority(m_MouseListener, 1);
	//_eventlistener->addEventListenerWithFixedPriority(m_KeyboardListener,1);
}

void InputHelper::VUpDate(unsigned long deltaMs)
{
}

void InputHelper::VOnAbort()
{
}

void InputHelper::MouseDown(cocos2d::Event * event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	Size size = Director::getInstance()->getWinSize();
	
	Vec2 pos(mouseEvent->getCursorX(), mouseEvent->getCursorY()+size.height-40);

	gloableEffect->PlayEffectAt(EFT_Explosion, pos);
}

void InputHelper::KeyDown(cocos2d::Event * event)
{
}
