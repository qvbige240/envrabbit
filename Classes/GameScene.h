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

	//添加背景
	void addBackGround();
	void addMenuButton();

	//地图初始化
	void mapInit();

	//生成随机块
	void randomBlocks();
	bool activateBlock(int row, int col);

	//数据初始化
	void gameDataInit();

	//按键和触摸回调函数
	void menuPauseCallback(CCObject* pSender);
	void menuOkCallback(CCObject* pSender);

	//事件分发
	void registerWithTouchDispatcher();
	//触摸回调
	virtual bool ccTouchBegan(CCTouch* touche, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	//手柄按键回调
	virtual bool keyAllClicked(int key_code, CCKeypadStatus key_status);

	//移动玩家
	void movePlayer();

	//移动选择
	void moveSelect(int dir);
	void setSelectPosition();

	//失败处理
	void failAnimation();
	void failOver();

	CCSprite *player;

	//被激活的块
	vector<CCSprite *> active_nodes;
	bool active_blocks[ROW][COL];
	bool vert_passed[ROW][COL];
	bool hori_passed[ROW][COL];

	bool isWin;
	bool isTouch;

	int player_c; //玩家所在列
	int player_r; //玩家所在行
	int step;	  //移动步数

	//手柄版特有
	int select_c; //选择的行
	int select_r; //选择的列
	CCSprite *selectSpr; //选择图标

	//数据显示层
	CCLayer *showLayer;
	bool isHand;		//是否为手柄环境
	bool isExistTouchLayer; //是否存在触摸层，为了屏蔽按键传递
	bool isExistGameOverLayer; //是否存在游戏结束层，为了屏蔽按键传递
	bool isChinese;		//是否为中文环境
};

#endif  // __GameLayer_H__