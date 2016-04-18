#ifndef __TouchLayer_H__
#define __TouchLayer_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "MainScene.h"
#include "GameScene.h"
#include "config.h"

using namespace cocos2d;
using namespace std;
class GameLayer;

class TouchLayer : public CCLayer
{
public:
	virtual bool init(GameLayer *gameLayer);
	virtual void onEnter();
	virtual void onExit();
	static TouchLayer *node(GameLayer *gameLayer);

	//�����ص�
	virtual bool keyAllClicked(int key_code, CCKeypadStatus key_status);
	//�����Ӱ����ص�����
	void menuBackMainCallback(CCObject* pSender);
	void menuGoBeginCallback(CCObject* pSender);
	void menuPlayCallback(CCObject* pSender);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void registerWithTouchDispatcher();

	bool isHand;
	//�¼��ַ�
	GameLayer * gameLayer;
	CCMenu *selectMenu;
	bool _bMenuItemClicked;
	static bool _isPauseLayer;
	bool _isFristTouch;
};
#endif
