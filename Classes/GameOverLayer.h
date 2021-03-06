#ifndef __GameOverLayer_H__
#define __GameOverLayer_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "MainScene.h"
#include "GameScene.h"
#include "config.h"

using namespace cocos2d;
using namespace std;
class GameLayer;

class GameOverLayer : public CCLayer
{
public:
	virtual bool init(GameLayer *gameLayer);
	virtual void onEnter();
	virtual void onExit();
	static GameOverLayer *node(GameLayer *gameLayer);

	//按键回调
	virtual bool keyAllClicked(int key_code, CCKeypadStatus key_status);
	//触摸加按键回调处理
	void menuGoBeginCallback(CCObject* pSender);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void registerWithTouchDispatcher();

	bool isHand;
	//事件分发
	GameLayer * gameLayer;
	CCMenu *selectMenu;
	bool _bMenuItemClicked;
	static bool isOverLayer;
};
#endif
