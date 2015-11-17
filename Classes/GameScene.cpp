#include "GameScene.h"
#include "AI.h"
#include "GameOverLayer.h"
using namespace cocos2d;

enum DIR{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

int l_choices[2][3][2] = {
	{
		{0, -1},
		{1, -1},
		{-1, -1}
	},
	{
		{0, -1},
		{1, 0}, 
		{-1, 0}
	}
};

int r_choices[2][3][2] = {
	{
		{0, 1},
		{1, 0},
		{-1, 0}
	},
	{
		{0, 1},
		{1, 1},
		{-1, 1}
	}
};

int t_choices[2][2][2] = {
	{
		{1, -1},
		{1, 0}
	},
	{
		{1, 0},
		{1, 1}
	}
};

int b_choices[2][2][2] = {
	{
		{-1, -1},
		{-1, 0}
	},
	{
		{-1, 0},
		{-1, 1}
	}
};

CCScene* GameLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		GameLayer *layer = GameLayer::node();
		CC_BREAK_IF(!layer);
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

GameLayer* GameLayer::node()
{
	GameLayer *pRet = new GameLayer();
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	} else { 
		delete pRet;
		pRet = NULL;
		return NULL;
	} 
}

void GameLayer::onEnter()
{
	//开启按键模式，注意要在onEnter之前调用
	setIsKeypadEnabled(true);
	CCLayer::onEnter();

	//开启触摸使能
	setIsTouchEnabled(true);

	//得到当前系统语言,默认为英文环境
	isChinese = false;
	ccLanguageType language_id = CCApplication::getCurrentLanguage();
	switch (language_id)
	{
	case kLanguageChinese:
		isChinese = true;
		break;
	case kLanguageEnglish:
	case kLanguageGerman:
	case kLanguageFrench:
	case kLanguageItalian:
	case kLanguageSpanish:
	case kLanguageRussian:
		break;
	default:break;
	}

}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
	bool bRet = false;
	do
	{
		//父类初始化
		CC_BREAK_IF(! CCLayer::init());

		//是否为手柄环境
		isHand = CCDirector::sharedDirector()->isHandset();
		//添加背景
		addBackGround();

		//添加按钮
		addMenuButton();

		//玩家
		player = CCSprite::spriteWithFile(GET_REALLY_FILE("22.png"));
		this->addChild(player, 3);
		//CCAnimate *action = CCAnimate::initWithAnimation(animation, true);
		
		//选择标志
		CCLog("isHand:%d", isHand);
		if(isHand){
			selectSpr = CCSprite::spriteWithFile(GET_REALLY_FILE("10.png"));
			this->addChild(selectSpr, 2);
		}

		//初始化地图
		mapInit();	
		
		//初始化游戏数据
		gameDataInit();

		bRet = true;
	} while (0);

	return bRet;
}

void GameLayer::addBackGround()
{
	//背景
	CCSprite* bgSpr = CCSprite::spriteWithFile(GET_REALLY_FILE("00.png"));
	bgSpr->setPosition(ccp(winSize.width/2, winSize.height/2));
	addChild(bgSpr, 1);

	//游戏logo
	CCSprite *logoSpr = CCSprite::spriteWithFile(GET_REALLY_FILE("12.png"));
	logoSpr->setPosition( ccp(winSize.width - 170, winSize.height/2 - 20));
	addChild(logoSpr, 1);
}
void GameLayer::addMenuButton()
{
	do 
	{
		//暂停按钮
		CCMenuItemImage *pauseItem;
		if(isHand){
			pauseItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("15_1.png"), GET_REALLY_FILE("16_1.png"),
				this, menu_selector(GameLayer::menuPauseCallback));
			CC_BREAK_IF(!pauseItem);
		}else {
			pauseItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("15.png"), GET_REALLY_FILE("16.png"),
				this, menu_selector(GameLayer::menuPauseCallback));
			CC_BREAK_IF(!pauseItem);
		}
		CCMenu *pauseMenu = CCMenu::menuWithItems(pauseItem, NULL);
		pauseMenu->setPosition(ccp(winSize.width - 60, winSize.height - 60));
		CC_BREAK_IF(!pauseMenu);
		this->addChild(pauseMenu, 2);

		//确定按钮		
		if(isHand){
			CCMenuItemImage *confirmItem;
			confirmItem = CCMenuItemImage::itemFromNormalImage(GET_REALLY_FILE("21_1.png"), GET_REALLY_FILE("25_1.png"),
				this, menu_selector(GameLayer::menuOkCallback));
			CC_BREAK_IF(!confirmItem);
			CCMenu *confirmMenu = CCMenu::menuWithItems(confirmItem, NULL);
			CC_BREAK_IF(!confirmMenu);
			confirmMenu->setPosition(ccp(winSize.width - 100, 30));
			this->addChild(confirmMenu, 1);
		}

	} while (0);

}

