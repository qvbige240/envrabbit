#include "ConfirmBackLayer.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "MainScene.h"
#include "GameScene.h"
#include "config.h"
#include "Common.h"

void ConfirmBackLayer::onEnter()
{
	setIsKeypadEnabled(true);
	CCLayer::onEnter();

	setIsTouchEnabled(true);
}

void ConfirmBackLayer::onExit()
{
	CCLayer::onExit();

}

ConfirmBackLayer* ConfirmBackLayer::node(bool isGameScene)
{
	ConfirmBackLayer *pRet = new ConfirmBackLayer();
	if(pRet && pRet->init(isGameScene)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool ConfirmBackLayer::init(bool isGameScene)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		//暂停游戏 TODO
		//CCDirector::sharedDirector()->pause();

		//是否为手柄环境
		isHand = CCDirector::sharedDirector()->isHandset();

		_isFristTouch = false;
		GameManager::sharedGameManager()->_isConfirmBackLayer = true;

		_isGameScene = isGameScene;

		//遮挡层
		CCLayerColor* layer = CCLayerColor::layerWithColorWidthHeight(ccc4f(0, 0, 0, 100), winSize.width, winSize.height);
		addChild(layer, 1);
		//添加按钮
		initMenuButton();

		bRet = true;
	} while (0);

	return bRet;
}
void ConfirmBackLayer::initMenuButton()
{
	char name[100] = {0};
	char nameEx[100] = {0};

	//添加背景
	sprintf(name, "%sb_sure.png", GameManager::sharedGameManager()->getPathDiffLanguage());
	CCSprite *bgSpr = CCSprite::spriteWithFile(name);
	bgSpr->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(bgSpr, 1);

	//确认
	sprintf(name, "%s%syes.png", GameManager::sharedGameManager()->getPathDiffLanguage(), GameManager::sharedGameManager()->getPathDiffOper());
	sprintf(nameEx, "%s%syes02.png", GameManager::sharedGameManager()->getPathDiffLanguage(), GameManager::sharedGameManager()->getPathDiffOper());
	CCMenuItemImage *okItem = CCMenuItemImage::itemFromNormalImage(name, nameEx,
		this, menu_selector(ConfirmBackLayer::menuOkCallback));

	//取消
	sprintf(name, "%s%sdelete.png", GameManager::sharedGameManager()->getPathDiffLanguage(), GameManager::sharedGameManager()->getPathDiffOper());
	sprintf(nameEx, "%s%sdelete02.png", GameManager::sharedGameManager()->getPathDiffLanguage(), GameManager::sharedGameManager()->getPathDiffOper());
	CCMenuItemImage *cancelItem = CCMenuItemImage::itemFromNormalImage(name, nameEx,
		this, menu_selector(ConfirmBackLayer::menuCancelCallback));

	selectMenu = CCMenu::menuWithItems(okItem, cancelItem, NULL);
	selectMenu->alignItemsHorizontallyWithPadding(10);
	selectMenu->setPosition(ccp(winSize.width/2, winSize.height/2 - 20));

	this->addChild(selectMenu, 1);
}

void ConfirmBackLayer::menuOkCallback(CCObject* pSender)
{
	//恢复游戏
	//CCDirector::sharedDirector()->resume();
	//播放点击声音
	//GameManager::sharedGameManager()->playClickEffect();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	GameManager::sharedGameManager()->_isConfirmBackLayer = false;

	CCScene *pScene = NULL;
	if(_isGameScene){
		//回到主界面  TODO  此版本本功能只在游戏主场景添加
		//pScene = MainLayer::scene();
		//CCDirector::sharedDirector()->replaceScene(pScene);
	}else {
		//游戏结束
		CCDirector::sharedDirector()->end();
	}
}

void ConfirmBackLayer::menuCancelCallback(CCObject* pSender)
{
	//恢复游戏
	//CCDirector::sharedDirector()->resume();
	//播放点击声音
	//GameManager::sharedGameManager()->playClickEffect();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	GameManager::sharedGameManager()->_isConfirmBackLayer = false;

	this->removeFromParentAndCleanup(true);
}

void ConfirmBackLayer::registerWithTouchDispatcher()
{
	//关键的一步，设置触摸优先级，阻止事件传递
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority -1, true);
}

bool ConfirmBackLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(_isFristTouch){
		return true;
	}
	_isFristTouch = true;

	//触摸标记，事件分发
	_bMenuItemClicked = selectMenu->ccTouchBegan(touch, event);

	return true;
}
void ConfirmBackLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(_bMenuItemClicked){
		selectMenu->ccTouchMoved(touch, event);
	}
}
void ConfirmBackLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	_isFristTouch = false;
	if(_bMenuItemClicked){
		selectMenu->ccTouchEnded(touch, event);
	}
}

bool ConfirmBackLayer::keyAllClicked(int key_code, CCKeypadStatus key_status)
{
	//CCLog("ConfirmBackLayer key_code:%d", key_code);
	if(key_status != KEY_PUTUP){
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
		break;
	case 'k':
	case 'K':
	case KEY_B:
		break;
	case 'l':
	case 'L':
	case KEY_X:
	case KEY_BACK:
		menuCancelCallback(NULL);
		break;
	case 'j':
	case 'J':
	case KEY_Y:
		menuOkCallback(NULL);
		break;
	default:
		//CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n",iKeyID,iKeyState);
		break;
	}

	return true;
}
