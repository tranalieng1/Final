#ifndef SKeyboard_h__
#define SKeyboard_h__

#include "cocos2d.h"
#include "Defnition.h"
#include <vector>

USING_NS_CC;

class SKeyboard : public Node
{
public:
	static	KeyState			getKeyState(EventKeyboard::KeyCode keyCode);
	static	std::vector<KeyBoardEvent*>	getEvents();
	static	void				release();
	static	SKeyboard*			get();

	virtual bool	init();
	virtual void	update(float delta);

	void onKeyPress(EventKeyboard::KeyCode code, Event* kEvent);
	void onKeyRelease(EventKeyboard::KeyCode code, Event* kEvent);

private:
	SKeyboard();
	~SKeyboard();

private:
	KeyState			*m_KeyMap;
	std::vector<KeyBoardEvent*>	m_EventStack;

	static SKeyboard			*m_Instance;
};

#endif // SKeyboard_h__
