#include "GameManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


GameManager* GameManager::s_pGameManager = NULL;

USING_NS_CC;

GameManager::GameManager(void)
{
	m_languageVersion = VERSION_CHINESE;
	m_bFlagClickType = false;

	m_iShowBoss1Num = 1;
	m_iShowBoss2Num = 1;
	m_iShowBoss3Num = 1;

	m_iBoss1BaseScore = 500;
	m_iBoss1ShowScore = 250;
	m_iBoss3BaseScore = 1500;
	m_iBoss3ShowScore = 500;
	m_iBoss2BaseScore = 3000;
	m_iBoss2ShowScore = 1000;

	// 	m_iBoss1BaseScore = userDefault->getIntegerForKey("Boss1Base",m_iBoss1BaseScore);
	// 	userDefault->setIntegerForKey("Boss1Base",m_iBoss1BaseScore);
	// 	m_iBoss1ShowScore = userDefault->getIntegerForKey("Boss1ShowScore",m_iBoss1ShowScore);
	// 	userDefault->setIntegerForKey("Boss1ShowScore",m_iBoss1ShowScore);
	// 	m_iBoss3BaseScore = userDefault->getIntegerForKey("Boss3Base",m_iBoss3BaseScore);
	// 	userDefault->setIntegerForKey("Boss3Base",m_iBoss3BaseScore);
	// 	m_iBoss3ShowScore = userDefault->getIntegerForKey("Boss3ShowScore",m_iBoss3ShowScore);
	// 	userDefault->setIntegerForKey("Boss3ShowScore",m_iBoss3ShowScore);
	// 	m_iBoss2BaseScore = userDefault->getIntegerForKey("Boss2Base",m_iBoss2BaseScore);
	// 	userDefault->setIntegerForKey("Boss2Base",m_iBoss2BaseScore);
	// 	m_iBoss2ShowScore = userDefault->getIntegerForKey("Boss2ShowScore",m_iBoss2ShowScore);
	// 	userDefault->setIntegerForKey("Boss2ShowScore",m_iBoss2ShowScore);

	const char *language = "";
	ccLanguageType language_id = CCApplication::getCurrentLanguage();
	switch (language_id)
	{
	case kLanguageEnglish:
		language = "English";
		setGameVersion(VERSION_ENGLISH);
		m_strFilePathRes = "English/";
		break;
	case kLanguageChinese:
		language = "Chinese";
		setGameVersion(VERSION_CHINESE);
		m_strFilePathRes = "Chinese/";
		break;
	case kLanguageGerman:
		language = "German";
		setGameVersion(VERSION_GERMAN);
		m_strFilePathRes = "German/";
		break;
	case kLanguageFrench:
	case kLanguageItalian:
	case kLanguageSpanish:
	case kLanguageRussian:
		language = "English";
		setGameVersion(VERSION_ENGLISH);
		m_strFilePathRes = "English/";
		break;
	default:break;
	}

	//³õÊ¼»¯ÒôÀÖ
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(getReallyFilePathRes("sound/backgroundMusic.wav").c_str());

	//setMusicValue(0.5f);
	//setEffectValue(0.5f);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5f);


#if 0

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_strFilePathRes = "./";
	setGameVersion(VERSION_ENGLISH);
	if(getGameVersion() == VERSION_ENGLISH)
	{
		m_strFilePathRes = "./English/";
	}
#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	m_strFilePathRes = "./Chinese/";
	if(cocos2d::CCApplication::getCurrentLanguage() != kLanguageChinese)
	{
		setGameVersion(VERSION_ENGLISH);
		m_strFilePathRes = "./English/";
	}

#endif  // CC_PLATFORM_LINUX

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif // CC_PLATFORM_ANDROID

#endif
}


GameManager::~GameManager(void)
{
}

GameManager* GameManager::sharedGameManager()
{
	if(s_pGameManager == NULL)
	{
		s_pGameManager = new GameManager;
	}

	return s_pGameManager;
}

void GameManager::pureGameManager()
{
	if(s_pGameManager != NULL)
	{
		CC_SAFE_DELETE(s_pGameManager);
	}
}

