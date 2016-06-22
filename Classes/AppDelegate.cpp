#include "AppDelegate.h"
#include "LogoScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "LogoScene.h"
#include "TouchLayer.h"
#include "GameOverLayer.h"
#include "CCEGLView.h"
USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		// Initialize OpenGLView instance, that release by CCDirector when application terminate.
		// The HelloWorld is designed as HVGA.
		CCEGLView * pMainWnd = new CCEGLView();
		CC_BREAK_IF(! pMainWnd
				|| ! pMainWnd->Create(TEXT("envRabbit"), 1024, 600));

#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

        // OpenGLView initialized in testsAppDelegate.mm on ios platform, nothing need to do here.

#endif  // CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		// OpenGLView initialized in HelloWorld/android/jni/helloworld/main.cpp
		// the default setting is to create a fullscreen view
		// if you want to use auto-scale, please enable view->create(320,480) in main.cpp
		// if the resources under '/sdcard" or other writeable path, set it.
		// warning: the audio source should in assets/
		// cocos2d::CCFileUtils::setResourcePath("/sdcard");

#endif  // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)

		// Initialize OpenGLView instance, that release by CCDirector when application terminate.
		// The HelloWorld is designed as HVGA.
		CCEGLView* pMainWnd = new CCEGLView(this);
		CC_BREAK_IF(! pMainWnd || ! pMainWnd->Create(320,480, WM_WINDOW_ROTATE_MODE_CW));

#ifndef _TRANZDA_VM_
		// on wophone emulator, we copy resources files to Work7/NEWPLUS/TDA_DATA/Data/ folder instead of zip file
		cocos2d::CCFileUtils::setResource("HelloWorld.zip");
#endif

#endif  // CC_PLATFORM_WOPHONE
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
		// MaxAksenov said it's NOT a very elegant solution. I agree, haha
		CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

		// Initialize OpenGLView instance, that release by CCDirector when application terminate.
		// The HelloWorld is designed as HVGA.
		CCEGLView * pMainWnd = new CCEGLView();
		CC_BREAK_IF(! pMainWnd
				|| ! pMainWnd->Create("cocos2d: Hello World", 1024, 600, 1024, 600));

		CCFileUtils::setResourcePath("Resources/");

#endif  // CC_PLATFORM_LINUX

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)

		CCEGLView * pMainWnd = new CCEGLView();
		CC_BREAK_IF(! pMainWnd|| ! pMainWnd->Create(this, 480, 320));
		pMainWnd->setDeviceOrientation(Osp::Ui::ORIENTATION_LANDSCAPE);
		CCFileUtils::setResourcePath("/Res/");

#endif  // CC_PLATFORM_BADA

#if (CC_TARGET_PLATFORM == CC_PLATFORM_QNX)
		CCEGLView * pMainWnd = new CCEGLView();
		CC_BREAK_IF(! pMainWnd|| ! pMainWnd->Create(480, 320));
		CCFileUtils::setResourcePath("./app/native/Resource");
#endif // CC_PLATFORM_QNX
		bRet = true;
	} while (0);
	return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

	// enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayFPS(false);
	pDirector->checkHandset();

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = LogoScene::scene();
	//CCScene *pScene = MainScene::scene();
	CCScene *pScene = LogoScene::scene();

    // run
    pDirector->runWithScene(pScene);
	/* =======add PauseMenu when interrupt==Start==by Duz on 2016-03-25====*/
	GameManager::sharedGameManager()->_isEnterGame = true;
	/* =======add PauseMenu when interrupt==End====by Duz on 2016-03-25====*/
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{

	CCDirector::sharedDirector()->pause();
		
	//新需求，游戏进行中时中断发生然后再进入游戏，游戏应弹出暂停菜单。
	GameManager::sharedGameManager()->_isInterrupt = true;

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	if((!TouchLayer::_isPauseLayer)  && (!GameOverLayer::isOverLayer)){
		CCDirector::sharedDirector()->resume();
	}

	/* 修改Bug: 游戏中“HOME”键后，切换系统语言，再进入游戏却没有音乐和音效了。
	 * 不知道是cocos2dx还是andiroid底层的问题。暂时改法：预加载音效，播放背景音乐
	 * 泰雷兹有可能在游戏最初底层中断就调用applicationWillEnterForeground函数，但此时还没进入游戏直接预加载的话会挂掉，
	 * 故加一个“进入游戏”的标志判断。
	 */
	if(GameManager::sharedGameManager()->_isEnterGame){
#if (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX)
		//±³¾°ÒôÀÖÔ¤¼ÓÔØ
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/backGroundMusic.wav");
		//µã»÷
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/click.wav");
		//ÒÆ¶¯
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/walk.wav");
		//»ñÊ¤
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/win.wav");
		//Ê§°Ü
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/fail.wav");
#endif
		if(!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()){
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/backGroundMusic.wav", true);
		}
	}


    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

//hx: for gen4
void AppDelegate::applicationCloseApp()
{
	CCLog("hx: quit\n");
	CCDirector::sharedDirector()->end();
}	
void AppDelegate::applicationClearRecord()
{
	CCLog("hx: clear\n");
	
}
//end