void GameLayer::mapInit()
{
	float ox = 0,  x = 0,  y = 0;
	CCSprite *block;
	//绿色方块背景初始化
	for (int row = 0; row < ROW; row++) {
		y = BLOCK_YREGION * row + OFFSET_ORIGINY;
		ox = (row % 2 == 1) * OFFSET_ODD + OFFSET_ORIGINX;
		for (int col = 0; col < COL; col++) {
			x = ox + BLOCK_XREGION * col;
			block = CCSprite::spriteWithFile(GET_REALLY_FILE("13.png"));
			block->setAnchorPoint(ccp(0, 0));
			block->setPosition(ccp(x, y));
			this->addChild(block, 1);
		}
	}
}

void GameLayer::gameDataInit()
{
	//清楚被激活的块
	for(int i = 0; i < active_nodes.size(); i++){
		//CCLog(")
		active_nodes[i]->removeFromParentAndCleanup(true);
	}
	active_nodes.clear();

	//被激活的块
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			active_blocks[i][j] = false;
		}
	}
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			vert_passed[r][c] = false;
			hori_passed[r][c] = false;
		}
	}

	isExistTouchLayer = false;
	isExistGameOverLayer = false;
	//玩家复位
	player_c = 4;
	player_r = 4;
	//玩家嗨动画
	CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("haha");
	CCAnimate *action = CCAnimate::actionWithAnimation(animation, true);
	player->stopAllActions();
	player->runAction(CCRepeatForever::actionWithAction(action));

	//选择标志复位
	select_c = 3;
	select_r = 3;

	//生成随机块
	randomBlocks();

	//移动步数清零
	step = 0;
	//游戏结果复位
	isWin = false;
	//触摸复位
	isTouch = false;
	isOver = false;

	//初始玩家坐标
	float x = (player_r % 2 == 1) * OFFSET_ODD + OFFSET_ORIGINX + BLOCK_XREGION * player_c + OFFSET_X;
	//float y = OFFSET_Y + BLOCK_YREGION * row;
	float y = BLOCK_YREGION * player_r + OFFSET_ORIGINY + OFFSET_Y;
	player->setAnchorPoint(ccp(0.5, 0));
	player->setPosition(ccp(x, y));

	//手柄版才有选择提示
	if(isHand){
		setSelectPosition();
	}
}
void GameLayer::setSelectPosition()
{
	float x = (select_r % 2 == 1) * OFFSET_ODD + OFFSET_ORIGINX + BLOCK_XREGION * select_c + OFFSET_X +4;
	//float y = OFFSET_Y + BLOCK_YREGION * row;
	float y = BLOCK_YREGION * select_r + OFFSET_ORIGINY ;
	selectSpr->setAnchorPoint(ccp(0.5, 0));
	selectSpr->setPosition(ccp(x, y));
}

void GameLayer::randomBlocks()
{
	//获取系统时间
	struct timeval now;
	gettimeofday(&now, NULL);

	//初始化随机种子
	//timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的 
	unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);//都转化为毫秒 
	srand(rand_seed);
	//float i = CCRANDOM_0_1()*(end-start+1)+start;  //产生一个从start到end间的随机数
	int nb = (int)(CCRANDOM_0_1()*(18 - 6 + 1) + 6);
	int r, c;
	CCLog("player_r:%d, player_c:%d",player_r, player_c);
	for (int i = 0; i < nb; i++) {
		r = (int)(CCRANDOM_0_1()*((ROW - 1) - 0 + 1) + 0);
		c = (int)(CCRANDOM_0_1()*((COL - 1) - 0 + 1) + 0);
		CCLog("r:%d, c:%d", r, c);
		if(r == player_r && c == player_c) {
			CCLOG("haha is repeat");
			continue;
		}
		activateBlock(r, c);
	}
}

bool GameLayer::activateBlock(int row, int col)
{
		
	if (!active_blocks[row][col]) {
		CCSprite *block = CCSprite::spriteWithFile(GET_REALLY_FILE("14.png"));
		block->setAnchorPoint(ccp(0, 0));
		//float x = OFFSET_X + (row % 2 == 1) * OFFSET_ODD + BLOCK_XREGION * col;
		float x = (row % 2 == 1) * OFFSET_ODD + OFFSET_ORIGINX + BLOCK_XREGION * col;
		//float y = OFFSET_Y + BLOCK_YREGION * row;
		float y = BLOCK_YREGION * row + OFFSET_ORIGINY;

		block->setPosition(ccp(x, y));
		this->addChild(block, 1);
		//保存激活块
		this->active_nodes.push_back(block);		
		active_blocks[row][col] = true;
		return true;
	}
	return false;
}

