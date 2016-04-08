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
	//��ȡ��ͬ������Դ·��
	const char* getPathDiffLanguage() const;
	//��ȡ��ͬ������Դ·��
	const char* getPathDiffOper() const;
	//ÿ�γ��������ʱ����Ҫ��ʼ���ֱ��õ�ָ�����
	cocos2d::CCSprite* createArrow();
	cocos2d::CCSprite* getCurSceneArrow();
	void moveArrow(cocos2d::CCPoint pointNew);
	void clickArrow(cocos2d::CCPoint point = cocos2d::CCPointZero); //�ֱ����ȷ�ϰ�ť

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

	//���ڽ�����汾����ʹ��plistʱ ������ָ��·���� ͼƬ��������
	std::string getReallyFilePathRes(const char* pFileName);

	cocos2d::CCPoint pointToSystem(cocos2d::CCPoint point);
	//end------

	//�����Ӳ��� ���ڸ�����ש������ʽ����
	void setFlagClickType(bool bFlagType);
	bool getFlagClickType();

	void removeNodeCallBack(cocos2d::CCNode* pObject);

	//����Ƿ��ж���Ϸ���ٽ�����Ϸ������Ϸ�����е�����ͣ�˵�
	bool _isInterrupt;
	bool _isEnterGame;
	bool _isConfirmBackLayer;
	//BOSS���ִ��� ���� ���ˢ��BOSS
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
