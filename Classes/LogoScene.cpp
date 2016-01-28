#include "LogoScene.h"
#include "SimpleAudioEngine.h"
#include "AirlineDefine.h"
using namespace cocos2d;

CCScene* LogoScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        LogoScene *layer = LogoScene::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{
    bool bRet = false;
    do 
    {

        CC_BREAK_IF(! CCLayer::init());

        CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite* pSpriteLogo = CCSprite::spriteWithFile("loading/loading_bg.png");
		pSpriteLogo->setPosition(ccp(size.width/2, size.height/2));
		addChild(pSpriteLogo);

		//loading动画
		//start
		//加载动画帧
		CCAnimation *animation = CCAnimation::animation();		
		char frameName[100] = {0};
		for( int i = 0;i < LOADING_IMG_CNT;i++){
			sprintf(frameName, "loading/loading_%d.png", i + 1);
			CCLog("frameName:%s", frameName);
			animation->addFrameWithFileName(frameName);
		}
		//创建动画
		CCAnimate* pAnimate = CCAnimate::actionWithDuration(0.8, animation, false);
		CCSprite* pLoadingAnimate = CCSprite::spriteWithFile("loading/loading_1.png");
		pLoadingAnimate->setPosition(ccp(LOADING_ANIM_POS_X, winSize.height - LOADING_ANIM_POS_Y - 7));

		addChild(pLoadingAnimate,1);
		pLoadingAnimate->runAction(CCRepeatForever::actionWithAction(pAnimate));
		//end

		//背景音乐预加载
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/backGroundMusic.wav");
		//点击
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/click.wav");
		//移动
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/walk.wav");
		//获胜
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/win.wav");
		//失败
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/fail.wav");

		//每次重新打开游戏，默认声音打开
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicOff", false);

		//加载待机动画
		{
			CCSpriteFrame* pSpriteFrame1 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("22.png")),CCRectMake(0,0,118,138));
			CCSpriteFrame* pSpriteFrame2 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("23.png")),CCRectMake(0,0,118,138));
			CCSpriteFrame* pSpriteFrame3 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("24.png")),CCRectMake(0,0,118,138));
			CCMutableArray<CCSpriteFrame*> *frames = CCMutableArray<CCSpriteFrame*>::arrayWithObjects(pSpriteFrame1,pSpriteFrame2,pSpriteFrame3,NULL);
			CCAnimation* pAnimation = CCAnimation::animationWithFrames(frames,0.2);
			//CCAnimate* pAnimate = CCAnimate::actionWithAnimation(pAnimation);
			CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation,"haha");
		}
		//加载失败动画
		{
			CCSpriteFrame* pSpriteFrame1 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("grasp1.png")),CCRectMake(0,0,118,138));
			CCSpriteFrame* pSpriteFrame2 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("grasp2.png")),CCRectMake(0,0,118,138));
			CCSpriteFrame* pSpriteFrame3 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("grasp3.png")),CCRectMake(0,0,118,138));
			CCSpriteFrame* pSpriteFrame4 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("grasp4.png")),CCRectMake(0,0,118,138));

			CCMutableArray<CCSpriteFrame*> *frames = CCMutableArray<CCSpriteFrame*>::arrayWithObjects(pSpriteFrame1,pSpriteFrame2,pSpriteFrame3,pSpriteFrame4, NULL);
			CCAnimation* pAnimation = CCAnimation::animationWithFrames(frames,0.2);
			//CCAnimate* pAnimate = CCAnimate::actionWithAnimation(pAnimation);
			CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation,"fail");
		}
		schedule(schedule_selector(LogoScene::GoScene),2.0f);

        bRet = true;
    } while (0);

    return bRet;
}
void LogoScene::GoScene( float fTime )
{
	unschedule(schedule_selector(LogoScene::GoScene));

	CCScene *pScene = MainScene::scene();
	CCTransitionFade* pTransition = CCTransitionFade::transitionWithDuration(1.0f, pScene, ccWHITE);
	/* CCDirector::sharedDirector()->replaceScene(pTransition); */
	CCDirector::sharedDirector()->replaceScene(pScene);
}
