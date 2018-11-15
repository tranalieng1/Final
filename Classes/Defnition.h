#ifndef __DEFNITION_H__
#define __DEFNITION_H__

#define DISPLAY_SPLASH_SCENE 1
#define TRANSITTION_TIME 1

#define POSITION_BEGIN_HEIGHT 0.2f
#define POSITION_BEGIN_WIDTH 0.5f

#define SPEED_MOVE_HORIZONTAL 0.0035
#define SPEED_MOVE_VERTICAL 0.002

////ARTHUR
#define PLAYER_JUMP 1.5f
#define ARTHUR_MOVE_SPEED 5.5f
#define TAG_MAVERICK 1
#define ARTHUR_CATEGORY_BITMASK					0x01
#define ARTHUR_COLLISION_AND_CONTACT_TEST_BITMASK 0x02
#define VELOCITY_VALUE_X 200.0f
#define VELOCITY_VALUE_Y 100.0f
//WALL
#define TAG_WALL 2
#define WALL_CATEGORY_BITMASK 0x000003
#define WALL_COLLISION_AND_CONTACT_TEST_BIT_MASK 0xFFFF

enum	KeyState
{
	KS_UP = 0,
	KS_DOWN,
	KS_PRESS,
	KS_RELEASE
};

struct	KeyBoardEvent
{
	cocos2d::EventKeyboard::KeyCode	keyCode;
	KeyState				stateEvent;

	KeyBoardEvent(cocos2d::EventKeyboard::KeyCode code, KeyState sEvent)
	{
		keyCode = code;
		stateEvent = sEvent;
	}
};

#define KEYMAP_SIZE			255

#endif // !__DEFNITION_H__

