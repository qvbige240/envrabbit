#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace std;
#include "config.h"
#include "Common.h"
#include "GameManager.h"
#include "TouchLayer.h"

class GameLayer : public CCLayer
{

public:

	virtual bool init();
	virtual void onEnter();
	static GameLayer* node();
	static cocos2d::CCScene* scene();

	//��ӱ���
	void addBackGround();
	void addMenuButton();

	//��ͼ��ʼ��
	void mapInit();

	//���������
	void randomBlocks();
	bool activateBlock(int row, int col);

	//���ݳ�ʼ��
	void gameDataInit();

	//�����ʹ����ص�����
	void menuPauseCallback(CCObject* pSender);
	void menuOkCallback(CCObject* pSender);

	//�¼��ַ�
	void registerWithTouchDispatcher();
	//�����ص�
	virtual bool ccTouchBegan(CCTouch* touche, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	//�ֱ������ص�
	virtual bool keyAllClicked(int key_code, CCKeypadStatus key_status);

	//�ƶ����
	void movePlayer();

	//�ƶ�ѡ��
	void moveSelect(int dir);
	void setSelectPosition();

	//ʧ�ܴ���
	void failAnimation();
	void failOver();

	CCSprite *player;

	//������Ŀ�
	vector<CCSprite *> active_nodes;
	bool active_blocks[ROW][COL];
	bool vert_passed[ROW][COL];
	bool hori_passed[ROW][COL];

	bool isWin;
	bool isTouch;

	int player_c; //���������
	int player_r; //���������
	int step;	  //�ƶ�����

	//�ֱ�������
	int select_c; //ѡ�����
	int select_r; //ѡ�����
	CCSprite *selectSpr; //ѡ��ͼ��

	//������ʾ��
	CCLayer *showLayer;
	bool isHand;		//�Ƿ�Ϊ�ֱ�����
	bool isExistTouchLayer; //�Ƿ���ڴ����㣬Ϊ�����ΰ�������
	bool isExistGameOverLayer; //�Ƿ������Ϸ�����㣬Ϊ�����ΰ�������
	bool isChinese;		//�Ƿ�Ϊ���Ļ���
};

#endif  // __GameLayer_H__