GAME_VERSION_LANGUAGE GameManager::getGameVersion()
{
	return m_languageVersion;
}

void GameManager::setGameVersion( GAME_VERSION_LANGUAGE language )
{
	m_languageVersion = language;
}

cocos2d::CCSprite* GameManager::createArrow()
{
	m_pArrow = CCSprite::spriteWithFile("Arrow.png");
	m_pArrow->setAnchorPoint(ccp(0,1.0f));

	return m_pArrow;
}

cocos2d::CCSprite* GameManager::getCurSceneArrow()
{
	return m_pArrow;
}

void GameManager::moveArrow( cocos2d::CCPoint pointNew )
{
	CCSize wndSize = CCDirector::sharedDirector()->getWinSize(); 
	if(pointNew.x > 0 && pointNew.x < wndSize.width && pointNew.y > 0 && pointNew.y < wndSize.height)
	{
		m_pArrow->setPosition(pointNew);
	}


}

void GameManager::clickArrow(CCPoint point)
{
	CCPoint pointClick = point;
	if(CCPoint::CCPointEqualToPoint(point,CCPointZero))
	{
		pointClick = m_pArrow->getPosition();
	}
	else
	{
		pointClick = point;
	}
	pointClick = pointToSystem(pointClick);
	CCSet* pSet = new CCSet;
	CCTouch* pTouch = new CCTouch;
	pTouch->SetTouchInfo(pointClick.x,pointClick.y);
	pSet->addObject(pTouch);
	CCTouchDispatcher::sharedDispatcher()->touches(pSet,NULL,CCTOUCHBEGAN);
	CCTouchDispatcher::sharedDispatcher()->touches(pSet,NULL,CCTOUCHENDED);

	CC_SAFE_DELETE(pSet);
	CC_SAFE_DELETE(pTouch);
}

cocos2d::CCPoint GameManager::pointToSystem( cocos2d::CCPoint point )
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCPoint retPoint = CCPointZero;
	switch (CCDirector::sharedDirector()->getDeviceOrientation())
	{
	case CCDeviceOrientationPortrait:
		retPoint = ccp(point.x, s.height - point.y);
		break;
	case CCDeviceOrientationPortraitUpsideDown:
		retPoint = ccp(s.width - point.x, point.y);
		break;
	case CCDeviceOrientationLandscapeLeft:
		retPoint.x = point.y;
		retPoint.y = point.x;
		break;
	case CCDeviceOrientationLandscapeRight:
		retPoint.x = s.height - point.y;
		retPoint.y = s.width - point.x;
		break;
	}


	return retPoint;
}

bool GameManager::getFlagClickType()
{
	return m_bFlagClickType;
}

void GameManager::setFlagClickType( bool bFlagType )
{
	m_bFlagClickType = bFlagType;
}

void GameManager::setMusicValue( float fValue )
{
	m_fMusicValue = fValue;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(fValue);
}

float GameManager::getMusicValue()
{
	return m_fMusicValue;
}

void GameManager::setEffectValue( float fValue )
{
	m_fEffectValue = fValue;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(fValue);
}

float GameManager::getEffectValue()
{
	return m_fEffectValue;
}

int GameManager::getBoss1BaseScore()
{
	return m_iBoss1BaseScore;
}

int GameManager::getBoss1ShowScore()
{
	return m_iBoss1ShowScore;
}

int GameManager::getBoss2BaseScore()
{
	return m_iBoss2BaseScore;
}

int GameManager::getBoss2ShowScore()
{
	return m_iBoss2ShowScore;
}

int GameManager::getBoss3BaseScore()
{
	return m_iBoss3BaseScore;
}

int GameManager::getBoss3ShowScore()
{
	return m_iBoss3ShowScore;
}

void GameManager::removeNodeCallBack( CCNode* pObject )
{
	if(pObject != NULL)
	{
		pObject->removeFromParentAndCleanup(true);
	}
}

std::string GameManager::getReallyFilePathRes(const char* pFileName)
{
	std::string strFilePath = CCFileUtils::fullPathFromRelativeFile(pFileName, m_strFilePathRes.c_str());
	return strFilePath;
}


