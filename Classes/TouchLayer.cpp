#include "TouchLayer.h"

void TouchLayer::onEnter()
{
	setIsKeypadEnabled(true);
	CCLayer::onEnter();

	setIsTouchEnabled(true);
}
bool TouchLayer::init(GameLayer *gameLayer)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		//是否为手柄环境
		isHand = CCDirector::sharedDirector()->isHandset();

		//保存游戏场景
		this->gameLayer = gameLayer;

		CCSize s = CCDirector::sharedDirector()->getWinSize();
		//遮挡层
		CCLayerColor* layer = CCLayerColor::layerWithColorWidthHeight(ccc4f(0, 0, 0, 200), s.width, s.height);
		addChild(layer, 1);		

		//主场景
		CCMenuItemImage *backMainItem;
		if(isHand){
			backMainItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("28_1.png"), GET_REALLY_FILE("29_1.png"),
				this, menu_selector(TouchLayer::menuBackMainCallback));
		}else {
			backMainItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("28.png"), GET_REALLY_FILE("29.png"),
				this, menu_selector(TouchLayer::menuBackMainCallback));
		}
		CC_BREAK_IF(!backMainItem);

		//重新开始
		CCMenuItemImage *goBeginItem;
		if(isHand){
			goBeginItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("17_1.png"), GET_REALLY_FILE("18_1.png"),
				this, menu_selector(TouchLayer::menuGoBeginCallback));
		}else {
			goBeginItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("17.png"), GET_REALLY_FILE("18.png"),
				this, menu_selector(TouchLayer::menuGoBeginCallback));
		}
		CC_BREAK_IF(!goBeginItem);

		//继续
		CCMenuItemImage *playItem;
		if(isHand){
			playItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("26_1.png"), GET_REALLY_FILE("27_1.png"), 
				this, menu_selector(TouchLayer::menuPlayCallback));
		}else{
			playItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("26.png"), GET_REALLY_FILE("27.png"), 
				this, menu_selector(TouchLayer::menuPlayCallback));
		}
		CC_BREAK_IF(!playItem);
		//菜单
		selectMenu = CCMenu::menuWithItems(backMainItem, goBeginItem, playItem, NULL);
		selectMenu->setPosition(ccp(s.width / 2 + 50 , s.height/2));
		CC_BREAK_IF(!selectMenu);
		selectMenu->alignItemsHorizontallyWithPadding(30);
		this->addChild(selectMenu, 1);

		bRet = true;
	} while (0);

	return bRet;
}
void TouchLayer::menuBackMainCallback(CCObject* pSender)
{
	//播放点击声音
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	CCScene *pScene = MainScene::scene();
	//切换到开始游戏场景
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void TouchLayer::menuGoBeginCallback(CCObject* pSender)
{
	//播放点击声音
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	gameLayer->gameDataInit();
	gameLayer->isExistTouchLayer = false;
	this->removeFromParentAndCleanup(true);
}

void TouchLayer::menuPlayCallback(CCObject* pSender)
{
	//播放点击声音
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	gameLayer->isExistTouchLayer = false;
	this->removeFromParentAndCleanup(true);
}

TouchLayer* TouchLayer::node(GameLayer *gameLayer)
{
	TouchLayer *pRet = new TouchLayer(); 
	if(pRet && pRet->init(gameLayer)) {
		pRet->autorelease(); 
		return pRet; 
	} else { 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

void TouchLayer::registerWithTouchDispatcher()
{
	//关键的一步，设置触摸优先级，阻止事件传递
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority -1, true);
}

bool TouchLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLog("hello ttouch");
	//触摸标记，事件分发
	_bMenuItemClicked = selectMenu->ccTouchBegan(touch, event);

	return true;
}
void TouchLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(_bMenuItemClicked){
		selectMenu->ccTouchMoved(touch, event);
	}
}
void TouchLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(_bMenuItemClicked){
		selectMenu->ccTouchEnded(touch, event);
	}
}

bool TouchLayer::keyAllClicked(int key_code, CCKeypadStatus key_status)
{

	CCLog("TouchLayer key_code:%d", key_code);
	if(key_status != KEY_PRESS){
		return true;
	}
	switch(key_code)
	{
	case 'w':
	case 'W':
	case KEY_UP:
		break;
	case 's':
	case 'S':
	case KEY_DOWN:
		break;
	case 'a':
	case 'A':
	case KEY_LEFT:
		break;
	case 'd':
	case 'D':
	case KEY_RIGHT:
		break;
	case 'i':
	case 'I':
	case KEY_A:
		menuGoBeginCallback(NULL);
		break;
	case 'k':
	case 'K':
	case KEY_B:
		break;
	case 'l':
	case 'L':
	case KEY_X:
	case KEY_BACK:
		menuPlayCallback(NULL);
		break;
	case 'j':
	case 'J':
	case KEY_Y:
		menuBackMainCallback(NULL);
		break;
	default:
		//CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n",iKeyID,iKeyState);
		break;
	}

	return true;
}
