#ifndef __ConfirmBackLayer_H__
#define __ConfirmBackLayer_H__

#include "cocos2d.h"
#include "Common.h"
#include  "GameScene.h"

using namespace cocos2d;
using namespace std;

class ConfirmBackLayer : public CCLayer
{
public:

	virtual bool init(bool isGameScene = true);
	virtual void onEnter();
	virtual void onExit();
	static ConfirmBackLayer *node(bool isGameScene = true);

	//添加按钮
	void initMenuButton();
	//按键回调
	virtual bool keyAllClicked(int key_code, CCKeypadStatus key_status);
	//触摸加按键回调处理
	void menuOkCallback(CCObject* pSender);
	void menuCancelCallback(CCObject* pSender);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void registerWithTouchDispatcher();

	bool isHand;
	bool _isWin;
	bool _isGameScene;
	//事件分发

	CCMenu *selectMenu;
	bool _bMenuItemClicked;
	bool _isFristTouch;
};
#endif
