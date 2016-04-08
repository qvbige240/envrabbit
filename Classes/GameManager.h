#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_


#include "cocos2d.h"
#include <string>

enum GAME_VERSION_LANGUAGE
{
	VERSION_CHINESE,
	VERSION_ENGLISH,
	VERSION_FRENCH,
	VERSION_GERMAN
};


#define GET_REALLY_FILE(path) (GameManager::sharedGameManager()->getReallyFilePathRes(path).c_str())
//#define GET_REALLY_FILE(path) (path)

class GameManager:public cocos2d::CCObject
{
public:
	GameManager(void);
	virtual ~GameManager(void);

	static GameManager* sharedGameManager();
	static void pureGameManager();

	GAME_VERSION_LANGUAGE getGameVersion();
	void setGameVersion(GAME_VERSION_LANGUAGE language);
	//获取不同语言资源路径
	const char* getPathDiffLanguage() const;
	//获取不同操作资源路径
	const char* getPathDiffOper() const;
	//每次场景进入的时候需要初始化手柄用的指针调用
	cocos2d::CCSprite* createArrow();
	cocos2d::CCSprite* getCurSceneArrow();
	void moveArrow(cocos2d::CCPoint pointNew);
	void clickArrow(cocos2d::CCPoint point = cocos2d::CCPointZero); //手柄点击确认按钮

	void setMusicValue(float fValue);
	float getMusicValue();

	void setEffectValue(float fValue);
	float getEffectValue();

	int getBoss1BaseScore();
	int getBoss1ShowScore();

	int getBoss2BaseScore();
	int getBoss2ShowScore();

	int getBoss3BaseScore();
	int getBoss3ShowScore();

	//用于解决引擎本身在使用plist时 设置了指定路径后 图片加载问题
	std::string getReallyFilePathRes(const char* pFileName);

	cocos2d::CCPoint pointToSystem(cocos2d::CCPoint point);
	//end------

	//插旗子操作 用于给地雷砖块点击方式区分
	void setFlagClickType(bool bFlagType);
	bool getFlagClickType();

	void removeNodeCallBack(cocos2d::CCNode* pObject);

	//标记是否中断游戏，再进入游戏后在游戏场景中弹出暂停菜单
	bool _isInterrupt;
	bool _isEnterGame;
	bool _isConfirmBackLayer;
	//BOSS出现次数 用于 随机刷新BOSS
	int m_iShowBoss1Num;
	int m_iShowBoss2Num;
	int m_iShowBoss3Num;



private:
	static GameManager* s_pGameManager;
	GAME_VERSION_LANGUAGE m_languageVersion;
	cocos2d::CCSprite* m_pArrow;

	bool m_bFlagClickType;
	std::string m_strFilePathRes;

	float m_fMusicValue;
	float m_fEffectValue;



	int m_iBoss1BaseScore;
	int m_iBoss1ShowScore;
	int m_iBoss2BaseScore;
	int m_iBoss2ShowScore;
	int m_iBoss3BaseScore;
	int m_iBoss3ShowScore;

};


#endif
