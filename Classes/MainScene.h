#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "GameManager.h"
#include "config.h"

using namespace std;

class MainScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	bool isHand;
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
	//手柄按键回调
	virtual bool keyAllClicked(int key_code, CCKeypadStatus key_status);
    // a selector callback
    virtual void menuStartCallback(CCObject* pSender);
	virtual void menuCloseCallback(CCObject* pSender);
	virtual void musicCallback(CCObject* sender);
	void musicSet();
	void musicSwitch();
	virtual void onEnter();
	virtual void onExit();
    // implement the "static node()" method manually
    //LAYER_NODE_FUNC(MainScene);
	static MainScene* node();
	CCMenu* musicMenu;
	CCMenuItemToggle* item1;

};

#endif  // __MainScene_SCENE_H__
