#include "MainScene.h"
//#include "XmlParser.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

CCScene* MainScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MainScene *layer = MainScene::node();
        CC_BREAK_IF(! layer);
		
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
	
    // return the scene
    return scene;
}

MainScene* MainScene::node()
{
	MainScene *pRet = new MainScene(); 
	if (pRet && pRet->init()) { 
		pRet->autorelease(); 
		return pRet; 
	} else { 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

void MainScene::onEnter()
{
	setIsKeypadEnabled(true);
	CCLayer::onEnter();

}
// on "init" you need to initialize your instance
bool MainScene::init()
{
    bool bRet = false;
    do 
    {
		//初始化父类
        CC_BREAK_IF(! CCLayer::init());

		//是否为手柄环境
		isHand = CCDirector::sharedDirector()->isHandset();

		//取得屏幕宽度
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		//背景
		CCSprite *bg = CCSprite::spriteWithFile(GET_REALLY_FILE("00.png"));
		bg->setPosition( ccp(winSize.width/2, winSize.height/2));
		addChild(bg, 1);

		//游戏logo
		CCSprite *logoSpr = CCSprite::spriteWithFile(GET_REALLY_FILE("09.png"));
		logoSpr->setPosition( ccp(winSize.width/2, winSize.height/2 + 200));
		addChild(logoSpr, 1);

		//添加开始游戏按钮
		CCMenuItemImage *startItem;
		if(isHand){
			startItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("01_1.png"), GET_REALLY_FILE("02_1.png"),
				this, menu_selector(MainScene::menuStartCallback));
		}else {
			startItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("01.png"), GET_REALLY_FILE("02.png"),
				this, menu_selector(MainScene::menuStartCallback));
		}
		//开始菜单
		CC_BREAK_IF(!startItem);
		CCMenu *startMenu = CCMenu::menuWithItems(startItem, NULL);
		startMenu->setPosition(ccp(winSize.width/2, winSize.height/2 - 50));
		CC_BREAK_IF(!startMenu);
		this->addChild(startMenu, 1);

		//添加关闭按钮
		CCMenuItemImage *closeItem;
		if(isHand){
			closeItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("07_1.png"),GET_REALLY_FILE("08_1.png"),
				this, menu_selector(MainScene::menuCloseCallback));
		}else {
			closeItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("07.png"),GET_REALLY_FILE("08.png"),
				this, menu_selector(MainScene::menuCloseCallback));
		}
		//关闭菜单
		CC_BREAK_IF(! closeItem);		
		CCMenu* closeMenu = CCMenu::menuWithItems(closeItem, NULL);
		closeMenu->setPosition(ccp(winSize.width - 60, 60));
		CC_BREAK_IF(! closeMenu);
		this->addChild(closeMenu, 1);

		//添加音乐设置按钮		
		if(isHand){
			item1 = CCMenuItemToggle::itemWithTarget(	this, 
				menu_selector(MainScene::musicCallback),
				CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("03_1.png"), GET_REALLY_FILE("04_1.png")),
				CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("05_1.png"), GET_REALLY_FILE("06_1.png")),
				NULL );
		}else {
			item1 = CCMenuItemToggle::itemWithTarget(	this, 
				menu_selector(MainScene::musicCallback),
				CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("03.png"), GET_REALLY_FILE("04.png")),
				CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("05.png"), GET_REALLY_FILE("06.png")),
				NULL );
		}
		//音乐菜单
		musicMenu = CCMenu::menuWithItems(item1, NULL);
		musicMenu->setPosition(ccp(winSize.width - 180, 60));
		CC_BREAK_IF(! musicMenu);

		// Add the menu to MainScene layer as a child layer.
		this->addChild(musicMenu, 1);

		//播放背景音乐
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/backGroundMusic.mp3", true);
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
		if(!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()){
		    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/backGroundMusic.wav", true);
		}

		musicSwitch();

        bRet = true;
    } while (0);

    return bRet;
}
void MainScene::musicSwitch()
{
	bool isMusicOff = CCUserDefault::sharedUserDefault()->getBoolForKey("musicOff");
	if(isMusicOff == true){//关声音
		CCLog("music close");
		item1->setSelectedIndex(1);
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicOff", true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
	}else {//开声音
		CCLog("open Music");
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicOff", false);
		item1->setSelectedIndex(0);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	}
}

void MainScene::menuStartCallback(CCObject* pSender)
{
	CCLOG("Start Game");
	//播放点击声音
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	CCScene *pScene = GameLayer::scene();
	//切换到开始游戏场景
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	//播放点击声音
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	CCDirector::sharedDirector()->end();
	//cout<<"ok, start Game"<<endl;
	CCLOG("Cloose Game");

}

void MainScene::musicCallback(CCObject* sender)
{
	int index = dynamic_cast<CCMenuItemToggle*>(sender)->getSelectedIndex();
	CCLOG("index:%d", dynamic_cast<CCMenuItemToggle*>(sender)->getSelectedIndex() ); 
	CCLOG("selected item: %x ", dynamic_cast<CCMenuItemToggle*>(sender)->selectedItem() ); 
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");

	if(0 == index){ //打开声音
		CCLog("open Music");
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicOff", false);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	}else if(1 == index){ //关闭声音
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicOff", true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
		CCLog("close Music");
	}

	//CCLOG("Music Set");

}
bool MainScene::keyAllClicked(int key_code, CCKeypadStatus key_status)
{
	CCLOG("key_code:%d", key_code);
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
		break;
	case 'k':
	case 'K':
	case KEY_B:
		musicSet();
		break;
	case 'l':
	case 'L':
	case KEY_X:
	case KEY_BACK:
		menuCloseCallback(NULL);
		break;
	case 'j':
	case 'J':
	case KEY_Y:
		menuStartCallback(NULL);
		break;

	default:
		//CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n",iKeyID,iKeyState);
		break;
	}

	return true;
}

void MainScene::musicSet()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	int index = item1->getSelectedIndex();
	if(index == 0){//打开声音
		CCLog("close Music");
		item1->setSelectedIndex(1);
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicOff", true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
	}else {//关闭声音
		CCLog("open Music");
		item1->setSelectedIndex(0);
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicOff", false);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	}
}
	
