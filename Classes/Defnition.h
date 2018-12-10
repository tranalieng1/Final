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
#define PLAYER_CATE	4				//0000100
#define PLAYER_COLL 226    //11100010
#define VELOCITY_VALUE_X 200.0f
#define VELOCITY_VALUE_Y 100.0f
#define TAG_PLAYER 4

////PERCIVAL
#define PLAYER_JUMP 1.5f
#define PERCIVAL_MOVE_SPEED 5.5f
#define TAG_MAVERICK 1
//#define PLAYER_CATE					0x001
//#define PLAYER_COLL 0x002
#define VELOCITY_VALUE_X 200.0f
#define VELOCITY_VALUE_Y 100.0f
//#define TAG_PLAYER 4



//Attack
#define TAG_ATTACK_ARTHUR 40
#define TAG_ATTACK_PERCIVAL 41

#define HIT_PLAYER_CATE 1  //0000001
#define HIT_PLAYER_COLL 88 //1011000

#define TAG_ATTACK_ENEMY 45

#define HIT_ENEMY_CATE 2  //0000010
#define HIT_ENEMY_COLL 4 //00000100
//WALL
#define TAG_WALL 33
#define WALL_CATE 128 //10010
#define WALL_COLL 0xFFFF
//ENEMY
#define ENEMY_CATE 8 //1000
#define ENEMY_COLL 193 //11000001
#define TAG_CREEP 20
//SCECRE
#define SECRET_CATE 16 //10000
#define SECRET_COLL 1 
#define TAG_SECRET 70
//ITEM
#define ITEM_CATE 32 //100000
#define ITEM_COLL 4 //100
//BOX
#define BOX_CATE 64 //1000000
#define BOX_COLL 13 //1101

//skill
#define TAG_SKILL_MB 50
#define TAG_SKILL_FLAME 51

//animation
#define TAG_ANIMATION 10
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

//Map
#define SCALE_MAP 4.0f
#define MAP_WIDTH (1970*SCALE_MAP)
#define MAP_HEIGHT	(205*SCALE_MAP)
#define KEYMAP_SIZE	255

#endif // !__DEFNITION_H__

