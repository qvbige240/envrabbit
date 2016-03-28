#include "GameOverLayer.h"
bool GameOverLayer::isOverLayer = false;
void GameOverLayer::onEnter()
{
	setIsKeypadEnabled(true);
	CCLayer::onEnter();

	setIsTouchEnabled(true);
}
bool GameOverLayer::init(GameLayer *gameLayer)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		isOverLayer = true;
		//是否为手柄环境
		isHand = CCDirector::sharedDirector()->isHandset();
		CCDirector::sharedDirector()->pause();
		//保存游戏场景
		this->gameLayer = gameLayer;

		CCSize s = CCDirector::sharedDirector()->getWinSize();
		//遮挡层
		CCLayerColor* layer = CCLayerColor::layerWithColorWidthHeight(ccc4f(0, 0, 0, 200), s.width, s.height);
		addChild(layer, 1);	

		CCSprite* pSprite;
		if(gameLayer->isWin){
			pSprite = CCSprite::spriteWithFile(GET_REALLY_FILE("19.png"));
			//添加分数标签	
			char info[64] = {0};
			sprintf(info, "%d", gameLayer->step);
			CCLabelBMFont *totalScore = CCLabelBMFont::labelWithString(info,  "Number.fnt");
			addChild(totalScore, 2);
			//totalScore->setAnchorPoint(ccp(0, 0));	
			ccColor3B c;
			c.r=231;
			c.g=156;
			c.b=37;
			totalScore->setColor(c);
			ccLanguageType language_id = CCApplication::getCurrentLanguage();
			switch (language_id)
			{
			case kLanguageFrench:
			case kLanguageChinese:
			    totalScore->setPosition( ccp(winSize.width/2 - 80, winSize.height/2 - 10 ));
				break;
			case kLanguageEnglish:
			case kLanguageGerman:
			case kLanguageItalian:
			case kLanguageSpanish:
			case kLanguageRussian:
			default:
			    totalScore->setPosition( ccp(winSize.width/2 + 80, winSize.height/2 - 10 ));
				break;
	}
		}else {
			pSprite = CCSprite::spriteWithFile(GET_REALLY_FILE("20.png"));
		}		
		CC_BREAK_IF(! pSprite);
		pSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
		this->addChild(pSprite, 1);

		//重新开始
		CCMenuItemImage *goBeginItem;
		if(isHand){
			goBeginItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("17_1.png"), GET_REALLY_FILE("18_1.png"),
				this, menu_selector(GameOverLayer::menuGoBeginCallback));
		}else {
			goBeginItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("17.png"), GET_REALLY_FILE("18.png"),
				this, menu_selector(GameOverLayer::menuGoBeginCallback));
		}
		CC_BREAK_IF(!goBeginItem);

		//菜单
		selectMenu = CCMenu::menuWithItems(goBeginItem, NULL);
		selectMenu->setPosition(ccp(s.width / 2 , s.height/2  - 100));
		CC_BREAK_IF(!selectMenu);
		selectMenu->alignItemsHorizontallyWithPadding(30);
		this->addChild(selectMenu, 1);

		bRet = true;
	} while (0);

	return bRet;
}

void GameOverLayer::menuGoBeginCallback(CCObject* pSender)
{
	GameManager::sharedGameManager()->_isInterrupt = false;
	CCDirector::sharedDirector()->resume();
	isOverLayer = false;
	//播放点击声音
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	gameLayer->gameDataInit();
	gameLayer->isExistGameOverLayer = false;
	this->removeFromParentAndCleanup(true);
	

}

GameOverLayer* GameOverLayer::node(GameLayer *gameLayer)
{
	GameOverLayer *pRet = new GameOverLayer(); 
	if(pRet && pRet->init(gameLayer)) {
		pRet->autorelease(); 
		return pRet; 
	} else { 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

void GameOverLayer::registerWithTouchDispatcher()
{
	//关键的一步，设置触摸优先级，阻止事件传递
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority -1, true);
}

bool GameOverLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLog("hello ttouch");
	//触摸标记，事件分发
	_bMenuItemClicked = selectMenu->ccTouchBegan(touch, event);

	return true;
}
void GameOverLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(_bMenuItemClicked){
		selectMenu->ccTouchMoved(touch, event);
	}
}
void GameOverLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(_bMenuItemClicked){
		selectMenu->ccTouchEnded(touch, event);
	}
}

bool GameOverLayer::keyAllClicked(int key_code, CCKeypadStatus key_status)
{
	CCLog("GameOverLayer key_code:%d", key_code);
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
		menuGoBeginCallback(NULL);
		break;
	case 'k':
	case 'K':
	case KEY_B:
		break;
	case 'l':
	case 'L':
	case KEY_BACK:
	case KEY_X:
		//menuPlayCallback(NULL);
		break;
	case 'j':
	case 'J':
	case KEY_Y:
		//menuBackMainCallback(NULL);
		break;
	default:
		//CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n",iKeyID,iKeyState);
		break;
	}

	return true;
}