void GameLayer::menuPauseCallback(CCObject* pSender)
{	
	//播放点击声音
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	CCLog("Pause");
	TouchLayer *layer	= TouchLayer::node(this);
	this->addChild(layer, 3);
	isExistTouchLayer = true;
}

void GameLayer::menuOkCallback(CCObject* pSender)
{
	//播放点击声音
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	if(isOver){
		return;
	}
	if (activateBlock(select_r, select_c)) {
		//CCLog("add is successful");
		//target.step ++;
		step++;
		movePlayer();
	}
}

void GameLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority + 1, true);
}

bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(isTouch){
		return true;
	}
	if(isOver){
		return true;
	}

	isTouch = true;

	CCPoint touchLocation = touch->locationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

	int row = (int )((touchLocation.y - OFFSET_ORIGINY) / BLOCK_YREGION);
	int col = (int )((touchLocation.x - (row % 2 == 1) * OFFSET_ODD - OFFSET_ORIGINX)/BLOCK_XREGION);

	if (col >= 0 && row >= 0 && col < COL && row < ROW) {
		//播放点击声音
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
		if (activateBlock(row, col)) {
			//CCLog("add is successful");
			step++;
			movePlayer();
		}
	}

	return true;
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	isTouch = false;
}

void GameLayer::movePlayer()
{
	int  r = player_r, c = player_c;

	int result[3] = {-1, -1, -1};
	int *resultP = NULL;
	int tempTEst[3] = {-1, -1, -1};
	int *temp = tempTEst;
	//int *result = test;
	//int *pTem = temp;

	//result = NULL;
	CCLog("&&&l_choices");
	temp = getDistance(r, c, (int *)l_choices, active_blocks, hori_passed, 0, 3);
	//
	if (resultP == NULL || (temp != NULL && temp[2] < result[2]))
	{
		//result = temp;
		resultP = temp;
		if(temp != NULL){
			result[0] = temp[0];
			result[1] = temp[1];
			result[2] = temp[2];
			CCLog("&&%d result[0]:%d, result[1]:%d, result[2]:%d", __LINE__, result[0], result[1], result[2]);
		}

	}
	CCLog("&&t_choices");
	temp = getDistance1(r, c, (int *)t_choices, active_blocks, vert_passed, 0, 2);
	//
	if (resultP == NULL || (temp != NULL && temp[2] < result[2])){
		//CCLog("temp[2]:%d", temp[2]);
		//result = temp;
		resultP = temp;
		if(temp != NULL){
			result[0] = temp[0];
			result[1] = temp[1];
			result[2] = temp[2];
			CCLog("&&%d result[0]:%d, result[1]:%d, result[2]:%d", __LINE__, result[0], result[1], result[2]);
		}
	}
	CCLog("&&b_choices");	
	temp = getDistance1(r, c, (int *)b_choices, active_blocks,vert_passed, 0, 2);
	//
	if (resultP == NULL || (temp !=NULL && temp[2] < result[2])){
		//CCLog("temp[2]:%d", temp[2]);
		//result = temp;
		resultP = temp;
		if(temp != NULL){
			result[0] = temp[0];
			result[1] = temp[1];
			result[2] = temp[2];
			CCLog("&&%d result[0]:%d, result[1]:%d, result[2]:%d", __LINE__, result[0], result[1], result[2]);
		}
	}
	CCLog("&&r_choices");
	temp = getDistance(r, c, (int *)r_choices, active_blocks, hori_passed, 0, 3);
	//
	if (resultP == NULL || (temp != NULL && temp[2] < result[2])){
		//CCLog("temp[2]:%d", temp[2]);
		//result = temp;
		resultP = temp;
		if(temp != NULL){
			result[0] = temp[0];
			result[1] = temp[1];
			result[2] = temp[2];
			CCLog("&&%d result[0]:%d, result[1]:%d, result[2]:%d", __LINE__, result[0], result[1], result[2]);
		}
	}

	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			hori_passed[r][c] && (hori_passed[r][c] = false);
		}
	}

	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			vert_passed[r][c] && (vert_passed[r][c] = false);
		}
	}	

	if (resultP == NULL) {
		/*
		if (!this.trapped) {
			this.trapped = true;
			this.player.stopAction(this.moving_action);
			this.player.runAction(this.trapped_action);
		}
		*/

		if (!active_blocks[r][c-1])
			player_c = c-1;
		else if (!active_blocks[r][c+1])
			player_c = c+1;
		else {
			int odd = (r % 2 == 1);
			int dr = r - 1, tr = r + 1, nc = c + (odd ? 0 : -1);

			if (!active_blocks[dr][nc]) {
				player_r = dr;
				player_c = nc;
				CCLog("  &&%d====player_r:%d, player_c:%d",__LINE__, player_r, player_c);
			}
			else if (!active_blocks[dr][nc+1]) {
				player_r = dr;
				player_c = nc+1;
				CCLog("  &&%d====player_r:%d, player_c:%d",__LINE__, player_r, player_c);
			}
			else if (!active_blocks[tr][nc]) {
				player_r = tr;
				player_c = nc;
				CCLog("  &&%d====player_r:%d, player_c:%d",__LINE__, player_r, player_c);
			}
			else if (!active_blocks[tr][nc+1]) {
				player_r = tr;
				player_c = nc+1;
				CCLog("  &&%d====player_r:%d, player_c:%d",__LINE__, player_r, player_c);
			}
			// WIN
			else {
				//gameScene.addChild(layers.winUI);
				//this.inited = false;
				isWin = true;
				isOver = true;
				CCLog("&&==YOU Win");

				GameOverLayer *layer = GameOverLayer::node(this);
				this->addChild(layer, 3);
				isExistGameOverLayer = true;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/win.wav");
			}
		}
	}
	// LOST
	else if (result[2] == 0) {
		//gameScene.addChild(layers.loseUI);
		//失败动画
		isOver = true;
		failAnimation();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/fail.wav");
	}
	else {
		player_r = result[0];
		player_c = result[1];
		CCLog("  &&%d====player_r:%d, player_c:%d",__LINE__, player_r, player_c);
	}	
	CCLog("  &&%d====player_r:%d, player_c:%d",__LINE__, player_r, player_c);

	float x = (player_r % 2 == 1) * OFFSET_ODD + OFFSET_ORIGINX + BLOCK_XREGION * player_c + OFFSET_X;
	//float y = OFFSET_Y + BLOCK_YREGION * row;
	float y = BLOCK_YREGION * player_r + OFFSET_ORIGINY + OFFSET_Y;

	//float x = OFFSET_X + BLOCK_XREGION * player_c ;
	//float y = OFFSET_Y + BLOCK_YREGION * player_r;
	player->setAnchorPoint(ccp(0.5, 0));
	player->setPosition(ccp(x, y));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/walk.wav");
}

