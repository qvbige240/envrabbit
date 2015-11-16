#include "LogoScene.h"
#include "SimpleAudioEngine.h"
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
		CCSprite* pSpriteLogo = CCSprite::spriteWithFile("loading/load_bg.png");
		pSpriteLogo->setPosition(ccp(size.width/2, size.height/2));
		addChild(pSpriteLogo);

		//���ض���
		CCSpriteFrame* pSpriteFrame1 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("loading/loading_1.png"),CCRectMake(0,0,39,16));
		CCSpriteFrame* pSpriteFrame2 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("loading/loading_2.png"),CCRectMake(0,0,39,16));
		CCSpriteFrame* pSpriteFrame3 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage("loading/loading_3.png"),CCRectMake(0,0,39,16));

		CCMutableArray<CCSpriteFrame*> *frames = CCMutableArray<CCSpriteFrame*>::arrayWithObjects(pSpriteFrame1,pSpriteFrame2,pSpriteFrame3,NULL);
		CCAnimation* pAnimation = CCAnimation::animationWithFrames(frames,0.2);
		CCAnimate* pAnimate = CCAnimate::actionWithAnimation(pAnimation);

		CCSprite* pLoadingAnimate = CCSprite::spriteWithFile("loading/loading_1.png");

		pLoadingAnimate->setPosition(ccp(629.5f,125.0f));

		addChild(pLoadingAnimate,1);
		pLoadingAnimate->setAnchorPoint(ccp(0.5f,0));
		pLoadingAnimate->runAction(CCRepeatForever::actionWithAction(pAnimate));

		//��������Ԥ����
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/backGroundMusic.wav");
		//���
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/click.wav");
		//�ƶ�
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/walk.wav");
		//��ʤ
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/win.wav");
		//ʧ��
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/fail.wav");

		//ÿ�����´���Ϸ��Ĭ��������
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicOff", false);

		//���ش�������
		{
			CCSpriteFrame* pSpriteFrame1 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("22.png")),CCRectMake(0,0,118,138));
			CCSpriteFrame* pSpriteFrame2 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("23.png")),CCRectMake(0,0,118,138));
			CCSpriteFrame* pSpriteFrame3 = CCSpriteFrame::frameWithTexture(CCTextureCache::sharedTextureCache()->addImage(GET_REALLY_FILE("24.png")),CCRectMake(0,0,118,138));
			CCMutableArray<CCSpriteFrame*> *frames = CCMutableArray<CCSpriteFrame*>::arrayWithObjects(pSpriteFrame1,pSpriteFrame2,pSpriteFrame3,NULL);
			CCAnimation* pAnimation = CCAnimation::animationWithFrames(frames,0.2);
			//CCAnimate* pAnimate = CCAnimate::actionWithAnimation(pAnimation);
			CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation,"haha");
		}
		//����ʧ�ܶ���
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
	CCDirector::sharedDirector()->replaceScene(pTransition);
}