void GameLayer::failAnimation()
{
	//玩家失败动画
	CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("fail");
	CCAnimate *action = CCAnimate::actionWithAnimation(animation, true);
	//player->runAction(CCRepeatForever::actionWithAction(action));

	CCFiniteTimeAction *seqence = CCSequence::actions(
		action,
		CCCallFunc::actionWithTarget(this, callfunc_selector(GameLayer::failOver)),
		NULL);
	player->stopAllActions();
	player->runAction(seqence);
	
	isWin = false;
	CCLOG("====YOU Lost");
}
void GameLayer::failOver()
{
	GameOverLayer *layer = GameOverLayer::node(this);
	this->addChild(layer, 3);
	isExistGameOverLayer = true;
}

bool GameLayer::keyAllClicked(int key_code, CCKeypadStatus key_status)
{
	CCLog("&&GameLayer key_code:%d, key_status:%d", key_code, key_status);
	if(isExistTouchLayer){ //如果触摸层存在了，则不做处理
		return true;
	}
	if(isExistGameOverLayer){ //如果gameOver层存在了，则不做处理
		return true;
	}
	if(KEY_PRESS != key_status){//按下状态
		return true;
	}
	switch(key_code)
	{
	case 'w':
	case 'W':
	case KEY_UP:
		moveSelect(UP);
		break;
	case 's':
	case 'S':
	case KEY_DOWN:
		moveSelect(DOWN);
		break;
	case 'a':
	case 'A':
	case KEY_LEFT:
		moveSelect(LEFT);
		break;
	case 'd':
	case 'D':
	case KEY_RIGHT:
		moveSelect(RIGHT);
		break;
	case 'i':
	case 'I':
	case KEY_A:
		break;
	case 'k':
	case 'K':
	case KEY_B:
		break;
	case 'l':
	case 'L':
	case KEY_X:
	case KEY_BACK:
		menuPauseCallback(NULL);
		break;
	case 'j':
	case 'J':
	case KEY_Y:
		menuOkCallback(NULL);
		break;

	default:
		//CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n",iKeyID,iKeyState);
		break;
	}

	return true;
}

void GameLayer::moveSelect(int dir)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/click.wav");
	switch(dir){
	case UP:
		if(select_r >= ROW -1){
			return;
		}
		select_r++;
		break;
	case DOWN:
		if(select_r <= 0){
			return;
		}
		select_r--;
		break;
	case LEFT:
		if(select_c <= 0){
			return;
		}
		select_c--;
		break;
	case RIGHT:
		if(select_c >= COL -1){
			return;
		}
		select_c++;
		break;
	}
	//设置选中标志位置
	setSelectPosition();
}
